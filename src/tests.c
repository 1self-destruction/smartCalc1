#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "SmartCalc_v1_0.h"

START_TEST(test_calculator_1) {
  char str_input[100] = "999.99999-0.0001+(9000^4-78/5)=";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);

  if (error == 0) {
    double result_org = 999.99999 - 0.0001 + (pow(9000, 4) - 78 / 5);
    ck_assert_float_eq(result, result_org);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_calculator_2) {
  char str_input[100] = "-45.6/5-67*4-(+8*2-5)=";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);

  if (error == 0) {
    double result_org = -45.6 / 5 - 67 * 4 - (+8 * 2 - 5);
    ck_assert_float_eq(result, result_org);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_calculator_3) {
  char str_input[100] = "45 mod 5=";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);

  if (error == 0) {
    double result_org = 45 % 5;
    ck_assert_float_eq(result, result_org);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_calculator_4) {
  char str_input[100] = "0.00001 mod 0.999=";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);

  if (error == 0) {
    double result_org = fmod(0.00001, 0.999);
    ck_assert_float_eq(result, result_org);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_calculator_5) {
  char str_input[100] = "0.00001 mod(0.999 + 9)=";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);

  if (error == 0) {
    double result_org = fmod(0.00001, (0.999 + 9));
    ck_assert_float_eq(result, result_org);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_calculator_6) {
  char str_input[100] = "0.00001+- 0.999=";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);
  if (error == 0) {
    double result_org = 0.00001 + -0.999;
    ck_assert_float_eq(result, result_org);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_calculator_7) {
  char str_input[100] = "4.56^ 0.999=";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);
  if (error == 0) {
    double result_org = pow(4.56, 0.999);
    ck_assert_float_eq(result, result_org);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_calculator_8) {
  char str_input[100] = "cos(5)=";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);
  if (error == 0) {
    double result_org = cos(5);
    ck_assert_float_eq(result, result_org);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_calculator_9) {
  char str_input[100] = "sin(5)=";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);
  if (error == 0) {
    double result_org = sin(5);
    ck_assert_float_eq(result, result_org);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_calculator_10) {
  char str_input[100] = "tan(5)=";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);
  if (error == 0) {
    double result_org = tan(5);
    ck_assert_float_eq(result, result_org);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_calculator_11) {
  char str_input[100] = "acos(0.245)=";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);
  if (error == 0) {
    double result_org = acos(0.245);
    ck_assert_float_eq(result, result_org);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_calculator_12) {
  char str_input[100] = "asin(0.567)=456";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);
  if (error == 0) {
    double result_org = asin(0.567);
    ck_assert_float_eq(result, result_org);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_calculator_13) {
  char str_input[100] = "atan(5)=";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);
  if (error == 0) {
    double result_org = atan(5);
    ck_assert_float_eq(result, result_org);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_calculator_14) {
  char str_input[100] = "sqrt(5)=";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);
  if (error == 0) {
    double result_org = sqrt(5);
    ck_assert_float_eq(result, result_org);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_calculator_15) {
  char str_input[100] = "ln(5)=";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);
  if (error == 0) {
    double result_org = log(5);
    ck_assert_float_eq(result, result_org);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_calculator_16) {
  char str_input[100] = "log(5)=";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);
  if (error == 0) {
    double result_org = log10(5);
    ck_assert_float_eq(result, result_org);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_calculator_17) {
  char str_input[100] = "sqrt(x*67^9.9999)=";
  int error = 0;
  double x = 5.89;
  double result = result_polish_notation(x, str_input, &error);
  if (error == 0) {
    double result_org = sqrt(x * pow(67.0, 9.9999));
    ck_assert_float_eq(result, result_org);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_calculator_18) {
  char str_input[100] = "x=";
  int error = 0;
  double x = -5.89;
  double result = result_polish_notation(x, str_input, &error);
  if (error == 0) {
    double result_org = x;
    ck_assert_float_eq(result, result_org);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_calculator_19) {
  char str_input[100] = "8*x=";
  int error = 0;
  double x = -5.89987;
  double result = result_polish_notation(x, str_input, &error);
  if (error == 0) {
    double result_org = 8 * x;
    ck_assert_float_eq(result, result_org);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_calculator_20) {
  char str_input[100] = "sqrt(5.89*67-9.9999)=";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);
  if (error == 0) {
    double result_org = sqrt(5.89 * 67 - 9.9999);
    ck_assert_float_eq(result, result_org);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_calculator_error_1) {
  char str_input[100] = "0.00001 modulus 0.999=";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_calculator_error_2) {
  char str_input[100] = "0.000.01 + 0.999=";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_calculator_error_3) {
  char str_input[100] = "0.001  0.999=";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_calculator_error_4) {
  char str_input[100] = "0.00001 uioi 0.999=";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_calculator_error_5) {
  char str_input[100] = "0.00001 u 0.999=";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_calculator_error_6) {
  char str_input[100] = "--+=";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_calculator_error_7) {
  char str_input[100] = "^ 0.999=";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_calculator_error_8) {
  char str_input[100] = "2*sin(5=";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_calculator_error_9) {
  char str_input[100] = "2*sin5)=";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(error, 6);
}
END_TEST

START_TEST(test_calculator_error_10) {
  char str_input[100] = "290*cos(5+3))";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(error, 5);
}
END_TEST

START_TEST(test_calculator_error_11) {
  char str_input[100] = "3*2/0=";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(error, 2);
}
END_TEST

START_TEST(test_calculator_error_12) {
  char str_input[100] = "sqrt(-12)=234";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(error, 4);
}
END_TEST

START_TEST(test_calculator_error_13) {
  char str_input[100] = "3+log(-14)";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(error, 4);
}
END_TEST

START_TEST(test_calculator_error_14) {
  char str_input[100] = "3+ln(-14)";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(error, 4);
}
END_TEST

START_TEST(test_calculator_error_15) {
  char str_input[100] = "()";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_calculator_error_16) {
  char str_input[100] = "23+(34+3))+123=";
  int error = 0;
  double result = result_polish_notation(0, str_input, &error);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(error, 5);
}
END_TEST

START_TEST(test_calculator_deposit_1) {
  int error = 0;
  deposit_calculation_result* result =
      deposit_result(200000, 24, 36.0, 13.0, 1, 0, NULL, NULL, &error);
  if (error == 0) {
    ck_assert_float_eq(result->interest_charges, 142027.397260);
    ck_assert_float_eq(result->tax_amount, 7413.561644);
    ck_assert_float_eq(result->amount_end_term, 200000.0);
    free(result);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_calculator_deposit_2) {
  int error = 0;
  deposit_calculation_result* result =
      deposit_result(200000, 24, 36.0, 13.0, 1, 1, NULL, NULL, &error);
  if (error == 0) {
    ck_assert_float_eq(result->interest_charges, 205863.558318);
    ck_assert_float_eq(result->tax_amount, 15712.262581);
    ck_assert_float_eq(result->amount_end_term, 405863.558318);
    free(result);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_calculator_deposit_3) {
  int error = 0;
  deposit_calculation_result* result =
      deposit_result(200000, 24, 36.0, 13.0, 2, 1, NULL, NULL, &error);
  if (error == 0) {
    ck_assert_float_eq(result->interest_charges, 202683.529994);
    ck_assert_float_eq(result->tax_amount, 15298.858899);
    ck_assert_float_eq(result->amount_end_term, 402683.529994);
    free(result);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_calculator_deposit_4) {
  int error = 0;
  deposit_calculation_result* result =
      deposit_result(200000, 24, 36.0, 13.0, 3, 1, NULL, NULL, &error);
  if (error == 0) {
    ck_assert_float_eq(result->interest_charges, 194920.776448);
    ck_assert_float_eq(result->tax_amount, 14289.700938);
    ck_assert_float_eq(result->amount_end_term, 394920.776448);
    free(result);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_calculator_deposit_5) {
  int error = 0;
  deposit_calculation_result* result =
      deposit_result(200000, 24, 36.0, 13.0, 4, 1, NULL, NULL, &error);
  // printf("1= %lf\n", result->interest_charges);
  //     printf("2= %lf\n", result->tax_amount);
  //     printf("3= %lf\n", result->amount_end_term);
  if (error == 0) {
    ck_assert_float_eq(result->interest_charges, 184524.647281);
    ck_assert_float_eq(result->tax_amount, 12938.204146);
    ck_assert_float_eq(result->amount_end_term, 384524.647281);
    free(result);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_calculator_deposit_6) {
  int error = 0;
  deposit_calculation_result* result = deposit_result(
      200000, 24, 36.0, 13.0, 4, 1, "25:50000;", "54:25000;", &error);
  if (error == 0) {
    ck_assert_float_eq(result->interest_charges, 207751.266898);
    ck_assert_float_eq(result->tax_amount, 15957.664697);
    ck_assert_float_eq(result->amount_end_term, 432751.266898);
    free(result);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_calculator_deposit_7) {
  int error = 0;
  deposit_calculation_result* result =
      deposit_result(200000, 24, 36.0, 13.0, 4, 1, "25:50000;30:100000;",
                     "54:25000;80:35000;", &error);
  if (error == 0) {
    ck_assert_float_eq(result->interest_charges, 267399.699849);
    ck_assert_float_eq(result->tax_amount, 23711.960980);
    ck_assert_float_eq(result->amount_end_term, 557399.699849);
    free(result);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_calculator_deposit_8) {
  int error = 0;
  deposit_calculation_result* result =
      deposit_result(200000, 24, 36.0, 13.0, 4, 1, "25:50000;30:100000",
                     "54:25000;80:35000;", &error);
  ck_assert_int_eq(error, 2);
  free(result);
}
END_TEST

START_TEST(test_calculator_deposit_9) {
  int error = 0;
  deposit_calculation_result* result =
      deposit_result(200000, 24, 36.0, 13.0, 4, 1, "25:50000;30:100000;",
                     "54:25000;8035000", &error);
  ck_assert_int_eq(error, 2);
  free(result);
}
END_TEST

void calc_tests(TCase* tc1_1) {
  tcase_add_test(tc1_1, test_calculator_1);
  tcase_add_test(tc1_1, test_calculator_2);
  tcase_add_test(tc1_1, test_calculator_3);
  tcase_add_test(tc1_1, test_calculator_4);
  tcase_add_test(tc1_1, test_calculator_5);
  tcase_add_test(tc1_1, test_calculator_6);
  tcase_add_test(tc1_1, test_calculator_7);
  tcase_add_test(tc1_1, test_calculator_8);
  tcase_add_test(tc1_1, test_calculator_9);
  tcase_add_test(tc1_1, test_calculator_10);
  tcase_add_test(tc1_1, test_calculator_11);
  tcase_add_test(tc1_1, test_calculator_12);
  tcase_add_test(tc1_1, test_calculator_13);
  tcase_add_test(tc1_1, test_calculator_14);
  tcase_add_test(tc1_1, test_calculator_15);
  tcase_add_test(tc1_1, test_calculator_16);
  tcase_add_test(tc1_1, test_calculator_17);
  tcase_add_test(tc1_1, test_calculator_18);
  tcase_add_test(tc1_1, test_calculator_19);
  tcase_add_test(tc1_1, test_calculator_20);
  tcase_add_test(tc1_1, test_calculator_error_1);
  tcase_add_test(tc1_1, test_calculator_error_2);
  tcase_add_test(tc1_1, test_calculator_error_3);
  tcase_add_test(tc1_1, test_calculator_error_4);
  tcase_add_test(tc1_1, test_calculator_error_5);
  tcase_add_test(tc1_1, test_calculator_error_6);
  tcase_add_test(tc1_1, test_calculator_error_7);
  tcase_add_test(tc1_1, test_calculator_error_8);
  tcase_add_test(tc1_1, test_calculator_error_9);
  tcase_add_test(tc1_1, test_calculator_error_10);
  tcase_add_test(tc1_1, test_calculator_error_11);
  tcase_add_test(tc1_1, test_calculator_error_12);
  tcase_add_test(tc1_1, test_calculator_error_13);
  tcase_add_test(tc1_1, test_calculator_error_14);
  tcase_add_test(tc1_1, test_calculator_error_15);
  tcase_add_test(tc1_1, test_calculator_error_16);
  tcase_add_test(tc1_1, test_calculator_deposit_1);
  tcase_add_test(tc1_1, test_calculator_deposit_2);
  tcase_add_test(tc1_1, test_calculator_deposit_3);
  tcase_add_test(tc1_1, test_calculator_deposit_4);
  tcase_add_test(tc1_1, test_calculator_deposit_5);
  tcase_add_test(tc1_1, test_calculator_deposit_6);
  tcase_add_test(tc1_1, test_calculator_deposit_7);
  tcase_add_test(tc1_1, test_calculator_deposit_8);
  tcase_add_test(tc1_1, test_calculator_deposit_9);
}

int main(void) {
  Suite* s1 = suite_create("Core");
  TCase* tc1_1 = tcase_create("Core");
  SRunner* sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);

  calc_tests(tc1_1);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
