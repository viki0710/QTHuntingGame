#include "huntingmodeltest.h"
#include "huntingpersistencemock.h"
#include "huntingmodel2.h"

HuntingModelTest::HuntingModelTest(QObject *parent) : QObject(parent)
{

}

void HuntingModelTest::test_startNewGame_whenGameStarted_thenGameStartedSignalSent()
{
    HuntingSave2 emptySave;
    HuntingPersistenceMock mock (emptySave);
    HuntingModel2 model (&mock);
    QSignalSpy signalSpy (&model, SIGNAL(boardCreated()));
    model.startNewGame(3);
    QVERIFY(signalSpy.length() == 1);
}


void HuntingModelTest::test_fieldClicked_whenWaitingForSelect_thenFieldIsSelected()
{
    HuntingSave2 emptySave;
    HuntingPersistenceMock mock (emptySave);
    HuntingModel2 model (&mock);
    model.startNewGame(3);
    model.fieldPressed(0,0);
    QVERIFY(model.getPrevCol() == 0);
    QVERIFY(model.getPrevRow() == 0);
}

void HuntingModelTest::test_fieldClicked_whenWaitingForMove_thenPlayerMoves()
{
    HuntingSave2 emptySave;
    HuntingPersistenceMock mock (emptySave);
    HuntingModel2 model (&mock);
    model.startNewGame(3);
    model.fieldPressed(0,0);
    model.fieldPressed(1,0);
    QVERIFY(model.getPrevCol() == 0);
    QVERIFY(model.getPrevRow() == 0);
    QVERIFY(model.getPlayer(0,0) == none);
    QVERIFY(model.getPlayer(1,0) == hunter);
}
void HuntingModelTest::test_fieldClicked_whenPlayerFinishesTurn_thenTurnChanges()
{
    HuntingSave2 emptySave;
    HuntingPersistenceMock mock (emptySave);
    HuntingModel2 model (&mock);
    model.startNewGame(3);
    QVERIFY(model.getTurn() == huntersTurn);
    model.fieldPressed(0,0);
    model.fieldPressed(1,0);
    QVERIFY(model.getTurn() == foxTurn);
}

void HuntingModelTest::test_checkHuntersWin_whenFoxIsSurrounded_thenHuntersWinSignalSent()
{
    QVector<QVector<Player>> board {
        QVector<Player> {Player::fox, Player::hunter, Player::none},
        QVector<Player> {Player::hunter, Player::none, Player::hunter},
        QVector<Player> {Player::none, Player::hunter, Player::none}
    };
    HuntingSave2 save(3, 2, 2, 7, select, huntersTurn, board);
    HuntingPersistenceMock mock (save);
    HuntingModel2 model (&mock);
    QSignalSpy signalSpy (&model, SIGNAL(huntersWin()));
    model.loadGame(save);
    QVERIFY(signalSpy.length() == 1);
}
void HuntingModelTest::test_checkFoxWins_whenOutOfSteps_thenFoxWinsSignalSent()
{
    QVector<QVector<Player>> board {
        QVector<Player> {Player::fox, Player::none, Player::hunter},
        QVector<Player> {Player::none, Player::none, Player::hunter},
        QVector<Player> {Player::none, Player::hunter, Player::hunter}
    };
    HuntingSave2 save(3, 2, 2, 12, select, huntersTurn, board);
    HuntingPersistenceMock mock (save);
    HuntingModel2 model (&mock);
    QSignalSpy signalSpy (&model, SIGNAL(foxWins()));
    model.loadGame(save);
    QVERIFY(signalSpy.length() == 1);
}

QTEST_MAIN(HuntingModelTest)
