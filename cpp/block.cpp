#include <cstdio>
#include <cstring>
#include "filesys.h"
//#include "format.cpp"

//申请一个数据块
unsigned short balloc(){
    //如果没有空的数据块，则提示磁盘已经占满了
    if(filsys.s_nfree == 0){
        printf("\nDiskFull! (filsys.s_nfree == 0)\n");
        return DISKFULL;
    }
    unsigned short tempStack[NICFREE+1];  //+1是为了除50个栈外，还有一个栈深的数据
    unsigned short free_block=filsys.s_free[filsys.s_pfree];
    //当指针指到最后一个时，先把超级块中的数据进行更新
    if(filsys.s_pfree==NICFREE-1){
        unsigned short nextBlock = filsys.s_free[NICFREE-1];    /*先从当前栈中获取下一组的组长块地址*/
        fseek(fd, DATASTART+nextBlock*BLOCKSIZ, SEEK_SET);
        fread(tempStack,(NICFREE+1) * sizeof(unsigned short),1,fd);   /*再从组长块中获取下一组的信息，放到栈中*/
        unsigned short free_block_num=tempStack[NICFREE];
        for(int i=0;i<free_block_num;i++){
            filsys.s_free[NICFREE-1-i]=tempStack[NICFREE-1-i];
        }
        //在组长块分配前，现将组长块中表的数据情空
        fseek(fd, DATASTART+filsys.s_free[NICFREE-1]*BLOCKSIZ, SEEK_SET);
        fwrite(EMPTY_BLOCK, BLOCKSIZ*sizeof(char), 1, fd);
        filsys.s_pfree=NICFREE-free_block_num;
    } else{
        filsys.s_free[filsys.s_pfree]=0;
        filsys.s_pfree++;
    }
    filsys.s_nfree--;
    filsys.s_fmod=SUPDATE;
    return free_block;
}

//文件系释放一个数据块
void bfree(unsigned short block_number){
    //将释放的块中的数据置空
    fseek(fd, DATASTART+block_number*BLOCKSIZ, SEEK_SET);
    fwrite(EMPTY_BLOCK, BLOCKSIZ*sizeof(char), 1, fd);
    if(filsys.s_pfree==0){
        unsigned short tempStack[NICFREE+1];  //+1是为了除50个栈外，还有一个栈深的数据
        //先将超级块中的数据放到 tempStack 中
        for (int i=0; i<NICFREE; i++){
            tempStack[NICFREE-1-i]=filsys.s_free[NICFREE-1-i];
            filsys.s_free[NICFREE-1-i]=0;
        }
        //栈深50存入最后一块
        tempStack[NICFREE]=NICFREE;
        //将栈中的表存到新进来的空闲块中
        fseek(fd, DATASTART+block_number*BLOCKSIZ, SEEK_SET);
        fwrite(tempStack, BLOCKSIZ*sizeof(char), 1, fd);
        //重置超级块中栈的数据
        filsys.s_free[NICFREE-1]=block_number;
        filsys.s_pfree=NICFREE-1;
    } else{
        filsys.s_pfree--;
        filsys.s_free[filsys.s_pfree]=block_number;  //先把释放的空闲块号存到栈中
    }
    filsys.s_nfree++;
    filsys.s_fmod=SUPDATE;
}

//将内容为 content 的数据存到第 block_num 块的数据块
void bwrite(unsigned short block_number, char * content){
    unsigned short length = strlen(content);
    fseek(fd, DATASTART+block_number*BLOCKSIZ, SEEK_SET);
    fwrite(content, length*sizeof(char), 1, fd);
}

char * bread(unsigned short block_number, unsigned short length){
    char * tempString;
    fseek(fd, DATASTART+block_number*BLOCKSIZ, SEEK_SET);
    fwrite(tempString, length*sizeof(char), 1, fd);
    return tempString;
}
