#include "graph.h"

#include "ui_graph.h"

graph::graph(QWidget *parent) : QDialog(parent), ui(new Ui::graph) {
  ui->setupUi(this);
  setWindowTitle("Graph");
  QLinearGradient plotGradient;
  plotGradient.setStart(0, 0);
  plotGradient.setFinalStop(0, 350);
  plotGradient.setColorAt(0, QColor(50, 50, 50));
  plotGradient.setColorAt(1, QColor(30, 30, 30));
  ui->widget->setBackground(plotGradient);
  ui->widget->xAxis->setBasePen(QPen(Qt::blue, 1));
  ui->widget->yAxis->setBasePen(QPen(Qt::blue, 1));
  ui->widget->xAxis->setTickLabelColor(Qt::white);
  ui->widget->yAxis->setTickLabelColor(Qt::white);
  ui->widget->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
  ui->widget->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
  ui->widget->xAxis->ticker()->setTickCount(10);
  ui->widget->yAxis->ticker()->setTickCount(10);
  ui->widget->xAxis->setTickPen(QPen(Qt::red, 1));
  ui->widget->yAxis->setTickPen(QPen(Qt::red, 1));
  ui->widget->xAxis->grid()->setPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
  ui->widget->yAxis->grid()->setPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));

  ui->inputX1->setText(QString::number(xBegin));
  ui->inputX2->setText(QString::number(xEnd));
  ui->inputY1->setText(QString::number(yBegin));
  ui->inputY2->setText(QString::number(yEnd));
}

graph::~graph() { delete ui; }

void graph::on_pushButton_Close_clicked() { this->close(); }

void graph::setExpression(QString Expression) { this->Expression = Expression; }

void graph::draw_graph() {
  setlocale(LC_ALL, "C");
  QString Style =
      "QLineEdit {\
                        background-color: rgb(70, 0, 0);\
                        color: white;\
                        border-radius: 10px;\
                        border: 1 solid red;\
                      }";
  QString StyleSet =
      "QLineEdit {\
                            background-color: rgb(30, 30, 30);\
                            color: white;\
                            border-radius: 10px;\
                          }\
                          QLineEdit:focus {\
                              border: 1px solid rgb(0, 200, 255);\
                              background-color: rgb(0, 20, 26);\
                          }";
  bool ok1, ok2, ok3, ok4;
  xBegin = ui->inputX1->text().toDouble(&ok1);
  xEnd = ui->inputX2->text().toDouble(&ok2);
  yBegin = ui->inputY1->text().toDouble(&ok3);
  yEnd = ui->inputY2->text().toDouble(&ok4);
  if (ok1 && ok2 && ok3 && ok4) {
    ui->inputX1->setStyleSheet(StyleSet);
    ui->inputX2->setStyleSheet(StyleSet);
    ui->inputY1->setStyleSheet(StyleSet);
    ui->inputY2->setStyleSheet(StyleSet);
    ui->widget->xAxis->setRange(xBegin, xEnd);
    ui->widget->yAxis->setRange(yBegin, yEnd);
    pixelX = ui->widget->xAxis->axisRect()->width();
    QByteArray text = Expression.toLocal8Bit();
    char *stringExpression = text.data();
    int error;
    cordinate *graph_points =
        graph_output_points(xBegin, xEnd, pixelX, stringExpression, &error);
    if (error == 0) {
      for (int i = 0; i < pixelX; i++) {
        x.push_back(graph_points[i].x);
        y.push_back(graph_points[i].y);
      }
      ui->widget->addGraph();
      ui->widget->graph(0)->addData(x, y);
      ui->widget->graph(0)->setPen(QPen(Qt::red));
      ui->widget->replot();
      ui->widget->setInteraction(QCP::iRangeZoom, true);
      ui->widget->setInteraction(QCP::iRangeDrag, true);
      ui->label->setWordWrap(true);
      ui->label->setText(Expression);
      free(graph_points);
    } else if (error == 1) {
      ui->label->setText("Error! in expression!");
    } else if (error == 2) {
      ui->label->setText("Error! Division by zero!");
    } else if (error == 3) {
      ui->label->setText("The number is infinity!");
    }
  } else {
    if (!ok1) {
      ui->inputX1->setStyleSheet(Style);
      ui->inputX1->setFocus();
    } else {
      ui->inputX1->setStyleSheet(StyleSet);
    }
    if (!ok2) {
      ui->inputX2->setStyleSheet(Style);
      ui->inputX2->setFocus();
    } else {
      ui->inputX2->setStyleSheet(StyleSet);
    }
    if (!ok3) {
      ui->inputY1->setStyleSheet(Style);
      ui->inputY1->setFocus();
    } else {
      ui->inputY1->setStyleSheet(StyleSet);
    }
    if (!ok4) {
      ui->inputY2->setStyleSheet(Style);
      ui->inputY2->setFocus();
    } else {
      ui->inputY2->setStyleSheet(StyleSet);
    }
  }
}

void graph::showEvent(QShowEvent *) { draw_graph(); }

void graph::on_pushButton_ok_clicked() { draw_graph(); }
