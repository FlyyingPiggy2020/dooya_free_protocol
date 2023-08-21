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
 * @Brief        : 杜亚开放协议
 */

/*---------- includes ----------*/
#include "stdint.h"
#include "inc/_misc.h"
#include "inc/_port.h"
#include "inc/_ops.h"
#include "inc/_receive_packet_parse.h"

/*---------- macro ----------*/
#define ARRAY_SIZE(x)                   (sizeof(x) / sizeof((x)[0]))
#define FIELD_SIZEOF(t, f)              (sizeof(((t *)0)->f))

#define RECV_BUF_SIZE 128
/*---------- type define ----------*/

/*---------- variable prototype ----------*/
static uint8_t  recv_buf[RECV_BUF_SIZE];
static uint32_t recv_size = 0;
/*---------- function prototype ----------*/

/*---------- variable ----------*/

/*---------- function ----------*/
void __dooya_free_protcol_recevie_thread(void)
{
    uint16_t _uscount = 0;
    free_protocol_port_t *port = free_protocol_get_port();

    _uscount = port->_read_buf(recv_buf + recv_size, RECV_BUF_SIZE);
    recv_size += _uscount;

    uint16_t pos = 0;
    uint16_t cnt = FIELD_SIZEOF(union protocol_dooya_free, common);
next:
    if (recv_size < FIELD_SIZEOF(union protocol_dooya_free, common)){
        goto size_not_enough;
    }
    pos = 0;
    /* 寻找符合格式的报文 */
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
    return;
}
/*---------- end of file ----------*/
