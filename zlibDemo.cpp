#define MAXBUFFERSIZE 200000

#include <iostream>
#include <cstdlib>
#include <zlib.h>
#include <cassert>
#include <cstring>

using namespace std;

class CZlibMgr {
public:
    CZlibMgr() = default;
    ~CZlibMgr() = default;

    bool mgrCompress(const char* pcContentBuf, char* pcCompBuf, unsigned long& ulComplen);
    bool mgrUnCompress(const char* pcCompBuf, char* pcContentBuf, unsigned long& ulComplen);

private:
    Byte compr[MAXBUFFERSIZE];
    Byte unCompr[MAXBUFFERSIZE];
};

bool CZlibMgr::mgrCompress(const char* pcContentBuf, char* pcCompBuf, unsigned long& ulCompLen) {
    if(!pcContentBuf || strlen(pcContentBuf) == 0) return false;
    memset(this->compr, 0x00, MAXBUFFERSIZE);
    
    uLong comprLen;
    int err;

    uLong len = strlen(pcContentBuf);
    comprLen = sizeof(compr)/sizeof(compr[0]);

    err = compress(this->compr, &comprLen, (const Bytef*)pcContentBuf, len);
    if(err != Z_OK) {
        cout << "compess error: " << err << endl;
        return false;
    }

    cout << "orignal size: " << len << " , compressed size : " << comprLen << endl;
    memcpy(pcCompBuf, compr, comprLen);
    ulCompLen = comprLen;

    return true;
}

bool CZlibMgr::mgrUnCompress(const char* pcCompBuf, char* pcUnCompBuf, unsigned long& ulCompLen) {
    if(!pcCompBuf || strlen(pcCompBuf) == 0) return false;
    memset(this->unCompr, 0, MAXBUFFERSIZE);
    uLong uncomprLen = MAXBUFFERSIZE;
    int err;

    err = uncompress(this->unCompr, &uncomprLen, (const Bytef *)pcCompBuf, ulCompLen);
    if (err != Z_OK)  {
        cout << "uncompess error: " << err << endl;
        return false;
    }

    cout << "compress size: " << ulCompLen << "  uncompressed size : " << uncomprLen << endl;
    memcpy(pcUnCompBuf, this->unCompr, uncomprLen);
    return true;
}

static CZlibMgr g_kZlibMgr;


int main(int argc, char* argv[]) {
    cout << sizeof(long) << "  " << sizeof(int) << endl;
    long uu1 = 10000;
    unsigned int i1 = 0;
    i1 = (unsigned int)uu1;
    cout << i1 << endl;
    int err;
    Byte compr[200000], uncompr[200000];    // big enough
    memset(compr, 0, 200000);
    memset(uncompr, 0, 200000);

    uLong comprLen, uncomprLen;
    const char* hello = "niasodn;awiuegbalksjdnf;awieufnalkjsdfn;awoiegja'diosjba;eoir|||wd;aowrungaweiasodn;awiuegbalksjdnf;awieufnalkjsdfn;awoiegja'diosjba;eoir|||wd;aowrungaweiasodn;awiuegbalksjdnf;awieufnalkjsdfn;awoiegja'diosjba;eoir|||wd;aowrungaweiasodn;awiuegbalksjdnf;awieufnalkjsdfn;awoiegja'diosjba;eoir|||wd;aowrungaweiasodn;awiuegbalksjdnf;awieufnalkjsdfn;awoiegja'diosjba;eoir|||wd;aowrungaweiasodn;awiuegbalksjdnf;awieufnalkjsdfn;awoiegja'diosjba;eoir|||wd;aowrungaweiasodn;awiuegbalksjdnf;awieufnalkjsdfn;awoiegja'diosjba;eoir|||wd;aowrungaweiasodn;awiuegbalksjdnf;awieufnalkjsdfn;awoiegja'diosjba;eoir|||wd;aowrungaweiasodn;awiuegbalksjdnf;awieufnalkjsdfn;awoiegja'diosjba;eoir|||wd;aowrungaweiasodn;awiuegbalksjdnf;awieufnalkjsdfn;awoiegja'diosjba;eoir|||wd;aowrungaweiasodn;awiuegbalksjdnf;awieufnalkjsdfn;awoiegja'diosjba;eoir|||wd;aowrungaweiasodn;awiuegbalksjdnf;awieufnalkjsdfn;awoiegja'diosjba;eoir|||wd;aowrungaweiasodn;awiuegbalksjdnf;awieufnalkjsdfn;awoiegja'diosjba;eoir|||wd;aowrungawe fq2;3i4;qo329upq98whe\"";

    unsigned long u1, u2;
    u1 = 0;
    u2 = 0;
    char sOutBuf[8096];
    g_kZlibMgr.mgrCompress(hello, sOutBuf, u1);
    cout << "======================> " << u1 << endl;

    char sUnCompressBuf[8096];
    memset(sUnCompressBuf, 0, sizeof(sUnCompressBuf));
    g_kZlibMgr.mgrUnCompress(sOutBuf, sUnCompressBuf, u1);
    cout << sUnCompressBuf << endl;
}