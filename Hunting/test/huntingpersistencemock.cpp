#include "huntingpersistencemock.h"

HuntingPersistenceMock::HuntingPersistenceMock(HuntingSave2 save): _save(save)
{
}

void HuntingPersistenceMock::save(QString path, HuntingSave2 state)
{

}

HuntingSave2 HuntingPersistenceMock::load(QString path)
{
    return _save;
}
