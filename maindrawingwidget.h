#ifndef MAINDRAWINGWIDGET_H
#define MAINDRAWINGWIDGET_H

#include <QWidget>
#include <vector>
#include "shape.h"
#include <QTimer>
#include <QGraphicsScene>
#include "toolset.h"

class MainDrawingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainDrawingWidget(QWidget *parent = nullptr);
    bool openImage(const QString &fileName);
    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);

private:
    int _shapeCopy;
    bool _copiedOnce;
    void paint(QPainter&);
    void drawShape(QPainter &painter, Shape &shape);
    Shape *_shapeMoving = nullptr;
    QPoint _positionOfShapeWhenClicked;
    QPoint _positionOfMouseWhenClicked;
    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);
    bool _drawing;
    int _myPenWidth;
    QColor _myPenColor;
    QImage _img;
    QPoint _lastDrawingPoint;
    Shape *_shapeResizing = nullptr;


protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    bool containsPoint(Shape &shape, QPoint point);
    Shape *shapeClicked(QPoint point);
    void showContextMenu(const QPoint &point);
};

#endif // MAINDRAWINGWIDGET_H
