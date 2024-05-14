#include "s21_deposit.h"

double get_tax_amount(double total_amount, double tax_rate) {
  return total_amount * tax_rate / 100;
}

double get_total_amount(double deposit_amount, double earned_money,
                        double tax_amount, bool is_capitalization) {
  double res = 0;
  if (is_capitalization == true) {
    res = deposit_amount;
  } else {
    res = deposit_amount + earned_money - tax_amount;
  }
  return res;
}

double get_total_earned(double *deposit_amount, double term,
                        double interest_rate, int MODE, bool is_capitalization,
                        double replenishments, double withdraws) {
  double earned_money_amount = 0;
  int period = MODE == MONTHLY ? 12 : 1;
  replenishments = MODE == MONTHLY ? replenishments : replenishments * 12;
  withdraws = MODE == MONTHLY ? withdraws : withdraws * 12;

  for (int i = 0; (double)i < term; i++) {
    double cumulative_earnings = 0;
    if (MODE == MONTHLY) {
      cumulative_earnings = *deposit_amount * interest_rate / 100 / period;
    }
    if (MODE == YEARLY) {
      if (i % 11 == 0 && i != 0) {
        cumulative_earnings = *deposit_amount * interest_rate / 100 / period;
      }
    }
    *deposit_amount += replenishments;
    *deposit_amount -= withdraws;
    if (is_capitalization) {
      *deposit_amount += cumulative_earnings;
    }
    earned_money_amount += cumulative_earnings;
  }

  return earned_money_amount;
}
