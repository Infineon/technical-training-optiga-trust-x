/**
* MIT License
*
* Copyright (c) 2018 Infineon Technologies AG
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE
*
*
* \file serial_io_iface.h
*
* \brief   This file provides the example for ECDSA Sign operation using #optiga_crypt_ecdsa_sign.
* 
*
* \ingroup
* @{
*/
 
#ifndef SERIAL_IO_IFACE_H_
#define SERIAL_IO_IFACE_H_

/**********************************************************************************************************************
 * DATA STRUCTURES
 *********************************************************************************************************************/
typedef struct{
  /// Pointer to UART hardware
  void* uart_config_ptr;
  /// RS232 receive complete flag
  uint8_t uart_rx_flag;
  /// RS232 transmit complete flag
  uint8_t uart_tx_flag;
  //
  uint16_t count;

}uart_ctx_t;

int terminal_io_read(uint8_t * data);
void terminal_io_write( uint8_t * message, int length);
void OPTIGAprintf(char *format, ...);
void HexDump(char * message, uint8_t *data, int len);
void HexDumpNoCR(char * message, uint8_t *data, int len);
int UTIL_hexStrToArray(char *str, uint8_t *res, int maxsize);


#endif /* SERIAL_IO_IFACE_H_ */
