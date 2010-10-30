#ifndef QMGLISTVIEW_H
#define QMGLISTVIEW_H

#include <QListView>

class QMgListView : public QListView
{
    Q_OBJECT
public:
    explicit QMgListView(QWidget *parent = 0);

private:
    void initControl();

protected:
    virtual QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers);

signals:

public slots:

};

#endif // QMGLISTVIEW_H
