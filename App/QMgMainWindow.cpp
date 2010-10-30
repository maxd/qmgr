#include <QtGui>
#include "QMgMainWindow.h"
#include "ui_QMgMainWindow.h"
#include "FileList/QMgFileList.h"
#include "FileList/QMgFileListController.h"

QMgMainWindow::QMgMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QMgMainWindow)
{
    ui->setupUi(this);

    setupFilesPanels();
}

QMgMainWindow::~QMgMainWindow()
{
    delete ui;
}

void QMgMainWindow::setupFilesPanels()
{
    QMgFileList *fileListL = new QMgFileList(this);
    QMgFileListController *controllerL = new QMgFileListController(fileListL, this);

    //controllerL->open("/home/closer/Temp/000");
    //controllerL->open("/home/closer/Torrent");
    //controllerL->open("/home/closer");
    controllerL->open("/");

    ui->leftFilesPanelPlaceholder->addWidget(fileListL);



    QMgFileList *fileListR = new QMgFileList(this);
    fileListR->setViewMode(FullFileList);
    QMgFileListController *controllerR = new QMgFileListController(fileListR, this);

    //controllerR->open("/home/closer/Temp/000");
    //controllerR->open("/home/closer/Torrent");
    //controllerR->open("/home/closer");
    controllerR->open("/");

    ui->rightFilesPanelPlaceholder->addWidget(fileListR);
}
