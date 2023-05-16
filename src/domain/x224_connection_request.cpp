#include "x224_connection_request.h"

// Constructor
X224ConnectionRequest::X224ConnectionRequest(uint16_t src_ref, uint16_t dst_ref) {
    m_tpdu_size = 0x0D;
    setSrcRef(src_ref);
    m_class_option = 0;
    setDstRef(dst_ref);
    memset(m_data, 0, sizeof(m_data));
}

// Set source reference
void X224ConnectionRequest::setSrcRef(uint16_t ref) {
    m_src_ref[0] = (ref >> 8) & 0xFF;
    m_src_ref[1] = ref & 0xFF;
}

// Set destination reference
void X224ConnectionRequest::setDstRef(uint16_t ref) {
    m_dst_ref[0] = (ref >> 8) & 0xFF;
    m_dst_ref[1] = ref & 0xFF;
}

// Serialize the PDU to a byte array
void X224ConnectionRequest::serialize(uint8_t* buffer) {
    buffer[0] = m_tpdu_size;
    memcpy(buffer + 1, m_src_ref, sizeof(m_src_ref));
    buffer[3] = m_class_option;
    memcpy(buffer + 4, m_dst_ref, sizeof(m_dst_ref));
    memcpy(buffer + 6, m_data, sizeof(m_data));
}
