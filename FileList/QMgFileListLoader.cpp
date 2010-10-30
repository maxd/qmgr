#include <QDirIterator>
#include "QMgFileInfo.h"
#include "QMgFileListLoader.h"

QMgFileListLoader::QMgFileListLoader(QList<QMgFileInfo *> &fsObjects, QObject *parent) :
    QThread(parent),
    cancelLoading(false),
    fsObjects(fsObjects)
{
}

void QMgFileListLoader::setDirPath(const QString& dirPath)
{
    this->dirPath = dirPath;
}

void QMgFileListLoader::run()
{
    Q_ASSERT(dirPath != NULL);
    Q_ASSERT(fsObjects.isEmpty());

    cancelLoading = false;

    QDir dir(dirPath);
    if (!dir.isRoot())
        fsObjects.append(new QMgFileInfo(QFileInfo("..")));

    QDirIterator it(dirPath, QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
    while(it.hasNext() && !cancelLoading) {
        it.next();
        fsObjects.append(new QMgFileInfo(it.fileInfo()));
    }
}

void QMgFileListLoader::cancel(unsigned long time) {
    if (isRunning()) {
        cancelLoading = true;

        bool result;
        result = wait(time);

        if (!result) {
            terminate();
            wait();
        }
    }
}
