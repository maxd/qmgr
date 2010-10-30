#ifndef QMGTABLEVIEW_H
#define QMGTABLEVIEW_H

#include <QTableView>

class QMgTableView : public QTableView
{
    Q_OBJECT
public:
    explicit QMgTableView(QWidget *parent = 0);

private:
    void initControl();

protected:
    virtual QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers);

signals:

public slots:

};

#endif // QMGTABLEVIEW_H
