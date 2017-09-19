#include "maindrawingwidget.h"
#include "mainwindow.h"
#include <QPainter>
#include <QPaintEvent>
#include "shape.h"
#include <QDebug>
#include <QMenu>

std::vector<Shape> _shapeFromIndex;

MainDrawingWidget::MainDrawingWidget(QWidget *parent) : QWidget(parent)
{
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint)), this, SLOT(showContextMenu(const QPoint &)));
}

void MainDrawingWidget::drawShape(QPainter &painter, Shape &shape)
{
    QPainterPath path;
    painter.setBrush(shape._colorFill);
    painter.setPen(QPen(shape._colorBorder, shape._lineWidth));

    if(shape._shapetype == Shape::ellipse){
        painter.drawEllipse(shape._boundingRect);
    }
    else if(shape._shapetype == Shape::triangle){

        path.moveTo(shape._boundingRect.left() + (shape._boundingRect.width() / 2), shape._boundingRect.top());
        path.lineTo(shape._boundingRect.bottomRight());
        path.lineTo(shape._boundingRect.bottomLeft());
        path.closeSubpath();
        painter.drawPath(path);
    }
    else
    {
        painter.drawRect(shape._boundingRect);
    }
}

void MainDrawingWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(event->rect(), Qt::white);

        for(Shape &shape : _shapeFromIndex){
            drawShape(painter, shape);
        }
}

void MainDrawingWidget::mousePressEvent(QMouseEvent *event)
{
   _shapeMoving = shapeClicked(event->pos());
    if (_shapeMoving){
        _positionOfShapeWhenClicked = _shapeMoving->_boundingRect.topLeft();
        _positionOfMouseWhenClicked = event->pos();
    }
}

void MainDrawingWidget::mouseMoveEvent(QMouseEvent *event)
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

void MainDrawingWidget::mouseReleaseEvent(QMouseEvent *event)
{
    _shapeMoving = nullptr;
}

bool MainDrawingWidget::containsPoint(Shape &shape, QPoint point)
{
    QRegion::RegionType regionType = (shape._shapetype == Shape::ellipse ? QRegion::Ellipse : QRegion::Rectangle);
    QRegion region(shape._boundingRect, regionType);
    return region.contains(point);
}

Shape *MainDrawingWidget::shapeClicked(QPoint point)
{
    for (int i=_shapeFromIndex.size()-1; i>=0; i-=1){
            if (containsPoint(_shapeFromIndex[i], point))
                    return &_shapeFromIndex[i];
        }
    return nullptr;
}

void MainDrawingWidget::showContextMenu(const QPoint &point)
{
    QMenu menuCreate;
    menuCreate.setTitle("Shape");
    QAction *actionCopy = menuCreate.addAction("Copy");
    QAction *actionPaste = menuCreate.addAction("Paste");
    QAction *actionDelete = menuCreate.addAction("Delete");
    QMenu menu;
    menu.addMenu(&menuCreate);
    QPoint positionOfMenu = mapToGlobal(point);
    QAction *actionChosen = menu.exec(positionOfMenu);

    if(actionChosen == actionDelete){
        for (int i=_shapeFromIndex.size()-1; i>=0; i-=1){
                if (containsPoint(_shapeFromIndex[i], point))
                    _shapeFromIndex.erase(_shapeFromIndex.begin() + i);
                    update();
       }
   }
    else if(actionChosen == actionCopy){
        for (int i=_shapeFromIndex.size()-1; i>=0; i-=1){
                if (containsPoint(_shapeFromIndex[i], point))
                    _shapeCopy = i;
                    update();
                    _copiedOnce = true;
        }
    }
    else if(actionChosen == actionPaste && _copiedOnce){
        Shape shape = _shapeFromIndex[_shapeCopy];
        shape._boundingRect = QRect(point, shape._boundingRect.size());
        _shapeFromIndex.push_back(shape);
        update();
    }
}
