#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent * );
    ~MainWindow();

private slots:
    void on_ButtonDraw_clicked();

    void on_ButtonClear_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
