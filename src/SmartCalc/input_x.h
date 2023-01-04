#ifndef INPUT_X_H
#define INPUT_X_H

#include <QDialog>

namespace Ui {
class input_x;
}

class input_x : public QDialog {
  Q_OBJECT

 public:
  explicit input_x(QWidget *parent = nullptr);
  ~input_x();

  QString value();

 private slots:
  void on_pushButton_ok_clicked();

 private:
  Ui::input_x *ui;
};

#endif  // INPUT_X_H
