#ifndef QMGFILELISTLOADER_H
#define QMGFILELISTLOADER_H

#include <QtCore>

class QMgFileInfo;

class QMgFileListLoader : public QThread
{
    Q_OBJECT
private:
    bool cancelLoading;
    QString dirPath;
    QList<QMgFileInfo *> &fsObjects;

public:
    explicit QMgFileListLoader(QList<QMgFileInfo *> &fsObjects, QObject *parent = 0);

    void setDirPath(const QString &dirPath);

    void run();
    void cancel(unsigned long time = 3000);

public slots:

};

#endif // QMGFILELISTLOADER_H
