#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->start->hide();
    ui->stop->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_openMap_clicked()
{
    input = QFileDialog::getOpenFileName(this, tr("Select map"), "C:", "Text files (*.text *.lay *.inp *.INP *.txt *.layout *.in *.input)");

    if (!input.isEmpty()) {
        emit on_start_clicked();
    }
}

void MainWindow::on_start_clicked()
{
    ui->openMap->setEnabled(false);
    ui->stop->setEnabled(true);

    //start a* algorithm
    astar = new Astar(this);
    astar->init(input);

    //get size mainwindow
    this->m = astar->getRow();
    this->n = astar->getCol();

    //set size mainwindow
    this->resize(m * 20, n * 20);
    QGraphicsScene *scene = new QGraphicsScene(0, 0, m, n);
    scene->setBackgroundBrush(QBrush(QColor(47, 47, 47)));
    ui->graphicsView->setAlignment( Qt::AlignLeft | Qt::AlignTop );
    ui->graphicsView->setScene(scene);

    //draw map
    astar->drawMap(scene);
}

void MainWindow::on_stop_clicked()
{
    ui->stop->setEnabled(false);
    ui->openMap->setEnabled(true);

    delete astar;
    input = "";
}
