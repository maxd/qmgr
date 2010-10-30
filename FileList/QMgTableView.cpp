#include <QHeaderView>
#include "QMgTableView.h"

QMgTableView::QMgTableView(QWidget *parent) :
    QTableView(parent)
{
    initControl();
}

void QMgTableView::initControl()
{
    this->setFrameShape(QFrame::NoFrame);

    this->setSelectionMode(QAbstractItemView::ContiguousSelection);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);

    this->setShowGrid(false);
    this->setSortingEnabled(true);
    this->setWordWrap(false);
    this->setIconSize(QSize(16, 16));

    this->horizontalHeader()->setCascadingSectionResizes(true);
    this->horizontalHeader()->setHighlightSections(false);
    this->horizontalHeader()->setSortIndicatorShown(true);
    this->horizontalHeader()->setMaximumHeight(23);

    this->verticalHeader()->setVisible(false);
    this->verticalHeader()->setDefaultSectionSize(20);
    this->verticalHeader()->setHighlightSections(false);
    this->verticalHeader()->setMinimumSectionSize(20);
}

QModelIndex QMgTableView::moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{
    QModelIndex newIndex;
    newIndex = QTableView::moveCursor(cursorAction, modifiers);

    switch(cursorAction) {
        case MoveLeft:
        case MoveHome:
            newIndex = this->model()->index(0, 0);
            break;
        case MoveRight:
        case MoveEnd:
            newIndex = this->model()->index(this->model()->rowCount() - 1, 0);
            break;
        default:
            break;
    }

    return newIndex;
}
