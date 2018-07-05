#include <cstdio>
#include "filesys.h"

static unsigned int block_buf[BLOCKSIZ]

unsigned short balloc(){
  unsigned short free_block,free_block_num;
  int i;
  //超级快中的空闲块块数为0说明无空间可以申请了
  if(filsys.s_nfree == 0){
     printf("\nDiskFull! (filsys.s_nfree == 0)\n");
     return DISKFULL;
  }
  //如果可以申请，申请 空闲块堆栈中的指针所指向的数据块
  free_block=filsys.s_free[filsys.s_pfree];
  if(filsys.s_pfree==NICFREE-1){  //当操作栈中只剩下一个的时候，将组长快的信息提取放入超级块的空闲块栈中

    //为什么读取(562-filsys.s_nfree)*BLOCKSIZ 偏移的数据块
    fseek(fd, DATASTART+(562-filsys.s_nfree)*BLOCKSIZ, SEEK_SET);
    //为什么读取(562-filsys.s_nfree)*BLOCKSIZ 偏移的数据块

    fread(block_buf,1,BLOCKSIZ,fd);
    fre_block_num=block_buf[NICFREE];
    for(i=0;i<free_block_num;i++){
      filsys.s_free[NICFREE-1-i]=block_buf[i];
    }
    filsys.s_pfree=NICFREE-fre_block_num;
  } else{
      filsys.s_pfree++;
  }
  filsys.s_nfree--;
  filsys.s_fmod=SUPDATE;
  return free_block;
}


bfree(unsigned short block_num){
  unsigned short i=0;
  filsys.s_free++;
  if(filsys.s_free == 0){
    block_buf[NICFREE]=NICFREE;
    for(i=0; i<NICFREE; i++){
      bolock_buf[i]=filsys.s_free[NICFREE-1-i];
    }
    filsys.s_pfree=NICFREE-1;
  }
  fseek(fd,BLOCKSIZ,SEEL_SET);
  fwrite(block_bug,1,BLCOSIZ,fd);
  filsys.s_nfree++;
  filsys.s_fmod=SUPDATE;
}
