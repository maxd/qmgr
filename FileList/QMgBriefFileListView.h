#ifndef QMGBRIEFFILELISTVIEW_H
#define QMGBRIEFFILELISTVIEW_H

#include <QtGui>
#include "QMgFileListViewInterface.h"

namespace Ui {
    class QMgBriefFileListView;
}

class QMgListView;

class QMgBriefFileListView : public QWidget, public QMgFileListViewInterface
{
    Q_OBJECT
    Q_INTERFACES(QMgFileListViewInterface)

private:
    Ui::QMgBriefFileListView *ui;

    QHeaderView *headerView;
    QMgListView *fileList;

    QSortFilterProxyModel *model;

public:
    explicit QMgBriefFileListView(QWidget *parent = 0);
    virtual ~QMgBriefFileListView();

    virtual void setModel(QSortFilterProxyModel *model);
    virtual void setSelectionModel(QItemSelectionModel *selectionModel);
    virtual void scrollTo(const QModelIndex &index, QAbstractItemView::ScrollHint hint = QAbstractItemView::EnsureVisible);

private:
    void initControl();

signals:
    void openDirectoryRequest(const QString &dir);

private slots:
    void fileListActivatedHandler(QModelIndex index);
    void headerViewSortIndicatorChangedHandler(int columnIndex, Qt::SortOrder order);

};

#endif // QMGBRIEFFILELISTVIEW_H
