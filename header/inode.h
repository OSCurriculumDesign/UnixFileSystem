#ifndef INODE_H
#define INODE_H

#include "const.h"

/* 文件系统数据结构 */
/*
 dinode是inode在磁盘中的储存形式,
 这类对象对于体积十分敏感
 经过测试，该类的体积是56
 test log:
 Sizeof Dinode is 64
 所以可以放心用
 */
struct Dinode{
    // 关联的文件数目
    unsigned short associated;
    // 一共八位, 表示执行权限和该结点是（文件/文件夹）的属性
    unsigned short data_mode;
    // 所属的用户id
    unsigned short uid;
    // 所属的组id
    unsigned short gid;
    // 文件/文件夹大小
    unsigned long data_size;
    // 索引表，索引data块
    unsigned int data_addr[NADDR];
};

/*
 inode是dinode在内存中的组织形式
 值得注意的是，在C++中，子类继承父类，其体积要稍微比想象中要大
 幸运的是，我们并不关注inode的体积，因为我们只在内存中使用它
 */
struct Inode: public Dinode {
    // 每一个hash值对应一个inode链表
    // i_forw指向下一个结点
    Inode* next;
    // i_back指向第一个结点，第一个结点的这个指针指向自己
    Inode* prev;
    // 不清楚有什么用，姑且当作是当前目录或者文件的修改标志符号
    char flag;
    // 结点号，每个inode在内存中的唯一表示
    unsigned int mem_ino;
    // 引用计数
    unsigned int ref_count;
};

struct Hinode {
    // 每一个hash table项指向一个链表
    Inode* head;
};

/*
 存在data块中的数据，如果指向这个块的inode或者dinode是文件属性
 那么，一个data块内部的数据不再是direct而是单纯的数据
 而又如果这个inode/dinode是文件夹类型的，那么这个被指向的data块的
 内容是direct的数组,由于我们使用64位操作系统和编译器，索引hash_i_node的
 d_ino是4位的，为了凑齐两个字节我们把DIRSIZ修改为12，保证一个direct是16Bytes的

 direct: 16 bytes
 */
struct Direct {
    char dir_name[DIRSIZ];
    unsigned int disk_ino;
};

struct Dir {
    Direct direct[DIRNUM];
    int size;
};

// ialloc.cpp实现这两个接口
Inode* ialloc(void);
bool ifree(unsigned int dinode_id);

// igetput.cpp实现这两个接口
Inode* iget(unsigned int dinode_id);
bool iput(Inode* inode_ptr);


#endif
