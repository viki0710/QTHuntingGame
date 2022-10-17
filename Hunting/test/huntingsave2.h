#ifndef HUNTINGSAVE2_H
#define HUNTINGSAVE2_H

#include <QVector>
#include "states2.h"

struct HuntingSave2
{
    int boardSize;
    int prevRow, prevCol;
    int numOfSteps;
    Phase phase;
    Turn turn;
    QVector<QVector<Player>> board;
    HuntingSave2() {}
    HuntingSave2(int boardSize, int prevRow, int prevCol, int numOfSteps, Phase phase, Turn turn, QVector<QVector<Player>> board)
    {
        this->boardSize = boardSize;
        this->prevRow = prevRow;
        this->prevCol = prevCol;
        this->numOfSteps = numOfSteps;
        this->phase = phase;
        this->turn = turn;
        this->board = board;
    }
};

#endif // HUNTINGSAVE2_H
