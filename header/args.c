#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "args.h"
#include "mem.h"

#define skip_space(p) while(*p&&isspace(*p)){p++;}
#define ARGS_NAME_LENGTH 1024

char**
Args_get(char* line,char* delim,int* nargs){
    char* p=line;
    *nargs=0;
    skip_space(p);
    while(*p){
        if(strchr(delim,*p)==NULL){
            ++*nargs;
            p++;
            while(*p&&strchr(delim,*p)==NULL){
                p++;
            }
        }else{
            while(*p&&strchr(delim,*p)!=NULL){
                p++;
            }
        }
    }
    char** args;
    safer_malloc(args,*nargs*sizeof(char*));
    p=line;
    char sbuf[ARGS_NAME_LENGTH];
    char* sp=sbuf;
    int idx=0,len;
    skip_space(p);
    while(*p){
        while(*p&&strchr(delim,*p)==NULL){
            *sp++=*p++;
        }
        *sp='\0';
        len=sp-sbuf+1;
        if(len>1){
            safer_malloc(args[idx],len);
            strncpy(args[idx],sbuf,len);
            sp=sbuf;
            idx++;
        }
        while(*p&&strchr(delim,*p)!=NULL){
            p++;
        }
    }
    *sp='\0';
    len=sp-sbuf+1;
    if(len>1){
        safer_malloc(args[idx],len);
        strncpy(args[idx],sbuf,len);
    }
    return args;
}

char*
Args_join(char** args,int nargs,char* delim){
    int len=0,dlen=strlen(delim);
    for(int i=0;i<nargs;i++){
        len+=strlen(args[i])+dlen;
    }
    len=len-dlen+1;
    char* dst,*p;
    safer_malloc(dst,len);
    p=dst;
    strcpy(p,args[0]);
    p+=strlen(args[0]);
    for(int i=1;i<nargs;i++){
        strcpy(p,delim);
        p+=dlen;
        strcpy(p,args[i]);
        p+=strlen(args[i]);
    }
    *p='\0';
    return dst;
}

void
Args_free(char*** args,int nargs){
    for(int i=0;i<nargs;i++){
        safer_free(args[0][i]);
    }
    safer_free(*args);
}
