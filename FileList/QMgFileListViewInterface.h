#ifndef QMGFILELISTVIEWINTERFACE_H
#define QMGFILELISTVIEWINTERFACE_H

#include <QtGui>

class QMgFileListViewInterface
{
public:
    virtual ~QMgFileListViewInterface() {}

    virtual void setModel(QSortFilterProxyModel *model) = 0;
    virtual void setSelectionModel(QItemSelectionModel *selectionModel) = 0;
    virtual void scrollTo(const QModelIndex &index, QAbstractItemView::ScrollHint hint = QAbstractItemView::EnsureVisible) = 0;

    // SIGNALS
    virtual void openDirectoryRequest(const QString &dir) = 0;
};

Q_DECLARE_INTERFACE(QMgFileListViewInterface, "QMgFileListViewInterface/1.0")

#endif // QMGFILELISTVIEWINTERFACE_H
