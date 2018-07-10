#include "filesys.h"

// 这个源文件专门用来定义全局变量
// 用来作为数据段


FILE * fd;
Filsys filsys;
Hinode hinode[NHINO];

Dir dir;

File sys_ofile[SYSOPENFILE];

User user[USERNUM];

Inode * cur_path_inode;

int user_id, file_block;

Pwd password [PWDNUM];


// extern FILE * fd ;
// extern Pwd pwd[PWDNUM];
