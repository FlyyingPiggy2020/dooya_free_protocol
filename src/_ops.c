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
#include "../inc/_misc.h"
#include "../inc/_port.h"
/*---------- macro ----------*/
#define TRANS_BUF_SIZE 16

#define MOTOR_ROUTE 0X02
#define ROUTE_DIR   0X03
#define MOTOR_STATE 0X05
#define MOTOR_ANGLE 0X06
#define ANGLE_DIR   0X07
#define ANGLE_REF   0X08
#define DEVICE_TYPE 0XF0
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
static uint16_t sync = 0xAAAA;
/*---------- function ----------*/
void _dooya_free_porotocol_common(cmd_dooya_free cmd, uint8_t start_or_reg, uint8_t *data, uint8_t len)
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

/**
 * @brief 读电机状态
 * @return {*}
 */
void _read_state(void)
{
    _dooya_free_porotocol_common(READ, 0x00,NULL,0x0B);
}

/**
 * @brief 读电机遇阻系数
 * @return {*}
 */
void _read_resistance(void)
{
    _dooya_free_porotocol_common(READ, 0x31,NULL,0x01);
}

/**
 * @brief 读电机类型
 * @return {*}
 */
void _read_device_type(void)
{
    _dooya_free_porotocol_common(READ, DEVICE_TYPE, NULL, 0x01);
}

/**
 * @brief 写电机类型
 * @param {uint8_t} _type
 * @return {*}
 */
void _write_device_type(uint8_t _type)
{
    static uint8_t type;
    type = _type;
    _dooya_free_porotocol_common(WRITE, DEVICE_TYPE, &type, 0x01);
}
/**
 * @brief 读电机方向
 * @return {*}
 */
void _read_motor_dir(void)
{
    _dooya_free_porotocol_common(READ, ROUTE_DIR,NULL,0x01);
}

/**
 * @brief 写电机方向
 * @param {uint8_t} dir
 * @return {*}
 */
void _wrtie_motor_dir(uint8_t _dir)
{
    static uint8_t dir;
    dir = _dir;
    _dooya_free_porotocol_common(WRITE, ROUTE_DIR,&dir,0x01);
}
/*---------- end of file ----------*/
