#include <cstdio>
#include <cassert>
#include <cstring>

#include "filesys.h"

int login(unsigned short uid, char* password){

}

int init_root_user(char *password){
    Inode* inode=iget(3);
    Pwd *root = new Pwd();
    root->p_uid = 0;
    root->p_gid = 0;
    strcpy(root->password,password);

    fseek(fd,DATASTART+2*BLOCKSIZ, SEEK_SET);
    fwrite(password,sizeof(Pwd), 1,fd);
    fflush(fd);
    iput(inode);

}

int logout(unsigned short uid){

}
