#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "maindrawingwidget.h"
#include "shape.h"
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     Ui::MainWindow *ui;

private slots:
     void on_actionSquare_triggered();
     void on_actionCircle_triggered();
     void on_actionTriangle_triggered();
     void on_actionSave_triggered();
     void on_actionOpen_triggered();
     void on_actionColorpicker_triggered();
     void on_actionBorderColor_triggered();

protected:
     QString _colorShapeBoxColor;
     QString _colorBorderBoxColor;
     QColor _currentShapeColor = Qt::white;
     QColor _currentBorderColor = Qt::black;
;

     QPushButton *colorShapeBox;
     QPushButton *colorBorderBox;

};

#endif // MAINWINDOW_H
