#ifndef GAMEMAPVIEW_H
#define GAMEMAPVIEW_H

#include <QWidget>
#include <QFrame>
class QGridLayout;
class GameMapModel;
class QTimer;
class GameMapView : public QFrame
{
    Q_OBJECT
public:
    explicit GameMapView(QWidget *parent = 0);
    explicit GameMapView(size_t row_, size_t col_, QWidget *parent = 0);
    
signals:
protected:
    void resizeEvent(QResizeEvent *);
    
public slots:
    void updateCell(size_t row, size_t col, bool state);
    void setTimerInterval(int msec);
private:
    QGridLayout *grid;
    GameMapModel *model;
    QTimer *timer;

    void initGame(size_t row_, size_t col_);
    void resetModelAndGrid(size_t row_, size_t col_);

    
};

#endif // GAMEMAPVIEW_H
