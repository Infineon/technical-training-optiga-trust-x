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
* \file main.c
*
* \brief   This file provides the example for ECDSA Sign operation using #optiga_crypt_ecdsa_sign.
* 
*
* \ingroup
* @{
*/

#include <cmd_iface.h>
#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include <serial_io_iface.h>
#include <stdio.h>
#include "xmc_gpio.h"
#include "xmc_scu.h"
#include "cbuf.h"


/**

 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. It is responsible for
 * invoking the APP initialization dispatcher routine - DAVE_Init() and hosting the place-holder for user application
 * code.
 */

int main(void)
{
  DAVE_STATUS_t status;
  uint8_t ch = 0;

  status = DAVE_Init();           /* Initialization of DAVE APPs  */

  if(status != DAVE_STATUS_SUCCESS)
  {
    /* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
	OPTIGAprintf("DAVE APPs initialization failed\n");

    while(1U)
    {

    }
  }

  app_menu();
  OPTIGAprintf("$");
  /* Placeholder for user application code. The while loop below can be replaced with user application code. */
  while(1U)
  {
	  if (terminal_io_read(&ch))
	  {
		OPTIGAprintf("%c",ch);
		if ( ch == 0x0d || ch == 0x0a ) {
			OPTIGAprintf("\n");
			app_parse_cmd();
			} else {
			CBUF_Push( cmdQ, ch );  // queue character into circular buffer
		}
	  }
  }
}
