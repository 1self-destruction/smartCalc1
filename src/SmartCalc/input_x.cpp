#include "input_x.h"

#include "ui_input_x.h"

input_x::input_x(QWidget *parent) : QDialog(parent), ui(new Ui::input_x) {
  ui->setupUi(this);
  setWindowTitle("Enter X...");
  ui->lineEdit->setFocus();
}

input_x::~input_x() { delete ui; }

QString input_x::value() { return ui->lineEdit->text(); }

void input_x::on_pushButton_ok_clicked() {
  QString SetStyle =
      "QLineEdit {\
                              background-color: rgb(70, 0, 0);\
                              color: white;\
                              border-radius: 10px;\
                              border: 1 solid red;\
                            }";
  bool ok;
  ui->lineEdit->text().toDouble(&ok);
  if (ok) {
    this->close();
  } else {
    ui->lineEdit->setStyleSheet(SetStyle);
  }
}
