#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "str.h"
#define MAX_BUF 1024*64

char*
reverse(char* str,int start,int end){
    static char org[MAX_BUF];
    snprintf(org,strlen(str)+1,"%s",str);
    char* p=str;
    char tmp;
    for(;start<end;start++,end--){
        tmp=*(p+start);
        *(p+start)=*(p+end);
        *(p+end)=tmp;
    }
    return org;
}

char*
append(char* str){
    static char buf[MAX_BUF];
    static char* pbuf=buf;
    char* pend=buf+MAX_BUF;
    if(pbuf>=pend){
        return NULL;
    }
    if(str==NULL){
        *pbuf='\0';
        pbuf=buf;
        return buf;
    }
    strcpy(pbuf,str);
    pbuf+=strlen(str);
}

int
starts_with(const char* str,const char* prefix){
    int slen=strlen(str);
    int plen=strlen(prefix);
    return strncasecmp(str,prefix,plen)==0;
}

int
ends_with(const char* str,const char* suffix){
    int slen=strlen(str);
    int flen=strlen(suffix);
    return strncasecmp(str+slen-flen,suffix,flen)==0;
}

char*
ltrim(char* str,const char* prefix){
    int slen=strlen(str);
    int plen=strlen(prefix);
    if(starts_with(str,prefix)){
        memmove(str,str+plen,slen-plen+1);
    }
    return str;
}

char*
rtrim(char* str,const char* suffix){
    if(ends_with(str,suffix)){
        *(str+strlen(str)-strlen(suffix))='\0';
    }
    return str;
}

char*
delall_btw(char* str,char* head,char* tail,int reserve){
    assert(str!=NULL&&head!=NULL);
    char lv_tail[16];
    if(tail==NULL){
        strcpy(lv_tail,"\n");
    }else{
        strcpy(lv_tail,tail);
    }
    char* pnew=str;
    char* pold=str;
    int hlen=strlen(head);
    int tlen=strlen(lv_tail);
    int depth=0;
    for(;*pold!='\0';){
        if(strncmp(pold,head,hlen)==0){
            depth++;
            if(reserve){
                strncpy(pnew,pold,hlen);
                pnew+=hlen;
            }
            pold+=hlen;
            if(strcmp(head,lv_tail)==0){
                depth--;
            }
        }else{
            *pnew++=*pold++;
        }
        while(*pold!='\0'&&depth){
            if(strncmp(pold,lv_tail,tlen)==0){
                depth--;
                if(reserve){
                    strncpy(pnew,pold,tlen);
                    pnew+=tlen;
                }
                pold+=tlen;
            }else if(strncmp(pold,head,hlen)==0){
                depth++;
                if(reserve){
                    strncpy(pnew,pold,hlen);
                    pnew+=hlen;
                }
                pold+=hlen;
            }else{
                pold++;
            }
        }
    }
    *pnew='\0';
    return str;
}

char*
del_lines_contain(char* str,char* factors){
}

char*
del_lines_ncontain(char* str,char* factors){
    char* pavail=str;
    char* pend=str;
    char* pcur=str;
    int update;
    for(;*pcur!='\0';){
        update=0;
        while(*pcur!='\0'){
            if(strchr(factors,*pcur)!=NULL){
                update=1;
            }
            if(*pcur=='\n')break;
            *pend++=*pcur++;
        }
        *pend++=*pcur++;
        if(update){
            pavail=pend;
        }else{
            pend=pavail;
        }
    }
    *pavail='\0';
    return str;
}

char*
delmore_newline(char* str){
    char* oldp=str;
    char* newp=str;
    for(;*oldp!='\0';){
        *newp=*oldp;
        if(*oldp=='\n'){
            if(oldp==str){
                newp--;
            }
            while(*oldp!='\0'&&*oldp=='\n'){
                oldp++;
            }
        }else{
            oldp++;
        }
        newp++;
    }
    *newp='\0';
    return str;
}
