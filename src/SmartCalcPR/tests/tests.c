#include <check.h>

#include "../lib/s21_calc.h"

START_TEST(test_overflow_1) {
    char arr_expr[] = "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1";
    double result_std = 1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1;
    int error = 0;
    error = s21_std_validator(arr_expr);
    double result_mine;
    result_mine = s21_calculate_all(arr_expr, &error);
    ck_assert_float_eq(result_std, result_mine);
}
END_TEST

START_TEST(test_overflow_2) {
    char arr_expr[] = "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1";
    int error = 0;
    error = s21_std_validator(arr_expr);
    s21_calculate_all(arr_expr, &error);
    ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_sum) {
    char arr_expr[] = "3 + 11";
    double result_std = 3. + 11.;
    int error = 0;
    error = s21_std_validator(arr_expr);
    double result_mine;
    result_mine = s21_calculate_all(arr_expr, &error);
    ck_assert_float_eq(result_std, result_mine);
}
END_TEST

START_TEST(test_min) {
    char arr_expr[] = "3 - 11";
    double result_std = 3. - 11.;
    int error = 0;
    error = s21_std_validator(arr_expr);
    double result_mine;
    result_mine = s21_calculate_all(arr_expr, &error);
    ck_assert_float_eq(result_std, result_mine);
}
END_TEST

START_TEST(test_mul) {
    char arr_expr[] = "3 * 11";
    double result_std = 3. * 11.;
    int error = 0;
    error = s21_std_validator(arr_expr);
    double result_mine;
    result_mine = s21_calculate_all(arr_expr, &error);
    ck_assert_float_eq(result_std, result_mine);
}
END_TEST

START_TEST(test_div) {
    char arr_expr[] = "3 / 11";
    double result_std = 3. / 11.;
    int error = 0;
    error = s21_std_validator(arr_expr);
    double result_mine;
    result_mine = s21_calculate_all(arr_expr, &error);
    ck_assert_float_eq(result_std, result_mine);
}
END_TEST

START_TEST(test_M) {
    char arr_expr[] = "-8";
    double result_std = -8.;
    int error = 0;
    error = s21_std_validator(arr_expr);
    double result_mine;
    result_mine = s21_calculate_all(arr_expr, &error);
    ck_assert_float_eq(result_std, result_mine);
}
END_TEST

START_TEST(test_P) {
    char arr_expr[] = "+8";
    double result_std = +8.;
    int error = 0;
    error = s21_std_validator(arr_expr);
    double result_mine;
    result_mine = s21_calculate_all(arr_expr, &error);
    ck_assert_float_eq(result_std, result_mine);
}
END_TEST

START_TEST(test_P_2) {
    char arr_expr[] = "+4+1";
    double result_std = +4+1;
    int error = 0;
    error = s21_std_validator(arr_expr);
    double result_mine;
    result_mine = s21_calculate_all(arr_expr, &error);
    ck_assert_float_eq(result_std, result_mine);
}
END_TEST

START_TEST(test_unreal_1) {
    char arr_expr[] = "-5+45.8-22.1*4+11^2*(-1+2-1*4)";
    double result_std = -5 + 45.8 - 22.1 * 4 + pow(11, 2) * (-1 + 2 - 1 * 4);
    int error = 0;
    error = s21_std_validator(arr_expr);
    double result_mine;
    result_mine = s21_calculate_all(arr_expr, &error);
    ck_assert_float_eq(result_std, result_mine);
}
END_TEST

START_TEST(test_unreal_2) {
    char arr_expr[] = "-57.234+18*3-0.0001";
    double result_std = -57.234 + 18 * 3 - 0.0001;
    int error = 0;
    error = s21_std_validator(arr_expr);
    double result_mine;
    result_mine = s21_calculate_all(arr_expr, &error);
    ck_assert_float_eq(result_std, result_mine);
}
END_TEST

START_TEST(test_unreal_3) {
    char arr_expr[] = "999.99999+15-3.000001-0.0001*4";
    double result_std = 999.99999 + 15 - 3.000001 - 0.0001 * 4;
    int error = 0;
    error = s21_std_validator(arr_expr);
    double result_mine;
    result_mine = s21_calculate_all(arr_expr, &error);
    ck_assert_float_eq(result_std, result_mine);
}
END_TEST

START_TEST(test_unreal_4) {
    char arr_expr[] = "0.99-1+0.999";
    double result_std = 0.99 - 1 + 0.999;
    int error = 0;
    error = s21_std_validator(arr_expr);
    double result_mine;
    result_mine = s21_calculate_all(arr_expr, &error);
    ck_assert_float_eq(result_std, result_mine);
}
END_TEST

START_TEST(test_mod) {
    char arr_expr[] = "89mod5";
    double result_std = fmod(89, 5);
    int error = 0;
    error = s21_std_validator(arr_expr);
    double result_mine;
    result_mine = s21_calculate_all(arr_expr, &error);
    ck_assert_float_eq(result_std, result_mine);
}
END_TEST

START_TEST(test_sqr) {
    char arr_expr[] = "57^5";
    double result_std = pow(57, 5);
    int error = 0;
    error = s21_std_validator(arr_expr);
    double result_mine;
    result_mine = s21_calculate_all(arr_expr, &error);
    ck_assert_float_eq(result_std, result_mine);
}
END_TEST

START_TEST(test_func_1) {
    char arr_expr[] = "ln(32)";
    double result_std = log(32);
    int error = 0;
    error = s21_std_validator(arr_expr);
    double result_mine;
    result_mine = s21_calculate_all(arr_expr, &error);
    ck_assert_float_eq(result_std, result_mine);
}
END_TEST

START_TEST(test_func_2) {
    char arr_expr[] = 
      "tan(atan(0.5))     +acos(0.05-0.003)-cos(3^(2))-"
      "ln(107-cos(sin(3.14)))";
    double result_std = tan(atan(0.5)) + acos(0.05 - 0.003) - cos(pow(3, 2)) -
                       log(107 - cos(sin(3.14)));
    int error = 0;
    error = s21_std_validator(arr_expr);
    double result_mine;
    result_mine = s21_calculate_all(arr_expr, &error);
    ck_assert_float_eq(result_std, result_mine);
}
END_TEST

START_TEST(test_func_3) {
    char arr_expr[] = "tan(0.2)";
    double result_std = tan(0.2);
    int error = 0;
    error = s21_std_validator(arr_expr);
    double result_mine;
    result_mine = s21_calculate_all(arr_expr, &error);
    ck_assert_float_eq(result_std, result_mine);
}
END_TEST

START_TEST(test_func_4) {
    char arr_expr[] = "-sin(4^2)";
    double result_std = -sin(pow(4, 2));
    int error = 0;
    error = s21_std_validator(arr_expr);
    double result_mine;
    result_mine = s21_calculate_all(arr_expr, &error);
    ck_assert_float_eq(result_std, result_mine);
}
END_TEST

START_TEST(test_func_5) {
    char arr_expr[] = "-cos(tan(0.5))";
    double result_std = -cos(tan(0.5));
    int error = 0;
    error = s21_std_validator(arr_expr);
    double result_mine;
    result_mine = s21_calculate_all(arr_expr, &error);
    ck_assert_float_eq(result_std, result_mine);
}
END_TEST

START_TEST(test_func_6) {
    char arr_expr[] = "-asin(1)";
    double result_std = -asin(1);
    int error = 0;
    error = s21_std_validator(arr_expr);
    double result_mine;
    result_mine = s21_calculate_all(arr_expr, &error);
    ck_assert_float_eq(result_std, result_mine);
}
END_TEST

START_TEST(test_func_7) {
    char arr_expr[] = "-sqrt(9)";
    double result_std = -sqrt(9);
    int error = 0;
    error = s21_std_validator(arr_expr);
    double result_mine;
    result_mine = s21_calculate_all(arr_expr, &error);
    ck_assert_float_eq(result_std, result_mine);
}
END_TEST

START_TEST(test_error_1) {
    char arr_expr[] = "-10..";
    int error = 0;
    error = s21_std_validator(arr_expr);
    ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_error_2) {
    char arr_expr[] = "--10.";
    int error = 0;
    error = s21_std_validator(arr_expr);
    ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_error_3) {
    char arr_expr[] = "log(-8)";
    int error = 0;
    error = 0;
    s21_calculate_all(arr_expr, &error);
    ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_error_4) {
    char arr_expr[] = ".";
    int error = 0;
    error = 0;
    s21_calculate_all(arr_expr, &error);
    ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_error_5) {
    char arr_expr[] = "aboba";
    int error = 0;
    error = 0;
    s21_calculate_all(arr_expr, &error);
    ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_error_6) {
    char arr_expr[] = "";
    int error = 0;
    error = 0;
    s21_calculate_all(arr_expr, &error);
    ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_error_7) {
    char arr_expr[] = "(56+67";
    int error = 0;
    error = 0;
    s21_calculate_all(arr_expr, &error);
    ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_error_8) {
    char arr_expr[] = "taan(243)";
    int error = 0;
    error = 0;
    s21_calculate_all(arr_expr, &error);
    ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_error_9) {
    char arr_expr[] = "cs(2423)";
    int error = 0;
    error = 0;
    s21_calculate_all(arr_expr, &error);
    ck_assert_int_eq(error, 1);
}
END_TEST

void calculation_tests(TCase *tc1_1) {
  tcase_add_test(tc1_1, test_overflow_1);
  tcase_add_test(tc1_1, test_overflow_2);
  tcase_add_test(tc1_1, test_sum);
  tcase_add_test(tc1_1, test_min);
  tcase_add_test(tc1_1, test_mul);
  tcase_add_test(tc1_1, test_div);
  tcase_add_test(tc1_1, test_P);
  tcase_add_test(tc1_1, test_P_2);
  tcase_add_test(tc1_1, test_M);
  tcase_add_test(tc1_1, test_unreal_1);
  tcase_add_test(tc1_1, test_unreal_2);
  tcase_add_test(tc1_1, test_unreal_3);
  tcase_add_test(tc1_1, test_unreal_4);
  tcase_add_test(tc1_1, test_mod);
  tcase_add_test(tc1_1, test_sqr);
  tcase_add_test(tc1_1, test_func_1);
  tcase_add_test(tc1_1, test_func_2);
  tcase_add_test(tc1_1, test_func_3);
  tcase_add_test(tc1_1, test_func_4);
  tcase_add_test(tc1_1, test_func_5);
  tcase_add_test(tc1_1, test_func_6);
  tcase_add_test(tc1_1, test_func_7);
  tcase_add_test(tc1_1, test_error_1);
  tcase_add_test(tc1_1, test_error_2);
  tcase_add_test(tc1_1, test_error_3);
  tcase_add_test(tc1_1, test_error_4);
  tcase_add_test(tc1_1, test_error_5);
  tcase_add_test(tc1_1, test_error_6);
  tcase_add_test(tc1_1, test_error_7);
  tcase_add_test(tc1_1, test_error_8);
  tcase_add_test(tc1_1, test_error_9);
}
int main() {
  Suite *s1 = suite_create("s21_smartcalc: ");
  TCase *tc1_1 = tcase_create("s21_smartcalc: ");
  SRunner *sr = srunner_create(s1);
  int nf;
  suite_add_tcase(s1, tc1_1);
  calculation_tests(tc1_1);
  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nf == 0 ? 0 : 1;
}