#include "filesys.h"

// 这个源文件专门用来定义全局变量
// 用来作为数据段


FILE * fd;
Filsys filsys;
Hinode hinode[NHINO];
Dir dir;

// extern File sys_ofile[SYSOPENFILE];
// extern Filsys filsys;
// extern FILE * fd ;
// extern Pwd pwd[PWDNUM];
// extern User user[USERNUM];
// extern Inode * cur_path_inode;
// extern int user_id, file_block;