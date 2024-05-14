#include "s21_credit.h"

bool s21_credit_calculate(const double loan_total, const int time,
                          const double percent, bool type, CrList_t *head) {
  if (type == 0) {
    s21_calculate_anuitential(loan_total, time, percent, head);
  } else if (type == 1) {
    s21_calculate_differential(loan_total, time, percent, head);
  }
  return type;
}

void s21_calculate_anuitential(const double loan_total, const int time,
                               const double percent, CrList_t *head) {
  double mounth_pay = 0.0;
  double debt_total = 0.0;

  mounth_pay =
      loan_total *
      ((0.01 * percent / 12) +
       (((0.01 * percent / 12)) / (pow(1 + (0.01 * percent / 12), time) - 1)));
  s21_floatf(&mounth_pay);
  double percent_part = 0.0;
  double debt_part = 0.0;
  double loan_left = loan_total;
  double percent_total = 0.0;
  for (int i = 0; i < time; i++) {
    percent_part = loan_left * (0.01 * percent / 12);
    s21_floatf(&percent_part);
    debt_part = mounth_pay - percent_part;
    s21_floatf(&debt_part);
    debt_total += debt_part;
    s21_floatf(&debt_total);
    loan_left -= debt_part;
    s21_floatf(&loan_left);
    percent_total += percent_part;
    s21_CrList_add_node(head, percent_part + debt_part, debt_part, percent_part,
                        loan_left);
  }
  s21_CrList_add_node(head, mounth_pay, percent_total,
                      loan_total + percent_total, 0.0);
}

void s21_calculate_differential(const double loan_total, const int time,
                                const double percent, CrList_t *head) {
  double loan_part = loan_total / time;
  double loan_left = loan_total;
  double total_pay = 0.0;
  double debt_total = 0.0;
  double percent_total = 0.0;
  for (int i = 0; i < time; i++) {
    double percent_curr = loan_left * (0.01 * percent / 12);
    s21_floatf(&percent_curr);
    double combined_pay = percent_curr + loan_part;
    total_pay += combined_pay;
    debt_total += loan_part;
    percent_total += percent_curr;
    loan_left -= loan_part;
    s21_CrList_add_node(head, combined_pay, loan_part, percent_curr, loan_left);
  }
  s21_CrList_add_node(head, total_pay, debt_total, percent_total, 0.0);
}

int s21_floatf(double *num) {
  double whole;
  double fract = modf(*num, &whole);
  fract *= 100;
  if ((int)(fract * 10) % 10 >= 5) {
    fract += 1;
  }
  modf(fract, &fract);
  fract /= 100;
  *num = whole + fract;
  return 0;
}
