#ifndef HUNTINGMODELTEST_H
#define HUNTINGMODELTEST_H

#include <QObject>
#include <QtTest>
#include <QCoreApplication>

class HuntingModelTest : public QObject
{
    Q_OBJECT
public:
    explicit HuntingModelTest(QObject *parent = nullptr);

private slots:
    void test_startNewGame_whenGameStarted_thenGameStartedSignalSent();
    void test_fieldClicked_whenWaitingForSelect_thenFieldIsSelected();
    void test_fieldClicked_whenWaitingForMove_thenPlayerMoves();
    void test_fieldClicked_whenPlayerFinishesTurn_thenTurnChanges();
    void test_checkHuntersWin_whenFoxIsSurrounded_thenHuntersWinSignalSent();
    void test_checkFoxWins_whenOutOfSteps_thenFoxWinsSignalSent();
};

#endif // HUNTINGMODELTEST_H
