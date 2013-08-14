#ifndef GAMEMAPMODEL_H
#define GAMEMAPMODEL_H

#include <QObject>
#include <cstddef>
#include <vector>

class GameMapModel : public QObject
{
    Q_OBJECT
public:
    explicit GameMapModel(size_t rowCnt, size_t colCnt, QObject *parent = 0);
    void setState(size_t r, size_t c, bool state);
    virtual void cellToNextState(size_t row_, size_t col_);

signals:
    void updateUi(size_t row_, size_t col_, bool live);
protected:
    virtual size_t getLiveAroundCnt(size_t i, size_t j);

    void initMap(size_t rowCnt, size_t colCnt);

public slots:
    void debug(size_t r, size_t c, bool live);
    void mapToNextState();
    void random();
    void resetMap(size_t row_, size_t col_);

private:
    typedef std::vector<std::vector<bool> > map_t;

    map_t map;
    map_t tmp;
    size_t row;
    size_t col;
    
};

#endif // GAMEMAPMODEL_H
