#ifndef SHAPE_H
#define SHAPE_H

#include <QWidget>

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
