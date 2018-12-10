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

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include <cmd_iface.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include "cbuf.h"
#include "serial_io_iface.h"

/*OPTIGA Trust Include Files*/
#include "optiga/optiga_crypt.h"
#include "optiga/optiga_util.h"

/*Global variable used for this exercise*/
uint8_t global_random[32] = {};
uint8_t global_digest[32] = {};
uint8_t global_signature[80] = {};
uint8_t global_sig_length = 0;
uint8_t global_pubkey[80] = {};
uint8_t global_pubkey_length = 0;


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
	optiga_lib_status_t optiga_status = OPTIGA_LIB_ERROR;
	uint8_t rnd[32];

	do{
		OPTIGAprintf("Retrieving random numbers from OPTIGA Trust X:\r\n");
		optiga_status = optiga_crypt_random(OPTIGA_RNG_TYPE_TRNG, rnd, sizeof(rnd));
		if(optiga_status != 0)
			break;
		memcpy(global_random, rnd, sizeof(rnd));
		HexDump(rnd, sizeof(rnd));

	}while(0);

	return optiga_status;
}

int optx_get_sha256(void)
{
	optiga_lib_status_t optiga_status = OPTIGA_LIB_ERROR;

	uint8_t hash_context_buffer [130];
	optiga_hash_context_t hash_context;
	uint8_t data_to_hash [] = {"OPTIGA Trust X, Hardened Security"};
	hash_data_from_host_t hash_data_host;


	hash_context.context_buffer = hash_context_buffer;
	hash_context.context_buffer_length = sizeof(hash_context_buffer);
	hash_context.hash_algo = OPTIGA_HASH_TYPE_SHA_256;

	uint8_t digest[32];

	do{
		OPTIGAprintf("Message to Hash: -OPTIGA Trust X, Hardened Security- \r\n");
		OPTIGAprintf("OPTIGA Trust X Performing SHA256 of Message\r\n");

		//Hash start
		optiga_status = optiga_crypt_hash_start(&hash_context);
		if(optiga_status != OPTIGA_LIB_SUCCESS)
		{
			break;
		}

		//Hash update
		hash_data_host.buffer = data_to_hash;
		hash_data_host.length = sizeof(data_to_hash);

		optiga_status = optiga_crypt_hash_update(&hash_context,
												 // OPTIGA_CRYPT_OID_DATA stands for OID
												 OPTIGA_CRYPT_HOST_DATA,
												 &hash_data_host);
		if(optiga_status != OPTIGA_LIB_SUCCESS)
		{
			break;
		}

		// hash finalize
		optiga_status = optiga_crypt_hash_finalize(&hash_context,
												   digest);

		if(optiga_status != OPTIGA_LIB_SUCCESS)
		{
			break;
		}

		HexDump(digest, sizeof(digest));
		memcpy(global_digest, digest, sizeof(digest));
	}while(0);

	return optiga_status;
}

int optx_genKey_pair(void)
{
	optiga_lib_status_t optiga_status;
	optiga_key_id_t optiga_key_id;

	//To store the generated public key as part of Generate key pair
	uint8_t public_key [100];
	uint16_t public_key_length = sizeof(public_key);

	do{
		/**
		 * Generate ECC Key pair
		 *       - Use ECC NIST P 256 Curve
		 *       - Specify the Key Usage (Key Agreement or Sign based on requirement)
		 *       - Store the Private key in OPTIGA Key store
		 *       - Export Public Key
		 */
		optiga_key_id = OPTIGA_KEY_STORE_ID_E0F1;
		//for Session based, use OPTIGA_KEY_ID_SESSION_BASED as key id as shown below.
		//optiga_key_id = OPTIGA_KEY_ID_SESSION_BASED;
		optiga_status = optiga_crypt_ecc_generate_keypair(OPTIGA_ECC_NIST_P_256,
														  (uint8_t)OPTIGA_KEY_USAGE_SIGN,
														  FALSE,
														  &optiga_key_id,
														  public_key,
														  &public_key_length);
		if (OPTIGA_LIB_SUCCESS != optiga_status)
		{
			//Key pair generation failed
			break;
		}

		HexDump(public_key, public_key_length);
		memcpy(global_pubkey, public_key, public_key_length);
		global_pubkey_length = public_key_length;

	}while(0);

	return optiga_status;
}



int optx_sign_hash(void)
{
	optiga_lib_status_t optiga_status;

	 uint8_t signature [80];     //To store the signture generated
	 uint16_t signature_length = sizeof(signature);

	do{
		OPTIGAprintf("OPTIGA Trust Signing Message: \r\n");
		optiga_status = optiga_crypt_ecdsa_sign(global_digest,
		                                        sizeof(global_digest),
												OPTIGA_KEY_STORE_ID_E0F1,
		                                        signature,
		                                        &signature_length);
		if (OPTIGA_LIB_SUCCESS != optiga_status)
			break;
		HexDump(signature, signature_length);
		memcpy(global_signature, signature, signature_length);
		global_sig_length = signature_length;

	}while(0);

	return optiga_status;
}

int optx_verify_sig(void)
{
	optiga_lib_status_t optiga_status;

	public_key_from_host_t public_key_details = {
													global_pubkey,
													global_pubkey_length,
													OPTIGA_ECC_NIST_P_256
	                                               };


	do{
		optiga_status = optiga_crypt_ecdsa_verify (global_digest,
		                                           sizeof(global_digest),
												   global_signature,
		                                           global_sig_length,
												   // OPTIGA_CRYPT_OID_DATA stands for OID in the public_key_details
												   OPTIGA_CRYPT_HOST_DATA,
		                                           &public_key_details);
		if (OPTIGA_LIB_SUCCESS != optiga_status)
			break;
	}while(0);
	return optiga_status;
}

int optx_sign_verify_sig(void)
{
	optiga_lib_status_t optiga_status;
	do{
		OPTIGAprintf("OPTIGA Trust Sign/Verify Message: \r\n\n");
		do{

		OPTIGAprintf("1-. Generate a random ECC Key pair: \r\n\n");
		optiga_status = optx_genKey_pair();
		OPTIGAprintf("\r\n");
		if (optiga_status != 0)
			break;
		OPTIGAprintf("2-. Hash (SHA256) the message to sign: \r\n\n");
		optiga_status = optx_get_sha256();
		OPTIGAprintf("\r\n");
		if (optiga_status != 0)
			break;
		OPTIGAprintf("3-. Sign the SHA256 digest with our private ECC256 key: \r\n\n");
		optiga_status = optx_sign_hash();
		OPTIGAprintf("\r\n");
		if (optiga_status != 0)
			break;
		OPTIGAprintf("4-. Verify signature of message with public ECC256 key: \r\n\n");
		optiga_status = optx_verify_sig();
		OPTIGAprintf("\r\n");
		if (optiga_status != 0)
			break;
		}while(0);

		if (optiga_status != 0)
			break;
		OPTIGAprintf("Message is Authentic: \r\n\n");
	}while(0);

	return optiga_status;
}

int optx_ecdh_derive_key(void)
{
	optiga_lib_status_t optiga_status;
	uint8_t decryption_key [16] = {0};
	uint8_t public_key [80];
	uint16_t public_key_length = sizeof(public_key);
	optiga_key_id_t optiga_key_id;
	uint8_t label [] = "";



	// Peer public key details for the ECDH operation
	static uint8_t peer_public_key [] =
	{
	    //Bit string format
	    0x03,
	        //Remaining length
	        0x42,
	            //Unused bits
	            0x00,
	            //Compression format
	            0x04,
	            //Public Key
	            0x94, 0x89, 0x2F, 0x09, 0xEA, 0x4E, 0xCA, 0xBC, 0x6A, 0x4E, 0xF2, 0x06, 0x36, 0x26, 0xE0, 0x5D,
	            0xE0, 0xD5, 0xF9, 0x77, 0xEA, 0xC3, 0xB2, 0x70, 0xAC, 0xE2, 0x19, 0x00, 0xF5, 0xDB, 0x56, 0xE7,
	            0x37, 0xBB, 0xBE, 0x46, 0xE4, 0x49, 0x76, 0x38, 0x25, 0xB5, 0xF8, 0x94, 0x74, 0x9E, 0x1A, 0xB6,
	            0x5A, 0xF1, 0x29, 0xD7, 0x3A, 0xB6, 0x9B, 0x80, 0xAC, 0xC5, 0xE1, 0xC3, 0x10, 0xF2, 0x16, 0xC6,
	};


	do{
		OPTIGAprintf("1.- Using Peer PubKey for ECDH key agreement: \r\n\n");
		HexDump(peer_public_key, sizeof(peer_public_key));
		OPTIGAprintf("\r\n");

		public_key_from_host_t peer_public_key_details = {
															(uint8_t *)&peer_public_key,
															sizeof(peer_public_key),
															OPTIGA_ECC_NIST_P_256
														   };
		OPTIGAprintf("2-. Generate a random seed: \r\n\n");
		optiga_status = optx_get_rng();
		OPTIGAprintf("\r\n");
		if (OPTIGA_LIB_SUCCESS != optiga_status)
		{
			// Key pair generation failed
			break;
		}


		OPTIGAprintf("3-. Generate an ECC256 Key Pair for the session: \r\n");
		OPTIGAprintf("    Private Key Securely stored in OPTIGA Trust\r\n\n");
		/**
		 * Generate ECC Key pair - To use the private key with ECDH in the next step
		 *       - Use ECC NIST P 256 Curve
		 *       - Specify the Key Usage as Key Agreement
		 *       - Store the Private key with in OPTIGA Session
		 *       - Export Public Key
		 */
		optiga_key_id = OPTIGA_SESSION_ID_E100;
		optiga_status = optiga_crypt_ecc_generate_keypair(OPTIGA_ECC_NIST_P_256,
														  (uint8_t)OPTIGA_KEY_USAGE_KEY_AGREEMENT,
														  FALSE,
														  &optiga_key_id,
														  public_key,
														  &public_key_length);
		OPTIGAprintf("    Public Key is send to Peer\r\n\n");
		HexDump(public_key, public_key_length);
		OPTIGAprintf("\r\n");
		if (OPTIGA_LIB_SUCCESS != optiga_status)
		{
			// Key pair generation failed
			break;
		}


		OPTIGAprintf("4-. Performing Key Agreement ECDH(E): \r\n");
		OPTIGAprintf("    Pre-master secret is securely stored in OPTIGA Trust\r\n\n");
		 /**
		 * Perform ECDH using the Peer Public key
		 *       - Use ECC NIST P 256 Curve
		 *       - Provide the peer public key details
		 *       - Export the generated shared secret
		 */
		optiga_status = optiga_crypt_ecdh(optiga_key_id,
										  &peer_public_key_details,
										  FALSE,
										  (uint8_t *)&optiga_key_id);
		OPTIGAprintf("\r\n");
		if (OPTIGA_LIB_SUCCESS != optiga_status)
		{
			//ECDH Operation failed.
			break;
		}

		OPTIGAprintf("5-. Using OPTIGA Trust internal KDF and Premaster Secret to generate a session key: \r\n");
		OPTIGAprintf("    Session key can securely be used for AES encryption of communication channel\r\n\n");

		/**
		 * Derive key (e.g. decryption key) using optiga_crypt_tls_prf_sha256 with I2C communication.
		 *       - Use shared secret from F1D0 data object
		 */
		optiga_status = optiga_crypt_tls_prf_sha256(optiga_key_id, /* Input secret OID */
													label,
													sizeof(label),
													global_random,
													sizeof(global_random),
													sizeof(decryption_key),
													TRUE,
													decryption_key);
		OPTIGAprintf("\r\n");
		if(OPTIGA_LIB_SUCCESS != optiga_status)
		{
			//Derive key operation failed.
			break;
		}

		OPTIGAprintf("6-. Encryption Key: \r\n");
		HexDump(decryption_key, sizeof(decryption_key));
		OPTIGAprintf("\r\n");
	}while(0);

	return optiga_status;
}


int optx_read_ifx_cert(void)
{
	optiga_lib_status_t optiga_status;
	uint16_t offset, bytes_to_read;
	uint16_t optiga_oid;
	uint8_t read_data_buffer[1024];
	do{
		//Read device end entity certificate from OPTIGA
		optiga_oid = eDEVICE_PUBKEY_CERT_IFX;
		offset = 0x00;
		bytes_to_read = sizeof(read_data_buffer);

		/**
		 * 1. Read data from a data object (e.g. certificate data object)
		 *    using optiga_util_read_data.
		 */
		optiga_status = optiga_util_read_data(optiga_oid,
											  offset,
											  read_data_buffer,
											  &bytes_to_read);

		if (OPTIGA_LIB_SUCCESS != optiga_status)
		{
			//Reading the data object failed.
			break;
		}

		OPTIGAprintf("Infineon Endorsement Certificate provisioned in factory: \r\n");
		__hexdump_ascii__(read_data_buffer, bytes_to_read);

	}while(0);

	return optiga_status;
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

