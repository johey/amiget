#include "../utility.c"

TEST(utility, rtrim) {
  char trimmed[100];
  ASSERT_STREQ(rtrim(trimmed, (char *)"first"), (char *)"first");
  ASSERT_STREQ(rtrim(trimmed, (char *)"second   "), (char *)"second");
  ASSERT_STREQ(rtrim(trimmed, (char *)"third\n"), (char *)"third");
  ASSERT_STREQ(rtrim(trimmed, (char *)""), (char *)"");
  ASSERT_STREQ(rtrim(trimmed, (char *)" "), (char *)"");
  ASSERT_STREQ(rtrim(trimmed, (char *)"\n"), (char *)"");
  ASSERT_STREQ(rtrim(trimmed, (char *)"\t"), (char *)"");
}

TEST(utility, str_split) {
  char *parts[SPLIT_N_MAX];
  unsigned int size;

  size = str_split(parts, (char *)"", (char *)":");
  ASSERT_EQ(0, size);
  ASSERT_EQ(NULL, parts[0]);
  split_clean(parts, size);

  size = str_split(parts, (char *)"one:1", (char *)":");
  ASSERT_EQ(2, size);
  ASSERT_STREQ((char *)"one", parts[0]);
  ASSERT_STREQ((char *)"1", parts[1]);
  split_clean(parts, size);

  size = str_split(parts, (char *)"two", (char *)":");
  ASSERT_EQ(1, size);
  ASSERT_STREQ((char *)"two", parts[0]);
  split_clean(parts, size);

  size = str_split(parts, (char *)"", (char *)":");
  ASSERT_EQ(0, size);
  ASSERT_EQ(NULL, parts[0]);
  split_clean(parts, size);

  size = str_split(parts, (char *)":hej:svej::", (char *)":");
  ASSERT_EQ(2, size);
  ASSERT_STREQ((char *)"hej", parts[0]);
  split_clean(parts, size);
}

