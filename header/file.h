#ifndef _FILE_H
#define _FILE_H
FILE* File_open(const char* name,const char* mode);
void File_close(FILE* f);
size_t File_size(FILE* f);
char* File_getctx(FILE* f,size_t fsize);
void File_freectx(char* ctx,size_t fsize);
#endif
