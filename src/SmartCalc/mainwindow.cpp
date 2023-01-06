#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowTitle("SmartCalc");
  ui->result->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(numbers()));
  connect(ui->pushButton_sum, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_bracket_open, SIGNAL(clicked()), this,
          SLOT(brackets()));
  connect(ui->pushButton_bracket_close, SIGNAL(clicked()), this,
          SLOT(brackets()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(brackets()));

  ui->pushButton_equal->setCheckable(true);
  ui->pushButton_dot->setCheckable(true);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::numbers() {
  QPushButton *button = (QPushButton *)sender();
  if (ui->pushButton_equal->isChecked() ||
      ui->result->text().contains("Error! Division by zero!") ||
      ui->result->text().contains("Error! in expression!") ||
      ui->result->text().contains("The number is infinity!") ||
      ui->result->text().contains("Error! x: data entered incorrectly") ||
      ui->result->text().contains("Sqrt,ln,log: cannot be less than zero!")) {
    ui->pushButton_equal->setChecked(false);
    ui->result->setText("");
  }
  QString new_lable;
  new_lable = (ui->result->text() + button->text());
  ui->result->setText(new_lable);
  ui->pushButton_dot->setChecked(true);
}

void MainWindow::operations() {
  QPushButton *button = (QPushButton *)sender();
  if (ui->result->text().contains("Error! Division by zero!") ||
      ui->result->text().contains("Error! in expression!") ||
      ui->result->text().contains("The number is infinity!") ||
      ui->result->text().contains("Error! x: data entered incorrectly") ||
      ui->result->text().contains("Sqrt,ln,log: cannot be less than zero!")) {
    ui->result->setText("");
  }
  if (button->text() == "mod") {
    ui->result->setText(ui->result->text() + " mod ");
  } else {
    ui->result->setText(ui->result->text() + button->text());
  }
  if (ui->pushButton_equal->isChecked()) {
    ui->pushButton_equal->setChecked(false);
  }
  ui->pushButton_dot->setChecked(false);
}

void MainWindow::brackets() {
  QPushButton *button = (QPushButton *)sender();
  if (ui->pushButton_equal->isChecked() ||
      ui->result->text().contains("Error! Division by zero!") ||
      ui->result->text().contains("Error! in expression!") ||
      ui->result->text().contains("The number is infinity!") ||
      ui->result->text().contains("Error! x: data entered incorrectly") ||
      ui->result->text().contains("Sqrt,ln,log: cannot be less than zero!")) {
    ui->pushButton_equal->setChecked(false);
    ui->result->setText("");
  }
  ui->result->setText(ui->result->text() + button->text());
  ui->pushButton_dot->setChecked(false);
}

void MainWindow::functions() {
  QPushButton *button = (QPushButton *)sender();
  if (ui->pushButton_equal->isChecked() ||
      ui->result->text().contains("Error! Division by zero!") ||
      ui->result->text().contains("Error! in expression!") ||
      ui->result->text().contains("The number is infinity!") ||
      ui->result->text().contains("Error! x: data entered incorrectly") ||
      ui->result->text().contains("Sqrt,ln,log: cannot be less than zero!")) {
    ui->pushButton_equal->setChecked(false);
    ui->result->setText("");
  }
  ui->result->setText(ui->result->text() + button->text() + "(");
  ui->pushButton_dot->setChecked(false);
}

void MainWindow::on_pushButton_equal_clicked() {
  QString str = ui->result->text();
  double x = 0;
  if (str.size() != 0 && !(str.contains("Error! Division by zero!")) &&
      !(str.contains("Error! in expression!")) &&
      !(str.contains("The number is infinity!")) &&
      !(str.contains("Error! x: data entered incorrectly")) &&
      !(str.contains("Sqrt,ln,log: cannot be less than zero!"))) {
    setlocale(LC_ALL, "C");
    if (ui->result->text().contains("x")) {
      input = new input_x(this);
      input->setModal(true);
      input->exec();
      QString value = input->value();

      bool ok;
      x = value.toDouble(&ok);
      if (!ok) {
        ui->result->setText("Error! x: data entered incorrectly");
        return;
      }
    }
  }
  ui->pushButton_equal->setChecked(true);
  QString label = ui->result->text();
  QByteArray text = label.toLocal8Bit();
  char *string = text.data();
  int error;
  double res = result_polish_notation(x, string, &error);
  if (error == 0) {
    ui->result->setText(QString::number(res, 'g', 15));
  } else if (error == 2) {
    ui->result->setText("Error! Division by zero!");
    ui->pushButton_dot->setChecked(false);
  } else if (error == 3) {
    ui->result->setText("The number is infinity!");
    ui->pushButton_dot->setChecked(false);
  } else if (error == 4) {
    ui->result->setText("Sqrt,ln,log: cannot be less than zero!");
    ui->pushButton_dot->setChecked(false);
  } else {
    ui->result->setText("Error! in expression!");
    ui->pushButton_dot->setChecked(false);
  }
}

void MainWindow::on_pushButton_delete_clicked() {
  QString str = ui->result->text();
  if (!(str.contains("Error! in expression!")) &&
      !(str.contains("Error! Division by zero!")) &&
      !(str.contains("The number is infinity!")) &&
      !(str.contains("Error! x: data entered incorrectly")) &&
      !(str.contains("Sqrt,ln,log: cannot be less than zero!"))) {
    if (str.endsWith("sqrt(") || str.endsWith("atan(") ||
        str.endsWith("acos(") || str.endsWith("asin(") ||
        str.endsWith(" mod ")) {
      str.remove(str.size() - 5, 5);
      ui->result->setText(str);
    } else if (str.endsWith("sin(") || str.endsWith("cos(") ||
               str.endsWith("tan(") || str.endsWith("log(")) {
      str.remove(str.size() - 4, 4);
      ui->result->setText(str);
    } else if (str.endsWith("ln(")) {
      str.remove(str.size() - 3, 3);
      ui->result->setText(str);
    } else {
      str.remove(str.size() - 1, 1);
      ui->result->setText(str);
    }
    ui->pushButton_equal->setChecked(false);
  }
}

void MainWindow::on_pushButton_delete_all_clicked() {
  ui->pushButton_equal->setChecked(false);
  ui->pushButton_dot->setChecked(false);
  ui->result->setText("");
}

void MainWindow::on_pushButton_dot_clicked() {
  if (!(ui->pushButton_dot->isChecked())) {
    if (ui->pushButton_equal->isChecked()) {
      ui->pushButton_equal->setChecked(false);
    }
    ui->result->setText(ui->result->text() + ".");
  }
  ui->pushButton_dot->setChecked(false);
}

void MainWindow::on_pushButton_credit_clicked() {
  credit_calc = new credit(this);
  credit_calc->setModal(true);
  credit_calc->exec();
}

void MainWindow::on_pushButton_graph_clicked() {
  QString str = ui->result->text();
  if (str.size() != 0 && !(str.contains("Error! Division by zero!")) &&
      !(str.contains("Error! in expression!")) &&
      !(str.contains("The number is infinity!")) &&
      !(str.contains("Error! x: data entered incorrectly")) &&
      !(str.contains("Sqrt,ln,log: cannot be less than zero!"))) {
    graph_input = new graph(this);
    graph_input->setExpression(ui->result->text());
    graph_input->setModal(true);
    graph_input->exec();
    ui->pushButton_equal->setChecked(true);
  }
}
