#ifndef NODE_H
#define NODE_H

#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <queue>
#include <QThread>
#include <QTimer>
#include <QChar>
#include <QMessageBox>

struct Location {
    int x, y;
    Location() { x = y = 0; }
    Location(int row, int col) { x = row, y = col; }
};

class Node
{
public:
    Node(Location, int, int);
    void updateG();
    int getF() const;
    int getG() const;
    void calcF(Location);
    int heuristic(Location);
    Location getLocation() const;
    friend bool operator<(const Node& a, const Node& b) { return a.getF() > b.getF(); }

private:
    int currentX, currentY;
    int f, g;
};

#endif // NODE_H
