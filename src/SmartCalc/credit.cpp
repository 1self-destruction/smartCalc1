#include "credit.h"

#include "ui_credit.h"

credit::credit(QWidget *parent) : QDialog(parent), ui(new Ui::credit) {
  ui->setupUi(this);
  setWindowTitle("Credit calculator");

  ui->radioButton_annuity->setChecked(true);
  ui->label_result_4->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
  ui->label_result_3->setAlignment(Qt::AlignVCenter | Qt::AlignCenter);
  ui->label_result_2->setAlignment(Qt::AlignVCenter | Qt::AlignCenter);
  ui->label_result_1->setAlignment(Qt::AlignVCenter | Qt::AlignCenter);
  ui->label_calculation_results->setAlignment(Qt::AlignVCenter |
                                              Qt::AlignCenter);
}

credit::~credit() { delete ui; }

void credit::on_pushButton_exit_clicked() { this->close(); }

void credit::on_pushButton_calculate_clicked() {
  QString Style =
      "QLineEdit {\
                        background-color: rgb(30, 30, 30);\
                        color: white;\
                        border-radius: 10px;\
                      }\
                      QLineEdit:focus {\
                          border: 1px solid rgb(0, 200, 255);\
                          background-color: rgb(0, 20, 26);\
                      }";
  QString SetStyle =
      "QLineEdit {\
                            background-color: rgb(70, 0, 0);\
                            color: white;\
                            border-radius: 10px;\
                            border: 1 solid red;\
                          }";
  QString StylBar =
      "QDialog {\
                            background-color: rgb(0, 0, 0);\
                        }\
                        QScrollArea {\
                            border: none;\
                        }\
                        QScrollBar:vertical {\
                            width: 0px;\
                        }";
  QString SetStyleBar =
      "QDialog {\
                            background-color: rgb(0, 0, 0);\
                         }\
                         QScrollArea {\
                            border: none;\
                         }\
                         QScrollBar:Vertical {\
                            background-color: rgb(50, 50, 50);\
                            border: none;\
                            width: 13px;\
                            border-radius: 5px;\
                            margin: 5px 0 5px 0;\
                         }\
                         QScrollBar::handle:vertical {\
                             background-color: rgb(80, 80, 122);\
                             min-height: 30px;\
                             border-radius: 5px;\
                         }\
                         QScrollBar::handle:vertical:hover{	\
                             background-color: rgb(255, 0, 127);\
                         }\
                         QScrollBar::handle:vertical:pressed {\
                             background-color: rgb(185, 0, 92);\
                         }\
                         QScrollBar::sub-line:vertical {\
                             border: none;\
                             background-color: rgb(59, 59, 90);\
                             height: 15px;\
                             border-top-left-radius: 5px;\
                             border-top-right-radius: 5px;\
                             subcontrol-position: top;\
                         }\
                         QScrollBar::sub-line:vertical:hover {\
                             background-color: rgb(255, 0, 127);\
                         }\
                         QScrollBar::sub-line:vertical:pressed {\
                             background-color: rgb(185, 0, 92);\
                         }\
                         QScrollBar::add-line:vertical {\
                             border: none;\
                             background-color: rgb(59, 59, 90);\
                             height: 15px;\
                             border-bottom-left-radius: 5px;\
                             border-bottom-right-radius: 5px;\
                             subcontrol-position: bottom;\
                         }\
                         QScrollBar::add-line:vertical:hover {\
                             background-color: rgb(255, 0, 127);\
                         }\
                         QScrollBar::add-line:vertical:pressed {\
                             background-color: rgb(185, 0, 92);\
                         }\
                         QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {\
                             background: none;\
                         }\
                         QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {\
                             background: none;\
                         }";
  bool ok1, ok2, ok3;
  double amount, term, rate;
  QString Amount = ui->lineEdit_1->text();
  QString Term = ui->lineEdit_2->text();
  QString Rate = ui->lineEdit_3->text();
  amount = ui->lineEdit_1->text().toDouble(&ok1);
  term = ui->lineEdit_2->text().toInt(&ok2);
  rate = ui->lineEdit_3->text().toDouble(&ok3);
  if (!ok1 || !ok2 || !ok3) {
    if (!ok1) {
      ui->lineEdit_1->setStyleSheet(SetStyle);
    } else {
      ui->lineEdit_1->setStyleSheet(Style);
    }
    if (!ok2) {
      ui->lineEdit_2->setStyleSheet(SetStyle);
    } else {
      ui->lineEdit_2->setStyleSheet(Style);
    }
    if (!ok3) {
      ui->lineEdit_3->setStyleSheet(SetStyle);
    } else {
      ui->lineEdit_3->setStyleSheet(Style);
    }
    ui->label_result_1->setText("");
    ui->label_result_2->setText("");
    ui->label_result_3->setText("");
    ui->label_result_4->setText("");
    ui->label_monthly_payment->setText("");
    ui->label_calculation_results->setText("");
    ui->label_overpayment_loan->setText("");
    ui->label_total_payment->setText("");
    this->setStyleSheet(StylBar);
  } else {
    setlocale(LC_ALL, "C");
    ui->lineEdit_1->setStyleSheet(Style);
    ui->lineEdit_2->setStyleSheet(Style);
    ui->lineEdit_3->setStyleSheet(Style);
    ui->label_result_4->setText("");
    this->setStyleSheet(StylBar);
    ui->label_monthly_payment->setText("Monthly payment:");
    ui->label_calculation_results->setText("Calculation results");
    ui->label_overpayment_loan->setText("Overpayment on a loan:");
    ui->label_total_payment->setText("Total payment:");
    if (ui->radioButton_annuity->isChecked()) {
      QString credit_expression = "(";
      credit_expression.append(Amount);
      credit_expression.append("*");
      credit_expression.append(Rate);
      credit_expression.append("/(12*100))/(1-(1+");
      credit_expression.append(Rate);
      credit_expression.append("/(12*100))^-");
      credit_expression.append(Term);
      credit_expression.append(")");
      QByteArray text = credit_expression.toLocal8Bit();
      char* string = text.data();
      int error;
      double res = result_polish_notation(0, string, &error);
      if (error == 0) {
        QString resString = QString::number(res, 'f', 2);
        ui->label_result_1->setText(resString);
        credit_expression = resString;
        credit_expression.append("*");
        credit_expression.append(Term);
        text = credit_expression.toLocal8Bit();
        string = text.data();
        res = result_polish_notation(0, string, &error);
        if (error == 0) {
          QString resString = QString::number(res, 'f', 2);
          ui->label_result_3->raise();
          ui->label_result_3->setText(resString);
          credit_expression = resString;
          credit_expression.append("-");
          credit_expression.append(Amount);
          text = credit_expression.toLocal8Bit();
          string = text.data();
          res = result_polish_notation(0, string, &error);
          if (error == 0) {
            ui->label_result_2->setText(QString::number(res, 'f', 2));
          } else {
            ui->label_calculation_results->setText("Error!");
            ui->label_result_1->setText("");
            ui->label_result_2->setText("");
            ui->label_result_3->setText("");
            ui->label_result_4->setText("");
            ui->label_monthly_payment->setText("");
            ui->label_overpayment_loan->setText("");
            ui->label_total_payment->setText("");
          }
        } else {
          ui->label_calculation_results->setText("Error!");
          ui->label_result_1->setText("");
          ui->label_result_2->setText("");
          ui->label_result_3->setText("");
          ui->label_result_4->setText("");
          ui->label_monthly_payment->setText("");
          ui->label_overpayment_loan->setText("");
          ui->label_total_payment->setText("");
        }
      } else {
        ui->label_calculation_results->setText("Error!");
        ui->label_result_1->setText("");
        ui->label_result_2->setText("");
        ui->label_result_3->setText("");
        ui->label_result_4->setText("");
        ui->label_monthly_payment->setText("");
        ui->label_overpayment_loan->setText("");
        ui->label_total_payment->setText("");
      }
    } else {
      ui->label_monthly_payment->setText("Total payment:");
      ui->label_calculation_results->setText("Calculation results");
      ui->label_overpayment_loan->setText("Overpayment on a loan:");
      ui->label_total_payment->setText("Monthly payment:");
      QString credit_expression;
      QString resultStr = "";
      QString principal_payment = QString::number(amount / term, 'f', 2);
      double total_paid = 0;
      for (int i = 0; i < term; i++) {
        credit_expression = Amount;
        credit_expression.append("/");
        credit_expression.append(Term);
        credit_expression.append("+");
        credit_expression.append("(");
        credit_expression.append(Amount);
        credit_expression.append("-(");
        credit_expression.append(principal_payment);
        credit_expression.append("*");
        QString im = QString::number(i, 'g', 20);
        credit_expression.append(im);
        credit_expression.append("))*(");
        credit_expression.append(Rate);
        credit_expression.append("/100)/12");
        QByteArray text = credit_expression.toLocal8Bit();
        char* string = text.data();
        int error;
        double res = result_polish_notation(0, string, &error);
        total_paid += res;
        resultStr.append(QString::number(i + 1, 'g', 20));
        resultStr.append(":        ");
        resultStr.append(QString::number(res, 'f', 2));
        resultStr.append("\n");
      }
      this->setStyleSheet(SetStyleBar);
      ui->label_result_1->setText(QString::number(total_paid, 'f', 2));
      ui->scrollArea->raise();
      ui->label_result_4->setText(resultStr);
      double res_overpament = total_paid - amount;
      ui->label_result_2->setText(QString::number(res_overpament, 'f', 2));
    }
  }
}
