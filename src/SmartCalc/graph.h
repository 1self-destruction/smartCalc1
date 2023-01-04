#ifndef GRAPH_H
#define GRAPH_H

#include <locale.h>

#include <QDialog>
#include <QVector>

extern "C" {
#include "SmartCalc_v1_0.h"
}

namespace Ui {
class graph;
}

class graph : public QDialog {
  Q_OBJECT

 public:
  explicit graph(QWidget *parent = nullptr);
  ~graph();
  void showEvent(QShowEvent *);
  void draw_graph();
  void setExpression(QString Expression);
  QString Expression;

 private slots:
  void on_pushButton_Close_clicked();
  void on_pushButton_ok_clicked();

 private:
  Ui::graph *ui;
  double xBegin = -10, xEnd = 10, yBegin = -10, yEnd = 10;
  int pixelX;
  QVector<double> x, y;
};

#endif  // GRAPH_H
