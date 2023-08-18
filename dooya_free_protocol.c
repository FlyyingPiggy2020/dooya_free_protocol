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
 * @FilePath     : dooya_free_protocol.c
 * @Author       : lxf
 * @Date         : 2023-08-18 11:45:59
 * @LastEditors  : FlyyingPiggy2020 154562451@qq.com
 * @LastEditTime : 2023-08-18 14:41:42
 * @Brief        : ���ǿ���Э��
 */

/*---------- includes ----------*/
#include "stdint.h"
#include "dooya_free_protocol.h"
#include "inc/_port.h"

/*---------- macro ----------*/
#define ARRAY_SIZE(x)                   (sizeof(x) / sizeof((x)[0]))
#define FIELD_SIZEOF(t, f)              (sizeof(((t *)0)->f))

#define RECV_MSG_SIZE 128
/*---------- type define ----------*/

/*---------- variable prototype ----------*/
static uint8_t  recv_buf[RECV_MSG_SIZE];
static uint32_t recv_size = 0;
/*---------- function prototype ----------*/

/*---------- variable ----------*/
const uint16_t CRC16_Tab[] = {0x0000, 0xCC01, 0xD801, 0x1400, 0xF001, 0x3C00, 0x2800, 0xE401,
                              0xA001, 0x6C00, 0x7800, 0xB401, 0x5000, 0x9C01, 0x8801, 0x4400};
/*---------- function ----------*/

uint16_t _crc16(uint8_t crcbuf, uint16_t crc_16)
{
    uint8_t temp = ((uint8_t)(crc_16 & 0x000F)) ^ (crcbuf & 0x0F);
    crc_16 >>= 4;
    crc_16 ^= CRC16_Tab[temp];
    temp = ((uint8_t)(crc_16 & 0x000F)) ^ (crcbuf >> 4);
    crc_16 >>= 4;
    crc_16 ^= CRC16_Tab[temp];
    return crc_16;
}

uint16_t checksum_crc16_dooya(uint8_t *data, uint16_t len)
{
    uint8_t i;
    uint16_t crc16 = 0xffff;
    for (i = 0; i < len; i++)
    {
        crc16 = _crc16(*data++,crc16);
    }
    return crc16;
}
void dooya_free_protcol_recevie_thread(void)
{
    uint16_t _uscount = 0;

    _uscount = port->_read_buf(recv_buf + recv_size, RECV_MSG_SIZE);
    recv_size += _uscount;

    uint16_t pos = 0;
    uint16_t cnt = RECV_MSG_SIZE;
next:
    if (recv_size < FIELD_SIZEOF(union protocol_dooya_free, common)){
        goto size_not_enough;
    }
    pos = 0;
    /* Ѱ�ҷ��ϸ�ʽ�ı��� */
    while(1)
    {
        if (recv_size - pos < FIELD_SIZEOF(union protocol_dooya_free, common)){
            port->_memmove(recv_buf,recv_buf + pos, recv_size - pos);
            recv_size -= pos;
            goto size_not_enough;
        }
        if (recv_buf[pos + 0] == 0x55 && recv_buf[pos + 1] == 0xfe && recv_buf[pos + 2] == 0xfe){
            break;
        }
        pos++;
    }
    while(1)
    {
        if (pos + cnt > recv_size){
            goto data_error;
        }
        if (checksum_crc16_dooya(recv_buf + pos, cnt) == 0){
            break;
        }
        cnt++;
    }
    _receive_packet_parse(recv_buf + pos, cnt);
    port->_memmove(recv_buf, recv_buf + pos + cnt, recv_size - pos - cnt);
    recv_size = recv_size - pos - cnt;
    goto next;

data_error:
    port->_memmove(recv_buf, recv_buf + pos + 3, recv_size - pos -3);
    recv_size = recv_size - pos - 3;
    goto next;

size_not_enough:
    return 0;
}


/*---------- end of file ----------*/