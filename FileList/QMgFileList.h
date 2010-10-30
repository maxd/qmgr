#ifndef QMGFILELIST_H
#define QMGFILELIST_H

#include <QtGui>
#include "QMgFileListViewMode.h"

class QMgFileListViewInterface;

namespace Ui {
    class QMgFileList;
}

class QMgFileList : public QWidget
{
    Q_OBJECT
private:
    Ui::QMgFileList *ui;

    QSortFilterProxyModel *model;
    QItemSelectionModel *selectionModel;

    QMgFileListViewMode viewMode;
    QMgFileListViewInterface *fileListView;

    QMovie *reloadIndicator;

public:
    explicit QMgFileList(QWidget *parent = 0);
    ~QMgFileList();

    void setModel(QSortFilterProxyModel *model);
    void setSelectionModel(QItemSelectionModel *selectionModel);
    void setViewMode(QMgFileListViewMode viewMode);

    void setTitle(const QString &dirPath);
    void showReloadIndicator(bool show);

    void scrollTo(const QModelIndex &index, QAbstractItemView::ScrollHint hint = QAbstractItemView::EnsureVisible);

protected:
    virtual void keyPressEvent(QKeyEvent *event);

signals:
    void openDirectoryRequest(const QString &dir);
    void keyPressed(QKeyEvent *event);
};

#endif // QMGFILELIST_H
