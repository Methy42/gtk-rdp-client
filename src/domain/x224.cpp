#include "x224.h"

X224_Negotiation::X224_Negotiation(const uv_buf_t *buffer)
{
    type = buffer->base[1];
    flags = buffer->base[2];
    length = ((uint16_t)buffer->base[2] << 8) | (uint16_t)buffer->base[3];
    result = ((uint32_t)buffer->base[4] << 24) | ((uint32_t)buffer->base[5] << 16) | ((uint32_t)buffer->base[6] << 8) | (uint32_t)buffer->base[7];
}

uint8_t X224_Negotiation::get_type()
{
    return type;
}

uint8_t X224_Negotiation::get_flags()
{
    return flags;
}

uint16_t X224_Negotiation::get_length()
{
    return length;
}

uint32_t X224_Negotiation::get_result()
{
    return result;
}

X224_Connect_Result::X224_Connect_Result(const uv_buf_t *buffer)
{
    length = buffer->base[0];
    code = buffer->base[1];

    uv_buf_t negotiation_buffer = uv_buf_init((char*)malloc(8), 8);
    negotiation_buffer.len = 8;
    std::memset(negotiation_buffer.base, 0, negotiation_buffer.len);
    std::memcpy(negotiation_buffer.base, buffer->base + 6, negotiation_buffer.len);

    for (size_t i = 0; i < 8; ++i) {
        printf("%02X ", negotiation_buffer.base[i]);
    }

    printf("\n");

    negotiation = new X224_Negotiation(&negotiation_buffer);

    free(negotiation_buffer.base);
}

uint8_t X224_Connect_Result::get_length()
{
    return length;
}

uint8_t X224_Connect_Result::get_code()
{
    return code;
}

X224_Negotiation* X224_Connect_Result::get_negotiation()
{
    return negotiation;
}

void X224::create_connect_buffer(uv_buf_t *buffer)
{
    buffer->base[0] = 0x0E;                         // length
    buffer->base[1] = X224_TPDU_CONNECTION_REQUEST; // code
    buffer->base[2] = 0x00;                         // 1
    buffer->base[3] = 0x00;                         // 2
    buffer->base[4] = 0x00;                         // 3
    buffer->base[5] = 0x00;                         // padding
    buffer->base[6] = 0x00;                         // cookie
    buffer->base[7] = TYPE_RDP_NEG_REQ;             // negotiate security layer type
    buffer->base[8] = 0x00;                         // negotiate security layer flag
    buffer->base[9] = 0x08;                         // negotiate security layer length
    buffer->base[10] = 0x00;                        // negotiate security layer result
    buffer->base[11] = 0x01;                        // protocolNeg
    buffer->base[12] = 0x00;                        // nouse
    buffer->base[13] = 0x00;                        // nouse
    buffer->base[14] = 0x00;                        // nouse
    buffer->base[15] = 0x00;                        // nouse
}

void X224::recv_connection_result(uv_buf_t* buffer)
{
    X224_Connect_Result* result = new X224_Connect_Result(buffer);
    printf("X224_Connect_Result: length=%02X, code=%02X\n", result->get_length(), result->get_code());
    printf("X224_Negotiation: type=%02X, flags=%02X, length=%02X, result=%02X\n", result->get_negotiation()->get_type(), result->get_negotiation()->get_flags(), result->get_negotiation()->get_length(), result->get_negotiation()->get_result());
}