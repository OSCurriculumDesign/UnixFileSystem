#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "filesys.h"

using namespace std;

int shutDown(){
  fseek(fd, 0, SEEK_SET);
  fwrite(&filsys, sizeof(filsys), 1, fd);
  halt_inodes();
  return 1;
}

int start(){
  fseek(fd, 0, SEEK_SET);
  fread(&filsys, sizeof(filsys), 1, fd);
  restore_inode_state();
  return 1;
}
