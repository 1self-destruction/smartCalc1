#include "deposit.h"

#include "ui_deposit.h"

deposit::deposit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deposit) {
    ui->setupUi(this);
    setWindowTitle("DepositCalc");
    ui->label_calculation_results->setAlignment(Qt::AlignVCenter |
                                                Qt::AlignCenter);
    ui->label_interest_charges->setAlignment(Qt::AlignVCenter | Qt::AlignCenter);
    ui->label_result_3->setAlignment(Qt::AlignVCenter | Qt::AlignCenter);
    ui->label_result_2->setAlignment(Qt::AlignVCenter | Qt::AlignCenter);
    ui->label_result_1->setAlignment(Qt::AlignVCenter | Qt::AlignCenter);
    ui->label_tax_amount->setAlignment(Qt::AlignVCenter | Qt::AlignCenter);
    ui->label_amount_end_term->setAlignment(Qt::AlignVCenter | Qt::AlignCenter);
    ui->comboBox->addItem("Everyday", 0);
    ui->comboBox->addItem("Every week", 1);
    ui->comboBox->addItem("Monthly", 2);
    ui->comboBox->addItem("Quarterly", 3);
    ui->comboBox->addItem("Semiannually", 4);
    ui->comboBox->addItem("Yearly", 5);
    ui->comboBox->addItem("End of term", 6);
    ui->lineEdit_list_replenishment->setPlaceholderText("15:10000;30:15000;");
    ui->lineEdit_list_withdrawals->setPlaceholderText("15:1000;30:5000;");
}

deposit::~deposit() { delete ui; }

void deposit::on_pushButton_exit_clicked() { this->close(); }

void deposit::on_pushButton_calculate_clicked() {
    setlocale(LC_ALL, "C");
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
    QString deposiy_amount = ui->lineEdit_amount->text();
    QString period = ui->lineEdit_placement->text();
    QString rate = ui->lineEdit_rate->text();
    QString tax_rate = ui->lineEdit_tax_rate->text();
    QString replenishment = ui->lineEdit_list_replenishment->text();
    QString withdrawals = ui->lineEdit_list_withdrawals->text();
    QVariant p = ui->comboBox->itemData(ui->comboBox->currentIndex());
    bool ok1, ok2, ok3, ok4;
    int withdrawal_period = p.toInt();
    double amount_num = deposiy_amount.toDouble(&ok1);
    int period_num = period.toInt(&ok2);
    double rate_num = rate.toDouble(&ok3);
    double tax_rate_num = tax_rate.toDouble(&ok4);
    QByteArray text1 = replenishment.toLocal8Bit();
    char* replenishment_char = text1.data();
    QByteArray text2 = withdrawals.toLocal8Bit();
    char* withdrawals_char = text2.data();
    if (!ok1 || !ok2 || !ok3 || !ok4) {
      ui->label_result_1->setText("");
      ui->label_result_2->setText("");
      ui->label_result_3->setText("");
      ui->label_calculation_results->setText("");
      ui->label_interest_charges->setText("");
      ui->label_tax_amount->setText("");
      ui->label_amount_end_term->setText("");
      if (!ok1) {
        ui->lineEdit_amount->setStyleSheet(SetStyle);
      } else {
        ui->lineEdit_amount->setStyleSheet(Style);
      }
      if (!ok2) {
        ui->lineEdit_placement->setStyleSheet(SetStyle);
      } else {
        ui->lineEdit_placement->setStyleSheet(Style);
      }
      if (!ok3) {
        ui->lineEdit_rate->setStyleSheet(SetStyle);
      } else {
        ui->lineEdit_rate->setStyleSheet(Style);
      }
      if (!ok4) {
        ui->lineEdit_tax_rate->setStyleSheet(SetStyle);
      } else {
        ui->lineEdit_tax_rate->setStyleSheet(Style);
      }
    } else {
      ui->lineEdit_amount->setStyleSheet(Style);
      ui->lineEdit_placement->setStyleSheet(Style);
      ui->lineEdit_rate->setStyleSheet(Style);
      ui->lineEdit_tax_rate->setStyleSheet(Style);
      ui->label_calculation_results->setText("Calculation results");
      ui->label_interest_charges->setText("Interest charges");
      ui->label_tax_amount->setText("Tax amount");
      ui->label_amount_end_term->setText("Amount at the end of the term");

      int capitalization;
      if (ui->checkBox->isChecked()) {
        capitalization = 1;
      } else {
        capitalization = 0;
      }
      int error = 0;
      if (strlen(replenishment_char) == 0) {
        replenishment_char = NULL;
      }
      if (strlen(withdrawals_char) == 0) {
        withdrawals_char = NULL;
      }

      deposit_calculation_result* result = deposit_result(
          amount_num, period_num, rate_num, tax_rate_num, withdrawal_period,
          capitalization, replenishment_char, withdrawals_char, &error);
      if (error > 0) {
        ui->lineEdit_list_replenishment->setStyleSheet(SetStyle);
        ui->lineEdit_list_withdrawals->setStyleSheet(SetStyle);
        ui->label_calculation_results->setText("");
        ui->label_interest_charges->setText("");
        ui->label_tax_amount->setText("");
        ui->label_amount_end_term->setText("");
        ui->label_result_1->setText("");
        ui->label_result_2->setText("");
        ui->label_result_3->setText("");
      } else {
        ui->lineEdit_list_replenishment->setStyleSheet(Style);
        ui->lineEdit_list_withdrawals->setStyleSheet(Style);
        ui->label_result_1->setText(
            QString::number(result->interest_charges, 'f', 2));
        ui->label_result_2->setText(QString::number(result->tax_amount, 'f', 2));
        ui->label_result_3->setText(
            QString::number(result->amount_end_term, 'f', 2));
      }

      if (result != NULL) {
        free(result);
      }
    }
}

