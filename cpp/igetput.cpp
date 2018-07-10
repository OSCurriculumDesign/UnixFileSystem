#include <cstdio>
#include <cassert>

#include "inode.h"
#include "filesys.h"
//#include "block.cpp"i
//#include "format.cpp"

using namespace std;

#define YOU_GUESS(fake_arg) do{\
    for(int aa=0;aa<10;aa++){\
        newInode = new Inode();\
    }\
}while(false)

// 静态的辅助函数和变量
static Dinode block_buf[BLOCKSIZ/DINODESIZ];

static inline void get_blocks_addrs_by_pinode(Inode* src, vector<unsigned int>& dest) {
    Inode* tmp = nullptr;
    dest.clear();
    unsigned int sz = src->data_size/BLOCKSIZ + (src->data_size%BLOCKSIZ?1:0);
    if(sz <= NADDR - 2) for(int i = 0; i < sz; ++i) dest.push_back(src->data_addr[i]);
    else if(sz > NADDR - 2 && sz <= NADDR - 2 + NADDR) {
        for(int i = 0; i < NADDR - 2; ++i) dest.push_back(src->data_addr[i]);
        tmp = iget(src->data_addr[NADDR - 2]);
        assert(tmp);
        for(int i = NADDR - 2; i < sz; ++i) dest.push_back(tmp->data_addr[i - NADDR + 2]);
        iput(tmp); tmp = nullptr;
    } else if(sz > NADDR - 2 + NADDR && sz <= NADDR - 2 + 2*NADDR) {
        for(int i = 0; i < NADDR - 2; ++i) dest.push_back(src->data_addr[i]);
        tmp = iget(src->data_addr[NADDR - 2]);
        assert(tmp);
        for(int i = NADDR - 2; i < NADDR - 2 + NADDR; ++i) dest.push_back(tmp->data_addr[i - NADDR + 2]);
        iput(tmp);
        tmp = iget(src->data_addr[NADDR - 1]);
        assert(tmp);
        for(int i = 2*NADDR - 2; i < sz; ++i) dest.push_back(tmp->data_addr[i - 2*NADDR + 2]);
        iput(tmp);
    }
}


// 实现inode.h中的接口

/**
 * iget 函数
 * 功能：根据请求的inode的编号向内存中已经组织好的inode组织表的inode
 *      如果内存中没有，那么从硬盘中读取相对应的dinode并将其扩展成inode
 *      组织编入inode表中
 * 参数：inode或者dinode的id
 * 描述：
 *      如果inode已经被组织进入内存中了，直接返回内存中相对应的inode的地址
 *      否则返回新申请的inode块的地址
 *      一般而言，调用这个函数，我们默认调用者要使用或者查看这个文件，所以引用计数会加一
 * 返回值：所要的inode的指针
 *
 */
Inode* iget(unsigned int dinode_id) {
    int hash = dinode_id%NICINOD;
    unsigned long addr;
    Inode* tmp;
    Inode* newInode;

    if(hinode[hash].head != nullptr) {
        tmp = hinode[hash].head;
        while(tmp) {
            if(tmp->mem_ino == dinode_id) {
                // 引用计数加一
                tmp->ref_count++;
                return tmp;
            } else tmp = tmp->next;
        }
    }

    // 不存在id符合要求的inode_id
    // 1. 计算dinode在磁盘中的地址
    addr = DINODESTART + dinode_id*DINODESIZ;

    // 2. 向堆区申请新的Inode结构体
    YOU_GUESS();
    newInode = new Inode();
    // 3. 把磁盘中的Dinode读取进入Inode中
    /* --- 这里很容易出bug，注意这里 --- */
    fseek(fd, addr, SEEK_SET);
    fread((Dinode*)newInode, DINODESIZ, 1, fd);

    // 4. 把新结点放到hinode[hash]队列中
    //    使用的是类似链表头插法的算法
    newInode->next = hinode[hash].head;
    newInode->prev = newInode;
    if(newInode->next != nullptr) newInode->next->prev = newInode;
    hinode[hash].head = newInode;

    // 5. 初始化Inode结点,新申请的结点默认没有引用计数，但是要将它返回给调用者，所以相当于
    //    引用了一次
    newInode->ref_count = 0 + 1;
    // 默认没有改变当前inode
    newInode->flag = 0;
    // mem_ino和硬盘中的索引块号应当是完全一致的
    newInode->mem_ino = dinode_id;

    // // 这波操作我没看懂
    // newInode->di_size = 3*(DIRSIZ+4);
    // if(dinode_id == 3) newInode->di_size = BLOCKSIZ;
    return newInode;
}


/**
 * iput 函数
 * 功能：根据给定的inode地址，释放该地址中的inode结点，并且修改必要信息
 * 参数：inode的地址
 * 描述：
 *      把给定的inode结点的引用计数减一，如果引用计数归零，删除该inode，如果成功执行
 *      释放结点的操作，返回true否则返回false
 * 返回值：释放成功与否
 *
 */

bool iput(Inode* pinode) {
    // 有关联文件
    if(pinode->ref_count > 1) {
        pinode->ref_count--;
        return false;
    } else {
        if(pinode->associated != 0) {
            // 如果有关联文件，写回
            long addr = DINODESTART + pinode->mem_ino*DINODESIZ;
            fseek(fd, addr, SEEK_SET);
            fwrite((Dinode*)pinode, DINODESIZ, 1, fd);
        } else free_all_blocks_of_the_old_file(pinode, true);

        // 释放内存中的结点
        if(pinode->next == nullptr) pinode->prev->next = nullptr;
        else {
            pinode->next->prev = pinode->prev;
            pinode->prev->next = pinode->next;
        }
        delete pinode;
    }
    return true;
}


/**
 * 给定一个inode的id，我返回两个值，第一个是data
 * 如果没有找到Inode或者这个Inode的datasize是0,
 *     return <0, {}>
 */
pair<unsigned int, vector<unsigned int>> get_datsz_and_blocks_addrs(unsigned int inode_id) {
    Inode* pinode = iget(inode_id);
    vector<unsigned int> dest; 
    if(!pinode || pinode->data_size == 0) return make_pair(0, vector<unsigned int>());
    else {
        get_blocks_addrs_by_pinode(pinode, dest);
        return make_pair(pinode->data_size, dest);
    }
}
