#ifndef TEST_H
#define TEST_H
#include <cstdio>

#define SYSTEM_PAUSE do{\
    printf("Press Enter key to continue...");\
    fgetc(stdin);\
}while(false)

#define sysp(fake_arg) SYSTEM_PAUSE

#define BREAKPOINT(msg) do{\
    printf("checkpoint %20s, line %d, file %s \n", msg, __LINE__, __FILE__);\
    sysp();\
}while(false)

#define  bk(msg) BREAKPOINT(msg)

#endif