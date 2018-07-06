#ifndef FILESYS_H
#define FILESYS_H

#include <cstdio>
#include "const.h"
#include "inode.h"

struct Filsys{
    unsigned short s_isize;
    unsigned short s_fsize;
    unsigned int s_nfree;
    unsigned short s_pfree;
    unsigned short s_free[NICFREE];

    unsigned int s_ninode;
    unsigned short s_pinode;
    unsigned int s_inode[NICINOD];
    unsigned int s_rinode;

    char s_fmod;
};


struct Pwd{
    unsigned short p_uid;
    unsigned short p_gid;
    char password[PWDSIZ];
};


struct File{
    char f_flag;
    unsigned int f_count;
    Inode* f_inode;
    unsigned long f_off;
};


struct User{
    unsigned short u_default_mode;
    unsigned short u_uid;
    unsigned short u_gid;
    unsigned short u_ofile[NOFILE];
};


extern Hinode hinode[NHINO];
extern Dir dir;
extern File sys_ofile[SYSOPENFILE];
extern Filsys filsys;
extern FILE * fd ;
extern Pwd pwd[PWDNUM];
extern User user[USERNUM];
extern Inode * cur_path_inode;
extern int user_id, file_block;


extern Inode* iget(unsigned int dinode_id);
extern bool iput(Inode* pinode);
extern unsigned short baloc();
extern void bfree();
extern void bwrite(unsigned short block_number, char * content);
extern char * bread(unsigned short block_number, unsigned short length);
extern bool ifree(unsigned int dinode_id);
extern Inode* ialloc(void);
extern void bwrite(unsigned short block_number, char * content);
extern void bfree(unsigned short block_number);
extern unsigned short balloc();
extern void format();
// extern struct inode *ialoc();
// extern ifree();
// extern unsigned int namei();
// extern unsigned int iname();
// extern unsigned int aces();
// extern _dir();
// extern mkdir();
// extern chdir();
// extern dirlt();
// extern unsigned short open();
// extern create();
// extern unsigned int read();
// extern unsigned write();
// extern int login();
// extern logout();
// extern instal();
// extern close();
// extern halt();
#endif
