#include <cstring>
#include <cstdio>

#include "filesys.h"

// 静态辅助函数

// 实现filesys.h中的接口

/**
 *  根据名字返回第一个找到的同名的dir的dinode_id，
 *  如果没有找到，返回0
 */
unsigned int inode_id_by_name(char* name) {
    for(int i = 0; i < dir.size; ++i) {
        // 众所周知，0号disknode不允许调用
        if(!strcmp(dir.direct[i].dir_name, name) && (dir.direct[i].disk_ino != 0))
            return dir.direct[i].disk_ino;
    }
    // 没找到
    return 0;
}

/**
 *  根据名字生成一个新的direct对象插入dir表中
 *  如果找到空位则给新的direct名字赋值, 如果有条件的话
 *  最好给定dino的值，
 *  返回这个空位的索引
 *  如果没有这个空位，返回0,拒绝插入操作
 *  
 */
unsigned int insert_direct_to_dirlist_by_name(char* name, unsigned int dinode_id) {
    bool notfound = true;
    int i;
    for(i = 0; i < DIRNUM && notfound; ++i) {
        if(dir.direct[i].disk_ino == 0) notfound = false;
    }
    --i;

    if(notfound) {
        fprintf(stdout, "\nThe curr dir is full\n");
        return 0;
    } else {
        strcpy(dir.direct[i].dir_name, name);
        dir.direct[i].disk_ino = dinode_id;
        return i;
    }
}