#include <cstdio>
#include <cassert>

#include "filesys.h"

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
            return ;
        } else free_all_blocks_of_the_old_file(pinode, false);


        // from book, I dont understand the following codes
        for(i = 0; i < SYSOPENFILE; ++i) {
            if(sys_ofile[i].f_inode == pinode)
                sys_ofile[i].f_off = 0;
        }

        for(i = 0; i < NOFILE; ++i) {
            if(user[user_id].u_ofile[i] == SYSOPENFILE + 1) {
                user[user_id].u_uid = pinode->uid;
                user[user_id].u_gid = pinode->gid;
                for(j = 0; j < SYSOPENFILE; ++j) {
                    if(sys_ofile[j].f_count == 0) {
                        user[user_id].u_ofile[i] = j;
                        sys_ofile[j].f_flag = mode;
                    }
                }
                return i; // return i;
            }
            return -1; // 缺省
        }
    } else { // 不存在
        pinode = ialloc();
        di_ith = insert_direct_to_dirlist_by_name(filename);
        dir.size++;

        dir.direct[di_ith].disk_ino = pinode->mem_ino;
        if(di_ith < DIRNUM - 1) dir.direct[di_ith + 1].disk_ino = 0;
        pinode->data_mode = user[user_id].u_default_mode | DIFILE;
        pinode->uid = user[user_id].u_uid;
        pinode->gid = user[user_id].u_gid;
        pinode->data_size = file_block;
        pinode->associated = 1;


        for(i = 0; i < SYSOPENFILE; ++i) {
            if(sys_ofile[i].f_count == 0) break;
        }

        user[user_id].u_ofile[j] = i;
        sys_ofile[i].f_flag = mode;
        sys_ofile[i].f_count = 0;
        sys_ofile[i].f_off = 0;
        sys_ofile[i].f_inode = pinode;

        return j;

    } 
}