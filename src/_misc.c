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
 * @FilePath     : _misc.c
 * @Author       : lxf
 * @Date         : 2023-08-18 18:59:51
 * @LastEditors  : FlyyingPiggy2020 154562451@qq.com
 * @LastEditTime : 2023-08-18 19:00:10
 * @Brief        : 
 */


/*---------- includes ----------*/
#include "stdint.h"
#include "inc/_misc.h"
/*---------- macro ----------*/
/*---------- type define ----------*/
/*---------- variable prototype ----------*/
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
/*---------- end of file ----------*/
