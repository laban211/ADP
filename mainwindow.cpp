#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "maindrawingwidget.h"
#include "shape.h"
#include <QFileDialog>
#include <QPainter>
#include <QLabel>
#include <QDesktopWidget>
#include <QTextStream>
#include <QColorDialog>
#include <QColor>
#include <QPushButton>

extern std::vector<Shape> _shapeFromIndex;

extern Toolset myToolset;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
        //Creates Shape Color box
        colorShapeBox = new QPushButton(this);
        ui->rightToolBar->addWidget(colorShapeBox);
        colorShapeBox->setText("Shape color");
        //Creates Border Color box
        colorBorderBox = new QPushButton(this);
        ui->rightToolBar->addWidget(colorBorderBox);
        colorBorderBox->setText("Border color");


        connect(colorShapeBox, SIGNAL(clicked()), this, SLOT(on_actionColorpicker_triggered()));
        connect(colorBorderBox, SIGNAL(clicked()), this, SLOT(on_actionBorderColor_triggered()));

        //Allocate memory for object
        //_toolset = new Toolset;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSquare_triggered()
{
    Shape square(Shape::rectangle, QRect(100,100,100,100), 3, _currentShapeColor, _currentBorderColor);
    _shapeFromIndex.push_back(square);
    update();
}

void MainWindow::on_actionCircle_triggered()
{
    Shape circle(Shape::ellipse, QRect(100,100,100,100), 3, _currentShapeColor, _currentBorderColor);
    _shapeFromIndex.push_back(circle);
    update();
}

void MainWindow::on_actionTriangle_triggered()
{
    Shape triangle(Shape::triangle, QRect(100,100,100,100), 3, _currentShapeColor, _currentBorderColor);
    _shapeFromIndex.push_back(triangle);
    update();
}

void MainWindow::on_actionSave_triggered()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save image"), "", tr("PNG file (*.png)"));

    if (path.isEmpty())
        return;

    QImage image(centralWidget()->size(), QImage::Format_ARGB32);
    QPainter painter(&image);
    centralWidget()->render(&painter);
    image.save(path);
}

void MainWindow::on_actionOpen_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open image"), "", tr("PNG file (*.png)"));
    if(path.isEmpty())
        return;

    QPixmap image(path);
    QLabel *label = new QLabel(centralWidget());
    label->setPixmap(image);
    label->show();

}

void MainWindow::on_actionColorpicker_triggered()
{

    QColor colorShapeTest = QColorDialog::getColor();

    if(colorShapeTest.isValid()){

    _currentShapeColor = colorShapeTest;
    _colorShapeBoxColor = QString("background-color: %1").arg(_currentShapeColor.name());
    colorShapeBox->setStyleSheet(_colorShapeBoxColor);
    }
}

void MainWindow::on_actionBorderColor_triggered()
{
    QColor colorBorderTest = QColorDialog::getColor();

    if(colorBorderTest.isValid()){
    _currentBorderColor = colorBorderTest;
    _colorBorderBoxColor = QString("background-color: %1").arg(_currentBorderColor.name());
    colorBorderBox->setStyleSheet(_colorBorderBoxColor);
    }

}

void MainWindow::on_actionMove_triggered()
{
    myToolset.changeToolset(Toolset::moveMode);
}

void MainWindow::on_actionResize_triggered()
{
    myToolset.changeToolset(Toolset::resizeMode);
}
