#ifndef TAMPILAN_H
#define TAMPILAN_H

#include <QMainWindow>
#include <QWidget>

class QPushButton;
class QLineEdit;

namespace Ui {
class tampilan;
}

class tampilan : public QMainWindow
{
    Q_OBJECT

public:
    explicit tampilan(QWidget *parent = 0);
    ~tampilan();

private slots:
    void on_simpanButton_clicked();
    void on_resetButton_clicked();
    void on_cariButton_clicked();

private:
    Ui::tampilan *ui;
};

#endif // TAMPILAN_H
