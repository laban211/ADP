#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <vector>
#include "shape.h"
#include <QTimer>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    void drawShape(QPainter &painter, Shape &shape);
    Shape *_shapeMoving = nullptr;
    QPoint _positionOfShapeWhenClicked;
    QPoint _positionOfMouseWhenClicked;
    QImage *_imageObject;
    QPixmap image;
    QGraphicsScene *scene;

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
    void showContextMenu(const QPoint &point);


    void on_actionSave_triggered();

    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
    std::vector<Shape> _shapeFromIndex;
    int _shapeCopy;
    bool _copiedOnce = false;

};

#endif // MAINWINDOW_H
