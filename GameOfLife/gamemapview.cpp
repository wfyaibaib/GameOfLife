#include "gamemapview.h"
#include <QGridLayout>
#include "cellwidget.h"
#include "gamemapmodel.h"
#include <QTimer>
#include <QResizeEvent>
GameMapView::GameMapView(QWidget *parent):QFrame(parent)
{
    initGame(30, 30);
    this->show();
}

GameMapView::GameMapView(size_t row_, size_t col_, QWidget *parent) :
    QFrame(parent)
{
    initGame(row_, col_);
    this->show();

}

void GameMapView::resizeEvent(QResizeEvent *e)
{
    int width = e->size().width();
    int height = e->size().height();
    int min  = width < height ? width : height;
  //  this->resize(min, min);
    e->accept();
}

void GameMapView::updateCell(size_t row, size_t col, bool state)
{
    CellWidget* cell = static_cast<CellWidget*>(this->grid->itemAtPosition(row, col)->widget());
    cell->changeState(state);
}

void GameMapView::setTimerInterval(int msec)
{
    this->timer->setInterval(msec);
}

void GameMapView::initGame(size_t row_, size_t col_)
{
    // grid
    this->grid = new QGridLayout(this);

    for (size_t i = 0; i < row_; ++i)
        for (size_t j = 0; j < col_; ++j)
        {
            grid->addWidget(new CellWidget(), i, j, 1, 1);
        }
    this->grid->setHorizontalSpacing(3);
    this->grid->setVerticalSpacing(3);
    this->setLayout(grid);
    // model
    this->model = new GameMapModel(row_, col_, this);
    connect(model, SIGNAL(updateUi(size_t,size_t,bool)),
            this, SLOT(updateCell(size_t,size_t,bool)));

    this->model->random();// will emit signal to this
    // timer
    timer = new QTimer(this);
    timer->setInterval(500);
    connect(timer, SIGNAL(timeout()),
            this->model, SLOT(mapToNextState()));
    timer->start();
}


void GameMapView::resetModelAndGrid(size_t row_, size_t col_)
{// there must exist a grid and a model
    if (row_ == this->grid->rowCount() && col_ == this->grid->columnCount())
        return;
    // grid
    this->grid->deleteLater();
    this->grid = new QGridLayout(this);
    for (size_t i = 0; i < row_; ++i)
        for (size_t j = 0; j < col_; ++j)
        {
            grid->addWidget(new CellWidget(), i, j, 1, 1);
        }
    this->setLayout(grid);
    // model
    this->model->resetMap(row_, col_);
    connect(model, SIGNAL(updateUi(size_t,size_t,bool)),
            this, SLOT(updateCell(size_t,size_t,bool)));

    this->model->random();// will emit signal to this
}
