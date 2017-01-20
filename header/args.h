#ifndef _ARGS_H
#define _ARGS_H
char** Args_get(char* line,char* delim,int* nargs);
char* Args_join(char** args,int nargs,char* delim);
void Args_free(char*** args,int nargs);
#endif
