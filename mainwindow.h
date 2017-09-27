#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "maindrawingwidget.h"
#include "shape.h"
#include <QPushButton>
#include "toolset.h"
#include <QResizeEvent>

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
     void on_penButton_clicked();
     void on_actionMove_triggered();

     void on_actionResize_triggered();
     void on_eraseButton_clicked();

     void on_actionSave_Image_Data_triggered();

     void on_actionOpen_Image_Data_triggered();

private:
     Toolset _toolset;
     MainDrawingWidget *mainDrawingWidget;

protected:
     QString _colorShapeBoxColor;
     QString _colorBorderBoxColor;
     QColor _currentShapeColor = Qt::white;
     QColor _currentBorderColor = Qt::black;
     QPushButton *colorShapeBox;
     QPushButton *colorBorderBox;
     QPushButton *penButton;
     QPushButton *eraseButton;

};


#endif // MAINWINDOW_H
