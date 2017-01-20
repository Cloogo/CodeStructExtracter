#ifndef _TEST_HELPER_H
#define _TEST_HELPER_H
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "file.h"
int total=0,failed=0;

#define test_cond(cond,...) do{\
    total++;\
    if(cond){\
    }else{\
        printf("%s args[",#cond);\
        printf(__VA_ARGS__);\
        printf("]:");\
        printf(" failed.\n");\
    failed++;\
    }\
}while(0)

int nerrs=0;
#define test_conds(cond) do{\
    if(cond){\
    }else{\
        nerrs++;\
    }\
}while(0)
#define conds_report(...) do{\
    total++;\
    if(nerrs==0){\
    }else{\
        printf(__VA_ARGS__);\
        printf(" failed.\n");\
        failed++;\
    }\
    nerrs=0;\
}while(0)

#define test_report() printf("%d tested,%d failed.\n",total,failed)

#define timecost(op,trial,n) do{\
    int timesum=0;\
    for(int i=1;i<=trial;i++){\
        int starttime=clock();\
        for(int j=1;j<=n;j++){\
                op;\
        }\
        int during=clock()-starttime;\
        timesum+=during;\
    }\
    printf("%s cost:%.2fns %.2fms %.2fs\n",#op,(float)timesum*1e9/((trial)*(n)*CLOCKS_PER_SEC),(float)timesum*1e3/((trial*(n)*CLOCKS_PER_SEC)),(float)timesum/((trial)*(n)*CLOCKS_PER_SEC));\
}while(0)

time_t t;
#define generate_seed() do{\
    time(&t);\
    srand(t);\
}while(0)

#define log_seed(filename) do{\
    if(failed){\
        FILE* logf=File_open(filename,"a");\
        fprintf(logf,"%lu\n",t);\
        File_close(logf);\
    }\
}while(0)
#endif
