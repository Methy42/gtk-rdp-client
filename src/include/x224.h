#ifndef X224_H
#define X224_H

#include <cstdint>
#include <cstring>
#include <uv.h>

const uint16_t X224_TPDU_CONNECTION_REQUEST = 0xE0;
const uint16_t X224_TPDU_CONNECTION_CONFIRM = 0xD0;
const uint16_t X224_TPDU_DISCONNECT_REQUEST = 0x80;
const uint16_t X224_TPDU_DATA = 0xF0;
const uint16_t X224_TPDU_ERROR = 0x70;

const uint16_t TYPE_RDP_NEG_REQ = 0x01;
const uint16_t TYPE_RDP_NEG_RSP = 0x02;
const uint16_t TYPE_RDP_NEG_FAILURE = 0x03;

const uint32_t PROTOCOL_RDP = 0x00000000;
const uint32_t PROTOCOL_SSL = 0x00010000;
const uint32_t PROTOCOL_HYBRID = 0x00000002;
const uint32_t PROTOCOL_HYBRID_EX = 0x00000008;

class X224_Negotiation {
private:
    uint8_t type;
    uint8_t flags;
    uint16_t length;
    uint32_t result;
public:
    X224_Negotiation(const uv_buf_t* buffer);

    uint8_t get_type();

    uint8_t get_flags();

    uint16_t get_length();

    uint32_t get_result();
};

class X224_Connect_Result {
private:
    uint8_t length;
    uint8_t code;
    X224_Negotiation* negotiation;
public:
    X224_Connect_Result(const uv_buf_t* buffer);

    uint8_t get_length();

    uint8_t get_code();

    X224_Negotiation* get_negotiation();
};

class X224 {
public:
    static void create_connect_buffer(uv_buf_t* buffer);

    static void recv_connection_result(uv_buf_t* buffer);
};

#endif // X224_H