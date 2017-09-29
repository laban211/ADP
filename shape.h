#ifndef SHAPE_H
#define SHAPE_H

#include <QWidget>
#include <QCoreApplication>
#include <QFile>
#include <QDataStream>
#include <QString>
#include <QDebug>
#include <QRect>
#include <QColor>

class Shape
{
public:
    Shape(){}
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

    friend QDataStream &operator<<(QDataStream &ds, Shape &shape);
    friend QDataStream &operator>>(QDataStream &ds, Shape &shape);
};

inline QDataStream &operator>>(QDataStream &ds, Shape &shape)
{
    return ds >> shape._boundingRect >> shape._colorBorder >> shape._colorFill >> shape._lineWidth >> ((qint32&)shape._shapetype);
}

inline QDataStream &operator<<(QDataStream &ds, Shape &shape)
{
    return ds << shape._boundingRect << shape._colorBorder << shape._colorFill << shape._lineWidth << shape._shapetype;
}
#endif // SHAPE_H


