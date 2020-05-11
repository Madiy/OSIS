#include "secondwindow.h"
#include "ui_secondwindow.h"
#include <QPainter>

SecondWindow::SecondWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
    x = 0;
    y = 0;
}

SecondWindow::~SecondWindow()
{
    delete ui;
}

void SecondWindow::GetMessage(int figure, QColor* color, bool _isDraw)
{
    this->figure = figure;
    this->color = color;
    isDraw = _isDraw;
    repaint();
}

void SecondWindow::paintEvent(QPaintEvent *event)
{
    if(isDraw)
    {
        QPainter *paint = new QPainter(this);

        // Round One!!!
        QPointF points[4] = {
              QPointF(x, y+20),
              QPointF(x+20, y),
              QPointF(x, y-20),
              QPointF(x-20, y)
        };
        QPointF points2[10] = {
                QPointF(90, 0),
                QPointF(114, 70),
                QPointF(182, 71),
                QPointF(129, 112),
                QPointF(148, 181),
                QPointF(90, 142),
                QPointF(35, 181),
                QPointF(55, 112),
                QPointF(0, 71),
                QPointF(71, 71)
        };
        for(int i=0; i < 10; i++){
            points2[i] = QPoint(points2[i].x()/2+x, points2[i].y()/2 + y);
        }

        paint->setPen(QPen(Qt::black, 0));
        paint->setRenderHint(QPainter::Antialiasing, true);
        paint->setBrush(QBrush(*color, Qt::SolidPattern));

        switch(figure){
            case 1:
                paint->drawPolygon(points, 4);
                break;
            case 2:
                paint->drawRect(x-20/2, y-20/2, 20, 20);
                break;
            case 3:
                paint->drawEllipse(x-20/2, y-20/2, 20, 20);
                break;
            case 4:
                paint->drawPolygon(points2, 10);
        }

        paint->end();
    }
}
void SecondWindow::mousePressEvent(QMouseEvent *event)
{
    x = event->x();
    y = event->y();
}
