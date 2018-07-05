#include <cstdio>
#include "inode.h"
#include "filesys.h"
#include "block2.c"

// 静态的辅助函数和变量
static Dinode block_buf[BLOCKSIZ/DINODESIZ];


// 实现inode.h中的接口

Inode* iget(unsigned int dinode_id) {
    int inode_id = dinode_id%NICINOD;
    unsigned long addr;
    Inode* tmp;
    Inode* newInode;

    if(hinode[inode_id].i_forw != nullptr) {
       tmp = hinode[inode_id].i_forw;
        while(tmp) {
            if(tmp->i_ino == inode_id) {
                // 引用计数加一
                tmp->i_count++;
                return tmp;
            } else tmp = tmp->i_forw;
        }
    }

    // 不存在id符合要求的inode_id
    // 1. 计算dinode在磁盘中的地址
    addr = DINODESTART + dinode_id*DINODESIZ;

    // 2. 向堆区申请新的结构题
    newInode = new Inode;

    // 3. 把磁盘中的Dinode读取进入Inode中
    /* --- 这里很容易出bug，注意这里 --- */
    fseek(fd, addr, SEEK_SET);
    fread((Dinode*)newInode, DINODESIZ, 1, fd);

    // 4. 把新结点放到hinode[inode]队列中
    newInode->i_forw = hinode[inode_id].i_forw;
    newInode->i_back = newInode;
    if(newInode->i_forw != nullptr) newInode->i_forw->i_back = newInode;
    hinode[inode_id].i_forw = newInode;

    // 5. 初始化Inode结点
    newInode->i_count = 0 + 1;
    newInode->i_flag = 0;
    newInode->i_ino = dinode_id;

    // 这波操作我没看懂
    newInode->di_size = 3*(DIRSIZ+4);
    if(dinode_id == 3) newInode->di_size = BLOCKSIZ;

    return newInode;
}

bool iput(Inode* pinode) {
    // 有关联文件
    if(pinode->i_count > 1) {
        pinode->i_count--;
        return false;
    } else {
        if(pinode->di_number != 0) {
            // 如果没有关联文件，写回
            long addr = DINODESTART + pinode->i_ino*DINODESIZ;
            fseek(fd, addr, SEEK_SET);
            fwrite((Dinode*)pinode, DINODESIZ, 1, fd);
        } else {
            unsigned int block_num = pinode->di_size/BLOCKSIZ;
            for(int i = 0; i < block_num; ++i) bfree(pinode->di_addr[i]);
            ifree(pinode->i_ino);
        }

        // 释放内存中的结点
        if(pinode->i_forw == nullptr) pinode->i_back->i_forw = nullptr;
        else {
            pinode->i_forw->i_back = pinode->i_back;
            pinode->i_back->i_forw = pinode->i_forw;
        }
        delete pinode;
    }
    return true;
}
