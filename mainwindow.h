#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "maindrawingwidget.h"
#include "shape.h"
#include <QPushButton>
#include "toolset.h"
#include <QLabel>

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

     QLabel *shapeColorLabel;
     QLabel *borderColorLabel;
     QLabel *borderSizeLabel;
     void createButtons();

private slots:
     void on_actionSquare_triggered();
     void on_actionCircle_triggered();
     void on_actionTriangle_triggered();
     void on_actionSave_triggered();
     void on_actionOpen_triggered();
     void on_actionColorpicker_triggered();
     void on_actionBorderColor_triggered();
     void on_actionBorderSize_triggered();



     void on_actionMove_triggered();

     void on_actionResize_triggered();

     void on_actionColor_fill_triggered();

private:
     Toolset _toolset;

protected:


};

#endif // MAINWINDOW_H
