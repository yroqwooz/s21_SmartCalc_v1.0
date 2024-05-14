#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "plot_window.h"
#include <QDoubleValidator>
#include <QIntValidator>
#include <QMessageBox>

extern "C" {
    #include "lib/s21_calc.h"
    #include "lib/s21_credit.h"
    #include "lib/s21_deposit.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionSmart_Calculator_triggered();

    void on_actionCredit_Calculator_triggered();

    void on_actionDeposit_Calculator_triggered();

    void digits_numbers();
    void on_pushButton_dot_clicked();
    void operations();
    void trigonometric();
    void brackets();
    void on_pushButton_clear_clicked();
    void on_pushButton_end_clicked();
    void on_pushButton_backspace_clicked();
//    void on_pushButton_sqrt_clicked();

    void on_pushButton_graphic_clicked();

    void on_pushButton_x_clicked();

    void connect_windows();

    void on_calc_credit_button_clicked();

    void setup_credit_tablet();
    void signals_and_slots();
    void fill_credit_tablet(CrList_t *head, int time_res);
    void plot_window_handler();
    void set_validators();
//    void on_pushButton_clicked();
    void set_LE_readonly();

    void on_calc_dep_button_clicked();

private:
    Ui::MainWindow *ui;
    graph *plot_graph;
    bool is_plot_exist = false;
    QDoubleValidator double_validator;
    QDoubleValidator double_validator_signed;
    QIntValidator int_validator;

signals:
    void plot_signal(const char *);
};
#endif // MAINWINDOW_H
