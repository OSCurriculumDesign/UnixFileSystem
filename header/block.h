#ifndef BLOCK_H
#define BLOCK_H

#include "const.h"

struct block{
  unsigned short flag;                    //判断是否被用
  char content[410];                      //存储内容
  unsigned short blockStack[NICFREE];     //记录空闲块之间的组织结构
};

/* block 为空闲块，其大小为512字节，其中空闲块表占100字节(50*2)，content占410字节(410*1)，flag占2字节 */

#endif
