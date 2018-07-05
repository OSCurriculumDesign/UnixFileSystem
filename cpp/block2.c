#include <cstdio>
#include "block.h"
#include "filesys.h"

unsigned short balloc(){
  if(filsys.s_nfree == 0){
     printf("\nDiskFull! (filsys.s_nfree == 0)\n");
     return DISKFULL;
  }
  free_block=filsys.s_free[filsys.s_pfree];
  if(filsys.s_pfree==NICFREE-2){
    unsigned short nextGroup = filsys.s_free[NICFREE-1];
    fseek(fd, DATASTART+nextGroup*BLOCKSIZ, SEEK_SET);
    fread(block_buf,1,BLOCKSIZ,fd);
    fre_block_num=block_buf[NICFREE-1];
    for(i=0;i<free_block_num;i++){
      filsys.s_free[NICFREE-1-i]=block_buf[i];
    }
    filsys.s_pfree=NICFREE-fre_block_num;
  }
  return free_block;
}
