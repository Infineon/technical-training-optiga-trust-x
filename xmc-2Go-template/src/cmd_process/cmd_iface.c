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
* \file cmd_iface.c
*
* \brief   This file provides the example for ECDSA Sign operation using #optiga_crypt_ecdsa_sign.
* 
*
* \ingroup
* @{
*/

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include <cmd_iface.h>
#include <string.h>
#include <stdio.h>
#include "cbuf.h"
#include "serial_io_iface.h"


int app_menu(void)
{
	OPTIGAprintf("Usage:\n\r");
	OPTIGAprintf("optx_get_rng            ......................Optiga Trust X generates a 32 bit True RNG\n\r");
	OPTIGAprintf("optx_get_sha256         ......................Optiga Trust X performs a SHA256 hash of message\n\r");
	OPTIGAprintf("optx_genKey_pair        ......................Optiga Trust X generates ECC256 KeyPair\n\r");
	OPTIGAprintf("optx_sign_hash          ......................Optiga Trust X signs hash\n\r");
	OPTIGAprintf("optx_verify_sig         ......................Optiga Trust X verifies signature\n\r");
	OPTIGAprintf("optx_sign_verify_sig    ......................Optiga Trust X sign & verify process\n\r");
	OPTIGAprintf("optx_ecdh_derive_key    ......................Optiga Trust X creates ECDH shared secret\n\r");
	OPTIGAprintf("optx_read_ifx_cert      ......................Reading Infineon Endorsement Certificate\n\r");
	OPTIGAprintf("\n\r");
	return 0;
}

uint8_t cmdbytes[128];

int parse_cmd( char *commands )
{
	int status = -1;

	do{
		if ( !strcmp( commands, "help"))
		{
			app_menu();
		}else if (!strcmp( commands, "optx_get_rng"))
		{
			status = optx_get_rng();
			if(status != 0)
			{
				OPTIGAprintf("Fail to execute optx_get_rng\n\r");
				break;
			}
		}else if (!strcmp( commands, "optx_get_sha256"))
		{
			status = optx_get_sha256();
			if(status != 0)
			{
				OPTIGAprintf("Fail to execute optx_get_sha256\n\r");
				break;
			}

		}else if (!strcmp( commands, "optx_genKey_pair"))
		{
			status = optx_genKey_pair();
			if(status != 0)
			{
				OPTIGAprintf("Fail to execute optx_genKey_pair\n\r");
				break;
			}
		}else if (!strcmp( commands, "optx_sign_hash"))
		{
			status = optx_sign_hash();
			if(status != 0)
			{
				OPTIGAprintf("Fail to execute optx_sign_hash\n\r");
				break;
			}

		}else if (!strcmp( commands, "optx_verify_sig"))
		{
			status = optx_verify_sig();
			if(status != 0)
			{
				OPTIGAprintf("Fail to execute optx_verify_sig\n\r");
				break;
			}
			else
			{
				OPTIGAprintf("Signature Verified\n\r");
			}
		}else if (!strcmp( commands, "optx_sign_verify_sig"))
		{
			status = optx_sign_verify_sig();
			if(status != 0)
			{
				OPTIGAprintf("Fail to execute optx_verify_sig\n\r");
				break;
			}else
			{
				OPTIGAprintf("Signature Verified\n\r");
			}
		}else if (!strcmp( commands, "optx_ecdh_derive_key"))
		{
			status = optx_ecdh_derive_key();
			if(status != 0)
			{
				OPTIGAprintf("Fail to execute optx_echd\n\r");
				break;
			}
		}else if (!strcmp( commands, "optx_read_ifx_cert"))
		{
			status = optx_read_ifx_cert();
			if(status != 0)
			{
				OPTIGAprintf("Fail to read endorsement certificate\n\r");
				break;
			}
		}else if ( strlen(commands) )
		{
			OPTIGAprintf("\r\nSyntax error in command: %s\r\n", commands);
		}
	}while(0);

	return 0;
}

int optx_get_rng(void)
{

}

int optx_get_sha256(void)
{

}

int optx_genKey_pair(void)
{

}

int optx_sign_hash(void)
{

}

int optx_verify_sig(void)
{

}

int optx_sign_verify_sig(void)
{

}

int optx_ecdh_derive_key(void)
{

}


int optx_read_ifx_cert(void)
{

}



int app_parse_cmd(void)
{
	static char cmd[256];

	uint16_t i = 0;
	while( !CBUF_IsEmpty(cmdQ) && i < sizeof(cmd))
	cmd[i++] = CBUF_Pop( cmdQ );
	cmd[i] = '\0';
	parse_cmd(cmd);
	OPTIGAprintf( "$ ");
	return 0;
}

