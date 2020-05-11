#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <thread>

static int i = 0;
static bool isDraw = true;
static QPoint array[40];


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    timer->setInterval(20);
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTimeout()
{
    QPoint pos = QWidget::mapFromGlobal(QCursor::pos()) - QPoint(16,16);
    for (int i = 39; i >= 1; i--){
        array[i] = array[i-1];
    }
    array[0] = pos;

    repaint();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    if(isDraw)
    {
        QPainter *paint = new QPainter(this);

        paint->setPen(QPen(Qt::black, 0));
        //paint->setRenderHint(QPainter::Antialiasing, true);

        for ( int i =0; i < 40; i++){
            paint->drawText(array[i].x(), array[i].y(), 320, 32,0,"Может хватит уже?пж");
        }
        paint->end();
    }
}
