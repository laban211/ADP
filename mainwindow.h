#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <vector>
#include "shape.h"
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    void drawShape(QPainter &painter, Shape &shape);
    QPainterPath path;
    Shape *_shapeMoving = nullptr;
    QPoint _positionOfShapeWhenClicked;
    QPoint _positionOfMouseWhenClicked;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void on_actionSquare_triggered();
    void on_actionCircle_triggered();
    void on_actionTriangle_triggered();
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    bool containsPoint(Shape &shape, QPoint point);
    Shape *shapeClicked(QPoint point);


private:
    Ui::MainWindow *ui;
    std::vector<Shape> _shapeFromIndex;

};

#endif // MAINWINDOW_H
