#include "QMgFileListModel.h"

#include "QMgFileInfo.h"
#include "QMgFileListLoader.h"

const QString QMgFileListModel::columnNames[COLUMN_COUNT] = {
    QString("Name"),
    QString("Ext"),
    QString("Size"),
    QString("Date")
};

QMgFileListModel::QMgFileListModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    foLoader = new QMgFileListLoader(fsObjects);

    connect(foLoader, SIGNAL(started()), SIGNAL(started()));
    connect(foLoader, SIGNAL(finished()), SLOT(loaded()));
}

QMgFileListModel::~QMgFileListModel()
{
    if (foLoader->isRunning())
        foLoader->cancel();
    delete foLoader;

    qDeleteAll(fsObjects);
}

int QMgFileListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return fsObjects.size();
}

int QMgFileListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return COLUMN_COUNT;
}

QVariant QMgFileListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section);
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            if (section >= 0 && section < COLUMN_COUNT) {
                return QVariant(columnNames[section]);
            }
        }
    }
    return QVariant();
}

QVariant QMgFileListModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid()) {
        QMgFileInfo *mgfi = fsObjects.at(index.row());

        switch(role) {
            case Qt::DisplayRole:
                switch(index.column()) {
                    case 0:
                        return mgfi->fileName();
                    case 1:
                        return mgfi->extension();
                    case 2:
                        return mgfi->isDir() ? QVariant() : mgfi->size();
                    case 3:
                        return mgfi->created();
                }
                break;
            case Qt::DecorationRole:
                if (index.column() == 0)
                    return iconProvider.icon(mgfi->fileInfo());
                break;
            case Qt::UserRole:
                return QVariant::fromValue(fsObjects.at(index.row()));
        }
    }

    return QVariant();
}

bool QMgFileListModel::open(const QString &dirPath)
{
    Q_ASSERT(dirPath != NULL);

    if (activeDirectory.cd(dirPath)) {

        foLoader->cancel();

        qDeleteAll(fsObjects);
        fsObjects.clear();

        foLoader->setDirPath(activeDirectory.absolutePath());
        foLoader->start();

        timerId = startTimer(500);

        return true;
    }
    return false;
}

bool QMgFileListModel::open(const QMgMoveTo &moveTo)
{
    switch(moveTo) {
        case ParentDir:
            return open("..");
        case RootDir:
            return open(QDir::rootPath());
        case HomeDir:
            return open(QDir::homePath());
    }
    qFatal("Unknown QMgMoveTo type");
    return false;
}

void QMgFileListModel::loaded()
{
    killTimer(timerId);
    timerEvent(NULL);
    emit finished();
}

QDir QMgFileListModel::getActiveDirectory() const
{
    return activeDirectory;
}

void QMgFileListModel::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    reset();
}

void QMgFileListModel::cancel(unsigned long time)
{
    foLoader->cancel(time);
}

void QMgFileListModel::reload()
{
    open(activeDirectory.absolutePath());
}
