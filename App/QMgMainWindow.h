#ifndef QMGMAINWINDOW_H
#define QMGMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class QMgMainWindow;
}

class QMgMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QMgMainWindow(QWidget *parent = 0);
    ~QMgMainWindow();

private:
    Ui::QMgMainWindow *ui;
    void setupFilesPanels();
};

#endif // QMGMAINWINDOW_H
