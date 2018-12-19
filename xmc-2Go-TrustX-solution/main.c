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

/*OPTIGA Trust Include Files*/
#include "optiga/comms/optiga_comms.h"
#include "optiga/optiga_util.h"
#include "optiga/ifx_i2c/ifx_i2c_config.h"
#include "optiga/common/AuthLibSettings.h"

/*************************************************************************
*  function prototypes
*************************************************************************/
static int32_t optiga_init(void);
static int32_t optiga_deinit(void);

/*************************************************************************
*  Global
*************************************************************************/
optiga_comms_t optiga_comms = {(void*)&ifx_i2c_context_0,NULL,NULL, OPTIGA_COMMS_SUCCESS};

/*************************************************************************
*  functions
*************************************************************************/

static int32_t optiga_init(void)
{
	int32_t status = (int32_t) OPTIGA_LIB_ERROR;

	do
	{
		status = optiga_util_open_application(&optiga_comms);
		if(OPTIGA_LIB_SUCCESS != status)
		{
			sprintf(stderr, "Failure: CmdLib_OpenApplication(): 0x%04X", status);
			break;
		}

		status = OPTIGA_LIB_SUCCESS;
	} while(0);

	return status;
}

static int32_t optiga_deinit(void)
{
    int32_t status = (int32_t) OPTIGA_LIB_ERROR;

    //Close IFX I2C Protocol and switch off the security chip
    status = optiga_comms_close(&optiga_comms);
    if(OPTIGA_LIB_SUCCESS != status)
    {
    	sprintf(stderr, "Failure: optiga_comms_close(): 0x%04X", status);
    }

    printf("Device closed\n");
    return status;
}


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
  //Return value
  optiga_lib_status_t return_status = OPTIGA_LIB_ERROR;
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

  return_status = optiga_init();
  if (OPTIGA_LIB_SUCCESS != return_status)
  {
	  OPTIGAprintf("OPTIGA Trust initialization failed\n");
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
