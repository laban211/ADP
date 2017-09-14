#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPaintEvent>
#include "shape.h"

//drawing all 3 shapes
void MainWindow::drawShape(QPainter &painter, Shape &shape)
{
    painter.setBrush(shape._colorFill);
    painter.setPen(QPen(shape._colorBorder, shape._lineWidth));

    if(shape._shapetype == Shape::ellipse){
        painter.drawEllipse(shape._boundingRect);
    }
    else if(shape._shapetype == Shape::triangle){
       if(!_shapeMoving){
        path.moveTo(shape._boundingRect.left() + (shape._boundingRect.width() / 2), shape._boundingRect.top());
        path.lineTo(shape._boundingRect.bottomRight());
        path.lineTo(shape._boundingRect.bottomLeft());
        path.closeSubpath();
        painter.drawPath(path);
       }
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

        for(Shape &shape : _shapeFromIndex){
            drawShape(painter, shape);
        }
}

//toolbar buttons
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

void MainWindow::mousePressEvent(QMouseEvent *event)
{
   _shapeMoving = shapeClicked(event->pos());
    if (_shapeMoving){
        _positionOfShapeWhenClicked = _shapeMoving->_boundingRect.topLeft();
        _positionOfMouseWhenClicked = event->pos();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(_shapeMoving){
        QPoint positionOfMouseNow = event->pos();
        QPoint displacement = positionOfMouseNow - _positionOfMouseWhenClicked;
        QPoint positionOfShapeNow = _positionOfShapeWhenClicked + displacement;
        QRect newRect(positionOfShapeNow, _shapeMoving->_boundingRect.size());
        _shapeMoving->_boundingRect = newRect;
        update();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    _shapeMoving = nullptr;
}

bool MainWindow::containsPoint(Shape &shape, QPoint point)
{
    QRegion::RegionType regionType = (shape._shapetype == Shape::ellipse ? QRegion::Ellipse : QRegion::Rectangle);
    QRegion region(shape._boundingRect, regionType);
    return region.contains(point);
}

Shape *MainWindow::shapeClicked(QPoint point)
{
    for (int i=_shapeFromIndex.size()-1; i>=0; i-=1){
            if (containsPoint(_shapeFromIndex[i], point))
                    return &_shapeFromIndex[i];
        }
    return nullptr;
}
