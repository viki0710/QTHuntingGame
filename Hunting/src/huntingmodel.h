#ifndef HUNTINGMODEL_H
#define HUNTINGMODEL_H

#include <QObject>
#include <QVector>
#include "states.h"
#include "huntingpersistence.h"

class HuntingModel : public QObject
{
    Q_OBJECT

private:
    HuntingPersistenceInterface* _persistence;
    int _boardSize;
    int prevRow, prevCol;
    int numOfSteps = 0;
    Phase phase;
    Turn turn;
    QVector<QVector<Player>> _board;
    bool checkFoxWins();
    bool checkHuntersWin();

public:
    explicit HuntingModel(HuntingPersistenceInterface* persistence, QObject *parent = nullptr);
    void startNewGame(int size);
    void fieldPressed(int i, int j);
    int getBoardSize() const;
    Player getPlayer(int i, int j);
    int getPrevCol();
    int getPrevRow();
    Turn getTurn();
    int getNumOfSteps();
    void saveGame(QString path);
    bool loadGame(QString path);

signals:
    void boardCreated();
    void boardUpdated();
    void huntersWin();
    void foxWins();
};

#endif // HUNTINGMODEL_H
