#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "maindrawingwidget.h"
#include <QDebug>
#include "shape.h"
#include <QFileDialog>
#include <QPainter>
#include <QLabel>
#include <QDesktopWidget>
#include <QTextStream>
#include <QColorDialog>
#include <QColor>
#include <QPushButton>
#include <QInputDialog>

extern std::vector<Shape> _shapeFromIndex;
QColor _currentShapeColor = Qt::white;
QColor _currentBorderColor = Qt::black;
int _currentBorderSize = 3;
QString _colorShapeBoxColor;
QString _colorBorderBoxColor;
QPushButton *colorShapeBox;
QPushButton *colorBorderBox;
QPushButton *borderSizeBox;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

        createButtons();
        connect(colorShapeBox, SIGNAL(clicked()), this, SLOT(on_actionColorpicker_triggered()));
        connect(colorBorderBox, SIGNAL(clicked()), this, SLOT(on_actionBorderColor_triggered()));
        connect(borderSizeBox, SIGNAL(clicked()), this, SLOT(on_actionBorderSize_triggered()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createButtons(){
    //Creates label above Color shape box
    shapeColorLabel = new QLabel(this);
    ui->rightToolBar->addWidget(shapeColorLabel);
    shapeColorLabel->setText("Shape Color:");

    colorShapeBox = new QPushButton(this);
    ui->rightToolBar->addWidget(colorShapeBox);
    colorShapeBox->setMinimumHeight(10);
    colorShapeBox->setMinimumWidth(32);

    borderColorLabel = new QLabel(this);
    ui->rightToolBar->addWidget(borderColorLabel);
    borderColorLabel->setText("Border Color:");


    //Creates Border Color box
    colorBorderBox = new QPushButton(this);
    ui->rightToolBar->addWidget(colorBorderBox);
    colorBorderBox->setMinimumHeight(10);
    colorBorderBox->setMinimumWidth(32);

    borderSizeLabel = new QLabel(this);
    ui->rightToolBar->addWidget(borderSizeLabel);
    borderSizeLabel->setText("Border Size:");


    //skapar bordersize button
    borderSizeBox = new QPushButton(this);
    ui->rightToolBar->addWidget(borderSizeBox);
    borderSizeBox->setMinimumHeight(10);
    borderSizeBox->setMinimumWidth(32);
    QString borderSize = QString::number(_currentBorderSize);
    borderSizeBox->setText(borderSize);
}

void MainWindow::on_actionSquare_triggered()
{
    Shape square(Shape::rectangle, QRect(100,100,100,100), _currentBorderSize, _currentShapeColor, _currentBorderColor);
    _shapeFromIndex.push_back(square);
    update();
}

void MainWindow::on_actionCircle_triggered()
{
    Shape circle(Shape::ellipse, QRect(100,100,100,100), _currentBorderSize, _currentShapeColor, _currentBorderColor);
    _shapeFromIndex.push_back(circle);
    update();
}

void MainWindow::on_actionTriangle_triggered()
{
    Shape triangle(Shape::triangle, QRect(100,100,100,100), _currentBorderSize, _currentShapeColor, _currentBorderColor);
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

void MainWindow::on_actionBorderSize_triggered()
{
    bool ok;
    int borderSizeTest = QInputDialog::getInt(this, tr("Border Size"),
                                              tr(" "), _currentBorderSize, 0, 50, 1, &ok);

    _currentBorderSize = borderSizeTest;
    QString borderSize = QString::number(_currentBorderSize);
    borderSizeBox->setText(borderSize);


}

void MainWindow::on_actionMove_triggered()
{
    _toolset.changeToolset(Toolset::moveMode);
}

void MainWindow::on_actionResize_triggered()
{
    _toolset.changeToolset(Toolset::resizeMode);
}

void MainWindow::on_actionColor_fill_triggered()
{
    _toolset.changeToolset(Toolset::colorFill);
}
