#include "astar.h"

Astar::Astar(QObject *parent) : QObject(parent)
{}

void Astar::init(QString input)
{
    //open file
    QFile file(input);
    if (!file.open(QIODevice::ReadOnly)) {qDebug() << "error open file"; return; }

    /***
        0: valid
        1: invalid
        2: start
        3: end
    **/

    QTextStream in(&file);
    i = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();
        n = line.length();
        for (j = 0; j < n; j++) {
            //wall, map
            if (line[j] == ' ') map[i][j] = 0;
            else map[i][j] = 1;

            //start, end
            if (line[j] == 'P' || line[j] == 'p') {
                map[i][j] = 2;
                start.x = i;
                start.y = j;
            }
            if (line[j] == 'G' || line[j] == 'g') {
                map[i][j] = 3;
                end.x = i;
                end.y = j;
            }
        }
        i++;
    }
    m = i;

    memset(openNodes, 0, sizeof(openNodes));
    memset(closeNodes, 0, sizeof(closeNodes));

    this->path = findPath(start, end);
}

//A* algorithm
QString Astar::findPath(Location start, Location end)
{
    std::priority_queue<Node> q;
    static Node *Node1, *Node2;
    static int row, col, iNext, jNext;
    static char c;

    Node1 = new Node(start, 0, 0);
    Node1->calcF(end);
    q.push(*Node1);

    while (!q.empty()) {
        Node1 = new Node(q.top().getLocation(), q.top().getG(), q.top().getF());
        row = Node1->getLocation().x;
        col = Node1->getLocation().y;
        q.pop();

        openNodes[row][col] = 0;
        closeNodes[row][col] = 1;

        //goal
        if (row == end.x && col == end.y) {
            //create string find path
            QString path = "";
            while (!(row == start.x && col == start.y)) {
                j = dirMap[row][col];
                c = '0' + (j + NDIR / 2) % NDIR;
                path = c + path;
                row += iDir[j];
                col += jDir[j];
            }
            delete Node1;

            //remove left node if exists
            while (!q.empty()) q.pop();
            return path;
        }

        //else, get 4 director
        for (i = 0; i < NDIR; i++) {
            iNext = iDir[i] + row;
            jNext = jDir[i] + col;

            if (!(map[iNext][jNext] == 1 || closeNodes[iNext][jNext] == 1
                  || iNext < 0 || iNext > m - 1 || jNext < 0 || jNext > n -1)) {

                //create a child node
                Node2 = new Node(Location(iNext, jNext), Node1->getG(), Node1->getF());
                Node2->updateG();
                Node2->calcF(end);

                if (openNodes[iNext][jNext] == 0) {
                    openNodes[iNext][jNext] = Node2->getF();
                    q.push(*Node2);

                    dirMap[iNext][jNext] = (i + NDIR/2 ) % NDIR;
                } else {
                    delete Node2;
                }
            }
        }
        delete Node1;
    }
    return "";
}

//Draw map using GUI
void Astar::drawMap(QGraphicsScene * scene)
{
    this->scene = scene;
    //draw map
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            //wall
            if (map[j][i] == 1) {
                QImage image(":/icon/icon/tree.png");
                QGraphicsPixmapItem *wall = new QGraphicsPixmapItem(QPixmap::fromImage(image));
                wall->setPos(i * 15, j * 15);
                scene->addItem(wall); 
            }
            //start
            if (map[j][i] == 2) {
                QImage image(":/icon/icon/pacman-0.png");
                itemStart = new QGraphicsPixmapItem(QPixmap::fromImage(image));
                itemStart->setPos(i * 15, j * 15);
                scene->addItem(itemStart);
            }
            //end
            if (map[j][i] == 3) {
                QImage image(":/icon/icon/goal.png");
                QGraphicsPixmapItem *goal = new QGraphicsPixmapItem(QPixmap::fromImage(image));
                scene->addItem(goal);
                goal->setPos(i * 15, j * 15);
            }
        }
    }

    //animation pacman
    if (path.length() > 0) {
        k = 0;
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(movePacman()));
        timer->start(300);
    }
}

void Astar::movePacman() {
    QChar c;
    qreal oldX = itemStart->x(),
          oldY = itemStart->y(),
          curX, curY;
    if (k < path.length()) {
        c = path.at(k);
        //down
        if (c == '0') {
            //pacman
            QImage image(":/icon/icon/pacman-0.png");
            curY = itemStart->y() + 15;
            itemStart->setY(curY);
            itemStart->setPixmap(QPixmap::fromImage(image));

            //mark down
            QGraphicsTextItem *mark1 = this->scene->addText("v");
            mark1->setPos(oldX, oldY);
            mark1->setHtml("<div style='color: white;'><b>v</b></div>");

            qDebug() << "down";
        }
        //right
        if (c == '1') {
            //pacman
            QImage image(":/icon/icon/pacman-1.png");
            curX = itemStart->x() + 15;
            itemStart->setX(curX);
            itemStart->setPixmap(QPixmap::fromImage(image));

            //mark right
            QGraphicsTextItem *mark2 = this->scene->addText(">");
            mark2->setPos(oldX, oldY);
            mark2->setHtml("<div style='color: white;'><b>&gt;</b></div>");

            qDebug() << "right";
        }
        //up
        if (c == '2') {
            //pacman
            QImage image(":/icon/icon/pacman-2.png");
            curY = itemStart->y() - 15;
            itemStart->setY(curY);
            itemStart->setPixmap(QPixmap::fromImage(image));

            //mark up
            QGraphicsTextItem *mark3 = this->scene->addText("^");
            mark3->setPos(oldX, oldY);
            mark3->setHtml("<div style='color: white;'><b>^</b></div>");

            qDebug() << "up";
        }
        //left
        if (c == '3') {
            //pacman
            QImage image(":/icon/icon/pacman-3.png");
            curX = itemStart->x() -15;
            itemStart->setX(curX);
            itemStart->setPixmap(QPixmap::fromImage(image));

            //mark left
            QGraphicsTextItem *mark4 = this->scene->addText("<");
            mark4->setPos(oldX, oldY);
            mark4->setHtml("<div style='color: white;'><b>&lt;</b></div>");
            qDebug() << "left";
        }

        k++;
    } else {
        QMessageBox box;
        box.setText("A* finish");
        box.setWindowTitle("Done");
        box.exec();
        timer->stop();
    }
}

//send back to mainwindow
int Astar::getRow() const
{
    return this->m;
}
int Astar::getCol() const
{
    return this->n;
}
