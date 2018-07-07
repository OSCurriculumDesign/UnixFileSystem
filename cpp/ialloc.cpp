#include <cstdio>
#include "inode.h"
#include "filesys.h"
//#include "format.cpp"

// 辅助的static函数和变量
static Dinode block_buf[BLOCKSIZ/DINODESIZ];

// 实现inode.h中的接口
Inode* ialloc(void){
    Inode* tmp_inode_ptr = nullptr;
    unsigned int cur_di;
    int i, cnt;
    bool block_end_flag = false;

    if(filsys.s_pinode == NICINOD) {
        i = cnt = 0;
        block_end_flag = true;
        filsys.s_pinode = NICINOD - 1;
        cur_di = filsys.s_rinode;
        while((cnt < NICINOD) || (cnt <= filsys.s_ninode)) {
            if(block_end_flag) {
                fseek(fd, DINODESTART + cur_di*DINODESIZ, SEEK_SET);
                fread(block_buf, 1, BLOCKSIZ, fd);
                block_end_flag = false;
                i = 0;
            } // end of inner if
            while(block_buf[i].di_mode == DIEMPTY) {
                cur_di++;
                i++;
            } // end of inner while
            if(i == NICINOD) block_end_flag = true;
            else {
                filsys.s_inode[filsys.s_pinode--] = cur_di;
                cnt++;
            } // end of inner if-else
        } // end of middle while
        filsys.s_rinode = cur_di;
    } // end of outer if

    tmp_inode_ptr = iget(filsys.s_inode[filsys.s_pinode]);

    fseek(fd, DINODESTART+filsys.s_inode[filsys.s_pinode]*DINODESIZ, SEEK_SET);
    fwrite((Dinode*)tmp_inode_ptr, 1, sizeof(Dinode), fd);
    filsys.s_pinode++;
    filsys.s_ninode--;
    filsys.s_fmod = SUPDATE;
    return tmp_inode_ptr;
}


bool ifree(unsigned int dinode_id) {
    filsys.s_ninode++;
    if(filsys.s_pinode != NICINOD) {
        filsys.s_inode[filsys.s_pinode] = dinode_id;
        filsys.s_pinode++;
    } else {
        if(dinode_id < filsys.s_rinode) {
            filsys.s_inode[NICINOD] = dinode_id;
            filsys.s_rinode = dinode_id;
        }
    }
    return true;
}
