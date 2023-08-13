#include "../s21_sprintf.h"

char *p_f[] = {"%p %p %p f:%p",
               "%.0p %.p %p f:%0p\n",
               "%p %p %-40p f:%0p\n",
               "%-1p %1p %.1p f:%0p\n",
               "%1p %050p %50p f:%0p\n",
               "%-050p %050p %.50p f:%p\n",
               "%.50p %-.50p %100.50p f:%p\n",
               "%100.50p %-98.50p %-97.50p f:%p\n",
               "%096.50p %95.50p %-50.94p f:%p\n",
               "%050.93p %50.92p %50.91p f:%p\n",
               "%-050.90p %040.89p %040.89p f:%p\n"};

START_TEST(t1_int_p) {
  char my[10000] = "";
  char sys[10000] = "";
  for (int i = 0; i < 10000000; i += 66666) {
    for (int f = 0; f < 11; f++) {
      s21_sprintf(my, p_f[f], &i, &i, &i, &f);
      sprintf(sys, p_f[f], &i, &i, &i, &f);
      ck_assert_str_eq(my, sys);
    }
  }
}
END_TEST

START_TEST(t2_sct_p) {
  char my[10000] = "";
  char sys[10000] = "";
  arg_info s = give_flag_struct();
  arg_info s1 = give_flag_struct();
  arg_info s2 = give_flag_struct();
  arg_info s3 = give_flag_struct();
  for (int f = 0; f < 11; f++) {
    s21_sprintf(my, p_f[f], &s, &s1, &s2, &s3);
    sprintf(sys, p_f[f], &s, &s1, &s2, &s3);
    ck_assert_str_eq(my, sys);
  }
}
END_TEST

START_TEST(t3_double_p) {
  char my[10000] = "";
  char sys[10000] = "";
  for (double i = 0; i < 10000000; i += 66666) {
    for (int f = 0; f < 11; f++) {
      s21_sprintf(my, p_f[f], &i, &i, &i, &f);
      sprintf(sys, p_f[f], &i, &i, &i, &f);
      ck_assert_str_eq(my, sys);
    }
  }
}
END_TEST

START_TEST(t4_null) {
  char my[10000] = "";
  char sys[10000] = "";
  int *i = NULL;
  for (int f = 0; f < 11; f++) {
    s21_sprintf(my, p_f[f], NULL, &i, NULL, &f);
    sprintf(sys, p_f[f], NULL, &i, NULL, &f);
    ck_assert_str_eq(my, sys);
  }
}
END_TEST

Suite *suit(void) {
  Suite *s = suite_create("p_suit");
  TCase *tc = tcase_create("pointer_case");
  tcase_add_test(tc, t1_int_p);
  tcase_add_test(tc, t2_sct_p);
  tcase_add_test(tc, t3_double_p);
  tcase_add_test(tc, t4_null);
  suite_add_tcase(s, tc);
  return s;
}

int main(void) {
  Suite *s;
  int failed = 0;
  SRunner *runner;

  s = suit();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
