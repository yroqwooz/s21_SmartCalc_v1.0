#include "plot_window.h"

#include <QTextEdit>

#include "mainwindow.h"
#include "ui_plot_window.h"

graph::graph(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::graph),
      m_doubleValidator(-1000000, 1000000, 8, this),
      step_doubleValidator(0.0001, 20, 3, this) {
  ui->setupUi(this);
  is_set = false;

  QLocale locale(QLocale::English);
  m_doubleValidator.setNotation(QDoubleValidator::StandardNotation);
  step_doubleValidator.setNotation(QDoubleValidator::StandardNotation);
  m_doubleValidator.setLocale(locale);
  step_doubleValidator.setLocale(locale);
  ui->xmin_val->setValidator(&m_doubleValidator);
  ui->xmax_val->setValidator(&m_doubleValidator);
  ui->ymin_val->setValidator(&m_doubleValidator);
  ui->ymax_val->setValidator(&m_doubleValidator);
  ui->step_val->setValidator(&step_doubleValidator);
  set_default_values();

  x_min = ui->xmin_val->text().toDouble();
  x_max = ui->xmax_val->text().toDouble();
  y_min = ui->ymin_val->text().toDouble();
  y_max = ui->ymax_val->text().toDouble();
  h_step = ui->step_val->text().toDouble();
  x_temp = x_min;
  N = (x_max - x_min) / h_step + 2;

  ui->plotRender->addGraph();
  ui->plotRender->graph(0)->setData(x_vector, y_vector);
  ui->plotRender->yAxis->setRange(y_min, y_max);
  ui->plotRender->xAxis->setRange(x_min, x_max);

  ui->plotRender->setInteraction(QCP::iRangeZoom, true);
  ui->plotRender->setInteraction(QCP::iRangeDrag, true);
  ui->plotRender->replot();
}

graph::~graph() { delete ui; }

void graph::set_default_values() {
  ui->xmin_val->setText("-10");
  ui->xmax_val->setText("10");
  ui->ymin_val->setText("-10");
  ui->ymax_val->setText("10");
  ui->step_val->setText("0.1");
}

void graph::plot_slot(const char *str) {
  strncpy(math_expression, str, MAX_LEN);
  is_set = true;
  ui->plotRender->clearGraphs();
  render_graph();
}

void graph::render_graph() {
  N = (x_max - x_min) / h_step + 2;
  if (N > 1000000) {
    N = 1000000;
  }
  y_vector.clear();
  x_vector.clear();

  //  x_temp = x_min;

  char *ptr_temp = strchr(math_expression, 'l');
  if (ptr_temp != NULL) {
    if (*(++ptr_temp) == 'o') qDebug() << "FIND LOG";
    x_min = h_step;
  }

  x_temp = x_min;

  QPen my_pen;
  my_pen.setColor(QColor(12, 34, 123));
  my_pen.setWidthF(3);

  int error = 0;
  for (int i = 0; i < N && error == 0; i++) {
    double x_calc = 0;
    string temp = '(' + std::to_string(x_temp + i * h_step);
    temp.push_back(')');
    string amended_string = replace_x(math_expression, "x", temp);
    x_calc = s21_calculate_all(amended_string.c_str(), &error);
    if (x_calc > y_min && x_calc < y_max) {
      x_vector.push_back(x_min + i * h_step);
      y_vector.push_back(x_calc);
    }
  }
  ui->plotRender->addGraph();
  ui->plotRender->graph(0)->addData(x_vector, y_vector);
  ui->plotRender->graph(0)->setPen(my_pen);
  ui->plotRender->replot();
}

void graph::on_xmin_val_editingFinished() {
  if (is_set &&
      ui->xmin_val->text().toDouble() < ui->xmax_val->text().toDouble()) {
    x_min = ui->xmin_val->text().toDouble();
    ui->plotRender->clearGraphs();
    render_graph();
  }
}

void graph::on_xmax_val_editingFinished() {
  if (is_set &&
      ui->xmin_val->text().toDouble() < ui->xmax_val->text().toDouble()) {
    x_max = ui->xmax_val->text().toDouble();
    ui->plotRender->clearGraphs();
    render_graph();
  }
}

void graph::on_ymin_val_editingFinished() {
  if (is_set &&
      ui->ymin_val->text().toDouble() < ui->ymax_val->text().toDouble()) {
    y_min = ui->ymin_val->text().toDouble();
    ui->plotRender->clearGraphs();
    render_graph();
  }
}

void graph::on_ymax_val_editingFinished() {
  if (is_set &&
      ui->ymin_val->text().toDouble() < ui->ymax_val->text().toDouble()) {
    y_max = ui->ymax_val->text().toDouble();
    ui->plotRender->clearGraphs();
    render_graph();
  }
}

void graph::on_step_val_editingFinished() {
  if (is_set) {
    h_step = ui->step_val->text().toDouble();
    ui->plotRender->clearGraphs();
    render_graph();
  }
}

string graph::replace_x(char *source_string, const string &x_name,
                        const string &x_value) {
  size_t position = 0;
  string amended_string = source_string;
  while ((position = amended_string.find(x_name, position)) != string::npos) {
    amended_string.replace(position, x_name.length(), x_value);
    position += x_value.length();
  }

  return amended_string;
}

void graph::on_gen_plot_clicked() {
  x_min = ui->xmin_val->text().toDouble();
  x_max = ui->xmax_val->text().toDouble();
  y_min = ui->ymin_val->text().toDouble();
  y_max = ui->ymax_val->text().toDouble();
  h_step = ui->step_val->text().toDouble();
}
