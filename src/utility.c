#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "utility.h"

char *rtrim(char *out, char *in) {
  strcpy(out, in);
  unsigned int end = strlen(in);
  while (isspace(in[--end]));
  out[end + 1] = 0;
  return out;
}


unsigned int str_split(char *out[SPLIT_N_MAX], char *in, char *delimiter) {
  char *str, *token, buffer[1024];
  unsigned int i;

  strcpy(buffer, in);

  for (i = 0; i < SPLIT_N_MAX; i++) {
    out[i] = NULL;
  }

  for (i = 0, str = buffer; ; str = NULL) {
		token = strtok(str, delimiter);
		if (token == NULL)
			break;
    out[i] = (char *)malloc((strlen(token) + 1) * sizeof(char));
    strcpy(out[i], token);
    i++;
	}

	return i;
}


void split_clean(char *out[SPLIT_N_MAX], unsigned int size) {
  for (unsigned int i = 0; i < size; i++) {
    free(out[i]);
    out[i] = NULL;
  }
}

