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
 * @FilePath     : _receive_packet_parse.c
 * @Author       : lxf
 * @Date         : 2023-08-18 15:40:46
 * @LastEditors  : FlyyingPiggy2020 154562451@qq.com
 * @LastEditTime : 2023-08-18 15:41:10
 * @Brief        : 杜亚开放协议接收报文解析
 */


/*---------- includes ----------*/
#include "stdint.h"
#include "../inc/_receive_packet_parse.h"
#include "../dooya_free_protocol.h"
/*---------- macro ----------*/
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
static read_packet_parse_cb _read_packet_parse_cb;
/*---------- variable ----------*/
/*---------- function ----------*/


void _receive_packet_parse(const uint8_t *recv_buf, uint32_t recv_len)
{
    protocol_dooya_free_t protocol = (protocol_dooya_free_t)recv_buf;
    do{
        if(protocol->common.command == READ){
            if (_read_packet_parse_cb){
                _read_packet_parse_cb(protocol->common.payload_start, protocol->common.payload_length, protocol->common.payload);
            }
        }     
    }while(0);
}

void register_read_packet_parse(read_packet_parse_cb _cb)
{
    #warning "请注册这个回调函数"
    _read_packet_parse_cb = _cb;
}
/*---------- end of file ----------*/


