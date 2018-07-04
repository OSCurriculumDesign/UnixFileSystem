//定义本文件系统中的数据结构和常数
#define BLOCKSIZ  512  //每块大小
#define SYSOPENFILE 40  //系统打开文件表最大项数
#define DIRNUM  128  //每个目录所包含的最大目录项数（文件数）
#define DIRSIZ  14  //每个目录项名字部分所占字节数，另加i节点号2个字节
#define PWDSIZ   12  //口令字
#define PWDNUM   32  //最多可设32个口令登录
#define NOFILE  20  //每个用户最多可打开20个文件，即用户打开文件最大次数
#define NADDR 10  //每个i节点最多指向10块，addr[0]~addr[9]
#define NHINO  128  //共128个Hash链表，提供索引i节点（必须为2的幂）
#define USERNUM  10  //最多允许10个用户登录


/*filesys */
#define DINODESIZ  32 //每个磁盘i节点所占字节
#define DINODEBLK  32  //所有磁盘i节点共占32个物理块
#define FILEBLK  512  //共有512个目录文件物理块
#define NICFREE  50  //超级块中空闲块数组的最大块数
#define NICINOD  50  //超级块中空闲节点的最大块数
#define DINODESTART 2*BLOCKSIZ  //i节点起始地址
#define DATASTART (2+DINODEBLK)*BLOCKSIZ //目录、文件区起始地址


/*di_node*/
#define DIEMPTY 00000
#define DIFILE  01000
#define DIDIR   02000
/*user*/
#define UDIREAD 00001
#define UDIWRITE 00002
#define UDIEXICUTE 00004
/*group*/
#define GDIREAD 00010
#define GDIWRITE 00020
#define GDIEXICUTE 00040
/*other*/
#define ODIREAD 00100
#define ODIWRITE 00200
#define ODIEXICUTE 00400

#define read 1
#define write 2
#define exicute 4

#define DEFAULTMODE 00777


/*i_flag*/
#define IUPDATE 00002


/*s_fmod*/
#define SUPDATE 00001


/*f_flag*/
#define FREAD 00001
#define FWRITE 00002
#define FEXICUTE 00004


/*error*/
#define DISKFULL 65535


/*fseek origin*/
#define SEEK_SET 0



/* 文件系统数据结构 */
struct inode{
   struct inode *i_forw;
   struct inode *i_back;
   char i_flag;
   unsigned int i_ino;
   unsigned int i_count;
   unsigned short di_number;
   unsigned short di_mode;
   unsigned short di_uid;
   unsigned short di_gid;
   unsigned int di_size;
   unsigned int di_addr[NADDR];
 };


struct dinode{
  unsigned short di_number;
  unsigned short di_mode;
  unsigned short di_uid;
  unsigned short di_gid;
  unsigned long di_size;
  unsigned int di_addr[NADDR];
};


struct direct{
   char d_name[DIRSIZ];
   unsigned int d_ino;
 };


struct filsys{
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


struct pwd{
   unsigned short p_uid;
   unsigned short p_gid;
   char pasword[PWOSIZ];
 };


 struct dir{
   struct direct direct[DIR NUM];
   int size;
 };


 struct hinode{
   struct inode * i_forw;
 };


 struct file{
   char f_flag;
   unsigned int f_count;
   struct inode * f_inode;
   unsigned long f_off;
 };


 struct user{
   unsigned short u_default_mode;
   unsigned short u_uid;
   unsigned short u_gid;
   unsigned short u_ofile[NOFILE];
 };


extern struct hinode hinode[NHINO];
extern struct dir dir;
extern struct file sys_ofile[SYSOPENFILE];
extern struct filsys filsys;
extern struct pwdpwd[PWDNUM];
extern struct useruser[USERNUM];
extern FILE * fd ;
extern struct inode * cur_path_inode;
extern int user_id, file_block;


extern struct inode* iget();
extern iput();
extern unsigned int baloc();
extern bfree();
extern struct inode *ialoc();
extern ifree();
extern unsigned int namei();
extern unsigned int iname();
extern unsigned int aces();
extern _dir();
extern mkdir();
extern chdir();
extern dirlt();
extern unsigned short open();
extern create();
extern unsigned int read();
extern unsigned write();
extern int login();
extern logout();
extern instal();
extern format();
extern close();
extern halt();
