#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>

#include <zlib.h>

#include "zlibmgr.h"

using namespace std;

// class ZlibMgr {
// public:
//     ZlibMgr() = default;
//     ~ZlibMgr() = default;

//     static const unsigned int MAXBUFFSIZE = 200000;

//     bool zlibTool(Byte* src, Byte* dest, ulong& len, bool compress = true);

// private:
//     bool CompressTool(Byte* content, Byte* compress, ulong& len);
//     bool UnCompressTool(Byte* compress, Byte* content, ulong& len);

//     Byte compr_buf[MAXBUFFSIZE];
//     Byte cont_buf[MAXBUFFSIZE];
// };
// 静态的辅助变量还有辅助函数

// 实现zlibmgr.h中的接口

bool ZlibMgr::zlibTool(const char* src, char* dest, ulong& len, bool compress) {
    if(compress) return this->CompressTool(src, dest, len);
    else return this->UnCompressTool(src, dest, len);
    return false;
}

bool ZlibMgr::CompressTool(const char* content, char* compr, uLong& len) {
    if(!content || strlen(content) == 0) return false;
    memset(this->compr_buf, 0, ZlibMgr::MAXBUFFSIZE);
    
    ulong comprLen = sizeof(this->compr_buf)/sizeof(Byte);

    uLong contentLen = strlen(content);

    int err = compress(this->compr_buf, &comprLen, (const Bytef*)content, contentLen);

    if(err != Z_OK) {
        cout << "compess error: " << err << endl;
        return false;
    }
    cout << "orignal size: " << len << " , compressed size : " << comprLen << endl;
    memcpy(compr, this->compr_buf, comprLen);
    len = comprLen;
    return true;
}

bool ZlibMgr::UnCompressTool(const char* compr, char* content, uLong& len) {
    if(!compress || strlen(compr) == 0) return false;
    memset(this->cont_buf, 0, ZlibMgr::MAXBUFFSIZE);

    uLong contentLen = ZlibMgr::MAXBUFFSIZE;
    uLong comprLen = len;

    int err = uncompress((Bytef*)(this->cont_buf), &contentLen, (const Bytef *)compress, comprLen);
    if (err != Z_OK)  {
        cout << "uncompess error: " << err << endl;
        return false;
    }
    cout << "compress size: " << comprLen << "  uncompressed size : " << contentLen << endl;
    memcpy(content, this->cont_buf, contentLen);
    len = contentLen;
    return true;
}