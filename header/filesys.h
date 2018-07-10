#ifndef FILESYS_H
#define FILESYS_H

#include <cstdio>

#include "const.h"
#include "inode.h"
#include "test.h"

struct Filsys{
    //
    unsigned short s_isize;
    unsigned short s_fsize;
    unsigned int s_nfree;
    unsigned short s_pfree;
    unsigned short s_free[NICFREE];

    // 空闲索引结点的数目
    unsigned int free_inode_num;
    // 空闲索引结点指针,是超级块栈顶指针
    unsigned short free_inode_stacktop;
    // 空闲索引结点的数组,是一个栈
    unsigned int free_inodes_stack[NICINOD];
    // 被记录的索引结点
    unsigned int cached_inode_index;

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
extern Pwd password [PWDNUM];

// implement in ialloc.cpp
extern Inode* iget(unsigned int dinode_id);
extern bool iput(Inode* pinode);


// implement in block.cpp
extern unsigned short baloc();
extern void bfree();
extern void bwrite(unsigned short block_number, char * content);
extern char * bread(unsigned short block_number, unsigned short length);

// implement in ialloc.cpp
extern bool ifree(unsigned int dinode_id);
extern Inode* ialloc(void);

// ??? by Eric Lee
extern void bfree(unsigned short block_number);
extern unsigned short balloc();

// implement in format.cpp
extern void format();

// implement in name.cpp
// extern unsigned int namei();
// extern unsigned int iname();
extern unsigned int inode_id_by_name(char*);
extern unsigned int insert_direct_to_dirlist_by_name(char* name, unsigned int dinode_id = 1);

// implement in dir.cpp
extern void list_dir();
extern void mkdir(char*);
extern void chdir(char*);

// implement access.cpp
extern bool access(unsigned int user_id, Inode* pinode, unsigned short access_mode);

// implement in file.cpp
extern void free_all_blocks_of_the_old_file(Inode*, bool);
extern int create(unsigned int user_id, char* filename, unsigned short mode = DEFAULTMODE);
extern File* open(unsigned int user_id, char* filename, unsigned short openmode = DEFAULTMODE);
extern int close(unsigned int user_id, FILE* fp);
extern int del(unsigned int user_id, char* filename);
extern int read(File *fd,char *buff,unsigned int size);
extern int write(File *fd,char *buff,unsigned int size);

// implement in user.cpp
extern int login(unsigned short uid, char* password);
extern int init_root_user(char *password);
extern int logout(unsigned short uid);
extern int add_user(char *username,char *password,int group);

// implement in boot.cpp
extern int shutDown();
extern int start();


// extern unsigned int aces();
// extern void dirlt(int );

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
