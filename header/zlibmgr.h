#include <cstdlib>
#include <cstring>
#include <cassert>
#include <zlib.h>

class ZlibMgr {
public:
    ZlibMgr() = default;
    ~ZlibMgr() = default;

    static const unsigned int MAXBUFFSIZE = 200000;

    bool zlibTool(const char* src, char* dest, uLong& len, bool compress = true);

private:
    bool CompressTool(const char* content, char* compress, uLong& len);
    bool UnCompressTool(const char* compress, char* content, uLong& len);

    Byte compr_buf[MAXBUFFSIZE];
    Byte cont_buf[MAXBUFFSIZE];
};