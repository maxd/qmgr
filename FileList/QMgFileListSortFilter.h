#ifndef QMGFILELISTSORTFILTER_H
#define QMGFILELISTSORTFILTER_H

#include <QtCore>
#include <QSortFilterProxyModel>

class QMgFileListSortFilter : public QSortFilterProxyModel
{
    Q_OBJECT

    static const QString     PARENT_DIR;

public:
    explicit QMgFileListSortFilter(QObject *parent = 0);

    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;

private:
    bool compare(const QVariant &left, const QVariant &right) const;
};

#endif // QMGFILELISTSORTFILTER_H
