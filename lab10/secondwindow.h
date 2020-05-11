#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QDialog>
#include <QColor>
#include <QMouseEvent>
#include <QDebug>

namespace Ui {
class SecondWindow;
}

class SecondWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();
    void virtual paintEvent(QPaintEvent *event);
    void virtual mousePressEvent(QMouseEvent *event);
    int figure;
    QColor* color;
public slots:
    void GetMessage(int figure, QColor* color, bool isDraw);

private:
    Ui::SecondWindow *ui;
    bool isDraw = false;
    double x;
    double y;
};

#endif // SECONDWINDOW_H
