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
* \file serial_io_iface.c
*
* \brief   This file provides the example for ECDSA Sign operation using #optiga_crypt_ecdsa_sign.
* 
*
* \ingroup
* @{
*/


 #include <DAVE.h>
#include <serial_io_iface.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>


// Character code support macros
#define IsUpper(c)	(((c)>='A')&&((c)<='Z'))
#define IsLower(c)	(((c)>='a')&&((c)<='z'))
#define IsDigit(c)	(((c)>='0')&&((c)<='9'))

#if !defined(_WIN32) && !defined(__linux__) && !defined(__XC32__)
/*-----------------------------------------------------------------------*/
/* Put a character to the file                                           */
/*-----------------------------------------------------------------------*/
int f_putc (const char c)
{
	int length = 1;
	uint8_t str[3];

	str[0] = (uint8_t)c;
	if (c == '\n') str[length++] ='\r';	// LF -> CRLF conversion
	terminal_io_write(str, length);
	return 1;
}
/*-----------------------------------------------------------------------*/
/* Put a string to the file                                           */
/*-----------------------------------------------------------------------*/
int f_puts (char *str)
{
	int bytes = strlen(str);
	terminal_io_write((uint8_t*)str, bytes);
	return bytes;
}
#endif

/*-------------------------------------------------------------------------------
  Console output to Windows console or XMC4xxx USB-UART
 -------------------------------------------------------------------------------*/
void OPTIGAprintf(char *format, ...)
{
#if !defined(_WIN32) && !defined(__linux__) && !defined(__XC32__)
va_list arglist;
uint8_t flag, r;
int i, j, w;
uint32_t v;
char c, d, s[16], *p;
int res, chc, cc;

va_start(arglist, format);

for (cc = res = 0; cc != EOF; res += cc) {
	c = *format++;
	if (c == 0) break;			/* End of string */
	if (c != '%') {				/* Non escape character */
		cc = f_putc(c);
		continue;
	}
	w = flag = 0;
	c = *format++;
	if      (c == '0') { flag = 1; c = *format++; }		/* Flag: '0' padding */
	else if (c == '-') { flag = 2; c = *format++; }		/* Flag: left justified */

	while (IsDigit(c)) {		/* Precision */
		w = w * 10 + c - '0';
		c = *format++;
	}
	if (c == 'l' || c == 'L') { flag |= 4; c = *format++; } /* Prefix: Size is long int */
	if (!c) break;

	d = c;
	if (IsLower(d)) d -= 0x20;
	switch (d) {				/* Type is... */
	case 'S' :					/* String */
		p = va_arg(arglist, char*);
		for (j = 0; p[j]; j++) ;
		chc = 0;
		if (!(flag & 2))
			while (j++ < w)
				chc += (cc = f_putc(' '));

		chc += (cc = f_puts((char*)p));
		while (j++ < w)
			chc += (cc = f_putc(' '));
		cc = chc;
		continue;

	case 'C': cc = f_putc((char)va_arg(arglist, int)); continue; /* Character */
	case 'B': r = 2; break;     /* Binary */
	case 'O': r = 8; break;     /* Octal */
	case 'D':					/* Signed decimal */
	case 'U': r = 10; break;    /* Unsigned decimal */
	case 'X': r = 16; break;    /* Hexdecimal */
	default : cc = f_putc(c); continue; /* Unknown type (pass-through) */
	}

	/* Get an argument and put it in numeral */
	v = (flag & 4) ? (uint32_t)va_arg(arglist, long) : ((d == 'D') ? (uint32_t)(long)va_arg(arglist, int) : (uint32_t)va_arg(arglist, unsigned int));
	if (d == 'D' && (v & 0x80000000)) {
		v = 0 - v;
		flag |= 8;
	}
	i = 0;
	do {
		d = (char)(v % r); v /= r;
		if (d > 9) d += (c == 'x') ? 0x27 : 0x07;
		s[i++] = d + '0';
	} while (v && i < sizeof s / sizeof s[0]);
	if (flag & 8) s[i++] = '-';
	j = i; d = (flag & 1) ? '0' : ' ';
	res = 0;
	while (!(flag & 2) && j++ < w)
		res += (cc = f_putc(d));

	do res += (cc = f_putc(s[--i])); while(i);

	while (j++ < w) res += (cc = f_putc(' '));
	cc = res;
}
va_end( arglist );
#else
va_list arglist;
va_start(arglist, format);
vprintf(format, arglist);
va_end( arglist );
#endif
}

/*-------------------------------------------------------------------------------
   Convert hex string to byte array.
   Returns converted array length.
 -------------------------------------------------------------------------------*/
int UTIL_hexStrToArray(char *str, uint8_t *res, int maxsize)
{
    int numbytes = 0, hexstart = 0, hexlen;
    char seps[]    = " .<>/'\"-_\\:;\t";
    char hexvalid[] = "0x123456789ABCDEFabcdef";
    char hex[3];
    uint8_t tmp[8];   // sscanf saves 4 bytes instead of 1

    if (str == NULL || strlen(str) == 0) return 0;
    if (res == NULL) return 0;

    res[0] = '\0';
    while(1) {
        hexstart += (int)strspn(str + hexstart, seps);

        if (strlen(str + hexstart) > 2 && str[hexstart] == '0' && (str[hexstart + 1] == 'x' || str[hexstart + 1] == 'X') )
            hexstart += 2;                        // Check if hex value is in "0xAA" format and skip 0x

        if ((hexlen = (int)strspn(str + hexstart, hexvalid)) == 0) return numbytes;

        if (hexlen > 2) { hex[0] = str[hexstart]; hex[1] = str[hexstart + 1]; hex[2] = 0; hexstart += 2; }
        else            { strncpy (hex, str + hexstart, hexlen);         hex[hexlen] = 0; hexstart += hexlen; }

        if (sscanf(hex, "%x", (unsigned int*)tmp) > 0) res[numbytes++] = tmp[0];
        else return 0;
        if (numbytes >= maxsize) return numbytes;
    }
}
/*-------------------------------------------------------------------------
   String dump data to screen (in debug mode) and/or log file (if open)
   1 - message
   2 - parameter: pointer to dumped data
   3 - parameter: dumped data length
  -------------------------------------------------------------------------*/
void StrDump(char * message, uint8_t *data, int len)
{
    char str[200] = { 0 };
    int slen;

    if (message && strlen(message) > 0) {
        strncpy(str, message, sizeof(str)-1);
    }
    slen = (int)strlen(str);
    if (data && len) {
        strncat(str + slen, (char*)data, sizeof(str) - slen - 1);
        str[slen + len] = 0;
    }
    OPTIGAprintf("%s", str);
}
/*-------------------------------------------------------------------------
   Hex dump data to screen (in debug mode) and/or log file (if open)
   (without address)
   1 - message
   2 - parameter: pointer to dumped data
   3 - parameter: dumped data length
  -------------------------------------------------------------------------*/
void HexDumpNoCR(char * message, uint8_t *data, int len)
{
	int i, j, slen;
    char str[200] = { 0 };

    if (message && strlen(message) > 0) {
        strncpy(str, message, sizeof(str)-1);
    }

    OPTIGAprintf(message);

	for (i=0; i < len; i++, data++)
	{
		if ((i % 16) == 0 && i != 0)
		{
            OPTIGAprintf("%s\n\r", str);
        }
		sprintf(str + (i % 16) * 3, "%.2X ", *data);
	}
	OPTIGAprintf("%s", str);
	asm("nop");
}
//------------------------------------------------
void HexDump(char * message, uint8_t *data, int len)
{
    HexDumpNoCR(message, data, len);
	OPTIGAprintf("\n");
}

/****************************************************
 * UART READ AND WRITE HANDLING
 ****************************************************/
uart_ctx_t uart0_ctx =
{
  .uart_config_ptr = (void*)(&UART_0),
  .uart_rx_flag = 1,
  .uart_tx_flag = 1
};

void uart0_end_of_transmit_callback(void)
{
	uart0_ctx.uart_tx_flag = 0;
}
void uart0_end_of_receive_callback(void)
{
	uart0_ctx.uart_rx_flag = 0;
}

int terminal_io_read(uint8_t * data){
	uart0_ctx.uart_rx_flag = 1U;

	//lint --e{534} suppress "Return value is not required to be checked"
	UART_Receive(uart0_ctx.uart_config_ptr, data, 1);
	while (uart0_ctx.uart_rx_flag){;}
	return 1;
}

void terminal_io_write( uint8_t * message, int length ){
	uart0_ctx.uart_tx_flag = 1U;

	//lint --e{534} suppress "Return value is not required to be checked"
	UART_Transmit(uart0_ctx.uart_config_ptr, message, length);
	while (uart0_ctx.uart_tx_flag){;}
}
