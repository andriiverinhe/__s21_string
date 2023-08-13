#include "../s21_sprintf.h"

char *int_in[] = {"%d %d %d f:%d",
                  "%.0d %.d % d f:%+0d\n",
                  "%+ hd % hd %-40hd f:%-0d\n",
                  "%-1d % 1d %.1d f:% 0d\n",
                  "%+1d %050d %+050d f:%+- 0d\n",
                  "%-050d % 050d % .50d f:%d\n",
                  "%+.50d %-.50d % 100.50d f:%d\n",
                  "%+100.50d %-98.50d %-097.50d f:%d\n",
                  "%+096.50d % 095.50d %-050.94d f:%d\n",
                  "%+050.93d % 50.92d %+50.91d f:%d\n",
                  "%-50.90d %+40.89d % 40.89d f:%d\n"};

char *lint_in[] = {"%ld %ld %ld f:%ld",
                  "%.0ld %.ld % ld f:%+0ld\n",
                  "%+ld %+.ld % .ld f:%-0ld\n",
                  "%-1ld % 1ld %.1ld f:% 0ld\n",
                  "%+1ld %050ld %+050ld f:%+- 0ld\n",
                  "%-050ld % 050ld % .50ld f:%ld\n",
                  "%+.50ld %-.50ld % 100.50ld f:%ld\n",
                  "%+100.50ld %-98.50ld %-097.50ld f:%ld\n",
                  "%+096.50ld % 095.50ld %-050.94ld f:%ld\n",
                  "%+050.93ld % 50.92ld %+50.91ld f:%ld\n",
                  "%-50.90ld %+40.89ld % 40.88ld f:%ld\n"};

char *llint_in[] = {"%lld %lld %lld f:%lld",
                  "%.0lld %.lld % lld f:%+0lld\n",
                  "%+lld %+.lld % .lld f:%-0lld\n",
                  "%-1lld % 1lld %.1lld f:% 0lld\n",
                  "%+1lld %050lld %+050lld f:%+- 0lld\n",
                  "%-050lld % 050lld % .50lld f:%lld\n",
                  "%+.50lld %-.50lld % 100.50lld f:%lld\n",
                  "%+100.50lld %-98.50lld %-097.50lld f:%lld\n",
                  "%+096.50lld % 095.50lld %-050.94lld f:%lld\n",
                  "%+050.93lld % 50.92lld %+50.91lld f:%lld\n",
                  "%-50.90lld %+40.89lld % 40.89lld f:%lld\n"};

START_TEST(t1_neg) {
  char my[10000] = "";
  char sys[10000] = "";
  for (int i = INT_MIN; i < 0; i += 1000000) {
    for (int f = 0; f < 11; f++) {
      s21_sprintf(my, int_in[f], i, i, i, f);
      sprintf(sys, int_in[f], i, i, i, f);
      ck_assert_str_eq(my, sys);
    }
  }
}
END_TEST

START_TEST(t2_pos) {
  char my[10000] = "";
  char sys[10000] = "";
  for (int i = 0; i < 5000000; i += 10000) {
    for (int f = 0; f < 11; f++) {
      s21_sprintf(my, int_in[f], i, i, i, f);
      sprintf(sys, int_in[f], i, i, i, f);
      ck_assert_str_eq(my, sys);
    }
  }
  for (int f = 0; f < 11; f++) {
    s21_sprintf(my, int_in[f], INT_MAX, INT_MAX, INT_MAX, f);
    sprintf(sys, int_in[f], INT_MAX, INT_MAX, INT_MAX, f);
    ck_assert_str_eq(my, sys);
  }
}
END_TEST

START_TEST(t3_lneg) {
  char my[10000] = "";
  char sys[10000] = "";
  for (long int i = INT_MIN; i < 0; i += 1000000) {
    for (int f = 0; f < 11; f++) {
      s21_sprintf(my, lint_in[f], i, i, i, f);
      sprintf(sys, lint_in[f], i, i, i, f);
      ck_assert_str_eq(my, sys);
    }
  }
}
END_TEST

START_TEST(t4_lpos) {
  char my[10000] = "";
  char sys[10000] = "";
  for (long int i = 0; i < 5000000; i += 10000) {
    for (int f = 0; f < 11; f++) {
      s21_sprintf(my, lint_in[f], i, i, i, f);
      sprintf(sys, lint_in[f], i, i, i, f);
      ck_assert_str_eq(my, sys);
    }
  }
  for (int f = 0; f < 11; f++) {
    s21_sprintf(my, lint_in[f], LONG_MAX, LONG_MAX, LONG_MAX, f);
    sprintf(sys, lint_in[f], LONG_MAX, LONG_MAX, LONG_MAX, f);
    ck_assert_str_eq(my, sys);
  }
}
END_TEST

START_TEST(t5_llneg) {
  char my[10000] = "";
  char sys[10000] = "";
  for (long long int i = LLONG_MIN; i < 0; i += 1000000000000000000) {
    for (int f = 0; f < 11; f++) {
      s21_sprintf(my, llint_in[f], i, i, i, f);
      sprintf(sys, llint_in[f], i, i, i, f);
      ck_assert_str_eq(my, sys);
    }
  }
}
END_TEST

START_TEST(t6_llpos) {
  char my[10000] = "";
  char sys[10000] = "";
  for (long long int i = 0; i < 7000000000000000000; i += 1000000000000000000) {
    for (int f = 0; f < 11; f++) {
      s21_sprintf(my, llint_in[f], i, i, i, f);
      sprintf(sys, llint_in[f], i, i, i, f);
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
  char f[] = "%*.*d + %.*ld + %*lld some jibberish\n";
  s21_sprintf(my, f, w1, p1, INT_MAX, p2, LONG_MAX, w2, LLONG_MAX);
  sprintf(sys, f, w1, p1, INT_MAX, p2, LONG_MAX, w2, LLONG_MAX);
  ck_assert_str_eq(my, sys);
}
END_TEST

Suite *suit(void) {
  Suite *s = suite_create("int");
  TCase *tc = tcase_create("signed int");
  tcase_add_test(tc, t1_neg);
  tcase_add_test(tc, t2_pos);
  tcase_add_test(tc, t3_lneg);
  tcase_add_test(tc, t4_lpos);
  tcase_add_test(tc, t5_llneg);
  tcase_add_test(tc, t6_llpos);
  tcase_add_test(tc, t7_ast);
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
