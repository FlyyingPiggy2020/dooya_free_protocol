/*MIT License

Copyright (c) 2023 Lu Xianfan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/
/*
 * Copyright (c) 2023 by Moorgen Tech. Co, Ltd.
 * @FilePath     : _receive_packer _parse.h
 * @Author       : lxf
 * @Date         : 2023-08-18 15:55:26
 * @LastEditors  : FlyyingPiggy2020 154562451@qq.com
 * @LastEditTime : 2023-08-18 15:56:45
 * @Brief        : 
 */


/*---------- includes ----------*/
#include "stdint.h"
/*---------- macro ----------*/
/*---------- type define ----------*/
typedef union protocol_dooya_free *protocol_dooya_free_t;
#pragma pack(push)
#pragma pack(1)
union protocol_dooya_free{
    struct {
        uint8_t type;
        uint8_t sync_hi;
        uint8_t sync_lo;
        uint8_t command:4;
        uint8_t chanel:4;
        uint8_t payload_start;
        uint8_t payload_length;
        uint8_t payload[1];
    }common;
};
#pragma pack(pop)

/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
extern void _receive_packet_parse(const uint8_t *recv_buf, uint32_t recv_len);
/*---------- end of file ----------*/


