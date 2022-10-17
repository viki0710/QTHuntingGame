#include "huntingmodel2.h"
#include <QtMath>

HuntingModel2::HuntingModel2(HuntingPersistenceInterface2* persistence,QObject *parent) : QObject(parent)
{
    _persistence = persistence;
    numOfSteps = 0;
}

void HuntingModel2::startNewGame(int size)
{
    _board.clear();
    _boardSize = size;
    phase = select;
    turn = huntersTurn;
    numOfSteps = 0;

    for(int i = 0; i < _boardSize; i++) {
        QVector<Player> vec;
        for(int j = 0; j< _boardSize; j++) {
            Player p = none;
            if ((i == 0 && j == 0) ||
                (i == _boardSize-1 && j == 0) ||
                (i == 0 && j == _boardSize-1) ||
                (i == _boardSize-1 && j == _boardSize-1))
                p = hunter;
            if (i == (_boardSize-1)/2 && j == (_boardSize-1)/2)
                p = fox;
            vec.push_back(p);
        }
        _board.push_back(vec);
    }

    emit boardCreated();
    checkHuntersWin();
    checkFoxWins();
}

void HuntingModel2::fieldPressed(int row, int col)
{
    switch (phase) {
        case select: {
            if (turn == huntersTurn) {
                if (_board[row][col] == hunter) {
                    prevRow = row;
                    prevCol = col;
                    phase = move;
                }
            } else if (turn == foxTurn) {
                if (_board[row][col] == fox) {
                    prevRow = row;
                    prevCol = col;
                    phase = move;
                }
            }
            break;
        }
        case move: {
            if (_board[row][col] == none) {
                if ((row == prevRow+1 && col == prevCol) ||
                    (row == prevRow-1 && col == prevCol) ||
                    (row == prevRow && col == prevCol+1) ||
                    (row == prevRow && col == prevCol-1)) {
                    _board[row][col] = _board[prevRow][prevCol];
                    _board[prevRow][prevCol] = none;

                    if (turn == huntersTurn) turn = foxTurn;
                    else if (turn == foxTurn) turn = huntersTurn;
                    phase = select;
                    numOfSteps = numOfSteps + 1;
                }
            }
            break;
        }
        default: break;
    }

    emit boardUpdated();

    checkHuntersWin();
    checkFoxWins();
}

int HuntingModel2::getBoardSize() const
{
    return _boardSize;
}

Player HuntingModel2::getPlayer(int i, int j)
{
    return _board[i][j];
}

int HuntingModel2::getNumOfSteps()
{
    return numOfSteps;
}

bool HuntingModel2::checkFoxWins()
{
    if (numOfSteps == _boardSize*4) emit foxWins();
        return false;
}

bool HuntingModel2::checkHuntersWin()
{
    for (int i = 0; i < _board.size(); i++) {
        for (int j = 0; j < _board[i].size(); j++) {
            if(_board[i][j] == fox) {
                bool U = true, D = true, L = true, R = true;
                if (i != 0) if (_board[i-1][j] != hunter) L = false;
                if (j != 0) if (_board[i][j-1] != hunter) U = false;
                if (i != _boardSize-1) if (_board[i+1][j] != hunter) R = false;
                if (j != _boardSize-1) if (_board[i][j+1] != hunter) D = false;

                if (U && D && L && R) emit huntersWin();
                return true;
            }
        }
    }
}

void HuntingModel2::saveGame(QString path)
{
    HuntingSave2 save(_boardSize, prevRow, prevCol, numOfSteps, phase, turn, _board);
    _persistence->save(path, save);
}

bool HuntingModel2::loadGame(QString path)
{
    HuntingSave2 save = _persistence->load(path);

    _boardSize = save.boardSize;
    prevRow = save.prevRow;
    prevCol = save.prevCol;
    numOfSteps = save.numOfSteps;
    phase = save.phase;
    turn = save.turn;

    _board.clear();
    for(int i = 0; i < _boardSize; i++) {
        QVector<Player> vector;
        for(int j = 0; j < _boardSize; j++) {
            vector.append(save.board[i][j]);
        }
        _board.append(vector);
    }
    emit boardCreated();
    emit boardUpdated();
    checkHuntersWin();
    checkFoxWins();
    return true;
}

bool HuntingModel2::loadGame(HuntingSave2 save)
{
    _boardSize = save.boardSize;
    prevRow = save.prevRow;
    prevCol = save.prevCol;
    numOfSteps = save.numOfSteps;
    phase = save.phase;
    turn = save.turn;

    _board.clear();
    for(int i = 0; i < _boardSize; i++) {
        QVector<Player> vector;
        for(int j = 0; j < _boardSize; j++) {
            vector.append(save.board[i][j]);
        }
        _board.append(vector);
    }
    emit boardCreated();
    emit boardUpdated();
    checkHuntersWin();
    checkFoxWins();
    return true;
}

int HuntingModel2::getPrevCol()
{
    return prevCol;
}

int HuntingModel2::getPrevRow()
{
    return prevRow;
}

Turn HuntingModel2::getTurn()
{
    return turn;
}
