#ifndef MAINDRAWINGWIDGET_H
#define MAINDRAWINGWIDGET_H
#include <QWidget>
#include <vector>
#include "shape.h"
#include <QTimer>
#include <QGraphicsScene>
#include "mainwindow.h"


class MainDrawingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainDrawingWidget(QWidget *parent = nullptr);

private:
    int _shapeCopy;
    bool _copiedOnce;
    void paint(QPainter&);
    void drawShape(QPainter &painter, Shape &shape);
    Shape *_shapeMoving = nullptr;
    QPoint _positionOfShapeWhenClicked;
    QPoint _positionOfMouseWhenClicked;

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    bool containsPoint(Shape &shape, QPoint point);
    Shape *shapeClicked(QPoint point);
    void showContextMenu(const QPoint &point);
};

#endif // MAINDRAWINGWIDGET_H
