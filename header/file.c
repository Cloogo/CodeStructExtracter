#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

#include "err.h"

FILE* 
File_open(const char* name,const char* mode){
    FILE* f=fopen(name,mode);
    if(f==NULL){
        report_bug("fopen(%s,%s)",name,mode);
    }
    return f;
}

void
File_close(FILE* f){
    if(fclose(f)==EOF){
        report_bug("fclose()");
    }
}

size_t 
File_size(FILE* f){
    if(fseek(f,0,SEEK_END)==-1){
        report_bug("fseek(f,0,SEEK_END)");
    }
    return ftell(f);
}

char*
File_getctx(FILE* f,size_t fsize){
    char* ctx=mmap(NULL,fsize,PROT_WRITE,MAP_PRIVATE,fileno(f),0);
    if(ctx==MAP_FAILED){
        report_bug("mmap failed");
    }
    return ctx;
}

void
File_freectx(char* ctx,size_t fsize){
    munmap(ctx,fsize);
}
