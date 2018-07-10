/*初始化磁盘格式化程序format.c*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "filesys.h"
using namespace std;
void format(){
    struct Inode * inode;
    struct Direct dir_buf [BLOCKSIZ / (DIRSIZ+sizeof(unsigned int))];
    struct Pwd password [BLOCKSIZ/(PWDSIZ+4)];
    unsigned short block_buf[51];
    char * buf;
    int i, j;
    /*    creat the file system file */
    fd=fopen ("./filesystem", "wb+");
    buf=(char * ) malloc ((DINODEBLK+FILEBLK+2) * BLOCKSIZ * sizeof(char));
    if (buf==NULL){
        printf ("\nFile system file creat failed!(buf==NULL)\n");
        exit(0);
    }
    fseek(fd, 0, SEEK_SET);
    fwrite(buf, 1, (DINODEBLK+FILEBLK+2) * BLOCKSIZ * sizeof(char), fd);

    /*0.initialize the password */
    password[0].p_uid= 2116; password[0].p_gid= 03;
    strcpy(password[0].password, "dddd");
    password[1].p_uid= 2117; password[1].p_gid=03;
    strcpy(password[1].password, "bbbb");
    password[2].p_uid= 2118; password[2].p_gid=04;
    strcpy(password[2].password, "abcd");
    password[3].p_uid= 2119; password[3].p_gid=04;
    strcpy(password[3].password, "cccc");
    password[4].p_uid= 2220; password[4].p_gid=05;
    strcpy(password[4].password, "eeee");

    /*    1.creat the main directory and its sub dir etc and the file password */
    /* 0 empty dinode id */
    inode=iget(0);
    inode->data_mode=DIEMPTY;
    iput(inode);

    /* 1 main dir id */
    inode=iget(1);
    inode->associated=1;
    inode->data_mode=DEFAULTMODE|DIDIR;
    inode->data_size=3 *(DIRSIZ+sizeof(unsigned int));
    inode->data_addr[0]=1;    /* block 0tfl is used by the main directory */
    strcpy(dir_buf[0].dir_name, "..");
    dir_buf[0].disk_ino=1;
    strcpy(dir_buf[1].dir_name,".");
    dir_buf[1].disk_ino=1;
    strcpy(dir_buf[2].dir_name, "etc");
    dir_buf[2].disk_ino=2;
    fseek(fd, DATASTART, SEEK_SET);
    fwrite(dir_buf, 1, 3 * (DIRSIZ+sizeof(unsigned int)), fd);
    iput(inode);

    /* 2 etc dir id */
    inode=iget(2);
    inode ->associated = 1;
    inode->data_mode=DEFAULTMODE|DIDIR;
    inode->data_size=3 * (DIRSIZ+sizeof(unsigned int));
    inode->data_addr[0]=1;    /* block 0# is used by the etc */
    strcpy (dir_buf[0].dir_name, "..");
    dir_buf[0].disk_ino=1;
    strcpy(dir_buf[1].dir_name, "..");
    dir_buf[1].disk_ino=2;
    strcpy(dir_buf[2].dir_name, "password");
    dir_buf[2].disk_ino=3;
    fseek(fd, DATASTART+BLOCKSIZ * 1, SEEK_SET);
    fwrite (dir_buf, 1,3* (DIRSIZ+sizeof(unsigned int)),fd);
    iput(inode);

    /* 3 password id */
    inode=iget(3);
    inode->associated= 1;
    inode->data_mode=DEFAULTMODE |  DIFILE;
    inode->data_size=BLOCKSIZ;
    inode->data_addr[0]=2;
    for (i=5; i<PWDNUM; i++){
        password[i].p_uid=0;
        password[i].p_gid=0;
        strcpy(password[i].password,"    ");
    }
    fseek(fd,DATASTART+2*BLOCKSIZ, SEEK_SET);
    fwrite(password, 1, BLOCKSIZ,fd);
    iput(inode);

    /*    2. initialize the superblock */
    filsys.s_isize=DINODEBLK;
    filsys.s_fsize=FILEBLK;
    filsys.free_inode_num = DINODEBLK * BLOCKSIZ/DINODESIZ-4;
    filsys.s_nfree = FILEBLK-3;
    //超级块中 inode 信息的设置
    for (i=0; i<NICINOD; i++){
        /*    begin with 4, 0,1.2,3, is used by main, etc, password */
        filsys.free_inodes_stack[i] = 4 + i;
    }
    // 栈满
    filsys.free_inode_stacktop = 0;
    filsys.cached_inode_index = NICINOD + 4;      /*铭记指针就是上限*/

    block_buf[NICFREE]=NICFREE;
    for(i=511;i>11;i-=50){
        for(j=0;j<NICFREE;j++){
            block_buf[NICFREE-j-1]=i-j;
        }
        fseek(fd, DATASTART+BLOCKSIZ*(i-50), SEEK_SET);
        fwrite (block_buf, sizeof(block_buf), 1, fd);
    }
    block_buf[NICFREE]=9;
    for(j=0;j<9;j++){
        filsys.s_free[NICFREE-j-1]=i-j;
    }
    filsys.s_pfree=41;   //41=49-9+1
}
    // block_buf[NICFREE-1]=FILEBLK+1; /*FILEBLK+1 is a flag of end */
    // for (i=0; i<NICFREE-1; i++){
    //   block_buf[NICFREE-2-i]=FILEBLK-i;
    // }
    // fseek(fd, DATASTART+BLOCKSIZ * (FILEBLK-NICFREE-1), SEEK_SET);
    // fwrite (block_buf, 1, BLOCKSIZ, fd);
    // for    (i=FILEBLK-NICFREE-1; i>2; i-= NICFREE){
    //   for (j=0;j<NICFREE;j++){
    //     block_buf[j]=i-j;
    //   }
    //   fseek(fd ,DATASTART+BLOCKSIZ * (i-1) ,SEEK_SET);
    //   fwrite(block_buf, 1, BLOCKSIZ,fd);
    // }
    // i+=NICFREE   /*LTZ 如果不加的话 i 现在为-41*/
    // j=1;
    // for (i=i; i>2;i--){
    //   filsys.s_free[NICFREE+i-j] =i;
    // }
    // filsys.s_pfree=NICFREE -j;
    // filsys.s_pinode=0;
    // fseek(fd, BLOCKSIZ, SEEK_SET);
    // fwrite (&filsys,1,sizeof(struct filsys),fd);
