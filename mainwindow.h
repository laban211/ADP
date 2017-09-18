#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "shape.h"
#include "toolset.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    void drawShape(QPainter &painter, Shape &shape);
    QPainterPath path;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //Where do we want this to be?
    void toolsetChanged(Toolset toolset);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:


    void on_actionSquare_triggered();

    void on_actionCircle_triggered();

    void on_actionTriangle_triggered();

    void on_actionMove_triggered();

    void on_actionDelete_triggered();

    void on_actionResize_triggered();

private:
    Ui::MainWindow *ui;
    std::vector<Shape> _shapeFromIndex;
    Toolset _toolset;

};

#endif // MAINWINDOW_H
