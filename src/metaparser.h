#ifndef __METAPARSER_H
#define __METAPARSER_H

#include "list.h"
#include "utility.h"

typedef struct package_meta {
  char *name;
  unsigned char ver_maj, ver_min, ver_package;
  char *description;
} package_meta_t;

typedef struct toc {
  package_meta_t **packages;
  unsigned int size;
} toc_t;

int extract_meta_from_package(package_meta_t *pm, char *package);

unsigned int generate_toc(list_t *toc_list, char *packages_filename, char *toc_filename);
void parse_toc(toc_t *toc, char *path);
unsigned int toc_find_package(toc_t *toc, char *path);

// Init functions
toc_t *toc_init();
package_meta_t *package_meta_init();


// Destruct functions
void toc_destruct(toc_t *toc);
void package_meta_destruct(package_meta_t *package_meta);

#endif

