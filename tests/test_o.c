#include "../s21_sprintf.h"

char *o_in[] = {"%o %#o %o f:%o",
                  "%.0o %.o %o f:%0o\n",
                  "%ho %ho %-40ho f:%-0o\n",
                  "%-1o %1o %.1o f:%0o\n",
                  "%1o %050o %050o f:%- 0o\n",
                  "%-050o %050o %.50o f:%o\n",
                  "%.50o %-.50o %100.50o f:%o\n",
                  "%100.50o %-98.50o %-097.50o f:%o\n",
                  "%096.50o %095.50o %-050.94o f:%o\n",
                  "%050.93o %50.92o %50.91o f:%o\n",
                  "%-050.90o %040.89o %040.89o f:%o\n"};

char *lo_in[] = {"%lo %lo %lo f:%lo",
                  "%.0lo %.lo %lo f:%0lo\n",
                  "%#lo %#25lo %#-40lo f:%-0lo\n",
                  "%-1lo %1lo %.1lo f:%0lo\n",
                  "%1lo %050lo %050lo f:%- 0lo\n",
                  "%-050lo %050lo %.50lo f:%lo\n",
                  "%.50lo %-.50lo %100.50lo f:%lo\n",
                  "%100.50lo %-98.50lo %-097.50lo f:%lo\n",
                  "%096.50lo %095.50lo %-050.94lo f:%lo\n",
                  "%050.93lo %50.92lo %50.91lo f:%lo\n",
                  "%-050.90lo %040.89lo %040.89lo f:%lo\n"};

char *llo_in[] = {"%llo %llo %25llo f:%llo",
                  "%.0llo %.llo %llo f:%0llo\n",
                  "%#llo %#25llo %#-40llo f:%-0llo\n",
                  "%-1llo %1llo %.1llo f:%0llo\n",
                  "%1llo %050llo %050llo f:%- 0llo\n",
                  "%-050llo %050llo %.50llo f:%llo\n",
                  "%.50llo %-.50llo %100.50llo f:%llo\n",
                  "%100.50llo %-98.50llo %-097.50llo f:%llo\n",
                  "%096.50llo %095.50llo %-050.94llo f:%llo\n",
                  "%050.93llo %50.92llo %50.91llo f:%llo\n",
                  "%-050.90llo %040.89llo %040.89llo f:%llo\n"};


START_TEST(t1_int) {
  char my[10000] = "";
  char sys[10000] = "";
  for (unsigned int i = 0; i < 10000000; i += 66666) {
    for (int f = 0; f < 11; f++) {
      s21_sprintf(my, o_in[f], i, i, i, f);
      sprintf(sys, o_in[f], i, i, i, f);
      ck_assert_str_eq(my, sys);
    }
  }
}
END_TEST

START_TEST(t2_lint) {
  char my[10000] = "";
  char sys[10000] = "";
  for (long unsigned int i = INT_MAX; i < 4000000000; i += 1666666) {
    for (unsigned int f = 0; f < 11; f++) {
      s21_sprintf(my, lo_in[f], i, i, i, f);
      sprintf(sys, lo_in[f], i, i, i, f);
      ck_assert_str_eq(my, sys);
    }
  }
}
END_TEST

START_TEST(t3_llint) {
  char my[10000] = "";
  char sys[10000] = "";
  for (long long unsigned i = UINT_MAX; i < 10000000000000000; i += 5000000000000000) {
    for (unsigned int f = 0; f < 11; f++) {
      s21_sprintf(my, llo_in[f], i, i, i, f);
      sprintf(sys, llo_in[f], i, i, i, f);
      ck_assert_str_eq(my, sys);
    }
  }
}
END_TEST

START_TEST(t4_ast) {
  char my[10000] = "";
  char sys[10000] = "";
  int w1 = 10;
  int p1 = 5;
  int w2 = 6;
  int p2 = 17;
  char f[] = "%*.*o + %.*lo + %*llo some jibberish\n";
  s21_sprintf(my, f, w1, p1, UINT_MAX, p2, ULONG_MAX, w2, ULLONG_MAX);
  sprintf(sys, f, w1, p1, UINT_MAX, p2, ULONG_MAX, w2, ULLONG_MAX);
  ck_assert_str_eq(my, sys);
}
END_TEST

Suite *suit(void) {
  Suite *s = suite_create("o_suit");
  TCase *tc = tcase_create("o_case");
  tcase_add_test(tc, t1_int);
  tcase_add_test(tc, t2_lint);
  tcase_add_test(tc, t3_llint);
  tcase_add_test(tc, t4_ast);
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
