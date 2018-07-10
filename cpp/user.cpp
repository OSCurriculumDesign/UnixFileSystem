#include <cstdio>
#include <cassert>
#include <cstring>

#include "filesys.h"

int login(unsigned short uid, char* pwd){
    int i,j;
    for(i=0;i<PWDNUM;i++){
        if((uid==password[i].p_uid) && !(strcmp(pwd,password[i].password))){
            for(j=0;j<USERNUM;j++){
                if(user[j].u_uid == 0){
                    break;
                }
            }
            if(j==USERNUM){
                fprintf(stdout, "\ntoo much users\n");
                return 0;
            }else{
                user[j].u_uid = password[i].p_uid;
                user[j].u_gid = password[i].p_gid;
                user[j].u_default_mode = DEFAULTMODE;
                fprintf(stdout, "\nlogin success!\n");
                return 0;
            }
        }
    }
    if( i == PWDNUM){
        fprintf(stdout, "\nwrong uid or password\n");
        return 0;
    }
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
    int i,j;
    Inode * inode;
    for(i=0;i<USERNUM;i++){
        if(uid == user[i].u_uid){
            break;
        }
    }
    if(i == USERNUM){
        fprintf(stdout, "no such user\n");
        return 0;
    }
    user[i].u_uid = -1;
    fprintf(stdout, "logout success\n");
}
