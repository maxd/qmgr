#include <QDebug>
#include "QMgListView.h"

QMgListView::QMgListView(QWidget *parent) :
    QListView(parent)
{
    initControl();
}

void QMgListView::initControl()
{
    this->setFrameShape(QFrame::NoFrame);

    this->setSelectionMode(QAbstractItemView::ContiguousSelection);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);

    this->setWrapping(true);
    this->setResizeMode(QListView::Adjust);
    this->setIconSize(QSize(16, 16));
}

QModelIndex QMgListView::moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{
    QModelIndex oldIndex;
    QModelIndex newIndex;
    int pageSize;

    oldIndex = this->currentIndex();
    newIndex = QListView::moveCursor(cursorAction, modifiers);
    pageSize = qMin(model()->rowCount(), viewport()->height() / sizeHintForRow(0));

    if (oldIndex == newIndex) {
        switch(cursorAction) {
            case MoveLeft:
                newIndex = this->model()->index(0, 0);
                break;
            case MoveRight:
                newIndex = this->model()->index(this->model()->rowCount() - 1, 0);
                break;
            case MoveUp:
                newIndex = this->model()->index(qMax(0, oldIndex.row() - 1), 0);
                break;
            case MoveDown:
                newIndex = this->model()->index(qMin(this->model()->rowCount() - 1, oldIndex.row() + 1), 0);
                break;
            default:
                break;
        }
    }

    switch(cursorAction) {
        case MovePageUp:
            newIndex = this->model()->index(qMax(0, oldIndex.row() - pageSize), 0);
            break;
        case MovePageDown:
            newIndex = this->model()->index(qMin(this->model()->rowCount() - 1, oldIndex.row() + pageSize), 0);
            break;
        default:
            break;
    }

    return newIndex;
}
