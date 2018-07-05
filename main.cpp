#include "filesys.h"
#include <cstdio>

static void test_sizeof_Dinode(void) {
    fprintf(stdout, "Sizeof Dinode is %d\n",
    sizeof(unsigned short)*4 + sizeof(unsigned int)*NADDR + sizeof(unsigned long));
    fprintf(stdout, "The true sizeof the Dinode is %d\n", sizeof(Dinode));
    fprintf(stdout, "sizeof unsigned short is %d\n", sizeof(unsigned short));
    fprintf(stdout, "sizeof unsigned int is %d\n", sizeof(unsigned int));
    fprintf(stdout, "sizeof unsigned long is %d\n", sizeof(unsigned long));
    fprintf(stdout, "NADDR is %d\n\n\n", NADDR);
}

static void test_sizeof_Inode(void) {
    fprintf(stdout, "Sizeof Inode append is %d\n", 
    2*sizeof(Inode*)+sizeof(char)+2*sizeof(unsigned int));
    fprintf(stdout, "The true sizeof the Inode is %d\n", sizeof(Inode));
    fprintf(stdout, "sizeof unsigned short is %d\n", sizeof(unsigned short));
    fprintf(stdout, "sizeof unsigned int is %d\n", sizeof(unsigned int));
    fprintf(stdout, "sizeof unsigned long is %d\n", sizeof(unsigned long));
    fprintf(stdout, "NADDR is %d\n\n\n", NADDR);
}

static void test_sizeof_Direct(void) {
    fprintf(stdout, "Sizeof Direct is %d\n",
    sizeof(char)*DIRSIZ + sizeof(unsigned int));
    fprintf(stdout, "The true sizeof the Direct is %d\n", sizeof(Direct));
    fprintf(stdout, "sizeof char is %d\n", sizeof(char));
    fprintf(stdout, "sizeof unsigned int is %d\n", sizeof(unsigned int));
    fprintf(stdout, "DIRSIZ is %d\n\n\n", DIRSIZ);
}

int main(int argc, char* argv[]) {
    test_sizeof_Dinode();
    test_sizeof_Direct();
    return 0;
}
