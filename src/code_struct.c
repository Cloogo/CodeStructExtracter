#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/str.h"
#include "../header/file.h"
#include "../header/fmt.h"
#include "../header/args.h"
#include "../header/mem.h"

//extract structs (including:variants/declarations and methods) from c codes.
int
main(int argc,char* argv[]){
    if(argc<2){
        fprintf(stderr,"usage:%s file(s)\n",argv[0]);
        return 1;
    }
    int total_funcs=0,total_variants=0;
    for(int i=1;i<argc;i++){
        FILE* fin=File_open(argv[i],"r");
        size_t fsz=File_size(fin);
        char* code=File_getctx(fin,fsz);
        printf("< %s >:\n",argv[i]);
        delall_btw(code,"/*","*/",0);
        delall_btw(code,"//",NULL,0);
        delall_btw(code,"{","}",1);
        delall_btw(code,"#if","#endif",0);
        delall_btw(code,"asm",";",0);
        delall_btw(code,"#",NULL,0);
        delmore_newline(code);
        int nlines;
        char** lines=Args_get(code,"\n",&nlines);
        int sep=0;
        for(int i=0;i<nlines;i++){
            if(strrchr(lines[i],';')!=NULL){
                char* tmp=lines[i];
                lines[i]=lines[sep];
                lines[sep]=tmp;
                sep++;
            }
        }
        if(sep){
            total_variants+=sep;
            char* variants=Args_join(lines,sep,"\n");
            printf("%s",Fmt_text("Declaration/Variants:",30,'|','-',0));
            printf("%s\n",Fmt_text(variants,80,'|','-',1));
            safer_free(variants);
        }
        if(sep<nlines){
            total_funcs+=nlines-sep;
            char* func=Args_join(&lines[sep],nlines-sep,"\n");
            printf("%s",Fmt_text("Methods:",30,'|','-',0));
            printf("%s\n\n",Fmt_text(func,80,'|','-',1));
            safer_free(func);
        }
        Args_free(&lines,nlines);
        File_freectx(code,fsz);
        File_close(fin);
    }
    printf("%d global variants,%d functions.\n",total_variants,total_funcs);
    return 0;
}
