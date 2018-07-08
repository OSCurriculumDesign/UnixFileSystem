#include <cstdio>
#include "inode.h"
#include "filesys.h"
//#include "block.cpp"i
//#include "format.cpp"

// 静态的辅助函数和变量
static Dinode block_buf[BLOCKSIZ/DINODESIZ];


// 实现inode.h中的接口

/**
 * iget 函数
 * 功能：根据请求的inode的编号向内存中已经组织好的inode组织表的inode
 *      如果内存中没有，那么从硬盘中读取相对应的dinode并将其扩展成inode
 *      组织编入inode表中 
 * 参数：inode或者dinode的id
 * 描述：
 *      如果inode已经被组织进入内存中了，直接返回内存中相对应的inode的地址
 *      否则返回新申请的inode块的地址
 *      一般而言，调用这个函数，我们默认调用者要使用或者查看这个文件，所以引用计数会加一
 * 返回值：所要的inode的指针
 *      
 */
Inode* iget(unsigned int dinode_id) {
    int hash = dinode_id%NICINOD;
    unsigned long addr;
    Inode* tmp;
    Inode* newInode;

    if(hinode[hash].head != nullptr) {
        tmp = hinode[hash].head;
        while(tmp) {
            if(tmp->mem_ino == dinode_id) {
                // 引用计数加一
                tmp->ref_count++;
                return tmp;
            } else tmp = tmp->next;
        }
    }

    // 不存在id符合要求的inode_id
    // 1. 计算dinode在磁盘中的地址
    addr = DINODESTART + dinode_id*DINODESIZ;

    // 2. 向堆区申请新的Inode结构体
    newInode = new Inode;

    // 3. 把磁盘中的Dinode读取进入Inode中
    /* --- 这里很容易出bug，注意这里 --- */
    fseek(fd, addr, SEEK_SET);
    fread((Dinode*)newInode, DINODESIZ, 1, fd);

    // 4. 把新结点放到hinode[hash]队列中
    //    使用的是类似链表头插法的算法
    newInode->next = hinode[hash].head;
    newInode->prev = newInode;
    if(newInode->next != nullptr) newInode->next->prev = newInode;
    hinode[hash].head = newInode;

    // 5. 初始化Inode结点,新申请的结点默认没有引用计数，但是要将它返回给调用者，所以相当于
    //    引用了一次  
    newInode->ref_count = 0 + 1;
    // 默认没有改变当前inode
    newInode->flag = 0;
    // mem_ino和硬盘中的索引块号应当是完全一致的
    newInode->mem_ino = dinode_id;

    // // 这波操作我没看懂
    // newInode->di_size = 3*(DIRSIZ+4);
    // if(dinode_id == 3) newInode->di_size = BLOCKSIZ;
    return newInode;
}


/**
 * iput 函数
 * 功能：根据给定的inode地址，释放该地址中的inode结点，并且修改必要信息
 * 参数：inode的地址
 * 描述：
 *      把给定的inode结点的引用计数减一，如果引用计数归零，删除该inode，如果成功执行
 *      释放结点的操作，返回true否则返回false
 * 返回值：释放成功与否
 *      
 */

bool iput(Inode* pinode) {
    // 有关联文件
    if(pinode->ref_count > 1) {
        pinode->ref_count--;
        return false;
    } else {
        if(pinode->associated != 0) {
            // 如果没有关联文件，写回
            long addr = DINODESTART + pinode->mem_ino*DINODESIZ;
            fseek(fd, addr, SEEK_SET);
            fwrite((Dinode*)pinode, DINODESIZ, 1, fd);
        } else {
            unsigned int block_num = pinode->data_size/BLOCKSIZ;
            for(int i = 0; i < block_num; ++i) bfree(pinode->data_addr[i]);
            ifree(pinode->mem_ino);
        }

        // 释放内存中的结点
        if(pinode->next == nullptr) pinode->prev->next = nullptr;
        else {
            pinode->next->prev = pinode->prev;
            pinode->prev->next = pinode->next;
        }
        delete pinode;
    }
    return true;
}
