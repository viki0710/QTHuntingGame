#ifndef HUNTINGPERSISTENCE_H
#define HUNTINGPERSISTENCE_H

#include "huntingsave.h"
#include <QString>

class HuntingPersistenceInterface
{
public:
    virtual void save (QString path, HuntingSave state) = 0;
    virtual HuntingSave load (QString path) = 0;
};

class HuntingPersistence : public HuntingPersistenceInterface
{
public:
    HuntingPersistence();
    void save(QString path, HuntingSave state);
    HuntingSave load(QString path);
};

#endif // HUNTINGPERSISTENCE_H
