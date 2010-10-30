#ifndef QMGFULLFILELISTVIEW_H
#define QMGFULLFILELISTVIEW_H

#include <QWidget>
#include "QMgFileListViewInterface.h"

namespace Ui {
    class QMgFullFileListView;
}

class QMgTableView;

class QMgFullFileListView : public QWidget, public QMgFileListViewInterface
{
    Q_OBJECT
    Q_INTERFACES(QMgFileListViewInterface)

private:
    Ui::QMgFullFileListView *ui;

    QMgTableView *fileList;

public:
    explicit QMgFullFileListView(QWidget *parent = 0);
    virtual ~QMgFullFileListView();

    virtual void setModel(QSortFilterProxyModel *model);
    virtual void setSelectionModel(QItemSelectionModel *selectionModel);
    virtual void scrollTo(const QModelIndex &index, QAbstractItemView::ScrollHint hint = QAbstractItemView::EnsureVisible);

private:
    void initControl();

signals:
    void openDirectoryRequest(const QString &dir);

private slots:
    void fileListActivatedHandler(QModelIndex index);
};

#endif // QMGFULLFILELISVIEWT_H
