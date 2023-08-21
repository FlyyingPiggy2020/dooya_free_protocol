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
 * @FilePath     : dooya_free_protocol.h
 * @Author       : lxf
 * @Date         : 2023-08-18 13:25:16
 * @LastEditors  : FlyyingPiggy2020 154562451@qq.com
 * @LastEditTime : 2023-08-18 15:55:49
 * @Brief        : 
 */

#ifndef __DOOYA_FREE_PROTOCOL_H__
#define __DOOYA_FREE_PROTOCOL_H__
/*---------- includes ----------*/
#include "stdint.h"
#include "inc/_port.h"
/*---------- macro ----------*/
/*---------- type define ----------*/
/**
 * @brief 针对READ命令的解析
 * @param {uint8_t} start 起始地址
 * @param {uint8_t} length 长度
 * @param {uint8_t} *data 接收到的内容
 * @return {*}
 */
typedef void (*read_packet_parse_cb)(uint8_t start, uint8_t length, uint8_t *data);
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
extern void __dooya_free_protcol_recevie_thread(void);
extern void _dooya_free_porotocol_common(uint8_t cmd, uint8_t start_or_reg, uint8_t *data, uint8_t len);
extern void register_read_packet_parse(read_packet_parse_cb _cb);
#endif
/*---------- end of file ----------*/
