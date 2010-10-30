#include "QMgFileInfo.h"

QMgFileInfo::QMgFileInfo()
{
}

QMgFileInfo::QMgFileInfo(const QFileInfo &fileInfo) :
    fi(fileInfo)
{
    fi.isDir(); // Load isDir flag for improve speed of sorting
}

QMgFileInfo::~QMgFileInfo()
{
}

QFileInfo QMgFileInfo::fileInfo() const
{
    return fi;
}

bool QMgFileInfo::isDir() const
{
    return fi.isDir();
}

QString QMgFileInfo::fileName() const
{
    return fi.fileName();
}

QString QMgFileInfo::extension() const
{
    return !fi.isDir() && fi.fileName().at(0) != '.' ? fi.suffix() : QString();
}

qint64 QMgFileInfo::size() const
{
    return fi.size();
}

QDateTime QMgFileInfo::created() const
{
    return fi.created();
}
