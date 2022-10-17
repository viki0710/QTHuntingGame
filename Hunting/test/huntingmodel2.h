#ifndef HUNTINGMODEL2_H
#define HUNTINGMODEL2_H

#include <QObject>
#include <QVector>
#include "states2.h"
#include "huntingpersistencemock.h"

class HuntingModel2 : public QObject
{
    Q_OBJECT

private:
    HuntingPersistenceInterface2* _persistence;
    int _boardSize;
    int prevRow, prevCol;
    int numOfSteps = 0;
    Phase phase;
    Turn turn;
    QVector<QVector<Player>> _board;
    bool checkFoxWins();
    bool checkHuntersWin();

public:
    explicit HuntingModel2(HuntingPersistenceInterface2* persistence, QObject *parent = nullptr);
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
    bool loadGame(HuntingSave2 save);


signals:
    void boardCreated();
    void boardUpdated();
    void huntersWin();
    void foxWins();
};

#endif // HUNTINGMODEL2_H
