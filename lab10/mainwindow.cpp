#include "mainwindow.h"
#include "ui_mainwindow.h"

static int figure=0;
static QColor color = Qt::white;
static bool isDraw = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    timer->setInterval(20);
    timer->start();
    sw = new SecondWindow();
    connect(this, &MainWindow::sendMessage, sw, &SecondWindow::GetMessage);
    sw->showNormal();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onTimeout()
{
    if(ui->radioButton->isChecked())
        figure = 1;
    else if(ui->radioButton_2->isChecked())
        figure = 3;
    else if(ui->radioButton_3->isChecked())
        figure = 4;
    else if(ui->radioButton_7->isChecked())
        figure = 2;

    if(ui->radioButton_4->isChecked())
        color = Qt::red;
    else if(ui->radioButton_5->isChecked())
        color = Qt::blue;
    else if(ui->radioButton_6->isChecked())
        color = Qt::green;

    isDraw = ui->checkBox->isChecked();

    emit sendMessage(figure, &color, isDraw);
}
