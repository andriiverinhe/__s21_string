#include "../s21_sprintf.h"

char *s_in[] = {"%s %s yes",  "%.0s %.s\n",         "%.s %s\n",
                "%1s \n",     "%+ 050hs %+ 050s\n", "%-50s %.20s\n",
                "%020s %s\n", "%20.10s %s\n",       "%-20.10s %s\n",
                "%.25s %s\n", "%s %.25s\n"};
char *c_in[] = {"%c %c i:%d f:%d",
                "%.0c %.c i:%d f:%d\n",
                "%.c %c i:%d f:%d\n",
                "%1c %-c i:%d f:%d\n",
                "%+ 050c %+ 050c i:%d f:%d\n",
                "%-50c %.20c i:%d f:%d\n",
                "%020c %c i:%d f:%d\n",
                "%20.10c %c i:%d f:%d\n",
                "%-20.10c %c i:%d f:%d\n",
                "%.25c %c i:%d f:%d\n",
                "%c %.25c i:%d f:%d\n"};

START_TEST(s1_small) {
  char str[] = "test string";
  char str2[] = "MBJR WBAPU 7C";
  char out_my[1000] = "";
  char out_sys[1000] = "";
  for (int i = 0; i < 11; i++) {
    s21_sprintf(out_my, s_in[i], str, str2);
    sprintf(out_sys, s_in[i], str, str2);
    ck_assert_str_eq(out_my, out_sys);
  }
}
END_TEST

START_TEST(s2_spec_sym) {
  char str[] = "\ttab \\t \ttab \' \n\n\n 3newline \0string";
  char str2[] = "end string";
  char out_my[1000] = "";
  char out_sys[1000] = "";
  for (int i = 0; i < 11; i++) {
    s21_sprintf(out_my, s_in[i], str, str2);
    sprintf(out_sys, s_in[i], str, str2);
    ck_assert_str_eq(out_my, out_sys);
  }
}
END_TEST

START_TEST(s3_aster) {
  char str[] = "WAR IS PEACE FREEDOM IS SLAVERY IGNORANCE IS STRENGTH";
  char str2[] = "MBJR WBAPU 7C";
  char out_my[1000] = "";
  char out_sys[1000] = "";
  int w1 = 10;
  int p1 = 5;
  int w2 = 6;
  int p2 = 17;
  char f[] = "%*.*s + %.*s + %*s";
  s21_sprintf(out_my, f, w1, p1, str, p2, str, w2, str2);
  sprintf(out_sys, f, w1, p1, str, p2, str, w2, str2);
  ck_assert_str_eq(out_my, out_sys);
}
END_TEST

START_TEST(s4_wide) {
  wchar_t str[] = L"first test string";
  wchar_t str2[] = L"end string";
  char out_my[1000] = "";
  char out_sys[1000] = "";
  int w1 = 10;
  int p1 = 5;
  int w2 = 6;
  int p2 = 17;
  char f[] = "%*.*ls + %.*ls + %*ls";
  s21_sprintf(out_my, f, w1, p1, str, p2, str, w2, str2);
  sprintf(out_sys, f, w1, p1, str, p2, str, w2, str2);
  ck_assert_str_eq(out_my, out_sys);

  wchar_t str3[] = L"ßÔÔß§ negative test";
  wchar_t str4[] = L"end string";
  s21_sprintf(out_my, f, w1, p1, str3, p2, str3, w2, str4);
  sprintf(out_sys, f, w1, p1, str3, p2, str3, w2, str4);
  ck_assert_str_eq(out_my, out_sys);
}
END_TEST

START_TEST(s5_non_empty) {
  char str[] = "tHis A TeSt StRing";
  char str2[] = "end string";
  char out_my[1000] =
      "non empty out string must contain only new information\n";
  char out_sys[1000] =
      "non empty out string must contain only new information\n";
  for (int i = 0; i < 11; i++) {
    s21_sprintf(out_my, s_in[i], str, str2);
    sprintf(out_sys, s_in[i], str, str2);
    ck_assert_str_eq(out_my, out_sys);
  }
}
END_TEST

START_TEST(s6_big) {
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
  char str2[] =
      "ALL ANIMALS ARE EQUAL BUT SOME ANIMALS ARE MORE EQUAL THAN OTHERS.";
  char out_my[10000] = "";
  char out_sys[10000] = "";
  for (int i = 0; i < 11; i++) {
    s21_sprintf(out_my, s_in[i], str, str2);
    sprintf(out_sys, s_in[i], str, str2);
    ck_assert_str_eq(out_my, out_sys);
  }
}
END_TEST

START_TEST(c1_norm) {
  char my[1000] = "";
  char sys[1000] = "";
  for (int ch = 0; ch < 255; ch++) {
    for (int f = 0; f < 11; f++) {
      s21_sprintf(my, c_in[f], (char)ch, (char)ch, ch, f);
      sprintf(sys, c_in[f], (char)ch, (char)ch, ch, f);
      ck_assert_str_eq(my, sys);
    }
  }
}
END_TEST

START_TEST(c2_args) {
  char my[100000] = "";
  char sys[100000] = "";
  char str[] = "also some string to add";
  char f[] = "%*c %*c %*c %c %c %c %c %s";
  for (int ch = 0; ch < 255; ch++) {
    s21_sprintf(my, f, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, str);
    sprintf(sys, f, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, str);
    ck_assert_str_eq(my, sys);
  }
}
END_TEST

START_TEST(c3_wchar) {
  char my[100000] = "";
  char sys[100000] = "";
  char str[] = "also some string to add";
  char f[] = "%*lc %*lc %*lc %Lc %Lc %lc %lc %s";
  for (wchar_t ch = L' '; ch < 255; ch++) {
    s21_sprintf(my, f, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, str);
    sprintf(sys, f, ch, ch, ch, ch, ch, ch, ch, ch, ch, ch, str);
    ck_assert_str_eq(my, sys);
  }
}
END_TEST

START_TEST(s7_break_parser) {
  char my[100000] = "";
  char sys[100000] = "";
  char str[] = "also some string to add";
  char f[] = "%++s %--s %lls\n";
  s21_sprintf(my, f, str);
  sprintf(sys, f, str);
  ck_assert_str_eq(my, sys);
}
END_TEST

Suite *suit(void) {
  Suite *s = suite_create("s_c spefs");
  TCase *tc = tcase_create("string");

  tcase_add_test(tc, s1_small);
  tcase_add_test(tc, s2_spec_sym);
  tcase_add_test(tc, s3_aster);
  tcase_add_test(tc, s4_wide);
  tcase_add_test(tc, s5_non_empty);
  tcase_add_test(tc, s6_big);
  tcase_add_test(tc, s7_break_parser);
  
  TCase *tc2 = tcase_create("char");
  tcase_add_test(tc2, c1_norm);
  tcase_add_test(tc2, c2_args);
  tcase_add_test(tc2, c3_wchar);
  suite_add_tcase(s, tc);
  suite_add_tcase(s, tc2);
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
