#include <QItemSelectionModel>
#include "QMgFileListController.h"
#include "QMgFileListModel.h"
#include "QMgFileListSortFilter.h"
#include "QMgFileList.h"
#include "QMgFileInfo.h"

QMgFileListController::QMgFileListController(QMgFileList *fileList, QObject *parent) :
    QObject(parent),
    fileList(fileList)
{
    fileListModel = new QMgFileListModel(this);

    fileListSortFilter = new QMgFileListSortFilter(this);
    fileListSortFilter->setSourceModel(fileListModel);
    fileListSortFilter->sort(0, Qt::AscendingOrder);

    selectionModel = new QItemSelectionModel(fileListSortFilter, this);

    fileList->setModel(fileListSortFilter);
    fileList->setSelectionModel(selectionModel);

    connect(fileList, SIGNAL(openDirectoryRequest(const QString&)), SLOT(open(const QString&)));
    connect(fileList, SIGNAL(keyPressed(QKeyEvent*)), SLOT(keyPressed(QKeyEvent*)));
    connect(fileListModel, SIGNAL(started()), SLOT(fileListModelStarted()));
    connect(fileListModel, SIGNAL(finished()), SLOT(fileListModelFinished()));
    connect(fileListSortFilter, SIGNAL(modelAboutToBeReset()), SLOT(fileListSortFilterBeforeReset()));
    connect(fileListSortFilter, SIGNAL(layoutChanged()), SLOT(fileListSortFilterAfterLayoutChanged()));
}

void QMgFileListController::open(const QString & dirPath)
{
    activeItem = dirPath == ".." ? fileListModel->getActiveDirectory().dirName() : "..";

    if(fileListModel->open(dirPath)) {
        selectionModel->reset();
        fileList->setTitle(fileListModel->getActiveDirectory().absolutePath());
    }
}

void QMgFileListController::fileListModelStarted()
{
    fileList->showReloadIndicator(true);
}

void QMgFileListController::fileListModelFinished()
{
    fileList->showReloadIndicator(false);
}

void QMgFileListController::fileListSortFilterBeforeReset()
{
    if (selectionModel->currentIndex().isValid()) {
        QMgFileInfo *fi = selectionModel->currentIndex().data(Qt::UserRole).value<QMgFileInfo *>();
        activeItem = fi->fileInfo().fileName();
    }
}

void QMgFileListController::fileListSortFilterAfterLayoutChanged()
{
    for(int rowIndex = 0; rowIndex < fileListSortFilter->rowCount(); ++rowIndex) {
        QModelIndex mi = fileListSortFilter->index(rowIndex, 0);
        QMgFileInfo *fi = mi.data(Qt::UserRole).value<QMgFileInfo *>();
        if (fi->fileName() == activeItem) {
            selectionModel->setCurrentIndex(mi, QItemSelectionModel::Select | QItemSelectionModel::Rows);
            fileList->scrollTo(mi);
            break;
        }
    }
}

void QMgFileListController::keyPressed(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        fileListModel->cancel();
        event->accept();
    } else if (event->key() == Qt::Key_R && event->modifiers() == Qt::ControlModifier) {
        fileListModel->reload();
        event->accept();
    }
}
