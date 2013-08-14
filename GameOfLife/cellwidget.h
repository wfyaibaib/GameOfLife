#ifndef CELLWIDGET_H
#define CELLWIDGET_H

#include <QWidget>

class CellWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CellWidget(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

    
signals:
    
public slots:
    void changeState(bool state_);
private:
    bool state;
};

#endif // CELLWIDGET_H
