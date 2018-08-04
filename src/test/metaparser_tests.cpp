#include "../metaparser.c"

TEST(metaparser, package_meta) {
  package_meta_t *pm = package_meta_init();
  extract_meta_from_package(pm, (char *)"resources/test/testutility.lha");
  ASSERT_EQ(pm->ver_maj, 1);
  //ASSERT_EQ("testutility", pm->name);
  package_meta_destruct(pm);
}

TEST(metaparser, generate_toc) {
  char *toc_tmp = (char *)"/tmp/toc_tmp";
  unsigned int tocs;
  list_t *toclist = list_init();

  tocs = generate_toc(toclist, (char *)"resources/test/packages.txt", toc_tmp);
  ASSERT_EQ(2, tocs);
  
  toc_t *toc = toc_init();
  parse_toc(toc, toc_tmp);
  toc_destruct(toc);

  // Assert file is removed, verifies it was created
  ASSERT_EQ(remove(toc_tmp), 0);

  ASSERT_GT(toc_find_package(toc, (char *)"testutility"), 0);

  list_destruct(toclist);
}

TEST(metaparser, _parse_toc_entry) {
  char *buffer = (char *)"#name:2.3.4";
  package_meta_t *meta = package_meta_init();
  _parse_toc_entry(meta, buffer);

  ASSERT_STREQ(meta->name, "name");
  ASSERT_EQ(meta->ver_maj, 2);
  ASSERT_EQ(meta->ver_min, 3);
  ASSERT_EQ(meta->ver_package, 4);

  package_meta_destruct(meta);
}

