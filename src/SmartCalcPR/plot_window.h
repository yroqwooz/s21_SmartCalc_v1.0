#ifndef PLOT_H
#define PLOT_H

#include <string.h>

#include <QDialog>
#include <QDoubleValidator>
#include <QVector>
#include <iostream>

using namespace std;

namespace Ui {
class graph;
}

class graph : public QDialog {
    Q_OBJECT

public:
    explicit graph(QWidget *parent = nullptr);
    ~graph();

public slots:
    void plot_slot(const char *str);

private:
    Ui::graph *ui;
    // Plot
    double x_min, x_max, y_min, y_max;
    double h_step, x_temp;
    int N;
    QVector<double> x_vector, y_vector;
    char math_expression[255];
    string replace_x(char *amended_string, const string &x_name,
                     const string &x_value);
    void render_graph();
    bool is_set;
    QDoubleValidator m_doubleValidator;
    QDoubleValidator step_doubleValidator;

private slots:
    void set_default_values();
    void on_xmin_val_editingFinished();
    void on_xmax_val_editingFinished();
    void on_ymin_val_editingFinished();
    void on_ymax_val_editingFinished();
    void on_step_val_editingFinished();
//    void on_upd_val_clicked();
    void on_gen_plot_clicked();
};

#endif  // PLOT_H
