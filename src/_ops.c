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
 * @FilePath     : _ops.c
 * @Author       : lxf
 * @Date         : 2023-08-18 18:07:51
 * @LastEditors  : FlyyingPiggy2020 154562451@qq.com
 * @LastEditTime : 2023-08-18 18:57:57
 * @Brief        : 杜亚开放协议操作接口,注意写操作的长度是有限制的。
 */


/*---------- includes ----------*/
#include "stdint.h"
#include "string.h"
#include "../inc/_port.h"
#include "../inc/_misc.h"
/*---------- macro ----------*/
#define TRANS_BUF_SIZE 16
/*---------- type define ----------*/
typedef enum 
{
    READ = 0X07,
    WRITE = 0X02,
    CONTROL = 0X03,
    REQUEST = 0X04,
}cmd_dooya_free;
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
/*---------- variable ----------*/
/*---------- function ----------*/
void _dooya_free_porotocol_common(uint8_t cmd, uint8_t start_or_reg, uint8_t *data, uint8_t len)
{
    uint8_t trans_buf[TRANS_BUF_SIZE];
    uint8_t cnt = 0;
    uint16_t crc16 = 0;
    free_protocol_port_t *port = free_protocol_get_port();

    trans_buf[cnt++] = 0x55;
    trans_buf[cnt++] = 0xfe;
    trans_buf[cnt++] = 0xfe;
    trans_buf[cnt++] = (uint8_t)cmd;
    trans_buf[cnt++] = start_or_reg;
    if (cmd == READ){
        trans_buf[cnt++] = len;
        crc16 = checksum_crc16_dooya(trans_buf, cnt);
        trans_buf[cnt++] = crc16;
        trans_buf[cnt++] = crc16 >> 8;
    }
    if (cmd == WRITE){
        if(data != NULL && len <= 8){
            trans_buf[cnt++] = len;
            for (uint8_t i = 0; i < len; i++){
                trans_buf[cnt++] = data[i];
            }
            crc16 = checksum_crc16_dooya(trans_buf, cnt);
            trans_buf[cnt++] = crc16;
            trans_buf[cnt++] = crc16 >> 8;
        }
    }
    if (cmd == CONTROL){
        if (len != 0){
            for (uint8_t i  = 0; i < len; i++){
                trans_buf[cnt++] = data[i];
            }
        }
        crc16 = checksum_crc16_dooya(trans_buf, cnt);
        trans_buf[cnt++] = crc16;
        trans_buf[cnt++] = crc16 >> 8;
    }
    port->_send_buf(trans_buf, cnt);
}
/*---------- end of file ----------*/
