#include <cstdio>
#include <cassert>
#include <cstring>

#include "filesys.h"

/**
* i_free true 释放inode
*/
void free_all_blocks_of_the_old_file(Inode* pinode, bool i_free) {
    unsigned int block_num = pinode->data_size/BLOCKSIZ + (pinode->data_size%BLOCKSIZ?1:0);
    if(block_num <= 10)
        for(int i = 0; i < block_num && i < NADDR - 2; ++i) bfree(pinode->data_addr[i]);

    else if(block_num > 10 && block_num <= NADDR - 2 + NADDR) {
        for(int i = 0; i < NADDR - 2; ++i) bfree(pinode->data_addr[i]);

        Inode* next = iget(pinode->data_addr[NADDR - 2]);
        assert(next->data_mode & DIDATA);
        for(int i = NADDR - 2; i < block_num; ++i) bfree(next->data_addr[i - NADDR + 2]);
        iput(next); next = nullptr;

    } else {
        for(int i = 0; i < NADDR - 2; ++i) bfree(pinode->data_addr[i]);

        Inode* next = iget(pinode->data_addr[NADDR - 2]);
        assert(next->data_mode & DIDATA);
        for(int i = NADDR - 2; i < NADDR - 2 + NADDR; ++i) bfree(next->data_addr[i - NADDR + 2]);
        iput(next);

        next = iget(pinode->data_addr[NADDR - 1]);
        assert(next->data_mode & DIDATA);
        for(int i = NADDR - 2 + NADDR; i < NADDR - 2 + 2*NADDR && i < block_num; ++i)
            bfree(next->data_addr[i - 2*NADDR + 2]);
        iput(next); next = nullptr;
    }
    if(i_free) ifree(pinode->mem_ino);
}


/**
 * 创建文件
 * touch
 */

int create(unsigned int user_id, char* filename, unsigned short mode) {
    unsigned int dino, di_ith;
    Inode* pinode = nullptr;
    int i, j;
    dino = inode_id_by_name(filename);
    // 已经存在
    if(dino != 0) {
        pinode = iget(dino);
        if(!access(user_id, pinode, mode)) {
            iput(pinode);
            fprintf(stdout, "\ncreate access is denied!\n");
            return -1;
        } else {
            //清空inode指向的块，只留下inode
            free_all_blocks_of_the_old_file(pinode, false);
        }
        fprintf(stdout, "\nclear old file!\n");
        return 0;
    } else { // 不存在
        if(dir.size >= DIRNUM){
            return -1;
        }
        pinode = ialloc();
        di_ith = insert_direct_to_dirlist_by_name(filename);
        dir.size++;

        dir.direct[di_ith].disk_ino = pinode->mem_ino;
        if(di_ith < DIRNUM - 1) dir.direct[di_ith + 1].disk_ino = 0;
        pinode->data_mode = user[user_id].u_default_mode | DIFILE;
        pinode->uid = user[user_id].u_uid;
        pinode->gid = user[user_id].u_gid;
        pinode->data_size = 0;
        pinode->associated = 1;

        iput(pinode);
        fprintf(stdout, "\ncreate success!\n");
        return 0;
    }
}


/**
 * 打开文件
 *
 */

File* open(unsigned int user_id, char* filename, unsigned short openmode) {
    unsigned int dino;
    Inode* pinode = nullptr;
    dino = inode_id_by_name(filename);
    // 不存在
    if(dino == 0){
        fprintf(stdout, "\nfile does not exist!\n");
        return nullptr;
    }

    //获取inode
    pinode = iget(dino);
    //检查读取权限
    if(!access(user_id, pinode, openmode)) {
        iput(pinode);
        fprintf(stdout, "\ncreate access is denied!\n");
        return nullptr;
    }

    // struct File{
    //     char f_flag;
    //     unsigned int f_count;
    //     Inode* f_inode;
    //     unsigned long f_off;
    // };
    File * fp = new File();
    fp->f_inode = pinode;
    return fp;
}


/**
* 关闭文件
*
*/
int close(unsigned int user_id, File* fp){
    Inode* pinode = fp->f_inode;
    iput(pinode);
    delete(fp);
    fp = nullptr;
    return 0;
}


/**
* 删除文件
*
*/
int del(unsigned int user_id, char* filename){
    unsigned int dino, di_ith;
    Inode* pinode = nullptr;
    int i, j;
    dino = inode_id_by_name(filename);
    // 不存在
    if(dino == 0){
        return -1;
    }
    pinode = iget(dino);
    if(!access(user_id, pinode, WRITE)) {
        iput(pinode);
        fprintf(stdout, "\ndelete access is denied!\n");
        return -1;
    }

    for(i = 0; i < dir.size; ++i) {
        if(!strcmp(dir.direct[i].dir_name, filename)) break;
    }

    if(i == dir.size) return  -1;
    else for(int k = i; k < dir.size - 1; ++k) {
        strcpy(dir.direct[k].dir_name, dir.direct[k+1].dir_name);
        dir.direct[k].disk_ino = dir.direct[k+1].disk_ino;
    }
    dir.direct[dir.size - 1].disk_ino = 0;
    dir.size--;
    Inode* tmp = iget(dino);
    tmp->associated--;
    iput(tmp);
    return dir.size;
}

/**
* 文件读取
*/
int read(File *fd,char *buff,unsigned int size){
    Inode* pinode = fd->f_inode;
    char *temp_buff = buff;
    //TODO 判断是否为读取打开

}

/**
* 文件写入
*/
int write(File *fd,char *buff,unsigned int size){

}
