#include "../s21_sprintf.h"

char *e_in[] = {"%#e %e %e e:%e",
                "%#.0e %#.e %# e e:%+0e\n",
                "%+e % e %-40e e:%-0e\n",
                "%-1e % 1e %.1e e:% 0e\n",
                "%+1e %050e %#+050e e:%+- 0e\n",
                "%-050e % 050e % .8e e:%e\n",
                "%+.10E %-.10E % 100.10E e:%e\n",
                "%+10.08E %-10.08e %-10.08E e:%e\n",
                "%+010.08e % 010.08E %-010.08E e:%e\n",
                "%+050.10e % 050.10E %-50.10e e:%e\n",
                "%#+50.10e %# 40.10E %#-40.15e e:%e\n"};

char *le_in[] = {"%#Le %Le %Le Le:%Le",
                 "%#.0Le %#.Le %# Le Le:%+0Le\n",
                 "%+Le % Le %-40Le Le:%-0Le\n",
                 "%-1Le % 1Le %.1Le Le:% 0Le\n",
                 "%+1Le %050Le %#+050Le Le:%+- 0Le\n",
                 "%-050Le % 050Le % .28Le Le:%Le\n",
                 "%+.10LE %-.10Le % 100.10LE Le:%Le\n",
                 "%+10.20Le % 10.20LE %-10.20Le Le:%Le\n",
                 "%+010.20LE % 010.20Le %-010.20LE Le:%Le\n",
                 "%+050.15Le % 50.10Le %-50.10Le Le:%Le\n",
                 "%#+50.10Le %# 40.10Le %#-40.15Le Le:%Le\n"};

START_TEST(t1_sneg) {
  char my[10000] = "";
  char sys[10000] = "";
  for (double i = -10.73456780000000066; i < 0; i += 1.0) {
    for (int f = 0; f < 11; f++) {
      s21_sprintf(my, e_in[f], i, i, i, (double)f);
      sprintf(sys, e_in[f], i, i, i, (double)f);
      ck_assert_str_eq(my, sys);
    }
  }
  double i = 0;
  for (int f = 0; f < 11; f++) {
    s21_sprintf(my, e_in[f], i, i, i, (double)f);
    sprintf(sys, e_in[f], i, i, i, (double)f);
    ck_assert_str_eq(my, sys);
  }
}
END_TEST

START_TEST(t2_spos) {
  char my[10000] = "";
  char sys[10000] = "";
  for (double i = 10.1234567; i > 0; i -= 1.0) {
    for (int f = 0; f < 11; f++) {
      s21_sprintf(my, e_in[f], i, i, i, (double)f);
      sprintf(sys, e_in[f], i, i, i, (double)f);
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
      s21_sprintf(my, e_in[f], i, i, i, (double)f);
      sprintf(sys, e_in[f], i, i, i, (double)f);
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
      s21_sprintf(my, e_in[f], i, i, i, (double)f);
      sprintf(sys, e_in[f], i, i, i, (double)f);
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
      s21_sprintf(my, le_in[f], i, i, i, (long double)f);
      sprintf(sys, le_in[f], i, i, i, (long double)f);
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
      s21_sprintf(my, le_in[f], i, i, i, (long double)f);
      sprintf(sys, le_in[f], i, i, i, (long double)f);
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
  char f[] = "%*.*e + %.*Le + %*Le some jibberish\n";
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
    s21_sprintf(my, e_in[f], i, i, i, (double)f);
    sprintf(sys, e_in[f], i, i, i, (double)f);
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
  char f[] = "%e %e %+*.*e + %.*Le + % *Le some jibberish\n";
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
  Suite *s = suite_create("E e test");
  TCase *tc = tcase_create("e double");
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
