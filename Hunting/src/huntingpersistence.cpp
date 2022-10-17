#include "huntingpersistence.h"

#include <QFile>
#include <QTextStream>

HuntingPersistence::HuntingPersistence()
{

}

void HuntingPersistence::save(QString path, HuntingSave state)
{
    QFile saveFile(path);
    if (!saveFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream writer(&saveFile);
    writer << state.boardSize << " " << state.prevRow << " " << state.prevCol << "\n";
    writer << state.numOfSteps << " " << state.phase << " " << state.turn << "\n";
    for(int i = 0; i < state.boardSize; i++) {
        for(int j = 0; j < state.boardSize; j++) {
            writer << state.board[i][j] << " ";
        }
        writer << "\n";
    }
}

HuntingSave HuntingPersistence::load(QString path)
{
    int boardSize, prevRow, prevCol, numOfSteps, phase, turn;
    QFile saveFile(path);
    saveFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream reader(&saveFile);
    reader >> boardSize >> prevRow >> prevCol >> numOfSteps >> phase >> turn;

    QVector<QVector<Player>> board;
    for(int i = 0; i<boardSize; i++) {
        QVector<Player> vec;
        for(int j=0; j<boardSize; j++) {
            int p;
            reader >> p;
            vec.push_back((Player)p);
        }
        board.push_back(vec);
    }
    return HuntingSave(boardSize, prevRow, prevCol, numOfSteps, (Phase)phase, (Turn)turn, board);
}
