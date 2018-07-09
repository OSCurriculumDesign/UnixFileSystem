#include <cstdio>

#include "const.h"
#include "filesys.h"

// 实现filesys.h中的接口

bool access(unsigned int user_id, Inode* pinode, unsigned int access_mode) {
    switch(access_mode) {
        case READ:
            if(pinode->data_mode & ODIREAD) return true;
            else if((pinode->data_mode & GDIREAD) && user[user_id].u_gid == pinode->gid) return true;
            else if((pinode->data_mode & UDIREAD) && user[user_id].u_uid == pinode->uid) return true;
            else return false;
        case WRITE:
            if(pinode->data_mode & ODIWRITE) return true;
            else if((pinode->data_mode & GDIWRITE) && user[user_id].u_gid == pinode->gid) return true;
            else if((pinode->data_mode & UDIWRITE) && user[user_id].u_uid == pinode->uid) return true;
            else return false;
        case EXCUTE:
            if(pinode->data_mode & ODIEXCUTE) return true;
            else if((pinode->data_mode & GDIEXCUTE) && user[user_id].u_gid == pinode->gid) return true;
            else if((pinode->data_mode & UDIEXCUTE) && user[user_id].u_uid == pinode->uid) return true;
            else return false;
        case DEFAULTMODE: return true;
        default: return false;
    }
    return false;
}