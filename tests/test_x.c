#include "../s21_sprintf.h"

char *x_in[] = {"%x %#x %X f:%x",
                  "%.0x %.x %X f:%0x\n",
                  "%hx %hx %-40hX f:%-0x\n",
                  "%-1x %1x %.1X f:%0x\n",
                  "%1x %050x %050X f:%- 0x\n",
                  "%-050x %050x %.50X f:%x\n",
                  "%.50x %-.50x %100.50X f:%x\n",
                  "%100.50x %-98.50x %-097.50X f:%x\n",
                  "%096.50x %095.50x %-050.94X f:%x\n",
                  "%050.93x %50.92x %50.91X f:%x\n",
                  "%-050.90x %040.89x %040.89X f:%x\n"};

char *lx_in[] = {"%lx %lx %lx f:%lx",
                  "%.0lx %.lx %lx f:%0lx\n",
                  "%#lx %#25lx %#-40lX f:%-0lx\n",
                  "%-1lx %1lx %.1lx f:%0lx\n",
                  "%1lx %050lx %050lX f:%- 0lx\n",
                  "%-050lx %050lx %.50lX f:%lx\n",
                  "%.50lx %-.50lx %100.50lX f:%lx\n",
                  "%100.50lx %-98.50lx %-097.50lX f:%lx\n",
                  "%096.50lx %095.50lx %-050.94lX f:%lx\n",
                  "%050.93lx %50.92lx %50.91lx f:%lx\n",
                  "%-050.90lx %040.89lx %040.89lx f:%lx\n"};

char *llx_in[] = {"%llx %llx %25llx f:%llx",
                  "%.0llx %.llx %llx f:%0llx\n",
                  "%#llx %#25llx %#-40llx f:%-0llx\n",
                  "%-1llx %1llx %.1llx f:%0llx\n",
                  "%1llx %050llx %050llx f:%- 0llx\n",
                  "%-050llx %050llx %.50llx f:%llx\n",
                  "%.50llx %-.50llx %100.50llx f:%llx\n",
                  "%100.50llx %-98.50llx %-097.50llx f:%llx\n",
                  "%096.50llx %095.50llx %-050.94llx f:%llx\n",
                  "%050.93llx %50.92llx %50.91llx f:%llx\n",
                  "%-050.90llx %040.89llx %040.89llx f:%llx\n"};


START_TEST(t1_int) {
  char my[10000] = "";
  char sys[10000] = "";
  for (unsigned int i = 0; i < 10000000; i += 66666) {
    for (int f = 0; f < 11; f++) {
      s21_sprintf(my, x_in[f], i, i, i, f);
      sprintf(sys, x_in[f], i, i, i, f);
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
      s21_sprintf(my, lx_in[f], i, i, i, f);
      sprintf(sys, lx_in[f], i, i, i, f);
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
      s21_sprintf(my, llx_in[f], i, i, i, f);
      sprintf(sys, llx_in[f], i, i, i, f);
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
  char f[] = "%*.*x + %.*lX + %*llx some jibberish\n";
  s21_sprintf(my, f, w1, p1, UINT_MAX, p2, ULONG_MAX, w2, ULLONG_MAX);
  sprintf(sys, f, w1, p1, UINT_MAX, p2, ULONG_MAX, w2, ULLONG_MAX);
  ck_assert_str_eq(my, sys);
}
END_TEST

Suite *suit(void) {
  Suite *s = suite_create("x_suit");
  TCase *tc = tcase_create("x_case");
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
