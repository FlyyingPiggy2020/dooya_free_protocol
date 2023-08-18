#ifndef __DOOYA_FREE_PROTOCOL_H__
#define __DOOYA_FREE_PROTOCOL_H__
#include "stdint.h"

typedef union protocol_dooya_free *protocol_dooya_free_t;
#pragma pack(push)
#pragma pack(1)
union protocol_dooya_free{
    struct {
        uint8_t type;
        uint8_t sync_hi;
        uint8_t sync_lo;
        uint8_t chanel:4;
        uint8_t comand:4;
        uint8_t payload_length;
        uint8_t payload[0];
    }common;
};
#pragma pack(pop)

#endif
