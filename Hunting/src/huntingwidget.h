#ifndef HUNTINGWIDGET_H
#define HUNTINGWIDGET_H

#include "huntingmodel.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class HuntingWidget : public QWidget
{
    Q_OBJECT

public:
    HuntingWidget(QWidget *parent = nullptr);
    ~HuntingWidget();

private:
    HuntingModel* _model;
    QVBoxLayout* _mainLayout;
    QGridLayout* _buttonGridLayout;
    QHBoxLayout* _newGameRow;
    QVector<QVector<QPushButton*>> _buttonVector;
    QPushButton* _smallBoardButton;
    QPushButton* _mediumBoardButton;
    QPushButton* _bigBoardButton;
    QHBoxLayout* _stepsRow;
    QLabel* _stepsLabel;
    QHBoxLayout* _saveRow;
    QPushButton* _saveButton;
    QPushButton* _loadButton;
    void setButtonStyle(QPushButton* button, Player state);

private slots:
    void onBoardCreated();
    void onBoardUpdated();
    void onHuntersWin();
    void onFoxWins();
    void onSaveButtonClicked();
    void onLoadButtonClicked();
};

#endif // HUNTINGWIDGET_H
