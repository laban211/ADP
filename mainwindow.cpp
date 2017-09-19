#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPaintEvent>
#include "shape.h"
#include <QMenu>
#include <QDebug>
#include <QColorDialog>
#include <QApplication>
#include <QPushButton>
#include <QColor>
#include <QModelIndex>



//drawing all 3 shapes
void MainWindow::drawShape(QPainter &painter, Shape &shape)
{
    painter.setBrush(shape._colorFill);
    painter.setPen(QPen(shape._colorBorder, shape._lineWidth));

    if(shape._shapetype == Shape::ellipse){
        painter.drawEllipse(shape._boundingRect);
    }
    else if(shape._shapetype == Shape::triangle){
        path.moveTo(shape._boundingRect.left() + (shape._boundingRect.width() / 2), shape._boundingRect.top());
        path.lineTo(shape._boundingRect.bottomRight());
        path.lineTo(shape._boundingRect.bottomLeft());
        path.lineTo(shape._boundingRect.left() + (shape._boundingRect.width() / 2), shape._boundingRect.top());
        painter.drawPath(path);
    }
    else
    {
        painter.drawRect(shape._boundingRect);
    }

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMainWindow::showMaximized();
    //setting default colors
    currentShapeColor = Qt::white;
    currentBorderColor = Qt::black;
    //Creates Shape Color box
    colorShapeBox = new QPushButton(this);
    ui->rightToolBar->addWidget(colorShapeBox);
    colorShapeBox->setText("Shape color");
    //Creates Border Color box
    colorBorderBox = new QPushButton(this);
    ui->rightToolBar->addWidget(colorBorderBox);
    colorBorderBox->setText("Border color");


    connect(colorShapeBox, SIGNAL(clicked()), this, SLOT(on_actionColorpicker_triggered()));
    connect(colorBorderBox, SIGNAL(clicked()), this, SLOT(on_actionBorderColor_triggered()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

//fill background with white color and loops through all shapes to draw them on screen
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.fillRect(event->rect(), Qt::white);

    for (Shape &shape: _shapeFromIndex){
        drawShape(painter, shape);
     }
}

//toolbar buttons
void MainWindow::on_actionSquare_triggered()
{
    Shape square(Shape::rectangle, QRect(100,100,100,100), 3, currentShapeColor, currentBorderColor);
    _shapeFromIndex.push_back(square);
    update();
}

void MainWindow::on_actionCircle_triggered()
{
    Shape circle(Shape::ellipse, QRect(100,100,100,100), 3, currentShapeColor, currentBorderColor);
    _shapeFromIndex.push_back(circle);
    update();
}

void MainWindow::on_actionTriangle_triggered()
{
    Shape triangle(Shape::triangle, QRect(100,100,100,100), 3, currentShapeColor, currentBorderColor);
    _shapeFromIndex.push_back(triangle);
    update();
}


void MainWindow::on_actionColorpicker_triggered()
{

    QColor colorShapeTest = QColorDialog::getColor();

    if(colorShapeTest.isValid()){

    currentShapeColor = colorShapeTest;
    colorShapeBoxColor = QString("background-color: %1").arg(currentShapeColor.name());
    colorShapeBox->setStyleSheet(colorShapeBoxColor);
    }
}




void MainWindow::on_actionBorderColor_triggered()
{
    QColor colorBorderTest = QColorDialog::getColor();

    if(colorBorderTest.isValid()){
    currentBorderColor = colorBorderTest;
    colorBorderBoxColor = QString("background-color: %1").arg(currentBorderColor.name());
    colorBorderBox->setStyleSheet(colorBorderBoxColor);
    }

}
