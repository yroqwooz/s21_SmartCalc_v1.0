#ifndef DEPOSIT_CALC_H
#define DEPOSIT_CALC_H

#include <stdbool.h>

enum mode { MONTHLY, YEARLY };

double get_total_earned(double* deposit_amount, double term,
                        double interest_rate, int MODE, bool is_capitalization,
                        double replenishments, double withdraws);

double get_tax_amount(double total_amount, double tax_rate);

double get_total_amount(double deposit_amount, double earned_money,
                        double tax_amount, bool is_capitalization);

#endif  // DEPOSIT_CALC_H
