#ifndef TEST_H
#define TEST_H
#define bk(msg) printf("checkpoint %20s, line %d, file %s \n", msg, __LINE__, __FILE__)
#define BREAKPOINT(msg) bk(msg)
#endif