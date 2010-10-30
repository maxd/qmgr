#ifndef QMGFILELISTMODEL_H
#define QMGFILELISTMODEL_H

#include <QtCore>
#include <QFileIconProvider>

#include "QMgFileListViewMode.h"

class QMgFileInfo;
class QMgFileListLoader;

class QMgFileListModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    static const int COLUMN_COUNT = 4;

    static const QString columnNames[COLUMN_COUNT];

    QDir activeDirectory;
    QList<QMgFileInfo *> fsObjects;
    QMgFileListLoader *foLoader;

    QFileIconProvider iconProvider;

    int timerId;

public:
    explicit QMgFileListModel(QObject *parent = 0);
    ~QMgFileListModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    enum QMgMoveTo { ParentDir, RootDir, HomeDir };

    bool open(const QString &dirPath);
    bool open(const QMgMoveTo &moveTo);

    QDir getActiveDirectory() const;

    void cancel(unsigned long time = 3000);
    void reload();

protected:
    void timerEvent(QTimerEvent *event);

signals:
    void started();
    void finished();

public slots:
    void loaded();

};

#endif // QMGFILELISTMODEL_H
