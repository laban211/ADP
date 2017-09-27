#include "maindrawingwidget.h"
#include "mainwindow.h"
#include <QPainter>
#include <QPaintEvent>
#include "shape.h"
#include <QDebug>
#include <QMenu>
#include "toolset.h"
#include <QBrush>
#include <vector>

std::vector<Shape> _shapeFromIndex;

extern QColor _currentShapeColor;
extern QColor _currentBorderColor;
extern int _currentBorderSize;
extern QString _colorShapeBoxColor;
extern QString _colorBorderBoxColor;
extern QPushButton *colorShapeBox;
extern QPushButton *colorBorderBox;
extern QPushButton *borderSizeBox;


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
    QAction *actionApplyStyle = menuCreate.addAction("Apply style");
    QAction *actionCopyStyle = menuCreate.addAction("Copy style");

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
    else if(actionChosen == actionApplyStyle){
        for (int i=_shapeFromIndex.size()-1; i>=0; i-=1){
                if (containsPoint(_shapeFromIndex[i], point)){
                 _shapeFromIndex[i]._colorFill = _currentShapeColor;
                 _shapeFromIndex[i]._colorBorder = _currentBorderColor;
                 _shapeFromIndex[i]._lineWidth = _currentBorderSize;
                }
                update();
        }
    }
    else if(actionChosen == actionCopyStyle){
            for (int i=_shapeFromIndex.size()-1; i>=0; i-=1){
                    if (containsPoint(_shapeFromIndex[i], point)){

                        _currentShapeColor = _shapeFromIndex[i]._colorFill;
                        _currentBorderColor = _shapeFromIndex[i]._colorBorder;
                        _currentBorderSize = _shapeFromIndex[i]._lineWidth;

                        _colorBorderBoxColor = QString("background-color: %1").arg(_currentBorderColor.name());
                        colorBorderBox->setStyleSheet(_colorBorderBoxColor);

                        _colorShapeBoxColor = QString("background-color: %1").arg(_currentShapeColor.name());
                        colorShapeBox->setStyleSheet(_colorShapeBoxColor);

                        QString borderSize = QString::number(_currentBorderSize);
                        borderSizeBox->setText(borderSize);

                    }
                    update();
    }
}
}
