#ifndef CREDIT_H
#define CREDIT_H

#include <QDialog>

extern "C" {
#include "SmartCalc_v1_0.h"
}

namespace Ui {
class credit;
}

class credit : public QDialog {
  Q_OBJECT

 public:
  explicit credit(QWidget *parent = nullptr);
  ~credit();

 private slots:
  void on_pushButton_exit_clicked();
  void on_pushButton_calculate_clicked();

 private:
  Ui::credit *ui;
};

#endif  // CREDIT_H
