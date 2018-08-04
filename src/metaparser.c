#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "metaparser.h"

int extract_meta_from_package(package_meta_t *pm, char *package) {
  FILE *meta_file;

  pm->ver_maj = 1;

  system("lha xf resources/test/testutility-1.0.1.lha amiget_meta");
  meta_file = fopen("amiga_meta", "r");
  if (meta_file)
    fclose(meta_file);
  remove("amiga_meta");

  return 0;
}


void _parse_toc_entry(package_meta_t *meta, char *buffer) {
	buffer++;
  char *splits[SPLIT_N_MAX], *subsplits[SPLIT_N_MAX];
  unsigned int size, subsize;

  size = str_split(splits, buffer, (char *)":");
  meta->name = (char *)malloc((strlen(splits[0] + 1) * sizeof(char)));
  strcpy(meta->name, splits[0]);
  subsize = str_split(subsplits, splits[1], (char *)".");
  meta->ver_maj = atoi(subsplits[0]);
  meta->ver_min = atoi(subsplits[1]);
  meta->ver_package = atoi(subsplits[2]);
  split_clean(subsplits, subsize);
  split_clean(splits, size);
  printf("Name:'%s'\n", meta->name);
}


unsigned int generate_toc(list_t *toc_list, char *packages_filename, char *toc_filename) {
  FILE *packages_file, *toc_file;

  if (!(packages_file = fopen(packages_filename, "r"))) {
    printf("Cannot open file '%s' for reading.\n", packages_filename);
    return 0;
  }

  if (!(toc_file = fopen(toc_filename, "w"))) {
    printf("Cannot open file '%s' for writing.\n", toc_filename);
    return 0;
  }

  printf("Reading packages from '%s'\n", packages_filename);
  printf("Writing toc to '%s'\n", toc_filename);

  char buffer[1024];
  unsigned int tocs = 0;
  while(fgets(buffer, 1024, packages_file)) {
    rtrim(buffer, buffer);
    //printf("Line: '%s'\n", buffer);
    if (buffer[0] == '#') {
      package_meta_t *meta = package_meta_init();
      _parse_toc_entry(meta, buffer);
      list_push_back(toc_list, (package_meta_t *)meta, 1);
      package_meta_destruct(meta);
      tocs++;
      continue;
    }
  }

  fclose(packages_file);
  fclose(toc_file);

  return tocs;
}


void parse_toc(toc_t *toc, char *path) {
  FILE *file;
  if (!(file = fopen(path, "r"))) {
    printf("Cannot open file '%s' for reading.\n", path);
    return;
  }

  fclose(file);
}


unsigned int toc_find_package(toc_t *toc, char *path) {
  return 1;
}


// Init functions
toc_t *toc_init() {
  toc_t *toc = (toc_t *)malloc(sizeof(toc_t));
  if (!toc) {
    printf("Not enough memory for allocating toc\n");
    exit(1);
  }
  return toc;
}


package_meta_t *package_meta_init() {
  package_meta_t *package_meta = (package_meta_t *)malloc(sizeof(package_meta_t));
  if (!package_meta) {
    printf("Not enough memory for allocating package_meta\n");
    exit(1);
  }
  package_meta->name = NULL;
  package_meta->description = NULL;
  package_meta->ver_maj = 0;
  package_meta->ver_min = 0;
  package_meta->ver_package = 0;
  return package_meta;
}


// Destruct functions
void toc_destruct(toc_t *toc) {
  free(toc);
  toc = NULL;
}


void package_meta_destruct(package_meta_t *package_meta) {
  if (package_meta->name) {
    free(package_meta->name);
  }
  free(package_meta);
  package_meta = NULL;
}


