#include "ui_QMgFullFileListView.h"
#include "QMgFullFileListView.h"
#include "QMgFileInfo.h"
#include "QMgTableView.h"

QMgFullFileListView::QMgFullFileListView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QMgFullFileListView)
{
    ui->setupUi(this);

    initControl();
}

QMgFullFileListView::~QMgFullFileListView()
{
    delete ui;
}

void QMgFullFileListView::initControl()
{
    // QMgListView
    fileList = new QMgTableView(this);
    fileList->setObjectName("fileList");
    connect(fileList, SIGNAL(activated(QModelIndex)), SLOT(fileListActivatedHandler(QModelIndex)));

    ui->verticalLayout->addWidget(fileList);
}

void QMgFullFileListView::setModel(QSortFilterProxyModel *model)
{
    fileList->setModel(model);
    fileList->horizontalHeader()->setSortIndicator(model->sortColumn(), model->sortOrder());
    fileList->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
}

void QMgFullFileListView::setSelectionModel(QItemSelectionModel *selectionModel)
{
    fileList->setSelectionModel(selectionModel);
}

void QMgFullFileListView::fileListActivatedHandler(QModelIndex index)
{
    QMgFileInfo *fi = index.data(Qt::UserRole).value<QMgFileInfo *>();
    if (fi->isDir()) {
        emit openDirectoryRequest(fi->fileName());
    }
}

void QMgFullFileListView::scrollTo(const QModelIndex &index, QAbstractItemView::ScrollHint hint)
{
    fileList->scrollTo(index, hint);
}
