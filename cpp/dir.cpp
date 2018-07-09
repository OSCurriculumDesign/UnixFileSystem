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

// mkdir
void mkdir(char* newdir_name) {
    int dir_id, dir_pos;
    Inode* pinode =  nullptr;
    unsigned int block_id;

    Direct buf[BLOCKSIZ/(DIRSIZ+sizeof(unsigned int))];

    dir_id = inode_id_by_name(newdir_name);
    // 找到同名的
    if(dir_id != 0) {
        pinode = iget(dir_id);
        if(pinode->data_mode & DIDIR) fprintf(stdout, "\n%20s has already existed!\n", newdir_name);
        else if(pinode->data_mode & DIFILE) fprintf(stdout, "\n%20s is a file name!\n");
        else fprintf(stdout, "\nunknown error! This is a data inode\n");
    } else {
        dir_pos = insert_direct_to_dirlist_by_name(newdir_name);
        pinode = ialloc();
        dir_id = pinode->mem_ino;
        dir.direct[dir_pos].disk_ino = pinode->mem_ino;
        dir.size++;

        /*  */
        strcpy(buf[0].dir_name, ".");
        buf[0].disk_ino = dir_id;
        strcpy(buf[1].dir_name, "..");
        buf[1].disk_ino = cur_path_inode->mem_ino;
        buf[2].disk_ino = 0;

        // 请求 Eric lee review
        block_id = balloc();

        fseek(fd, DATASTART+block_id*BLOCKSIZ, SEEK_SET);
        fwrite(buf, BLOCKSIZ, 1, fd);

        pinode->data_size = 2*(DIRSIZ+sizeof(unsigned int));
        pinode->associated = 1;
        pinode->data_mode = user[user_id].u_default_mode | DIDIR;
        pinode->uid = user[user_id].u_uid;
        pinode->gid = user[user_id].u_gid;
        pinode->data_addr[0] = block_id;
        iput(pinode);
        pinode = nullptr;
        return ;
    }
}

void chdir() {

}

void dirlt() {

}
