#ifndef SHAPE_H
#define SHAPE_H

#include <QWidget>

<<<<<<< HEAD
class Shape : public QWidget
{
    Q_OBJECT
public:
    explicit Shape(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // SHAPE_H
=======
class Shape
{
public:
    enum Shapetype{
        ellipse, rectangle, triangle
    };

    Shape(Shapetype shapetype, QRect boundingRect, int lineWidth, QColor colorFill, QColor colorBorder):
        _shapetype(shapetype),
        _boundingRect(boundingRect),
        _lineWidth(lineWidth),
        _colorFill(colorFill),
        _colorBorder(colorBorder) { }

    Shapetype _shapetype;
    QRect _boundingRect;
    int _lineWidth;
    QColor _colorFill;
    QColor _colorBorder;
};

#endif // SHAPE_H
>>>>>>> jakoobsBranch
