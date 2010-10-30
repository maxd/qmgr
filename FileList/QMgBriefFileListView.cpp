#include "ui_QMgBriefFileListView.h"
#include "QMgBriefFileListView.h"
#include "QMgFileInfo.h"
#include "QMgListView.h"

QMgBriefFileListView::QMgBriefFileListView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QMgBriefFileListView)
{
    ui->setupUi(this);

    initControl();
}

QMgBriefFileListView::~QMgBriefFileListView()
{
    delete ui;
}

void QMgBriefFileListView::initControl()
{
    // QHeaderView
    headerView = new QHeaderView(Qt::Horizontal, this);
    headerView->setObjectName("header");
    headerView->setSortIndicatorShown(true);
    headerView->setClickable(true);
    headerView->setResizeMode(QHeaderView::Stretch);
    headerView->setMaximumHeight(23);
    connect(headerView, SIGNAL(sortIndicatorChanged(int, Qt::SortOrder)), SLOT(headerViewSortIndicatorChangedHandler(int, Qt::SortOrder)));

    ui->verticalLayout->addWidget(headerView);

    // QMgListView
    fileList = new QMgListView(this);
    fileList->setObjectName("fileList");
    connect(fileList, SIGNAL(activated(QModelIndex)), SLOT(fileListActivatedHandler(QModelIndex)));

    ui->verticalLayout->addWidget(fileList);
}

void QMgBriefFileListView::setModel(QSortFilterProxyModel *model)
{
    this->model = model;

    headerView->setModel(model);
    headerView->setSortIndicator(model->sortColumn(), model->sortOrder());

    fileList->setModel(model);
}

void QMgBriefFileListView::setSelectionModel(QItemSelectionModel *selectionModel)
{
    fileList->setSelectionModel(selectionModel);
}

void QMgBriefFileListView::headerViewSortIndicatorChangedHandler(int columnIndex, Qt::SortOrder order)
{
    model->sort(columnIndex, order);
}

void QMgBriefFileListView::fileListActivatedHandler(QModelIndex index)
{
    QMgFileInfo *fi = index.data(Qt::UserRole).value<QMgFileInfo *>();
    if (fi->isDir()) {
        emit openDirectoryRequest(fi->fileName());
    }
}

void QMgBriefFileListView::scrollTo(const QModelIndex &index, QAbstractItemView::ScrollHint hint)
{
    fileList->scrollTo(index, hint);
}
