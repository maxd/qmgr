#include "QMgFileListSortFilter.h"
#include "QMgFileInfo.h"

const QString     QMgFileListSortFilter::PARENT_DIR             = "..";

QMgFileListSortFilter::QMgFileListSortFilter(QObject *parent) :
        QSortFilterProxyModel(parent)
{
    setDynamicSortFilter(true);
}

bool QMgFileListSortFilter::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QMgFileInfo *leftFileInfo = sourceModel()->data(left, Qt::UserRole).value<QMgFileInfo *>();
    QMgFileInfo *rightFileInfo = sourceModel()->data(right, Qt::UserRole).value<QMgFileInfo *>();

    // The ".." directory should be always on the top
    if (leftFileInfo->fileName() == PARENT_DIR) {
        return sortOrder() == Qt::AscendingOrder;
    } else if (rightFileInfo->fileName() == PARENT_DIR) {
        return sortOrder() != Qt::AscendingOrder;
    }

    // The following two conditions group folders and files in separate groups (i.e. dirs above files)
    if (leftFileInfo->isDir() && !rightFileInfo->isDir()) {
        return sortOrder() == Qt::AscendingOrder;
    } else if (!leftFileInfo->isDir() && rightFileInfo->isDir()) {
        return sortOrder() != Qt::AscendingOrder;
    } else {
        QVariant leftData = sourceModel()->data(left);
        QVariant rightData = sourceModel()->data(right);

        return compare(leftData, rightData);
    }

    qFatal("Unhandled situation in lessThan");
    return false;
}

bool QMgFileListSortFilter::compare(const QVariant &left, const QVariant &right) const
{
    switch(left.type()) {
        case QVariant::DateTime: // For compare file creation/modification time
            return left.toDateTime() < right.toDateTime();
        case QVariant::LongLong: // For compare file size
            return left.toLongLong() < right.toLongLong();
        case QVariant::String:
            return QString::localeAwareCompare(left.toString(), right.toString()) < 0;
        case QVariant::Invalid:
            return true;
        default:
            /* do nothing */
            break;
    }

    qFatal("Unknown type for compare");
    return false;
}
