#include "mainwindow.h"
#include "ui_mainwindow.h"
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
#include <QDataStream>
#include <QInputDialog>

extern std::vector<Shape> _shapeFromIndex;
extern Toolset myToolset;
bool _penButtonChecked;
bool _eraseButtonChecked;
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




    mainDrawingWidget = new MainDrawingWidget;
    setCentralWidget(mainDrawingWidget);
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

    penButton = new QPushButton(this);
    ui->leftToolBar->addWidget(penButton);
    penButton->setCheckable(true);
    QPixmap pixPen(":/new/Resources/resource/pen.png");
    QIcon penIcon(pixPen);
    penButton->setIcon(penIcon);
    penButton->setIconSize(QSize(32, 32));


    eraseButton = new QPushButton(this);
    ui->leftToolBar->addWidget(eraseButton);
    eraseButton->setCheckable(true);
    QPixmap pixEraser(":/new/Resources/resource/eraser.png");
    QIcon eraserIcon(pixEraser);
    eraseButton->setIcon(eraserIcon);
    eraseButton->setIconSize(QSize(32, 32));

    connect(colorShapeBox, SIGNAL(clicked()), this, SLOT(on_actionColorpicker_triggered()));
    connect(colorBorderBox, SIGNAL(clicked()), this, SLOT(on_actionBorderColor_triggered()));
    connect(penButton, SIGNAL(clicked()), this, SLOT(on_penButton_clicked()));
    connect(eraseButton, SIGNAL(clicked()), this, SLOT(on_eraseButton_clicked()));
    connect(borderSizeBox, SIGNAL(clicked()), this, SLOT(on_actionBorderSize_triggered()));

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
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save image"), "", tr("PNG file (*.png)"));

    if (fileName.isEmpty())
        return;

    QImage image(centralWidget()->size(), QImage::Format_ARGB32);
    QPainter painter(&image);
    centralWidget()->render(&painter);
    image.save(fileName);
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"), QDir::currentPath());

    if (!fileName.isEmpty())
        mainDrawingWidget->openImage(fileName);
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

void MainWindow::on_penButton_clicked()
{
    if(penButton->isChecked()){
        eraseButton->setChecked(false);
        _penButtonChecked = true;
        _eraseButtonChecked = false;
    }else{
        _penButtonChecked = false;
    }
}

void MainWindow::on_eraseButton_clicked()
{
    if(eraseButton->isChecked()){
        penButton->setChecked(false);
        _eraseButtonChecked = true;
        _penButtonChecked = false;
    }else{
        _eraseButtonChecked = false;
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

void MainWindow::on_actionColorfill_triggered()
{
    myToolset.changeToolset(Toolset::colorFillMode);
}

void MainWindow::on_actionPipett_triggered()
{
    myToolset.changeToolset(Toolset::pipettMode);

}

void MainWindow::on_actionSave_Image_Data_triggered()
{
    QString fileN = QFileDialog::getSaveFileName(this, tr("Save image data"), "", tr("TXT file (*.txt)"));
    QDataStream dS;
    QFile fileOut;
    Shape shape;
    fileOut.setFileName(fileN);

    if(fileOut.open(QIODevice::WriteOnly)){
        dS.setDevice(&fileOut);
        dS.setVersion(QDataStream::Qt_5_9);

        for(unsigned long i = 0; i<_shapeFromIndex.size(); i++){
            shape = _shapeFromIndex[i];
            dS << shape;
        }
    }
    fileOut.flush();
    fileOut.close();
}

void MainWindow::on_actionOpen_Image_Data_triggered()
{
    QString fileN = QFileDialog::getOpenFileName(this, tr("Open image data"), "", tr("TXT file (*.txt)"));
    QDataStream dS;
    QFile fileIn;
    Shape shape;
    fileIn.setFileName(fileN);
    if(fileIn.open(QIODevice::ReadOnly)){

        dS.setDevice(&fileIn);
        dS.setVersion(QDataStream::Qt_5_9);

            while(!fileIn.atEnd()){
                dS >> shape;
                Shape newShape = shape;
                _shapeFromIndex.push_back(newShape);
                update();
           }
    fileIn.close();
    }
}


