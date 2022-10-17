#include "huntingwidget.h"

#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>

HuntingWidget::HuntingWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Hunting");
    setFixedSize(500, 560);

    _mainLayout = new QVBoxLayout();
    setLayout(_mainLayout);

    _newGameRow = new QHBoxLayout();
    _stepsRow = new QHBoxLayout();
    _smallBoardButton = new QPushButton("3x3");
    _smallBoardButton->setFixedHeight(60);
    _mediumBoardButton = new QPushButton("5x5");
    _mediumBoardButton->setFixedHeight(60);
    _bigBoardButton = new QPushButton("7x7");
    _bigBoardButton->setFixedHeight(60);
    _stepsLabel = new QLabel();
    _newGameRow->addWidget(_smallBoardButton);
    _newGameRow->addWidget(_mediumBoardButton);
    _newGameRow->addWidget(_bigBoardButton);
    _stepsLabel->setText("Steps: 0");
    _stepsRow->addWidget(_stepsLabel);
    _saveRow = new QHBoxLayout();
    _saveButton = new QPushButton("Save");
    _loadButton = new QPushButton("Load");
    _saveRow->addWidget(_saveButton);
    _saveRow->addWidget(_loadButton);

    _mainLayout->addLayout(_newGameRow);

    _buttonGridLayout = new QGridLayout();
    _mainLayout->addLayout(_buttonGridLayout);
    _mainLayout->addLayout(_stepsRow);
    _mainLayout->addLayout(_saveRow);
    _model = new HuntingModel(new HuntingPersistence(), this);

    connect(_model, &HuntingModel::boardCreated, this, &HuntingWidget::onBoardCreated);
    connect(_model, &HuntingModel::boardUpdated, this, &HuntingWidget::onBoardUpdated);
    connect(_model, &HuntingModel::huntersWin, this, &HuntingWidget::onHuntersWin);
    connect(_model, &HuntingModel::foxWins, this, &HuntingWidget::onFoxWins);
    connect(_smallBoardButton, &QPushButton::clicked, this, [this](){ _model->startNewGame(3); });
    connect(_mediumBoardButton, &QPushButton::clicked, this, [this](){ _model->startNewGame(5); });
    connect(_bigBoardButton, &QPushButton::clicked, this, [this](){ _model->startNewGame(7); });
    connect(_saveButton, &QPushButton::clicked, this, &HuntingWidget::onSaveButtonClicked);
    connect(_loadButton, &QPushButton::clicked, this, &HuntingWidget::onLoadButtonClicked);

    _model->startNewGame(3);

}

HuntingWidget::~HuntingWidget()
{
}

void HuntingWidget::setButtonStyle(QPushButton *button, Player p)
{
    switch(p) {
        case Player::none:
            button->setStyleSheet("background-color: white");
            break;
        case Player::hunter:
            button->setStyleSheet("background-color: green");
            break;
        case Player::fox:
            button->setStyleSheet("background-color: orange");
            break;
    }
}

void HuntingWidget::onBoardCreated()
{
    _stepsLabel->setText("Steps: 0");
    while(QLayoutItem* item = _buttonGridLayout->takeAt(0)) {
        delete item->widget();
        delete item;
    }
    _buttonVector.clear();

    int size = _model->getBoardSize();

    for(int i = 0; i < size; i++) {
        QVector<QPushButton*> vec;
        for (int j = 0; j < size; j++) {
            QPushButton* button = new QPushButton();
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            Player p = _model->getPlayer(i, j);
            setButtonStyle(button, p);

            connect(button, &QPushButton::clicked, this, [i, j, this](){ _model->fieldPressed(i,j); });

            _buttonGridLayout->addWidget(button, i, j);
            vec.append(button);
        }
        _buttonVector.append(vec);
    }
}

void HuntingWidget::onBoardUpdated()
{
    int size = _model->getBoardSize();

    for(int i = 0; i< size; i++) {
        for(int j = 0; j< size; j++) {
            Player p = _model->getPlayer(i, j);
            setButtonStyle(_buttonVector[i][j], p);
        }
    }

    _stepsLabel->setText("Steps: " + QString::number(_model->getNumOfSteps()));
}

void HuntingWidget::onHuntersWin()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Game over!");
    msgBox.setText("Congratulations! You won the game!\nWinner: Hunters");
    msgBox.exec();
    _model->startNewGame(_model->getBoardSize());
}

void HuntingWidget::onFoxWins()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Game over!");
    msgBox.setText("Congratulations! You won the game!\nWinner: Fox");
    msgBox.exec();
    _model->startNewGame(_model->getBoardSize());
}

void HuntingWidget::onSaveButtonClicked()
{
    QString path = QFileDialog::getSaveFileName(this, "Save game", "", "Save files (*.sav");
    if(path != "") {
        _model->saveGame(path);
    }
}

void HuntingWidget::onLoadButtonClicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Open save", "", "Save files (*.sav)");
    if(path != "") {
        _model->loadGame(path);
    }
}
