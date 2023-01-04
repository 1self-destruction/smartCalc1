#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <locale.h>

#include <QMainWindow>

#include "credit.h"
#include "graph.h"
#include "input_x.h"

extern "C" {
#include "SmartCalc_v1_0.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void numbers();
  void operations();
  void brackets();
  void functions();
  void on_pushButton_equal_clicked();
  void on_pushButton_delete_clicked();
  void on_pushButton_delete_all_clicked();
  void on_pushButton_dot_clicked();
  void on_pushButton_credit_clicked();
  void on_pushButton_graph_clicked();

 private:
  Ui::MainWindow *ui;
  input_x *input;
  credit *credit_calc;
  graph *graph_input;
};
#endif  // MAINWINDOW_H
