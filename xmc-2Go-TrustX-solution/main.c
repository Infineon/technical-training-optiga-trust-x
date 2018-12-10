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
