#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFont>
#include <QTimer>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer  *timer;
private slots:
    void on_ButtonStart_clicked();
    void on_ButtonStop_clicked();
    void on_EditText_textChanged();
    void onTimerMovingEvent();
};
#endif // MAINWINDOW_H
