#include "QMgFileList.h"
#include "ui_QMgFileList.h"

#include "QMgFileListViewInterface.h"
#include "QMgBriefFileListView.h"
#include "QMgFullFileListView.h"

QMgFileList::QMgFileList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QMgFileList),
    model(NULL),
    selectionModel(NULL),
    viewMode(BriefFileList),
    fileListView(NULL)
{
    ui->setupUi(this);

    setViewMode(viewMode);

    reloadIndicator = new QMovie(":/images/reload-white.gif", QByteArray(), this);
    ui->reloadIndicatorLabel->setMovie(reloadIndicator);
}

QMgFileList::~QMgFileList()
{
    if (fileListView != NULL)
        delete fileListView;

    delete ui;
}

void QMgFileList::setModel(QSortFilterProxyModel *model)
{
    this->model = model;

    if (fileListView != NULL)
        fileListView->setModel(model);
}

void QMgFileList::setSelectionModel(QItemSelectionModel *selectionModel)
{
    this->selectionModel = selectionModel;

    if (fileListView != NULL)
        fileListView->setSelectionModel(selectionModel);
}

void QMgFileList::setViewMode(QMgFileListViewMode viewMode)
{
    if (fileListView == NULL || this->viewMode != viewMode) {
        this->viewMode = viewMode;

        if (fileListView != NULL) {
            delete fileListView;
        }

        switch(viewMode) {
            case BriefFileList:
                fileListView = new QMgBriefFileListView;
                break;
            case FullFileList:
                fileListView = new QMgFullFileListView;
                break;
        }

        if (model != NULL) {
            fileListView->setModel(model);
        }

        if (selectionModel != NULL)
            fileListView->setSelectionModel(selectionModel);

        QWidget *widget = dynamic_cast<QWidget *>(fileListView);
        connect(widget, SIGNAL(openDirectoryRequest(const QString&)), SIGNAL(openDirectoryRequest(const QString&)));

        ui->verticalLayout->addWidget(widget);
    }
}

void QMgFileList::setTitle(const QString &dirPath)
{
    ui->titleLabel->setText(dirPath);
}

void QMgFileList::showReloadIndicator(bool show)
{
    ui->reloadIndicatorLabel->setVisible(show);
    show ? reloadIndicator->start() : reloadIndicator->stop();
}

void QMgFileList::scrollTo(const QModelIndex &index, QAbstractItemView::ScrollHint hint)
{
    fileListView->scrollTo(index, hint);
}

void QMgFileList::keyPressEvent(QKeyEvent *event)
{
    emit keyPressed(event);
    if (!event->isAccepted())
        QWidget::keyPressEvent(event);
}
