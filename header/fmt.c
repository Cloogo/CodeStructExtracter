#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "args.h"
#include "fmt.h"
#define MAX_TEXT_LENGTH 1024*1024
#define BORDER_WIDTH 1
#define SPACE_WIDTH 1
#define NEW_LINE_WIDTH 1
#define TAB_WIDTH 4
#define LINE_NUM_WIDTH 5
#define DEFAULT_WINSEP_WIDTH 5

char*
Fmt_text(const char* txt,int w,char lborder,char uborder,int labeled){
    static char buf[MAX_TEXT_LENGTH];
    char* pbuf=buf;
    int linew=BORDER_WIDTH+LINE_NUM_WIDTH*labeled+BORDER_WIDTH*labeled+\
              SPACE_WIDTH+w+SPACE_WIDTH+BORDER_WIDTH;
    memset(pbuf,uborder,linew*sizeof(char));
    pbuf+=linew;
    *pbuf++='\n';
    int newline=labeled;
    int linenum=1;
    const char *ptxt=txt;
    for(;*ptxt!='\0';){
        *pbuf++=lborder;
        if(labeled){
            if(newline){
                sprintf(pbuf,"%*d|",LINE_NUM_WIDTH,linenum);
                pbuf+=strlen(pbuf);
                newline=0;
            }else{
                sprintf(pbuf,"%.*s|",LINE_NUM_WIDTH,"           ");
                pbuf+=LINE_NUM_WIDTH+BORDER_WIDTH;
            }
        }
        *pbuf++=' ';
        int remain=w;
        for(;*ptxt!='\0'&&remain;){
            if(*ptxt=='\n'){
                ptxt++;
                if(labeled){
                    newline=1;
                    linenum++;
                }
                break;
            }else if(*ptxt=='\t'){
                ptxt++;
                if(remain>=TAB_WIDTH){
                    memset(pbuf,' ',TAB_WIDTH*sizeof(char));
                    pbuf+=TAB_WIDTH;
                    remain-=TAB_WIDTH;
                }else{
                    break;
                }
            }else{
                *pbuf++=*ptxt++;
                remain--;
            }
        }
        while(remain>0){
            *pbuf++=' ';
            remain--;
        }
        *pbuf++=' ';
        *pbuf++=lborder;
        *pbuf++='\n';
    }
    memset(pbuf,uborder,linew*sizeof(char));
    *(pbuf+linew)='\n';
    *(pbuf+linew+NEW_LINE_WIDTH)='\0';
    return buf;
}

char*
Fmt_texts(char* txt1,int w1,char* txt2,int w2){
    static char buf[MAX_TEXT_LENGTH];
    char* ftxt1=Fmt_text(txt1,w1,'|','-',1);
    int nlines1,nlines2;
    char** lines1=Args_get(ftxt1,"\n",&nlines1);
    char* ftxt2=Fmt_text(txt2,w2,'|','-',1);
    char** lines2=Args_get(ftxt2,"\n",&nlines2);
    if(nlines1>nlines2){
    }else{
        int tmp=nlines1;
        nlines1=nlines2;
        nlines2=tmp;
        char** ltmp=lines1;
        lines1=lines2;
        lines2=ltmp;
    }
    char* pbuf=buf;
    for(int i=0;i<nlines2;i++){
        sprintf(pbuf,"%s     %s\n",lines1[i],lines2[i]);
        pbuf+=strlen(pbuf);
    }
    for(int i=nlines2;i<nlines1;i++){
        sprintf(pbuf,"%s\n",lines1[i]);
        pbuf+=strlen(pbuf);
    }
    Args_free(&lines1,nlines1);
    Args_free(&lines2,nlines2);
    return buf;
}
