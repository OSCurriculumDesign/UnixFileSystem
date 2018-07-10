#include <iostream>
#include "filesys.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

int temp[14]={0};

// 静态辅助测试函数

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
    fprintf(stdout, "The true sizeof the Inode is %d\n\n\n", sizeof(Inode));
}

static void test_sizeof_Direct(void) {
    fprintf(stdout, "Sizeof Direct is %d\n",
    sizeof(char)*DIRSIZ + sizeof(unsigned int));
    fprintf(stdout, "The true sizeof the Direct is %d\n", sizeof(Direct));
    fprintf(stdout, "sizeof char is %d\n", sizeof(char));
    fprintf(stdout, "sizeof unsigned int is %d\n", sizeof(unsigned int));
    fprintf(stdout, "DIRSIZ is %d\n\n\n", DIRSIZ);
}


static int test_dir() {
    format();
    bk(" end of format");

    list_dir();
    bk(" before mkdir");

    // mkdir("new");

    // bk(" end mkdir");
    // list_dir();
    // chdir("new");
    return 0;
}

// cli入口函数

int main(int argc, const char * argv[]) {
    // format();

    // unsigned int block_buf[51];
    // for(int i=11; i<561; i+=50){
    //     fseek(fd, DATASTART+i*BLOCKSIZ, SEEK_SET);
    //     fread(block_buf, sizeof(block_buf), 1, fd);
    // }
    // for(int i=0; i<14; i++){
    //     temp[i]=balloc();
    //     cout<<temp[i]<<endl;
    // }
    // bfree(1);
    // bfree(4);
    // bfree(5);
    // bfree(3);
    // bfree(2);
    // bfree(10);
    // bfree(13);
    // bfree(6);
    // bfree(7);

    // for(int i=0; i<14; i++){
    //     temp[i]=balloc();
    //     cout<<temp[i]<<endl;
    // }
    // bwrite(234, "123123");
    // cout<< bread(234,512) <<endl;
    test_dir();
    return 0;
}



// #include <iostream>
// //#include "format.cpp"
// #include "filesys.h"
// #include <cstdio>
// #include "filesys.h"
// #include <cstdlib>
// #include <cstring>
// using namespace std;
//
// FILE * fd;
// Filsys filsys;
// Hinode hinode[NHINO];
//
// int main(int argc, char* argv[]) {
//     // test_sizeof_Dinode();
//     // test_sizeof_Inode();
//     // test_sizeof_Direct();
//     format();
//     return 0;
// }
//
//
