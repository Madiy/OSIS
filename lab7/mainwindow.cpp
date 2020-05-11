#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ButtonAdd_clicked()
{
    QString text=ui->lineEdit->text();
    int count=ui->listWidget->count();
    for ( int i=0;i<count;i++){
        if(ui->listWidget->item(i)->text().compare(text)==0)
        {
            return;
        }
    }
    ui->listWidget->addItem(text);

}

void MainWindow::on_ButtonToRight_clicked()
{
    QList<QListWidgetItem*> items_1=ui->listWidget->selectedItems();
    int count_1 = items_1.count();
    for(int i=0;i<count_1;i++)
    {
        QString text=items_1[i]->text();
        int count=ui->listWidget_2->count();
        bool isFinded=false;
        for ( int j=0;j<count;j++)
        {
            if(ui->listWidget_2->item(j)->text().compare(text)==0)
            {
                isFinded=true;
                break;
            }
        }
        if(!isFinded)
        {
            ui->listWidget_2->addItem(text);
        }
    }
}

void MainWindow::on_ButtonDelete_clicked()
{
    int currentRow_1=ui->listWidget->currentRow();

    int currentRow_2=ui->listWidget_2->currentRow();
    if(currentRow_1!=-1)
    {
        ui->listWidget->takeItem(currentRow_1);
    }
    if(currentRow_2!=-1)
    {
        ui->listWidget_2->takeItem(currentRow_2);
    }

}

void MainWindow::on_ButtonClear_clicked()
{
    ui->listWidget->clear();
    ui->listWidget_2->clear();
}
