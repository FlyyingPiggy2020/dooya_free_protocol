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
 * @FilePath     : _port.h
 * @Author       : lxf
 * @Date         : 2023-08-18 14:31:16
 * @LastEditors  : FlyyingPiggy2020 154562451@qq.com
 * @LastEditTime : 2023-08-18 15:02:00
 * @Brief        : 移植接口头文件
 */


/*---------- includes ----------*/
#include "stdint.h"


/*---------- macro ----------*/
/*---------- type define ----------*/
typedef struct free_protocol_port *free_protocol_port_t;
struct free_protocol_port{
    uint16_t (*_read_buf)(uint8_t *buf, uint16_t len);
    uint16_t (*_send_buf)(uint8_t *buf,uint16_t len);
    void (*_memmove)(void *dest,void const *src,uint16_t len);
};
extern free_protocol_port_t port;
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
extern void dooya_free_protocol_port_registration(free_protocol_port_t _port);
/*---------- end of file ----------*/


