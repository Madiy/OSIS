#include "mainwindow.h"
#include "ui_mainwindow.h"

int deltaPos=10;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerMovingEvent()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTimerMovingEvent()
{
    ui->LabelMoved->move(ui->LabelMoved->x()+deltaPos,ui->LabelMoved->y());
    if (ui->LabelMoved->x() >ui->centralwidget->size().width()-ui->LabelMoved->width() || ui->LabelMoved->x() <0 )
    {
        deltaPos=-deltaPos;
    }
}

void MainWindow::on_ButtonStart_clicked()
{
    timer->start(75);
}

void MainWindow::on_ButtonStop_clicked()
{
    timer->stop();
}

void MainWindow::on_EditText_textChanged()
{
    QFont myFont("Times New Roman", 8);
    QString str(ui->EditText->text());

    //use QFontMetrics this way;
    QFont font("Times New Roman", 0);
    QFontMetrics fm(font);
    int pixelsWide = fm.width(str);
    int pixelsHigh = fm.height();

    ui->LabelMoved->resize(pixelsWide, pixelsHigh);
    ui->LabelMoved->setText(str);
}
