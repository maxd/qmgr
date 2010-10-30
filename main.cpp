#include <QtGui>
#include "App/QMgMainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMgMainWindow w;
    w.show();

    return a.exec();
}
