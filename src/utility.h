#ifndef __UTILITY_H
#define __UTILITY_H

#define SPLIT_N_MAX 16

char *rtrim(char *out, char *in);
unsigned int str_split(char *out[SPLIT_N_MAX], char *in, char *delimiter);
void split_clean(char *out[SPLIT_N_MAX], unsigned int size);

#endif

