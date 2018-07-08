#include <cstdio>
#include <cstring>

#include "filesys.h"

// 静态辅助函数

static inline void print_data_mode_privilege(unsigned short data_mode, FILE* stream) {
    // 执行权限, 最后一位代表执行权限
    //          倒数第二位是写权限
    //          倒数第三位是读权限
    // 先取最后一位
    unsigned int privilege = data_mode & UDIEXICUTE;
    if(privilege) fprintf(stream, "x");
    else fprintf(stream, "-");

    privilege = data_mode & UDIWRITE;
    if(privilege) fprintf(stream, "w");
    else fprintf(stream, "-");

    privilege = data_mode & UDIREAD;
    if(privilege) fprintf(stream, "r");
    else fprintf(stream, "-");
}

static void print_block_chain(Inode* pinode) {
    // 打印出每个file的 物理索引块地址
    if(pinode->data_mode & DIFILE) {
        fprintf(stdout, " %ld ", pinode->data_size);
        printf("block chain: ");
        
        // 我们规定，最后两个物理地址索引是二级索引
        unsigned int sz = pinode->data_size/BLOCKSIZ + (pinode->data_size%BLOCKSIZ?1:0);

        if(sz <= NADDR - 2)
            for(int k = 0; k < sz; ++k) 
                fprintf(stdout, " %d ", pinode->data_addr[k]);
        else if(sz <= NADDR - 2 + NADDR) {
            for(int k = 0; k < NADDR - 2; ++k) fprintf(stdout, " %d ", pinode->data_addr[k]);
            Inode* next_inode = iget(pinode->data_addr[NADDR - 2]);
            for(int k = NADDR - 2; k < sz; ++k) fprintf(stdout, " %d ", next_inode->data_addr[k - NADDR + 2]);
            iput(next_inode);
            next_inode = nullptr;
        } else if(sz <= NADDR - 2 + 2*NADDR) {
            for(int k = 0; k < NADDR - 2; ++k) fprintf(stdout, " %d ", pinode->data_addr[k]);
            Inode* next_inode = iget(pinode->data_addr[NADDR - 2]);
            for(int k = NADDR - 2; k < NADDR - 2 + NADDR; ++k) fprintf(stdout, " %d ", next_inode->data_addr[k - NADDR + 2]);
            iput(next_inode);
            next_inode = iget(pinode->data_addr[NADDR -1]);
            for(int k = NADDR - 2 + NADDR; k < sz; ++k) fprintf(stdout, " %d ", next_inode->data_addr[k - 2*NADDR + 2]);
        } else fprintf(stdout, " Err! too much block to show\n");

    } else if(pinode->data_mode & DIDIR){
        fprintf(stdout, "<dir>block chain: %d\n", pinode->mem_ino);
    } else if(pinode->data_mode & DIDATA) fprintf(stdout, " Sorry, this is a data inode\n");
}

// ls操作
void list_dir() {
    unsigned short data_mode;
    Inode* pinode;

    fprintf(stdout, "\ncurr dir size: %d\n", dir.size);
    for(int i = 0; i < dir.size; ++i) {
        // 指向有用的结点
        if(dir.direct[i].disk_ino != 0) {
            fprintf(stdout, "%20s  ", dir.direct[i].dir_name);
            pinode = iget(dir.direct[i].disk_ino);
    
            data_mode = pinode?pinode->data_mode:DIEMPTY;
            if(data_mode & DIFILE) fprintf(stdout, " file   ");
            else if(data_mode & DIDIR) fprintf(stdout, "direct  ");
            else fprintf(stdout, "notfound ");

            print_data_mode_privilege(data_mode, stdout);
            print_block_chain(pinode);
            iput(pinode);
            pinode = nullptr;
        } 
    }
}


void mkdir() {

}

void chdir() {

}

void dirlt() {
    
}
