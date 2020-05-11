#include "mainwindow.h"
#include "ui_mainwindow.h"

int countOfPrimitives=0;
QList<QPoint> primitivesPoints;
QList<QRect> primitivesRects;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pixmapDraw("E:\\SC\\SP\\lab8\\Draw.png");
    QPixmap pixmapClear("E:\\SC\\SP\\lab8\\Clear.png");
    QIcon ButtonDrawIcon(pixmapDraw);
    QIcon ButtonClearIcon(pixmapClear);
    ui->ButtonDraw->setIcon(ButtonDrawIcon);
    ui->ButtonDraw->setIconSize(pixmapDraw.rect().size());
    ui->ButtonDraw->resize(pixmapDraw.rect().size());

    ui->ButtonClear->setIcon(ButtonClearIcon);
    ui->ButtonClear->setIconSize(pixmapClear.rect().size());
    ui->ButtonClear->resize(pixmapClear.rect().size());

    primitivesPoints = QList<QPoint>();
    for(int i=0;i<20;i++)
    {
        primitivesPoints.append(QPoint(20+20*(i%10),20+48*(i%7)));
    }
    primitivesRects = QList<QRect>();
    for(int i=0;i<20;i++)
    {
        primitivesRects.append(QRect(20+26*(i%14+2),100,10,20));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    if(countOfPrimitives!=0)
    {
       paint.setPen(QPen(Qt::blue, 2));
        for(int i=0;i<5;i++)
            paint.drawRect(primitivesPoints[i].x(),primitivesPoints[i].y(),20,10*i);
        paint.setPen(QPen(Qt::red, 2));
        for(int i=5;i<10;i++)
            paint.drawPie(primitivesRects[i],2,120);
        paint.setPen(QPen(Qt::green, 2));
        for(int i=10;i<15;i++)
            paint.drawLine(primitivesPoints[i],primitivesPoints[i+1]);
        paint.setPen(QPen(Qt::red, 4));
        for(int i=15;i<20;i++)
            paint.drawEllipse(primitivesRects[i]);
    }
}


void MainWindow::on_ButtonDraw_clicked()
{
    countOfPrimitives=20;
    repaint();
}

void MainWindow::on_ButtonClear_clicked()
{
    countOfPrimitives=0;

    repaint();
}
