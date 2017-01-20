#ifndef _ERR_H
#define _ERR_H
#define locate() printf("file=%s line=%d func=%s:",__FILE__,__LINE__,__FUNCTION__)

#define report_bug(...) do{\
    locate();\
    printf(__VA_ARGS__);\
    printf("\n");\
    fflush(stdout);\
}while(0)

#define err_handler(descr) do{report_bug(descr);abort();}while(0)

#define perr(descr) do{\
    locate();\
    perror(descr);\
    exit(1);\
}while(0)

extern void error(const char* fmt,...);
#endif
