#ifndef ASTAR_H
#define ASTAR_H

#include "node.h"
#include <QObject>
#include <QDebug>

#define NDIR 4

class Astar : public QObject
{
    Q_OBJECT
public:
    explicit Astar(QObject *parent = nullptr);

    void init(QString);
    QString findPath(Location, Location);
    void drawMap(QGraphicsScene*);
    int getRow() const;
    int getCol() const;

private:
    int i, j, m, n, k;
    QString path;

    QTimer *timer;
    Location start, end;
    QGraphicsPixmapItem *itemStart;
    QPainter *painter;
    QGraphicsScene * scene;

    int map[100][100];
    int openNodes[100][100];
    int closeNodes[100][100];
    int dirMap[100][100];

    const int iDir[NDIR] = {1, 0, -1, 0};
    const int jDir[NDIR] = {0, 1, 0, -1};

public slots:
    void movePacman();
};

#endif // ASTAR_H
