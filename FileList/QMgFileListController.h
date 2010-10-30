#ifndef QMGFILELISTCONTROLLER_H
#define QMGFILELISTCONTROLLER_H

#include <QObject>

class QMgFileListModel;
class QMgFileListSortFilter;
class QItemSelectionModel;
class QMgFileList;
class QKeyEvent;

class QMgFileListController : public QObject
{
    Q_OBJECT

private:
    QMgFileListModel *fileListModel;
    QMgFileListSortFilter *fileListSortFilter;

    QItemSelectionModel *selectionModel;

    QMgFileList *fileList;

    QString activeItem;

public:
    explicit QMgFileListController(QMgFileList *fileList, QObject *parent = 0);

signals:

public slots:
    void open(const QString & dirPath);
    void keyPressed(QKeyEvent *event);

    void fileListModelStarted();
    void fileListModelFinished();
    void fileListSortFilterBeforeReset();
    void fileListSortFilterAfterLayoutChanged();

};

#endif // QMGFILELISTCONTROLLER_H
