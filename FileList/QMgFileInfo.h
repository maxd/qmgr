#ifndef QMGFILEINFO_H
#define QMGFILEINFO_H

#include <QtCore>

class QMgFileInfo
{
private:
    QFileInfo fi;

public:
    QMgFileInfo();
    QMgFileInfo(const QFileInfo &fileInfo);
    ~QMgFileInfo();

    QFileInfo fileInfo() const;

    bool isDir() const;

    QString fileName() const;
    QString extension() const;

    qint64 size() const;

    QDateTime created() const;
};

Q_DECLARE_METATYPE(QMgFileInfo *);

#endif // QMGFILEINFO_H
