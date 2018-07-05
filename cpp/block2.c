#include <cstdio>
#include "block.h"
#include "filesys.h"

unsigned short balloc(){
  if(filsys.s_nfree == 0){
     printf("\nDiskFull! (filsys.s_nfree == 0)\n");
     return DISKFULL;
  }
  unsigned short tempStack[NICFREE+1];  //+1是为了除50个栈外，还有一个栈深的数据
  unsigned short free_block=filsys.s_free[filsys.s_pfree];
  if(filsys.s_pfree==NICFREE-1){
    unsigned short nextBlock = filsys.s_free[NICFREE-1];
    fseek(fd, DATASTART+nextBlock*BLOCKSIZ, SEEK_SET);
    fread(tempStack,51 * sizeof(unsigned short),1,fd);
    fre_block_num=tempStack[NICFREE];
    for(i=0;i<free_block_num;i++){
      filsys.s_free[NICFREE-1-i]=tempStack[i];
    }
    filsys.s_pfree=NICFREE-fre_block_num;
  }
  filsys.s_nfree--;
  filsys.s_fmod=SUPDATE;
  return free_block;
}

void bfree(unsigned short block_number){
  filsys.s_fre[s_pfree-1]=block_number;  //先把释放的空闲块号存到栈中
  if(filsys.s_free==1){
    unsigned short tempStack[NICFREE+1];  //+1是为了除50个栈外，还有一个栈深的数据
    for (i=0; i<NICFREE; i++){
      tempStack[i]=filsys.s_free[NICFREE-1-i];
      filsys.s_free[NICFREE-1-i]=0;
    }
    tempStack[NICFREE]=NICFREE;
    fseek(fd, DATASTART+filsys.s_free_master_number;*BLOCKSIZ, SEEK_SET);
    fwrite(tempStack,51 * sizeof(unsigned short),1,fd))
    filsys.s_free[NICFREE-1]=filsys.s_free_master_number;
    filsys.s_pfree=NICFREE-1;
    filsys.s_free_master_number=block_number;
  }
  filsys.s_nfree++;
}
