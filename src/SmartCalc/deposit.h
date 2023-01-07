#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <locale.h>

#include <QDialog>

extern "C" {
#include "SmartCalc_v1_0.h"
}

namespace Ui {
class deposit;
}

class deposit : public QDialog
{
    Q_OBJECT

public:
    explicit deposit(QWidget *parent = nullptr);
    ~deposit();

private slots:
    void on_pushButton_exit_clicked();
    void on_pushButton_calculate_clicked();

private:
    Ui::deposit *ui;
};

#endif // DEPOSIT_H
