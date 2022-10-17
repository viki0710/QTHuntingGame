#ifndef HUNTINGPERSISTENCE2_H
#define HUNTINGPERSISTENCE2_H

#include "huntingsave2.h"
#include <QString>

class HuntingPersistenceInterface2
{
public:
    virtual void save (QString path, HuntingSave2 state) = 0;
    virtual HuntingSave2 load (QString path) = 0;
};

class HuntingPersistence2 : public HuntingPersistenceInterface2
{
public:
    HuntingPersistence2();
    void save(QString path, HuntingSave2 state);
    HuntingSave2 load(QString path);
};

#endif // HUNTINGPERSISTENCE2_H
