#ifndef HUNTINGPERSISTENCEMOCK_H
#define HUNTINGPERSISTENCEMOCK_H

#include "huntingpersistence2.h"

class HuntingPersistenceMock: public HuntingPersistenceInterface2
{
public:
    HuntingPersistenceMock(HuntingSave2 save);
    void save(QString path, HuntingSave2 state);
    HuntingSave2 load(QString path);
private:
    HuntingSave2 _save;
};

#endif // HUNTINGPERSISTENCEMOCK_H
