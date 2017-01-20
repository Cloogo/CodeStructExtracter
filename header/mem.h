#ifndef _MEM_H
#define _MEM_H
#include <stdlib.h>
#include "err.h"
#define safer_malloc(ptr,size) do{\
    (ptr)=malloc((size));\
    if((ptr)==NULL){\
        err_handler("malloc");\
    }\
}while(0)
#define safer_free(ptr) do{\
    if((ptr)!=NULL){\
        free((ptr));\
        (ptr)=NULL;\
    }\
}while(0)
#endif
