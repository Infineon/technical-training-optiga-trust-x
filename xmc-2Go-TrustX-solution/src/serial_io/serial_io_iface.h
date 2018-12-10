/***********************************************************************************************************************
 *
 * Copyright (c) 2015, Infineon Technologies AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the
 * following conditions are met:
 *
 *   Redistributions of source code must retain the above copyright notice, this list of conditions and the  following
 *   disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *   following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *   Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 *   products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT  OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * To improve the quality of the software, users are encouraged to share modifications, enhancements or bug fixes
 * with Infineon Technologies AG (dave@infineon.com).
 ***********************************************************************************************************************/
#ifndef SERIAL_IO_IFACE_H_
#define SERIAL_IO_IFACE_H_


#include <stdio.h>

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
void HexDump(uint8_t *data, int len);
void HexDumpNoCR(uint8_t *data, int len);
int UTIL_hexStrToArray(char *str, uint8_t *res, int maxsize);


/// Maximum length of the file path
#define MAX_FILE_PATH_LENGTH      232

/// Maximum length current time
#define MAX_CURRENT_TIME_LENGTH   30

/// Maximum Sring length of the hexstring
#define MAXSTR_LEN				  255

/// How many numbers per line in hexdump
#define HEXDUMP_COLS    		  16

/// Some stdio libraries has hexdump build-in
#define HEXDUMP_ASCII(a, b)			__hexdump_ascii__(a, b)

inline void __hexdump_ascii__(const void* p_buf, uint32_t l_len);


#endif /* SERIAL_IO_IFACE_H_ */
