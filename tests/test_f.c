#include "../s21_sprintf.h"

char *f_in[] = {"%#f %f %f f:%f",
                "%#.0f %.0f %# f f:%+0f\n",
                "%+f % f %-40f f:%-0f\n",
                "%-1f % 1f %.1f f:% 0f\n",
                "%+1f %050f %#+050f f:%+- 0f\n",
                "%-050f % 050f % .28f f:%f\n",
                "%+.10f %-.10f % 100.10f f:%f\n",
                "%+10.20f % 10.20f %-10.20f f:%f\n",
                "%+010.20f % 010.20f %-010.20f f:%f\n",
                "%+050.10f % 050.10f %-50.10f f:%f\n",
                "%#-50.10f %#+40.10f %# 40.15f f:%f\n"};

char *lf_in[] = {"%#Lf %Lf %Lf Lf:%Lf",
                 "%#.0Lf %.0Lf %# Lf Lf:%+0Lf\n",
                 "%+Lf % Lf %-40Lf Lf:%-0Lf\n",
                 "%-1Lf % 1Lf %.1Lf Lf:% 0Lf\n",
                 "%+1Lf %050Lf %#+050Lf Lf:%+- 0Lf\n",
                 "%-050Lf % 050Lf % .28Lf Lf:%Lf\n",
                 "%+.10Lf %-.10Lf % 100.10Lf Lf:%Lf\n",
                 "%+10.20Lf %-10.20Lf %-10.20Lf Lf:%Lf\n",
                 "%+010.20Lf % 010.20Lf %-010.20Lf Lf:%Lf\n",
                 "%+050.15Lf % 050.10Lf %-50.10Lf Lf:%Lf\n",
                 "%#+50.10Lf %# 40.10Lf %#-40.15Lf Lf:%Lf\n"};

START_TEST(t1_sneg) {
  char my[10000] = "";
  char sys[10000] = "";
  for (double i = -10.73456780000000066; i < 0; i += 1.0) {
    for (int f = 0; f < 11; f++) {
      s21_sprintf(my, f_in[f], i, i, i, (double)f);
      sprintf(sys, f_in[f], i, i, i, (double)f);
      ck_assert_str_eq(my, sys);
    }
  }
  double i = 0;
  for (int f = 0.001; f < 11; f++) {
    s21_sprintf(my, f_in[f], i, i, i, (double)f);
    sprintf(sys, f_in[f], i, i, i, (double)f);
    ck_assert_str_eq(my, sys);
  }
}
END_TEST

START_TEST(t2_spos) {
  char my[10000] = "";
  char sys[10000] = "";
  for (double i = 10.1234567; i > 0; i -= 1.0) {
    for (int f = 0; f < 11; f++) {
      s21_sprintf(my, f_in[f], i, i, i, (double)f);
      sprintf(sys, f_in[f], i, i, i, (double)f);
      ck_assert_str_eq(my, sys);
    }
  }
}
END_TEST

START_TEST(t3_bneg) {
  char my[10000] = "";
  char sys[10000] = "";
  for (double i = -1234567890.73456780000000066; i < 0; i += 10000000.0) {
    for (int f = 0; f < 11; f++) {
      s21_sprintf(my, f_in[f], i, i, i, (double)f);
      sprintf(sys, f_in[f], i, i, i, (double)f);
      ck_assert_str_eq(my, sys);
    }
  }
}
END_TEST

START_TEST(t4_bpos) {
  char my[10000] = "";
  char sys[10000] = "";
  for (double i = 1234567890.1234567; i > 0; i -= 10000000.0) {
    for (int f = 0; f < 11; f++) {
      s21_sprintf(my, f_in[f], i, i, i, (double)f);
      sprintf(sys, f_in[f], i, i, i, (double)f);
      ck_assert_str_eq(my, sys);
    }
  }
  s21_sprintf(my, f_in[0], 9999.11, 9999.91, 9999.999, 9999.99999);
  sprintf(sys, f_in[0], 9999.11, 9999.91, 9999.999, 9999.99999);
  ck_assert_str_eq(my, sys);
}
END_TEST

START_TEST(t5_lneg) {
  char my[10000] = "";
  char sys[10000] = "";
  for (long double i = -101.73456780000000066L; i < 0; i += 1.0) {
    for (int f = 0; f < 11; f++) {
      s21_sprintf(my, lf_in[f], i, i, i, (long double)f);
      sprintf(sys, lf_in[f], i, i, i, (long double)f);
      ck_assert_str_eq(my, sys);
    }
  }
}
END_TEST

START_TEST(t6_lpos) {
  char my[10000] = "";
  char sys[10000] = "";
  for (long double i = 101.1234567L; i > 0; i -= 1.0) {
    for (int f = 0; f < 11; f++) {
      s21_sprintf(my, lf_in[f], i, i, i, (long double)f);
      sprintf(sys, lf_in[f], i, i, i, (long double)f);
      ck_assert_str_eq(my, sys);
    }
  }
}
END_TEST

START_TEST(t7_ast) {
  char my[10000] = "";
  char sys[10000] = "";
  int w1 = 10;
  int p1 = 5;
  int w2 = 6;
  int p2 = 17;
  char f[] = "%+*.*f + %.*Lf + %*Lf some jibberish\n";
  s21_sprintf(my, f, w1, p1, 1234678.98776545, p2, 1234678.98776545, w2,
              1234678.98776545L);
  sprintf(sys, f, w1, p1, 1234678.98776545, p2, 1234678.98776545, w2,
          1234678.98776545L);
  ck_assert_str_eq(my, sys);
}
END_TEST

START_TEST(t8_ninf) {
  char my[10000] = "";
  char sys[10000] = "";
  int w1 = 10;
  int p1 = 5;
  int w2 = 6;
  int p2 = 17;
  char f[] = "%f %f %+*.*f + %.*Lf + % *Lf some jibberish\n";
  s21_sprintf(my, f, -INFINITY, INFINITY, w1, p1, INFINITY, p2, -INFINITY, w2,
              INFINITY);
  sprintf(sys, f, -INFINITY, INFINITY, w1, p1, INFINITY, p2, -INFINITY, w2,
          INFINITY);
  ck_assert_str_eq(my, sys);
  s21_sprintf(my, f, NAN, NAN, w1, p1, NAN, p2, NAN, w2, -NAN);
  sprintf(sys, f, NAN, NAN, w1, p1, NAN, p2, NAN, w2, -NAN);
  ck_assert_str_eq(my, sys);
}

Suite *suit(void) {
  Suite *s = suite_create("f test");
  TCase *tc = tcase_create("double");
  tcase_add_test(tc, t1_sneg);
  tcase_add_test(tc, t2_spos);
  tcase_add_test(tc, t3_bneg);
  tcase_add_test(tc, t4_bpos);
  tcase_add_test(tc, t5_lneg);
  tcase_add_test(tc, t6_lpos);
  tcase_add_test(tc, t7_ast);
  tcase_add_test(tc, t8_ninf);
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
