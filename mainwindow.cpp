#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "maindrawingwidget.h"
#include <QDebug>
#include "shape.h"
#include <QFileDialog>
#include <QPainter>
#include <QLabel>
#include <QDesktopWidget>
#include <QTextStream>

extern std::vector<Shape> _shapeFromIndex;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSquare_triggered()
{
    Shape square(Shape::rectangle, QRect(100,100,100,100), 3, Qt::white, Qt::black);
    _shapeFromIndex.push_back(square);
    update();
}

void MainWindow::on_actionCircle_triggered()
{
    Shape circle(Shape::ellipse, QRect(100,100,100,100), 3, Qt::white, Qt::black);
    _shapeFromIndex.push_back(circle);
    update();
}

void MainWindow::on_actionTriangle_triggered()
{
    Shape triangle(Shape::triangle, QRect(100,100,100,100), 3, Qt::white, Qt::black);
    _shapeFromIndex.push_back(triangle);
    update();
}

void MainWindow::on_actionSave_triggered()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save image"), "", tr("PNG file (*.png)"));

    if (path.isEmpty())
        return;

    QImage image(centralWidget()->size(), QImage::Format_ARGB32);
    QPainter painter(&image);
    centralWidget()->render(&painter);
    image.save(path);
}

void MainWindow::on_actionOpen_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open image"), "", tr("PNG file (*.png)"));
    if(path.isEmpty())
        return;

    QPixmap image(path);
    QLabel *label = new QLabel(centralWidget());
    label->setPixmap(image);
    label->show();

}
