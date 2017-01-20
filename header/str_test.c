#include <stdio.h>
#include <string.h>
#include "test.h"
#include "str.h"

int
main(){
    char teststr[][16]={{"Hello world!"},{"Cloogo"},{"Google"},{"Neteasy"}};
    char wantstr[][16]={{"H!dlrow olle"},{"Cogool"},{"Gelgoo"},{"Nysaete"}};
    char buf[16];
    for(int i=0;i<4;i++){
        sprintf(buf,"%s",reverse(teststr[i],1,strlen(teststr[i])-1));
        test_cond(strcmp(teststr[i],wantstr[i])==0,"%s %s",buf,wantstr[i]);
    }
    test_cond(starts_with("Hello world","He")==1,"");
    test_cond(starts_with("Hello world","We")==0,"");
    test_cond(ends_with("Hello world","ld")==1,"");
    test_cond(ends_with("Hello world","le")==0,"");

    sprintf(buf,"%s","Hello world");
    test_cond(strcmp(ltrim(buf,"Hello")," world")==0,"");
    test_cond(strcmp(buf," world")==0,"");
    sprintf(buf,"%s","Hello world");
    test_cond(strcmp(rtrim(buf,"ld"),"Hello wor")==0,"");
    test_cond(strcmp(buf,"Hello wor")==0,"");

    sprintf(buf,"%s","");
    test_cond(strcmp(del_lines_ncontain(buf,""),"")==0,"");
    sprintf(buf,"%s","H");
    test_cond(strcmp(del_lines_ncontain(buf,"H"),"H")==0,"");
    sprintf(buf,"%s","Hello world");
    test_cond(strcmp(del_lines_ncontain(buf,"x"),"")==0,"");
    test_cond(strcmp(buf,"")==0,"");
    sprintf(buf,"%s","H\ne\nllo \nworld");
    test_cond(strcmp(del_lines_ncontain(buf,"o"),"llo \nworld")==0,"");
    sprintf(buf,"%s","\nH\ne\nllo \nworld");
    test_cond(strcmp(del_lines_ncontain(buf,"o"),"llo \nworld")==0,"");
    sprintf(buf,"%s","H\ne\nllo \nworld");
    test_cond(strcmp(del_lines_ncontain(buf,"x"),"")==0,"");
    sprintf(buf,"%s","H\ne\nllo \nworld");
    test_cond(strcmp(del_lines_ncontain(buf,"H"),"H\n")==0,"");
    sprintf(buf,"%s","H\ne\nllo \nworld");
    test_cond(strcmp(del_lines_ncontain(buf,"\n"),"H\ne\nllo \n")==0,"");
    sprintf(buf,"%s","H\ne\nllo \nworld");
    test_cond(strcmp(del_lines_ncontain(buf,"lo"),"llo \nworld")==0,"");
    test_report();
    return 0;
}
