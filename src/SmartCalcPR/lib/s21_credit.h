#ifndef CREDIT_CALC_H
#define CREDIT_CALC_H
#include "s21_calc.h"

typedef struct CrList_t {
  double payment;
  double pay_debt;
  double pay_percent;
  double remaining;
  struct CrList_t *next;

} CrList_t;

bool s21_credit_calculate(const double loan_total, const int time,
                          const double percent, bool type, CrList_t *head);
void s21_calculate_anuitential(const double loan_total, const int time,
                               const double percent, CrList_t *head);
void s21_calculate_differential(const double loan_total, const int time,
                                const double percent, CrList_t *head);

int s21_floatf(double *num);

// CrList functions

CrList_t *s21_CrList_create();
CrList_t *s21_CrList_find_last(CrList_t *head);
void s21_CrList_add_node(CrList_t *head, double payment, double pay_debt,
                         double pay_percent, double remaining);
void s21_CrList_remove(CrList_t *head);

#endif  // CREDIT_CALC_H
