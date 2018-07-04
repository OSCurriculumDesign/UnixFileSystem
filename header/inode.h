#ifndef INODE_H
#define INODE_H

#include "const.h"

/* 文件系统数据结构 */
/*
    dinode是inode在磁盘中的储存形式,
    这类对象对于体积十分敏感
    经过测试，该类的体积是56
    test log:
    Sizeof Dinode is 56
    sizeof unsigned short is 2
    sizeof unsigned int is 4
    sizeof unsigned long is 8
    NADDR is 10
    刚好10*4 + 4*2 + 8 = 56
    所以可以放心用
*/
struct Dinode{
    unsigned short di_number;
    unsigned short di_mode;
    unsigned short di_uid;
    unsigned short di_gid;
    unsigned long di_size;
    unsigned int di_addr[NADDR];
};

/*
    inode是dinode在内存中的组织形式
    值得注意的是，在C++中，子类继承父类，其体积要稍微比想象中要大
    幸运的是，我们并不关注inode的体积，因为我们只在内存中使用它
*/
struct Inode: public Dinode {
    Inode* i_forw;
    Inode* i_back;
    char i_flag;
    unsigned int i_ino;
    unsigned int i_count;
};

struct Hinode {
    Inode* i_forw;
};

/*
    X 这类对象对于体积十分敏感
    经过测试，该类的体积是20
    这和我们之前分析的16字节不同
    原因：我使用的是64位操作系统
    所以 d_ino占用4位，由于C++自动会给
    对象对齐4byte所以我们这里看到18变成20

    test log:
    Sizeof Direct is 18
    The ture sizeof the Direct is 20
    sizeof char is 1
    sizeof unsigned int is 4
    DIRSIZ is 14
*/
struct Direct {
    char d_name[DIRSIZ];
    unsigned int d_ino;
};

struct Dir {
    Direct direct[DIRNUM];
    int size;
};



#endif