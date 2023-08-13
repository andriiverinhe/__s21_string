#include "../s21_sprintf.h"

char *uint_in[] = {"%u %u %u f:%u",
                  "%.0u %.u %u f:%0u\n",
                  "%hu %hu %-40hu f:%-0u\n",
                  "%-1u %1u %.1u f:%0u\n",
                  "%1u %050u %050u f:%- 0u\n",
                  "%-050u %050u %.50u f:%u\n",
                  "%.50u %-.50u %100.50u f:%u\n",
                  "%100.50u %-98.50u %-097.50u f:%u\n",
                  "%096.50u %095.50u %-050.94u f:%u\n",
                  "%050.93u %50.92u %50.91u f:%u\n",
                  "%-050.90u %040.89u %040.89u f:%u\n"};

char *luint_in[] = {"%lu %lu %lu f:%lu",
                  "%.0lu %.lu %lu f:%0lu\n",
                  "%lu %25lu %-40lu f:%-0lu\n",
                  "%-1lu %1lu %.1lu f:%0lu\n",
                  "%1lu %050lu %050lu f:%- 0lu\n",
                  "%-050lu %050lu %.50lu f:%lu\n",
                  "%.50lu %-.50lu %100.50lu f:%lu\n",
                  "%100.50lu %-98.50lu %-097.50lu f:%lu\n",
                  "%096.50lu %095.50lu %-050.94lu f:%lu\n",
                  "%050.93lu %50.92lu %50.91lu f:%lu\n",
                  "%-050.90lu %040.89lu %040.89lu f:%lu\n"};

char *lluint_in[] = {"%llu %llu %25llu f:%llu",
                  "%.0llu %.llu %llu f:%0llu\n",
                  "%llu %25llu %-40llu f:%-0llu\n",
                  "%-1llu %1llu %.1llu f:%0llu\n",
                  "%1llu %050llu %050llu f:%- 0llu\n",
                  "%-050llu %050llu %.50llu f:%llu\n",
                  "%.50llu %-.50llu %100.50llu f:%llu\n",
                  "%100.50llu %-98.50llu %-097.50llu f:%llu\n",
                  "%096.50llu %095.50llu %-050.94llu f:%llu\n",
                  "%050.93llu %50.92llu %50.91llu f:%llu\n",
                  "%-050.90llu %040.89llu %040.89llu f:%llu\n"};


START_TEST(t1_int) {
  char my[10000] = "";
  char sys[10000] = "";
  for (unsigned int i = 0; i < 10000000; i += 66666) {
    for (int f = 0; f < 11; f++) {
      s21_sprintf(my, uint_in[f], i, i, i, f);
      sprintf(sys, uint_in[f], i, i, i, f);
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
      s21_sprintf(my, luint_in[f], i, i, i, f);
      sprintf(sys, luint_in[f], i, i, i, f);
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
      s21_sprintf(my, lluint_in[f], i, i, i, f);
      sprintf(sys, lluint_in[f], i, i, i, f);
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
  char f[] = "%*.*u + %.*lu + %*llu some jibberish\n";
  s21_sprintf(my, f, w1, p1, UINT_MAX, p2, ULONG_MAX, w2, ULLONG_MAX);
  sprintf(sys, f, w1, p1, UINT_MAX, p2, ULONG_MAX, w2, ULLONG_MAX);
  ck_assert_str_eq(my, sys);
}
END_TEST

Suite *suit(void) {
  Suite *s = suite_create("u_int");
  TCase *tc = tcase_create("unsigned int");
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
