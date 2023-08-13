#include "../s21_sprintf.h"

START_TEST(t1) {
  char str[] = "test string";
  char str2[] = "MBJR WBAPU 7C";
  char out_my[1000] = "";
  char out_sys[1000] = "";
  int res = 0;
  int sres = 0;
  s21_sprintf(out_my, "%n %s %s\n", &res, str, str2);
  sprintf(out_sys, "%n %s %s\n", &sres, str, str2);
  ck_assert_str_eq(out_my, out_sys);
  ck_assert_int_eq(res, sres);
}
END_TEST

START_TEST(t2) {
  char str[] = "test string";
  char str2[] = "MBJR WBAPU 7C";
  char out_my[1000] = "";
  char out_sys[1000] = "";
  int res = 0;
  int sres = 0;
  s21_sprintf(out_my, "%s %s %n\n", str2, str, &res);
  sprintf(out_sys, "%s %s %n\n", str2, str, &sres);
  ck_assert_str_eq(out_my, out_sys);
  ck_assert_int_eq(res, sres);
}
END_TEST

START_TEST(t3) {
  char str[] =
      "There was the same hearty cheering as before, and the mugs were emptied "
      "to the dregs. But as the animals outside gazed at the scene, it seemed "
      "to them that some strange thing was happening. What was it that had "
      "altered in the faces of the pigs? Clover's old dim eyes flitted from "
      "one face to another. Some of them had five chins, some had four, some "
      "had three. But what was it that seemed to be melting and changing? "
      "Then, the applause having come to an end, the company took up their "
      "cards and continued the game that had been interrupted, and the animals "
      "crept silently away. But they had not gone twenty yards when they "
      "stopped short. An uproar of voices was coming from the farmhouse. They "
      "rushed back and looked through the window again. Yes, a violent quarrel "
      "was in progress. There were shoutings, hangings on the table, sharp "
      "suspicious glances, furious denials. The source of the trouble appeared "
      "to be that Napoleon and Mr Pilkington had each played an ace of spades "
      "simultaneously. Twelve voices were shouting in anger, and they were all "
      "alike. No question, now, what had happened to the faces of the pigs. "
      "The creatures outside looked from pig to man, and from man to pig, and "
      "from pig to man again: but already it was impossible to say which was "
      "which.";
  char str2[] = "end string not counted";
  char out_my[10000] = "";
  char out_sys[10000] = "";
  int res = 0;
  int sres = 0;
  s21_sprintf(out_my, "%s \n\n\n\n\n\n %n %s\n", str, &res, str2);
  sprintf(out_sys, "%s \n\n\n\n\n\n %n %s\n", str, &sres, str2);
  ck_assert_str_eq(out_my, out_sys);
  ck_assert_int_eq(res, sres);
}
END_TEST

START_TEST(t4) {
  int str = 123456789;
  int str2 = -987654321;
  char out_my[1000] = "";
  char out_sys[1000] = "";
  int res = 0;
  int sres = 0;
  s21_sprintf(out_my, "%d %d %n\n", str2, str, &res);
  sprintf(out_sys, "%d %d %n\n", str2, str, &sres);
  ck_assert_str_eq(out_my, out_sys);
  ck_assert_int_eq(res, sres);
}
END_TEST

START_TEST(t5) {
  unsigned str = 123456789;
  unsigned str2 = -987654321;
  char out_my[1000] = "";
  char out_sys[1000] = "";
  int res = 0;
  int sres = 0;
  s21_sprintf(out_my, "%x %x %n\n", str2, str, &res);
  sprintf(out_sys, "%x %x %n\n", str2, str, &sres);
  ck_assert_str_eq(out_my, out_sys);
  ck_assert_int_eq(res, sres);
}
END_TEST

START_TEST(t6) {
  unsigned str = 123456789;
  unsigned str2 = -987654321;
  char out_my[1000] = "";
  char out_sys[1000] = "";
  int res = 0;
  int sres = 0;
  s21_sprintf(out_my, "%o %o %n some string\n", str2, str, &res);
  sprintf(out_sys, "%o %o %n some string\n", str2, str, &sres);
  ck_assert_str_eq(out_my, out_sys);
  ck_assert_int_eq(res, sres);
}
END_TEST

START_TEST(t7) {
  double str = 123456.789;
  double str2 = -9876.54321;
  double g = 0.12345;
  char out_my[1000] = "";
  char out_sys[1000] = "";
  int res = 0;
  int sres = 0;
  s21_sprintf(out_my, "%g %f %e %n some string\n", g, str2, str, &res);
  sprintf(out_sys, "%g %f %e %n some string\n", g, str2, str, &sres);
  ck_assert_str_eq(out_my, out_sys);
  ck_assert_int_eq(res, sres);
}
END_TEST


START_TEST(t8) {
  double str = 123456.789;
  double str2 = -9876.54321;
  double g = 0.12345;
  char out_my[1000] = "";
  char out_sys[1000] = "";
  long int res = 0;
  long int sres = 0;
  long long int res1 = 0;
  long long int sres1 = 0;
  s21_sprintf(out_my, "%g %f %e %ln %lln some string\n", g, str2, str, &res, &res1);
  sprintf(out_sys, "%g %f %e %ln %lln some string\n", g, str2, str, &sres, &sres1);
  ck_assert_str_eq(out_my, out_sys);
  ck_assert_int_eq(res, sres);
  ck_assert_int_eq(res1, sres1);
}
END_TEST

Suite *suit(void) {
  Suite *s = suite_create("n spec");
  TCase *tc = tcase_create("n case");
  tcase_add_test(tc, t1);
  tcase_add_test(tc, t2);
  tcase_add_test(tc, t3);
  tcase_add_test(tc, t4);
  tcase_add_test(tc, t5);
  tcase_add_test(tc, t6);
  tcase_add_test(tc, t7);
  tcase_add_test(tc, t8);
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
