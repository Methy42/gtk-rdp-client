#ifndef X224_CONNECTION_REQUEST_H
#define X224_CONNECTION_REQUEST_H

#include <cstdint>
#include <cstring>

class X224ConnectionRequest {
private:
    uint8_t m_tpdu_size; // Transport Protocol Data Unit Size
    uint8_t m_src_ref[2]; // Source Reference
    uint8_t m_class_option; // Class Option
    uint8_t m_dst_ref[2]; // Destination Reference
    uint8_t m_data[16]; // Data

public:
    // Constructor
    X224ConnectionRequest(uint16_t src_ref = 0, uint16_t dst_ref = 0);

    // Set source reference
    void setSrcRef(uint16_t ref);

    // Set destination reference
    void setDstRef(uint16_t ref);

    // Serialize the PDU to a byte array
    void serialize(uint8_t* buffer);
};

#endif // X224_CONNECTION_REQUEST_H
