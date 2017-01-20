#ifndef _STR_H
#define _STR_H
extern char* reverse(char* str,int start,int end);
extern char* append(char* str);
extern int starts_with(const char* str,const char* prefix);
extern int ends_with(const char* str,const char* suffix);
extern char* ltrim(char* str,const char* prefix);
extern char* rtrim(char* str,const char* suffix);
extern char* delall_btw(char* str,char* head,char* tail,int reserve);
extern char* delmore_newline(char* str);
extern char* del_lines_ncontain(char* str,char* factors);
#endif
