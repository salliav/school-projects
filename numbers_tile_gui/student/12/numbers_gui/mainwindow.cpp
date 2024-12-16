/* Module: Mainwindow / File: mainwindow.cpp
 * Includes the execution of graphic user interface of the game.
 */

#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gameboard.hh"
#include "numbertile.hh"

#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QColor>
#include <cmath>
#include <map>


const int SQUARE = 50;
const int MIN_GOAL = 4;
const int MAX_GOAL = 65536;
const int PULSE = 1000;
const QColor BIG_VALUES_COLOR = QColor(106, 90, 205);

Colors colors = {
{NEW_VALUE, QColor(173, 216, 230)},
{pow(2, 2), QColor(135, 206, 235)}, {pow(2, 3), QColor(65, 105, 225)},
{pow(2, 4), QColor(100, 149, 237)}, {pow(2, 5), QColor(0, 255, 255)},
{pow(2, 6), QColor(135, 206, 250)}, {pow(2, 7), QColor( 0, 191, 255)},
{pow(2, 8), QColor(70, 130, 180)}, {pow(2, 9), QColor(176, 224, 230)},
{pow(2, 10), QColor( 0, 255, 255)}, {pow(2, 11), QColor(224, 255, 255)}
};

Keys keys = {
{Qt::Key_W, UP},
{Qt::Key_S, DOWN},
{Qt::Key_A, LEFT},
{Qt::Key_D, RIGHT}
};


MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    gameboard_ = new GameBoard;
    timer_ = new QTimer(parent);
    scene_ = new QGraphicsScene(this);
    ui_->graphicsView->setScene(scene_);


    // Sets locations and colors for gui components.
    ui_->graphicsView->setGeometry(400, 30,
                                   SIZE*SQUARE+5,
                                   SIZE*SQUARE+5);
    ui_->seedLabel->setGeometry(90, 30, 100, 30);
    ui_->goalLabel->setGeometry(90, 80, 100, 30);
    ui_->seedLineEdit->setGeometry(200, 30, 120, 30);
    ui_->goalLineEdit->setGeometry(200, 80, 120, 30);
    ui_->okButton->setGeometry(90, 140, 80, 30);
    ui_->resetButton->setGeometry(240, 140, 80, 30);
    ui_->pauseButton->setGeometry(550, 300, 80, 30);
    ui_->textBrowser->setGeometry(90, 200, 230, 80);
    ui_->lcdNumberMin->setGeometry(370, 300, 80, 30);
    ui_->lcdNumberSec->setGeometry(450, 300, 80, 30);
    ui_->seedLineEdit->setStyleSheet("background-color: white");
    ui_->goalLineEdit->setStyleSheet("background-color: white");
    ui_->okButton->setStyleSheet("background-color: white");
    ui_->resetButton->setStyleSheet("background-color: white");
    ui_->pauseButton->setStyleSheet("background-color: white");
    ui_->lcdNumberMin->setStyleSheet("background-color: white");
    ui_->lcdNumberSec->setStyleSheet("background-color: white");
    ui_->textBrowser->setStyleSheet("background-color: white");

    // Sets initialization values for components
    game_is_on_ = false;
    time_ = 0;
    ui_->okButton->setEnabled(true);
    ui_->resetButton->setDisabled(true);
    ui_->pauseButton->setText("Pause");
    ui_->pauseButton->setDisabled(true);
    this->setStyleSheet("background-color: white");

    connect(timer_, &QTimer::timeout, this, &MainWindow::update_LCD);
    connect(ui_->pauseButton, &QPushButton::clicked, this, &MainWindow::control_timer);
    connect(ui_->okButton, &QPushButton::clicked, this, &MainWindow::init_game);
    connect(ui_->resetButton, &QPushButton::clicked, this, &MainWindow::reset_game);

    init_graphic_gameboard();

}
MainWindow::~MainWindow()
{
    delete gameboard_;
    gameboard_ = nullptr;

    delete timer_;
    timer_ = nullptr;

    delete ui_;
}

bool MainWindow::check_goal(int goal_value, int base) {

    if (base == goal_value) {
        return true;
    }
    else if (base > goal_value) {
        return false;
    }
    return check_goal(goal_value, base * 2);
}

void MainWindow::take_input()
{
    QString seed_str = "";
    seed_str = ui_->seedLineEdit->text();
    if (seed_str == "" or !seed_str.toInt()) {
        ui_->textBrowser->setText("Seed must be an integer."
                                    " Generating own seed.");
        seed_ = time(NULL);
    }
    else {
        seed_ = seed_str.toInt();
    }


    QString goal_str = "";
    goal_str = ui_->goalLineEdit->text();
    int base = 2;


    if (goal_str == "" or !goal_str.toInt()) {
        ui_->textBrowser->setText("Goal must be an integer. Using goal "
                                    +QString::number(DEFAULT_GOAL)+ ".");
        goal_ = DEFAULT_GOAL;

    } else if (goal_str.toInt() < MIN_GOAL or goal_str.toInt() > MAX_GOAL) {
        ui_->textBrowser->setText("Minimum goal is " +QString::number(MIN_GOAL)+
                                  " and maximum goal is " +QString::number(MAX_GOAL)+
                                  ". Using goal " +QString::number(DEFAULT_GOAL)+ ".");

    } else if (!check_goal(goal_str.toInt(), base)) {
        ui_->textBrowser->setText("Goal must be potens of 2. Using goal "
                                    +QString::number(DEFAULT_GOAL)+ ".");
        goal_ = DEFAULT_GOAL;
    } else {
        goal_ = goal_str.toInt();
    }    
}

void MainWindow::init_game()
{
    take_input();
    gameboard_->init_empty();
    gameboard_->fill(seed_);

    ui_->okButton->setDisabled(true);
    ui_->resetButton->setEnabled(true);
    ui_->pauseButton->setEnabled(true);

    draw_tiles(colors);
    game_is_on_ = true;
    timer_->start(PULSE);
}

void MainWindow::reset_game()
{
    reset_timer();   
    take_input();
    gameboard_->reset();

    // Sets the tiles back to white empty squares.
    for( auto y = 0; y < SIZE; ++y ) {
        for( auto x = 0; x < SIZE; ++x ) {
          QBrush tmpbrush(Qt::SolidPattern);
          tmpbrush.setColor(Qt::white);
          rects_.at(y).at(x)->setBrush(tmpbrush);
          texts_.at(y).at(x)->setPlainText("");
        }
    }

    this->setStyleSheet("background-color: white");
    ui_->textBrowser->setText("");
    ui_->pauseButton->setEnabled(true);
    ui_->pauseButton->setText("Pause");

    draw_tiles(colors);
    game_is_on_ = true;
    timer_->start(PULSE);

}

void MainWindow::init_graphic_gameboard()
{
    for(int row = 0; row < SIZE; row++) {
        std::vector<QGraphicsRectItem*> rect_rows;
        std::vector<QGraphicsTextItem*> txt_rows;
        for (int column = 0; column < SIZE; column++) {

            // Inits empty squares.
            QPen tmppen;
            tmppen.setColor(Qt::blue);
            QGraphicsRectItem* tmprect = scene_->addRect
                    (column * SQUARE, row * SQUARE, SQUARE, SQUARE, tmppen);
            tmprect->setPen(tmppen);

            QBrush tmpbrush(Qt::SolidPattern);
            tmpbrush.setColor(Qt::white);
            tmprect->setBrush(tmpbrush);

            // Inits blank texts for squares.
            QGraphicsTextItem* tmptxt = scene_->addText("");
            tmptxt->setPos(column * SQUARE, row * SQUARE);

            txt_rows.push_back(tmptxt);
            rect_rows.push_back(tmprect);
        }
        rects_.push_back(rect_rows);
        texts_.push_back(txt_rows);
    }
}

void MainWindow::draw_tiles(Colors colors) {

    for( auto y = 0; y < SIZE; ++y ) {
        for( auto x = 0; x < SIZE; ++x ) {              
          NumberTile* current = nullptr;
          current = gameboard_->get_item(std::make_pair(y, x));

          if (not current->is_empty()) {
              for (auto& unit : colors) {
                  if (current->get_value() == unit.first) {
                      QBrush tmpbrush(unit.second, Qt::SolidPattern);
                      rects_.at(y).at(x)->setBrush(tmpbrush);
                  }
                  if (current->get_value() > pow(2, 11)) {
                      QBrush tmpbrush(BIG_VALUES_COLOR, Qt::SolidPattern);
                      rects_.at(y).at(x)->setBrush(tmpbrush);
                  }
              }
              QString value_qstr;
              value_qstr = value_qstr.setNum(current->get_value());
              texts_.at(y).at(x)->setPlainText(value_qstr);

          } else {
              QBrush tmpbrush(Qt::SolidPattern);
              tmpbrush.setColor(Qt::white);
              rects_.at(y).at(x)->setBrush(tmpbrush);
              texts_.at(y).at(x)->setPlainText("");
            }
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
     if (not game_is_on_) {
        return;
     }


     // Clears messages after starting or finishing the game.
     ui_->textBrowser->setText("");

    for (auto& key : keys) {
        if (event->key() == (key.first)) {
            if (gameboard_->move(key.second, goal_)) {
                win();
            }
            gameboard_->new_value(false);
            draw_tiles(colors);
        }
    }

    if (gameboard_->is_full()) {
        lost();
        return;
    }
}

void MainWindow::win()
{
    game_is_on_ = false;
    timer_->stop();

    ui_->pauseButton->setDisabled(true);
    this->setStyleSheet("background-color: green");

    QString min = QString::number(ui_->lcdNumberMin->value());
    QString sec = QString::number(ui_->lcdNumberSec->value());
    ui_->textBrowser->setText("You reached the goal value of "
                              +QString::number(goal_) + " in time "
                                             +min+ ":" + sec +"!");
}

void MainWindow::lost()
{
    game_is_on_ = false;
    timer_->stop();

    ui_->pauseButton->setDisabled(true);
    this->setStyleSheet("background-color: red");

    ui_->textBrowser->setText("Can't add new tile, you lost!");
}

void MainWindow::update_LCD()
{
    time_++;
    ui_->lcdNumberMin->display(time_/60);
    ui_->lcdNumberSec->display(time_%60);
}

void MainWindow::reset_timer()
{
    ui_->lcdNumberMin->display(0);
    ui_->lcdNumberSec->display(0);
    time_ = 0;
}

void MainWindow::control_timer()
{
    if (game_is_on_) {
        timer_->stop();
        game_is_on_ = false;
        ui_->textBrowser->setText("Pause is on.");
        ui_->pauseButton->setText("Play");
        return;
    }
    if (not game_is_on_) {
        timer_->start(PULSE);
        game_is_on_ = true;
        ui_->textBrowser->setText("");
        ui_->pauseButton->setText("Pause");
        return;
    }
}
