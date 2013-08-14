#include "gamemapmodel.h"
#include <QDebug>
#include <QtGlobal> // qrand
#include <QTime>
GameMapModel::GameMapModel(size_t rowCnt, size_t colCnt, QObject *parent) :
    QObject(parent)
{
    initMap(rowCnt, colCnt);
    // debug
//    connect(this, SIGNAL(updateUi(size_t,size_t,bool)),
//            this, SLOT(debug(size_t,size_t,bool)));
}

void GameMapModel::setState(size_t r, size_t c, bool state)
{
    map[r][c] = state;
}

void GameMapModel::initMap(size_t rowCnt, size_t colCnt)
{
    qDebug() << "init begin!" << endl;

    row = rowCnt;
    col = colCnt;

    map.resize(row);
    tmp.resize(row);
    qDebug() << "init begin!" << endl;
    for (size_t i = 0; i < row; ++i)
    {
        map[i].resize(col);
        tmp[i].resize(col);
    }
    qDebug() << "init!" << endl;

}

void GameMapModel::debug(size_t r, size_t c, bool live)
{
    qDebug() << r << " ," << c << " ," << live << endl;
}


size_t GameMapModel::getLiveAroundCnt(size_t i, size_t j)
{
   // qDebug() << "getCnt: " << i << " " << j << endl;
    int cnt1 = 0;
    if (map[i][j]) cnt1 = -1;
    for (int x = -1; x <= 1; ++x)
        for (int y = -1; y <= 1; ++y)
        {
            int r = i + x;
            int c = j + y;
            if (r >= 0 && r < row && c >= 0 && c < col && map[r][c])
            {
               // qDebug() << r << " " << c << " is true\n";
                ++cnt1;
            }
        }
 //   qDebug() << "getCnt: " << i << " " << j << " " << cnt1 << endl;
    return cnt1;
}


void GameMapModel::cellToNextState(size_t row_, size_t col_)
{
    {
        // 3 alive 2 keep other dead
        size_t cnt = getLiveAroundCnt(row_, col_);
        switch (cnt)
        {
        case 3:
            tmp[row_][col_] = 1;
            break;
        case 2:
            tmp[row_][col_] = map[row_][col_];
            break;
        default:
            tmp[row_][col_] = 0;
        }
    }
}

void GameMapModel::mapToNextState()
{
    {
        for (size_t i = 0; i < row; ++i)
            for(size_t j = 0; j < col; ++j)
                cellToNextState(i, j);
        for (size_t i = 0; i < row; ++i)
            for(size_t j = 0; j < col; ++j)
            {
                if (map[i][j] != tmp[i][j])
                {
                    map[i][j] = tmp[i][j];
                    emit updateUi(i, j, map[i][j]);
                }

            }
    }
}

void GameMapModel::random()
{
    qsrand(QTime(0, 0, 0).msecsTo(QTime::currentTime()));
    for (size_t r = 0; r < row; ++r)
        for (size_t c = 0; c < col; ++c)
        {
            map[r][c] = qrand()%2;
        }
//    setState(0, 1, 1);
//    setState(1, 1, 1);
//    setState(2, 1, 1);
    for (size_t r = 0; r < row; ++r)
        for (size_t c = 0; c < col; ++c)
        {
            emit updateUi(r, c, map[r][c]);
        }

}

void GameMapModel::resetMap(size_t row_, size_t col_)
{
    if (row_ == row && col_ == col)
        return;
    row = row_;
    col = col_;
    map.resize(row = row_);
    for (size_t r = 0; r < row; ++r)
        map[r].resize(col);
    for (size_t r = 0; r < row; ++r)
        for (size_t c = 0; c < col; ++c)
        {
            map[r][c] = 0;
        }

}



