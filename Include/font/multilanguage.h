#ifndef MULTILANGUAGE_H
#define MULTILANGUAGE_H

#include "../common.h"

class CtmMultiLanguage
{
public:
    CtmMultiLanguage();

public:
    void        InitMult(QString strXmlPath);
    void        DestroyMult();
    QString     GetString(QString strKey);
    QString 	operator[] (QString strKey);

private:
    QHash<QString, QString> m_hashMap;
};

#endif // MULTILANGUAGE_H
