#include "tpkt.h"

void TPKT::pack(uv_buf_t buffer[19], uv_buf_t message[15]) {
    memcpy(buffer->base + 4, message->base, 15);
    buffer->base[0] = FASTPATH_ACTION_X224;
    buffer->base[1] = 0x00;
    buffer->base[2] = (buffer->len >> 8) & 0xFF;
    buffer->base[3] = buffer->len & 0xFF;
}