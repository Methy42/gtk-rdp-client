#ifndef TPKT_H
#define TPKT_H

#include <uv.h>

const uint16_t FASTPATH_ACTION_FASTPATH = 0x0;
const uint16_t FASTPATH_ACTION_X224 = 0x03;

class TPKT {
public:
    static void pack(uv_buf_t buffer[19], uv_buf_t message[15]);
};

#endif // TPKT_H