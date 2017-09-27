#include "maindrawingwidget.h"
#include <QPainter>
#include <QPaintEvent>
#include "shape.h"
#include <QDebug>
#include <QMenu>
#include "mainwindow.h"

std::vector<Shape> _shapeFromIndex;
extern bool _penButtonChecked;
extern bool _eraseButtonChecked;

MainDrawingWidget::MainDrawingWidget(QWidget *parent) : QWidget(parent)
{
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint)), this, SLOT(showContextMenu(const QPoint &)));
    //ny
    setAttribute(Qt::WA_StaticContents);
    scribbling = false;
}

bool MainDrawingWidget::openImage(const QString &fileName)
{
    QImage loadedImage;

    if (!loadedImage.load(fileName))
            return false;

    QSize newSize = loadedImage.size().expandedTo(size());
    resizeImage(&loadedImage, newSize);
    image = loadedImage;
    update();
    return true;
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
    else if(shape._shapetype == Shape::rectangle)
    {
        painter.drawRect(shape._boundingRect);
    }
}

void MainDrawingWidget::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    modified = true;
    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

void MainDrawingWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(event->rect(), Qt::white);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);

    if(_penButtonChecked){
        myPenWidth = 5;
        myPenColor = Qt::black;
    }else if(_eraseButtonChecked){
        myPenWidth = 20;
        myPenColor = Qt::white;
    }
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
    if (event->button() == Qt::LeftButton && _penButtonChecked || _eraseButtonChecked) {
            lastPoint = event->pos();
            scribbling = true;
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

    if ((event->buttons() & Qt::LeftButton) && scribbling)
            drawLineTo(event->pos());

}

void MainDrawingWidget::mouseReleaseEvent(QMouseEvent *event)
{
    _shapeMoving = nullptr;

    if (event->button() == Qt::LeftButton && scribbling) {
            drawLineTo(event->pos());
            scribbling = false;
        }
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

void MainDrawingWidget::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
            return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void MainDrawingWidget::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
            int newWidth = qMax(width() + 160, image.width());
            int newHeight = qMax(height() + 160, image.height());
            resizeImage(&image, QSize(newWidth, newHeight));
            update();
        }
        QWidget::resizeEvent(event);
}
