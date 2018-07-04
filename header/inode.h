#ifndef INODE_H
#define INODE_H

#include "const.h"

/* 文件系统数据结构 */
/*
    dinode是inode在磁盘中的储存形式
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

struct Direct {
    char d_name[DIRSIZ];
    unsigned int d_ino;
};

struct Dir {
    Direct direct[DIRNUM];
    int size;
};

#endif