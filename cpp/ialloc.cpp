#include <cstdio>
#include "inode.h"
#include "filesys.h"
//#include "format.cpp"

// 辅助的static函数和变量,宏
#define BLOCK_BUFSZ (BLOCKSIZ/DINODESIZ)
static Dinode block_buf[BLOCK_BUFSZ];

// 这个辅助函数根据给定的当前游标，读取一个block大小的数据块
// 并且把这个数据块存入block_buf中用来辅助遍历
static inline void read_blocks_to_dinode_buf(int curr_dinode_id) {
    fseek(fd, DINODESTART + curr_dinode_id*DINODESIZ, SEEK_SET);
    fread(block_buf, 1, BLOCKSIZ, fd);
}

// 实现inode.h中的接口

/**
 * ialloc 函数
 * 功能：根据超级块的成组链接法来返回一个空闲块
 * 参数：void
 * 描述：
 *      
 * 返回值：结果地址
 *      
 */
Inode* ialloc(void){
    // 结果指针
    Inode* tmp_inode_ptr = nullptr;
    // 扫描硬盘dinode的游标
    unsigned int cur_di;
    // 分别是扫描
    int i, cnt;
    bool block_end_flag = false;

    // 如果超级块是空的
    if(filsys.free_inode_stacktop == NICINOD) {
        i = cnt = 0;
        block_end_flag = true;
        filsys.free_inode_stacktop = NICINOD - 1;
        cur_di = filsys.cached_inode_index;
        while((cnt < NICINOD) || (cnt <= filsys.free_inode_num)) {
            if(block_end_flag) {
                read_blocks_to_dinode_buf(cur_di);
                block_end_flag = false;
                i = 0;
            } // end of inner if
            // while(block_buf[i].data_mode == DIEMPTY) {
            //     cur_di++;
            //     i++;
            // } // end of inner while
            for(int k = i; i < NICINOD && block_buf[k].data_mode == DIEMPTY; ) {
                ++cur_di;
                ++i;
                ++k;
                if(k == BLOCK_BUFSZ) {
                    k = 0;
                    read_blocks_to_dinode_buf(cur_di);
                }
            }
            if(i == NICINOD) block_end_flag = true;
            else {
                filsys.free_inodes[filsys.free_inode_stacktop--] = cur_di;
                cnt++;
            } // end of inner if-else
        } // end of middle while
        filsys.cached_inode_index = cur_di;
    } // end of outer if

    tmp_inode_ptr = iget(filsys.free_inodes[filsys.free_inode_stacktop]);

    fseek(fd, DINODESTART+filsys.free_inodes[filsys.free_inode_stacktop]*DINODESIZ, SEEK_SET);
    fwrite((Dinode*)tmp_inode_ptr, 1, sizeof(Dinode), fd);
    filsys.free_inode_stacktop++;
    filsys.free_inode_num--;
    filsys.s_fmod = SUPDATE;
    return tmp_inode_ptr;
}


bool ifree(unsigned int dinode_id) {
    filsys.free_inode_num++;
    if(filsys.free_inode_stacktop != NICINOD) {
        filsys.free_inodes[filsys.free_inode_stacktop] = dinode_id;
        filsys.free_inode_stacktop++;
    } else {
        if(dinode_id < filsys.cached_inode_index) {
            filsys.free_inodes[NICINOD] = dinode_id;
            filsys.cached_inode_index = dinode_id;
        }
    }
    return true;
}
