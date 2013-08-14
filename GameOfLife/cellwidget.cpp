#include "cellwidget.h"
#include <QPainter>
#include <QResizeEvent>
CellWidget::CellWidget(QWidget *parent) :
    QWidget(parent)
{
    this->state = false;
}

void CellWidget::paintEvent(QPaintEvent *)
{
    static const QBrush brush = QBrush(Qt::red);
    QPainter painter(this);
    painter.setBrush(brush);
    painter.setRenderHint(QPainter::Antialiasing);
    if (state)
    {
        int min = this->width() < this->height() ? width() : height();
         painter.drawRect(0, 0, min, min);
    }
}

void CellWidget::resizeEvent(QResizeEvent *e)
{
    int width = e->size().width();
    int height = e->size().height();
    int min  = width < height ? width : height;
    this->resize(min, min);
}


void CellWidget::changeState(bool state_)
{
    this->state = state_;
    update();
}
