#include "mainwindow.h"

#include <cstring>

#include "plot_window.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      double_validator_signed(-99999999999, 99999999999, 7, this),
      double_validator(0, 99999999999, 7, this),
      int_validator(0, 999, this) {
  ui->setupUi(this);

  plot_graph = new graph(this);

  setup_credit_tablet();
  set_validators();
  set_LE_readonly();

  QAction *buttonAction = new QAction(ui->pushButton_dot);
  buttonAction->setShortcuts({QKeySequence(","), QKeySequence(".")});
  ui->pushButton_dot->addAction(buttonAction);
  connect(buttonAction, &QAction::triggered, ui->pushButton_dot,
          &QPushButton::clicked);
  connect(ui->pushButton_dot, &QPushButton::clicked, this, []() {});
  signals_and_slots();
  connect_windows();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::plot_window_handler() {
  if (is_plot_exist == false) {
    plot_graph->show();
    plot_graph->setFixedSize(330, 460);
    plot_graph->move(this->x() - 330, this->y());
    is_plot_exist = true;
  } else {
    plot_graph->hide();
    is_plot_exist = false;
  }
}

void MainWindow::set_LE_readonly() {
  ui->total_pay_res->setReadOnly(true);
  ui->overpay_res->setReadOnly(true);
  ui->mounth_pay_res->setReadOnly(true);
  ui->percents_earned->setReadOnly(true);
  ui->tax_res->setReadOnly(true);
  ui->calced_income->setReadOnly(true);
  ui->x_res->setReadOnly(true);
}

void MainWindow::set_validators() {
  QLocale locale(QLocale::English);
  double_validator.setNotation(QDoubleValidator::StandardNotation);
  double_validator.setLocale(locale);
  int_validator.setLocale(locale);
  ui->sum_val->setValidator(&double_validator);
  ui->percent_val->setValidator(&double_validator);

  ui->dep_sum->setValidator(&double_validator);
  ui->percent_inter_dep->setValidator(&double_validator);
  ui->replenishments_dep->setValidator(&double_validator);
  ui->withdraws_dep->setValidator(&double_validator);
  ui->calced_income->setValidator(&double_validator);
  ui->time_val->setValidator(&int_validator);
  ui->time_val_dep->setValidator(&int_validator);
  ui->taxes_inter_dep->setValidator(&double_validator);

  ui->x_val->setValidator(&double_validator_signed);
}

void MainWindow::signals_and_slots() {
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(trigonometric()));
  connect(ui->pushButton_openBR, SIGNAL(clicked()), this, SLOT(brackets()));
  connect(ui->pushButton_endBR, SIGNAL(clicked()), this, SLOT(brackets()));
  connect(ui->pushButton_times, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(trigonometric()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(trigonometric()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(trigonometric()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(trigonometric()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(trigonometric()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(trigonometric()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(trigonometric()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(trigonometric()));
}

void MainWindow::on_actionSmart_Calculator_triggered() {
  ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_actionCredit_Calculator_triggered() {
  ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_actionDeposit_Calculator_triggered() {
  ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();

  QString new_label;
  new_label = ui->curr_num->text() + button->text();

  ui->curr_num->setText(new_label);
}

void MainWindow::on_pushButton_dot_clicked() {
  if (!(ui->curr_num->text().contains('.'))) {
    ui->curr_num->setText(ui->curr_num->text() + ".");
  }
}

void MainWindow::operations() {
  QPushButton *button = (QPushButton *)sender();
  QString main_label = ui->showresult->text();
  QString sub_label = ui->curr_num->text();
  main_label += sub_label;
  if (!main_label.isEmpty()) {
    QChar last_symb = main_label.back();
    if (last_symb == '+' || last_symb == '-' || last_symb == '*' ||
        last_symb == '/' || last_symb == '^' || last_symb == '%') {
      main_label.chop(1);
      if (!main_label.isEmpty()) {
        last_symb = main_label.back();
      }
    }
    if ((last_symb >= '0' && last_symb <= '9') || last_symb == ')' ||
        last_symb == 'x' ||
        ((last_symb == '(' || main_label.isEmpty()) &&
         (button->text() == '+' || button->text() == '-'))) {
      ui->showresult->setText(main_label + button->text());
      ui->curr_num->setText("");
    }

  } else if ((button->text() == '-' || button->text() == '+')) {
    main_label += button->text();
    ui->showresult->setText(main_label);
  }
}

void MainWindow::trigonometric() {
  QPushButton *button = (QPushButton *)sender();
  QString sub_label = ui->curr_num->text();

  sub_label += button->text() + '(';
  ui->curr_num->setText(sub_label);
}

void MainWindow::brackets() {
  QPushButton *button = (QPushButton *)sender();
  QString sub_label = ui->curr_num->text();
  QString main_label = ui->showresult->text();

  if (button->text() == '(') {
    if (sub_label.contains('(')) {
      ui->showresult->setText(main_label + sub_label);
      ui->curr_num->setText("");
    }
    ui->showresult->setText(main_label + sub_label);
    ui->curr_num->setText(button->text());
  }

  if (button->text() == ')' &&
      (main_label.count('(') + sub_label.count('(') > main_label.count(')'))) {
    ui->showresult->setText(main_label + sub_label + button->text());
    ui->curr_num->setText("");
  }
}

void MainWindow::on_pushButton_clear_clicked() {
  ui->showresult->setText("");
  ui->curr_num->setText("");
}

void MainWindow::on_pushButton_end_clicked() {
  QString main_label = ui->showresult->text();
  QString sub_label = ui->curr_num->text();
  if (!sub_label.isEmpty()) {
    main_label += sub_label;
    ui->showresult->setText(main_label);
    ui->curr_num->setText("");
  }
  if (!main_label.isEmpty()) {
    QChar last_char = main_label.back();
    if (last_char == '+' || last_char == '-' || last_char == '*' ||
        last_char == '/' || last_char == '%' || last_char == '^' ||
        last_char == '.') {
      main_label.chop(1);
      ui->showresult->setText(main_label);
    }
    int error = 0;
    main_label.replace(",", ".");
    if (main_label.contains("x")) {  // если есть х - рисуем график
      std::string str = main_label.toStdString();
      const char *expr = str.c_str();
      emit plot_signal(expr);

      if (ui->x_val->text().isEmpty() ==
          0) {  // Если есть х и значение для х - подставляем значение под х и
                // выводим в х_рес
        main_label.replace("x", '(' + ui->x_val->text() + ')');
        main_label.replace(",", ".");
        std::string str = main_label.toStdString();
        const char *expr = str.c_str();
        double res = s21_calculate_all(expr, &error);
        if (error == 0) {
          ui->x_res->setText(QString::number(res, 'g', 25));
        }
      }

    } else {  // в ином случае просто считаем
      std::string str = main_label.toStdString();
      const char *expr = str.c_str();
      double res = s21_calculate_all(expr, &error);
      qDebug() << expr;
      if (error == false) {
        ui->showresult->setText(QString::number(res, 'g', 25));
        ui->curr_num->setText("");
      }
    }
  }
}

void MainWindow::on_pushButton_backspace_clicked() {
  QString main_label;
  QString sub_label;
  main_label = ui->showresult->text();
  sub_label = ui->curr_num->text();
  if (sub_label.isEmpty()) {
    if (!main_label.isEmpty()) {
      main_label.chop(1);
      ui->showresult->setText(main_label);
    }
  } else {
    sub_label.chop(1);
    ui->curr_num->setText(sub_label);
  }
}

void MainWindow::connect_windows() {
  connect(this, &MainWindow::plot_signal, plot_graph, &graph::plot_slot);
}

void MainWindow::on_pushButton_graphic_clicked() {
  QString main_label = ui->showresult->text();
  QString sub_label = ui->curr_num->text();
  if (!sub_label.isEmpty()) {
    main_label.append(sub_label);
  }
  plot_window_handler();
}

void MainWindow::on_pushButton_x_clicked() {
  QPushButton *button = (QPushButton *)sender();
  QString sub_label = ui->curr_num->text();
  if (!sub_label.isEmpty()) {
    if (sub_label.back() != 'x') {
      ui->curr_num->setText(sub_label + button->text());
    }
  } else {
    ui->curr_num->setText(button->text());
  }
}

void MainWindow::setup_credit_tablet() {
  ui->tableWidget->setColumnWidth(0, 95);
  ui->tableWidget->setColumnWidth(1, 110);
  ui->tableWidget->setColumnWidth(2, 115);
}
void MainWindow::on_calc_credit_button_clicked() {
  if (ui->sum_val->text().isEmpty() == false &&
      ui->time_val->text().isEmpty() == false &&
      ui->percent_val->text().isEmpty() == false) {
    CrList_t *head = s21_CrList_create();
    double sum = ui->sum_val->text().toDouble();
    int time_res = ui->time_val->text().toDouble() *
                   pow(12, ui->time_scale->currentIndex());
    double percent = ui->percent_val->text().toDouble();
    bool type = ui->credit_type->currentIndex();

    ui->tableWidget->setRowCount(ui->time_val->text().toInt() *
                                 pow(12, ui->time_scale->currentIndex()));

    s21_credit_calculate(sum, time_res, percent, type, head);
    fill_credit_tablet(head, time_res);
    s21_CrList_remove(head);
  }
}

void MainWindow::fill_credit_tablet(CrList_t *head, int time_res) {
  CrList_t *ptr = head;
  int i = 0;
  for (i = 0; i < time_res; i++) {
    ptr = ptr->next;
    ui->tableWidget->insertRow(ui->tableWidget->rowCount() + 1);
    QTableWidgetItem *tbw_1 =
        new QTableWidgetItem(QString::number(ptr->payment, 'f', 2));
    QTableWidgetItem *tbw_2 =
        new QTableWidgetItem(QString::number(ptr->pay_debt, 'f', 2));
    QTableWidgetItem *tbw_3 =
        new QTableWidgetItem(QString::number(ptr->pay_percent, 'f', 2));
    QTableWidgetItem *tbw_4 =
        new QTableWidgetItem(QString::number(ptr->remaining, 'f', 2));
    ui->tableWidget->setItem(i, 0, tbw_1);
    ui->tableWidget->setItem(i, 1, tbw_2);
    ui->tableWidget->setItem(i, 2, tbw_3);
    ui->tableWidget->setItem(i, 3, tbw_4);
  }
  ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->total_pay_res->setText(QString::number(ptr->next->pay_percent, 'f', 2));
  ui->overpay_res->setText(QString::number(ptr->next->pay_debt, 'f', 2));
  if (ui->credit_type->currentIndex() == false) {
    ui->mounth_pay_res->setText(QString::number(ptr->next->payment, 'f', 2));
  } else {
    QString result_string = QString::number(head->next->payment, 'f', 2) +
                            " -- " + QString::number(ptr->payment, 'f', 2);
    ui->mounth_pay_res->setText(result_string);
  }
}

void MainWindow::on_calc_dep_button_clicked() {
  double sum = ui->dep_sum->text().toDouble();

  double interest_rate = ui->percent_inter_dep->text().toDouble();
  int time_dep = ui->time_val_dep->text().toInt();
  int mode_dep = ui->time_scale_dep->currentIndex();
  bool capitalization_dep = ui->is_capitalize->isChecked();
  double replenishments = ui->replenishments_dep->text().toDouble();
  double withdraws = ui->withdraws_dep->text().toDouble();

  double no_taxes_income =
      get_total_earned(&sum, time_dep, interest_rate, mode_dep,
                       capitalization_dep, replenishments, withdraws);
  double taxes_res =
      get_tax_amount(no_taxes_income, ui->taxes_inter_dep->text().toDouble());
  double with_taxes_income =
      get_total_amount(sum, no_taxes_income, taxes_res, capitalization_dep);

  ui->percents_earned->setText(QString::number(no_taxes_income, 'f', 2));
  ui->tax_res->setText(QString::number(taxes_res, 'f', 2));
  ui->calced_income->setText(QString::number(with_taxes_income, 'f', 2));
}
