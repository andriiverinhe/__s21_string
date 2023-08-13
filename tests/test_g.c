#include "../s21_sprintf.h"

char *g_in[] = {"%#g %g %g g:%g",
                "%#.0g %#.g %# g g:%+0g\n",
                "%+g % g %-40g g:%-0g\n",
                "%-1g % 1g %.1g g:% 0g\n",
                "%+1g %050g %#+050g g:%+- 0g\n",
                "%-050g % 050g % .8g g:%g\n",
                "%+.10g %-.10g % 100.10g g:%g\n",
                "%+10.8g %-10.8g %-10.8g g:%g\n",
                "%+010.8g % 010.8g %-010.8g g:%g\n",
                "%+050.10g % 050.10g %-50.10g g:%g\n",
                "%#+50.10g %# 40.10g %#-40.15g g:%g\n"};

char *lg_in[] = {"%#Lg %Lg %Lg Lg:%Lg",
                 "%#.0Lg %#.Lg %# Lg Lg:%+0Lg\n",
                 "%+Lg % Lg %-40Lg Lg:%-0Lg\n",
                 "%-1Lg % 1Lg %.1Lg Lg:% 0Lg\n",
                 "%+1Lg %050Lg %#+050Lg Lg:%+- 0Lg\n",
                 "%-050Lg % 050Lg % .8Lg Lg:%Lg\n",
                 "%+.10Lg %-.10Lg % 100.10Lg Lg:%Lg\n",
                 "%+10.9Lg % 10.9Lg %-10.9Lg Lg:%Lg\n",
                 "%+010.9Lg % 010.9Lg %-010.12Lg Lg:%Lg\n",
                 "%+050.15Lg % 50.10Lg %-50.10Lg Lg:%Lg\n",
                 "%#+50.10Lg %# 40.10Lg %#-40.15Lg Lg:%Lg\n"};

START_TEST(t1_sneg) {
  char my[10000] = "";
  char sys[10000] = "";
  for (double i = -10.73456780000000066; i < 0; i += 1.0) {
    for (int f = 0; f < 11; f++) {
      s21_sprintf(my, g_in[f], i, i, i, (double)f);
      sprintf(sys, g_in[f], i, i, i, (double)f);
      ck_assert_str_eq(my, sys);
    }
  }
  double i = 0;
  for (int f = 0; f < 11; f++) {
    s21_sprintf(my, g_in[f], i, i, i, (double)f);
    sprintf(sys, g_in[f], i, i, i, (double)f);
    ck_assert_str_eq(my, sys);
  }
}
END_TEST

START_TEST(t2_spos) {
  char my[10000] = "";
  char sys[10000] = "";
  for (double i = 10.1234567; i > 0; i -= 1.0) {
    for (int f = 0; f < 11; f++) {
      s21_sprintf(my, g_in[f], i, i, i, (double)f);
      sprintf(sys, g_in[f], i, i, i, (double)f);
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
      s21_sprintf(my, g_in[f], i, i, i, (double)f);
      sprintf(sys, g_in[f], i, i, i, (double)f);
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
      s21_sprintf(my, g_in[f], i, i, i, (double)f);
      sprintf(sys, g_in[f], i, i, i, (double)f);
      ck_assert_str_eq(my, sys);
    }
  }
}
END_TEST

START_TEST(t5_lneg) {
  char my[10000] = "";
  char sys[10000] = "";
  for (long double i = -101.73456780000000066L; i < 0; i += 1.0) {
    for (int f = 0; f < 11; f++) {
      s21_sprintf(my, lg_in[f], i, i, i, (long double)f);
      sprintf(sys, lg_in[f], i, i, i, (long double)f);
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
      s21_sprintf(my, lg_in[f], i, i, i, (long double)f);
      sprintf(sys, lg_in[f], i, i, i, (long double)f);
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
  char f[] = "%*.*g + %.*Lg + %*Lg some jibberish\n";
  s21_sprintf(my, f, w1, p1, 1234678.98776545, p2, 1234678.98776545L, w2,
              1234678.98776545L);
  sprintf(sys, f, w1, p1, 1234678.98776545, p2, 1234678.98776545L, w2,
          1234678.98776545L);
  ck_assert_str_eq(my, sys);
}
END_TEST

START_TEST(t8_z) {
  char my[10000] = "";
  char sys[10000] = "";
  double i = 0.0001;
  for (int f = 0; f < 11; f++) {
    s21_sprintf(my, g_in[f], i, i, i, (double)f);
    sprintf(sys, g_in[f], i, i, i, (double)f);
    ck_assert_str_eq(my, sys);
  }
}
END_TEST

START_TEST(t9_ninf) {
  char my[10000] = "";
  char sys[10000] = "";
  int w1 = 10;
  int p1 = 5;
  int w2 = 6;
  int p2 = 17;
  char f[] = "%g %g %+*.*g + %.*Lg + % *Lg some jibberish\n";
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
  Suite *s = suite_create("G g test");
  TCase *tc = tcase_create("g double");
  tcase_add_test(tc, t1_sneg);
  tcase_add_test(tc, t2_spos);
  tcase_add_test(tc, t3_bneg);
  tcase_add_test(tc, t4_bpos);
  tcase_add_test(tc, t5_lneg);
  tcase_add_test(tc, t6_lpos);
  tcase_add_test(tc, t7_ast);
  tcase_add_test(tc, t8_z);
  tcase_add_test(tc, t9_ninf);
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
