/**
 ******************************************************************************
 * @file    cloud.c
 * @author  MCD Application Team
 * @version	3.0.0
 * @date	20-July-2018
 * @brief   .
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics International N.V.
 * All rights reserved.</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted, provided that the following conditions are met:
 *
 * 1. Redistribution of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of other
 *    contributors to this software may be used to endorse or promote products
 *    derived from this software without specific written permission.
 * 4. This software, including modifications and/or derivative works of this
 *    software, must execute solely and exclusively on microcontroller or
 *    microprocessor devices manufactured by or for STMicroelectronics.
 * 5. Redistribution and use of this software other than as permitted under
 *    this license is void and will automatically terminate your rights under
 *    this license.
 *
 * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
 * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
 * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"
#include "net.h"
#include "heap.h"
#include "cloud.h"
#include "dns.h"

#include "user.h"

#ifdef FFT_DEMO
#include "fft.h"
extern char dataOut[256];
extern UART_HandleTypeDef console_uart;
extern void *ACCELERO_handle;

#endif //  FFT_DEMO

#if (defined USE_LWIP)
void InitRTC(void);
void Netif_Config(BluemixEthConfiguration_t EthConfiguration);
extern struct netif gnetif;
#endif //USE_LWIP

extern int net_if_init(void * if_ctxt);
extern int net_if_deinit(void * if_ctxt);

/* Private defines -----------------------------------------------------------*/
#define CLOUD_TIMEDATE_TLS_VERIFICATION_IGNORE  /**< Accept to connect to a server which is not verified by TLS */

/* Private typedef -----------------------------------------------------------*/
typedef enum
{
	CLOUD_DEMO_WIFI_INITIALIZATION_ERROR      = -2,
	CLOUD_DEMO_MAC_ADDRESS_ERROR              = -3,
	CLOUD_DEMO_WIFI_CONNECTION_ERROR          = -4,
	CLOUD_DEMO_IP_ADDRESS_ERROR               = -5,
	CLOUD_DEMO_CONNECTION_ERROR               = -6,
	CLOUD_DEMO_TIMEDATE_ERROR                 = -7,
	CLOUD_DEMO_C2C_INITIALIZATION_ERROR       = -8
} CLOUD_DEMO_Error_t;

/* Private function prototypes -----------------------------------------------*/
void CLOUD_Error_Handler(int errorCode);

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
void CLOUD_Error_Handler(int errorCode)
{
	switch (errorCode)
	{
	case (CLOUD_DEMO_C2C_INITIALIZATION_ERROR):
	case (CLOUD_DEMO_WIFI_INITIALIZATION_ERROR):
	{
		printf("Error initializing the module!\n");

		break;
	}
	case (CLOUD_DEMO_MAC_ADDRESS_ERROR):
    	{
		printf("Error detecting module!\n");

		break;
    	}
	case (CLOUD_DEMO_WIFI_CONNECTION_ERROR):
    	{
		printf("Error connecting to AP!\n");

		break;
    	}
	case (CLOUD_DEMO_IP_ADDRESS_ERROR):
    	{
		printf("Error retrieving IP address!\n");

		break;
    	}
	case (CLOUD_DEMO_CONNECTION_ERROR):
    	{
		printf("Error connecting to Cloud!\n");

		break;
    	}
	case (CLOUD_DEMO_TIMEDATE_ERROR):
    	{
		printf("Error initializing the RTC from the network time!\n");

		break;
    	}
	default:
	{
		break;
	}
	}

	while (1)
	{
		BSP_LED_Toggle(LED_GREEN);
		HAL_Delay(200);
	}
}

net_ipaddr_t ipAddr;
net_macaddr_t macAddr;
bool nfcHWPresent = false;

int platform_init(void)
{
	net_ipaddr_t ipAddr;
	net_macaddr_t macAddr;

#ifdef HEAP_DEBUG
	stack_measure_prologue();
#endif

	printf("\r\n");
	printf("**************************************************************************\r\n");
	printf("***                         HTL Wels IoT client                        ***\r\n");
	printf("**************************************************************************\n\r");

	/* Network initialization */
	if (net_init(&hnet, NET_IF, (net_if_init)) != NET_OK)
	{
#ifdef USE_C2C
		CLOUD_Error_Handler(CLOUD_DEMO_C2C_INITIALIZATION_ERROR);
#else
		CLOUD_Error_Handler(CLOUD_DEMO_IP_ADDRESS_ERROR);
#endif
		return -1;
	}

	if (net_get_mac_address(hnet, &macAddr) == NET_OK)
	{
		msg_info("Mac address: %02X:%02X:%02X:%02X:%02X:%02X\n",
				macAddr.mac[0], macAddr.mac[1], macAddr.mac[2], macAddr.mac[3], macAddr.mac[4], macAddr.mac[5]);
	}
	else
	{
		CLOUD_Error_Handler(CLOUD_DEMO_MAC_ADDRESS_ERROR);
		return -1;
	}

	/* Slight delay since the netif seems to take some time prior to being able
   to retrieve its IP address after a connection. */
	HAL_Delay(500);

	msg_info("Retrieving the IP address.\n");

	if (net_get_ip_address(hnet, &ipAddr) != NET_OK)
	{
		CLOUD_Error_Handler(CLOUD_DEMO_IP_ADDRESS_ERROR);
		return -1;
	}
	else
	{
		switch(ipAddr.ipv)
		{
		case NET_IP_V4:
			msg_info("IP address: %d.%d.%d.%d\n", ipAddr.ip[12], ipAddr.ip[13], ipAddr.ip[14], ipAddr.ip[15]);
			break;
		case NET_IP_V6:
		default:
			CLOUD_Error_Handler(CLOUD_DEMO_IP_ADDRESS_ERROR);
			return -1;
		}
	}

	msg_info("Retrieving the Gateway IP address.\n");

	if (net_get_gw_ip_address(hnet, &ipAddr) != NET_OK)
	{
		CLOUD_Error_Handler(CLOUD_DEMO_IP_ADDRESS_ERROR);
		return -1;
	}
	else
	{
		switch(ipAddr.ipv)
		{
		case NET_IP_V4:
			msg_info("Gateway IP address: %d.%d.%d.%d\n", ipAddr.ip[12], ipAddr.ip[13], ipAddr.ip[14], ipAddr.ip[15]);
			break;
		case NET_IP_V6:
		default:
			CLOUD_Error_Handler(CLOUD_DEMO_IP_ADDRESS_ERROR);
			return -1;
		}
	}

	msg_info("Retrieving the DNS Server IP address.\n");
	const ip_addr_t* dns = dns_getserver(0);
	memcpy(&(ipAddr.ip[12]), &(dns->addr), 4);
	msg_info("DNS Server IP address: %d.%d.%d.%d\n", ipAddr.ip[12], ipAddr.ip[13], ipAddr.ip[14], ipAddr.ip[15]);

	/* End of network initialisation */

	/* Security and cloud parameters definition */
	/* Define, or allow to update if the user button is pushed. */
//	skip_reconf = (checkTLSRootCA() == 0);
//
//	if (skip_reconf == true)
//	{
//		printf("Push the User button (Blue) within the next 3 seconds if you want to update "
//				"the device security parameters or credentials.\n\n\r");
//		skip_reconf = (Button_WaitForPush(3000) == BP_NOT_PUSHED);
//	}
//
//	if (skip_reconf == false)
//	{
//		updateTLSCredentials();
//	}
	/* End of security and cloud parameters definition */

#ifdef SENSOR
	int res = init_sensors();
	if(0 != res)
	{
		msg_error("init_sensors returned error : %d\n", res);
	}
#endif /* SENSOR */

	return 0;
}

void    platform_deinit()
{
	/* Close Cloud connectivity demonstration */
	printf("\n*** Cloud connectivity demonstration ***\n\n\r");
	printf("Cloud connectivity demonstration completed\n\r");
#ifdef USE_LWIP
	//#else

	(void)net_deinit(hnet, (net_if_deinit));

#ifdef   HEAP_DEBUG
	stack_measure_epilogue();
	uint32_t heap_max,heap_current,stack_size;

#ifdef   FIREWALL_MBEDLIB
	heap_firewall_stat(&heap_max,&heap_current,&stack_size);
	msg_info("FireWall Heap Max allocation 0x%x (%d), current allocation 0x%x (%d), Stack max size 0x%x (%d)\n",heap_max,heap_max,heap_current,heap_current,stack_size,stack_size);
#endif

	heap_stat(&heap_max,&heap_current,&stack_size);
	msg_info("Heap Max allocation 0x%x (%d), current allocation 0x%x (%d), Stack max size 0x%x (%d)\n",heap_max,heap_max,heap_current,heap_current,stack_size,stack_size);
#endif
#endif // USE_LWIP  
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
