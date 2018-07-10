#include <cstdio>
#include <climits>
#include <cstring>

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

static inline void push_free_inode_stk(int dinode_id) {
    filsys.free_inodes_stack[filsys.free_inode_stacktop] = dinode_id;
    // 由于这个stacktop是unsigned short类型的，我得防止它溢出了
    filsys.free_inode_stacktop = !filsys.free_inode_stacktop ? NICINOD : filsys.free_inode_stacktop-1;
}

static inline void pop_free_inode_stk(void) {
    // 丢弃栈顶Inode编号
    filsys.free_inode_stacktop++;
    // 空闲inode的整体数目减少了
    filsys.free_inode_num--;
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

    // 如果超级块是空的,我们默认栈顶偏移量小于栈底，也就是每次push我们把stacktop--
    if(filsys.free_inode_stacktop == NICINOD) {

        int cnt = 0;
        cur_di = filsys.cached_inode_index;

        while((cnt <= NICINOD) && (cnt <= filsys.free_inode_num)) {
            int i;
            for(i = 0; i < NICINOD; ++i, ++cur_di) {
                int k = i % BLOCK_BUFSZ;
                if(0 == k) read_blocks_to_dinode_buf(cur_di);
                // 如果当前遍历的块是空闲块，找到目标，跳出循环
                if(block_buf[k].data_mode == DIEMPTY) break;
            }
            // 没有找到空闲的dinode，开始下一次循环
            if(i == NICINOD) continue;
            // 0, 1, 2, 3是固定被占用的dinode
            else if(cur_di > 3) {
                // 当前cur_di压栈，游标cur_di向下移动
                push_free_inode_stk(cur_di);
                cur_di++;
                cnt++;
            } else return nullptr; // 不知道什么情况，返回空指针
        } 
        // 下一个开始的地址
        filsys.cached_inode_index = cur_di;
    }
    // 从栈顶取inode，具体细节交给iget
    tmp_inode_ptr = iget(filsys.free_inodes_stack[filsys.free_inode_stacktop]);
    
    fseek(fd, DINODESTART+filsys.free_inodes_stack[filsys.free_inode_stacktop] * DINODESIZ, SEEK_SET);
    fwrite((Dinode*)tmp_inode_ptr, 1, sizeof(Dinode), fd);
    pop_free_inode_stk();
    // ???
    filsys.s_fmod = SUPDATE;
    return tmp_inode_ptr;
}


bool ifree(unsigned int dinode_id) {
    filsys.free_inode_num++;
    if(filsys.free_inode_stacktop != 0)
        push_free_inode_stk(dinode_id);
    else {
        // // 如果满了，我们把栈看成数组，找出dinode_id最大的那个淘汰出缓冲栈
        // // 并且将cached_index游标寄存器记录为数组中最小的dinode_id
        // unsigned int max_dinode_id = 0, min_dinode_id = UINT_MAX;
        // unsigned int max_index, min_index;
        // for(int i = 0; i < NICINOD; ++i) {
        //     if(filsys.free_inodes_stack[i] > max_dinode_id) {
        //         max_dinode_id = filsys.free_inodes_stack[i];
        //         max_index = i;
        //     }
        //     if(filsys.free_inodes_stack[i] < min_dinode_id) {
        //         min_dinode_id = filsys.free_inodes_stack[i];
        //         min_index = i;
        //     }
        // }
        // filsys.cached_inode_index = min_dinode_id + 1;
        // filsys.free_inodes_stack[max_index] = dinode_id;

        // 这里用到了成组链接法技术，这是第二个方案
        filsys.cached_inode_index = filsys.free_inodes_stack[0];
        filsys.free_inode_stacktop = NICINOD - 1;
        filsys.free_inodes_stack[filsys.free_inode_stacktop] = dinode_id;
    }
    return true;
}


void halt_inodes(void) {
    for(int i = 0; i < NHINO; ++i) {
        Inode* tmp = hinode[i].head;
        while(tmp) {
            tmp->ref_count = 0 + 1; // 即将被放入磁盘
            iput(tmp);
        }
    }
}

void restore_inode_state() {
    cur_path_inode = iget(1);
    Direct dir_buf [BLOCKSIZ / (DIRSIZ+sizeof(unsigned int))];
    fseek(fd, DATASTART+cur_path_inode->data_addr[0]*BLOCKSIZ, SEEK_SET);
    fread(dir_buf, BLOCKSIZ, 1, fd);
    memcpy(dir.direct, dir_buf, cur_path_inode->data_size);

//    dir.direct[0].disk_ino = 1;
//    strcpy(dir.direct[0].dir_name, ".");
//    dir.direct[1].disk_ino = 1;
//    strcpy(dir.direct[1].dir_name, "..");
//    dir.direct[2].disk_ino = 2;
//    strcpy(dir.direct[2].dir_name, "etc");

//    dir.size = 3;
//    dir.direct[dir.size].disk_ino = 0;
}
