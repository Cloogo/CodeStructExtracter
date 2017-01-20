#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem.h"
#include "args.h"
#include "test.h"

int
main(){
    int nargs;
    char** args=Args_get("trim text.c"," ",&nargs);
    test_cond(nargs==2&&strcmp(args[0],"trim")==0&&strcmp(args[1],"text.c")==0,"Args_get(\"trim text.c\",\" \"):");
    Args_free(&args,nargs);

    args=Args_get("trim text.c","",&nargs);
    test_cond(nargs==1&&strcmp(args[0],"trim text.c")==0,"Args_get(\"trim text.c\",\"\"\"\"):");
    Args_free(&args,nargs);

    args=Args_get("  trim   text.c  "," ",&nargs);
    test_cond(nargs==2&&strcmp(args[0],"trim")==0&&strcmp(args[1],"text.c")==0,"Args_get(\"  trim   text.c  \",\" \"):");
    Args_free(&args,nargs);

    args=Args_get("  trim   text.c"," ",&nargs);
    test_cond(nargs==2&&strcmp(args[0],"trim")==0&&strcmp(args[1],"text.c")==0,"Args_get(\"  trim   text.c\",\" \"):");
    Args_free(&args,nargs);

    args=Args_get("    "," ",&nargs);
    test_cond(nargs==0,"Args_get(\"     \",\" \"):");
    Args_free(&args,nargs);

    args=Args_get("trim text:edit"," :",&nargs);
    test_cond(nargs==3&&strcmp(args[0],"trim")==0&&strcmp(args[1],"text")==0&&strcmp(args[2],"edit")==0,"Args_get(\"trim text:edit\",\" :\"):");
    Args_free(&args,nargs);

    args=Args_get("trim text : edit   "," :",&nargs);
    test_cond(nargs==3&&strcmp(args[0],"trim")==0&&strcmp(args[1],"text")==0&&strcmp(args[2],"edit")==0,"Args_get(\"trim text : edit   \",\" :\"):");
    Args_free(&args,nargs);

    args=Args_get("trim::: text : edit   "," :",&nargs);
    test_cond(nargs==3&&strcmp(args[0],"trim")==0&&strcmp(args[1],"text")==0&&strcmp(args[2],"edit")==0,"Args_get(\"trim text : edit   ::::\",\" :\"):");

    char* before=Args_join(args,nargs," ");
    char* after=Args_join(args,nargs,"/");
    test_cond(strcmp(after,"trim/text/edit")==0,"Args_join(\"%s\",\"/\"):",before);
    safer_free(before);
    safer_free(after);
    Args_free(&args,nargs);

    args=Args_get("trim"," :",&nargs);
    test_cond(nargs==1&&strcmp(args[0],"trim")==0,"Args_get(\"trim\",\" :\"):");
    before=Args_join(args,nargs," ");
    after=Args_join(args,nargs,"/");
    test_cond(strcmp(after,"trim")==0,"Args_join(\"%s\",\"/\"):",before);
    safer_free(before);
    safer_free(after);
    Args_free(&args,nargs);

    args=Args_get("  ::"," :",&nargs);
    test_cond(nargs==0,"Args_get(\"  :: \",\" :\"):");
    Args_free(&args,nargs);

    args=Args_get(":::trim   "," :",&nargs);
    test_cond(nargs==1&&strcmp(args[0],"trim")==0,"Args_get(\":::trim   \",\" :\"):");
    Args_free(&args,nargs);

    char buf[53];
    for(int i=0;i<52;i++){
        if(i%2==0){
            buf[i]=':';
        }else{
            buf[i]='a'+i/2;
        }
    }
    buf[52]='\0';
    char descr[1024];
    sprintf(descr,"%s",buf);
    args=Args_get(buf,":",&nargs);
    test_conds(nargs==26);
    for(int i=0;i<26;i++){
        buf[0]='a'+i;
        buf[1]='\0';
        test_conds(strcmp(args[i],buf)==0);
    }
    conds_report("Args_get(\"%s\",\":\"):",descr);

    before=Args_join(args,nargs," ");
    after=Args_join(args,nargs,"/");
    test_cond(strcmp(after,"a/b/c/d/e/f/g/h/i/j/k/l/m/n/o/p/q/r/s/t/u/v/w/x/y/z")==0,"Args_join(\"%s\",\"/\"):",before);
    safer_free(before);
    safer_free(after);
    Args_free(&args,nargs);
    test_report();
    return 0;
}
