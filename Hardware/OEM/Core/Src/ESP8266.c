/**
******************************************************************************
@brief functions for the ESP8266 wifi-module
@details
@file ESP8266.c
@author  Jonatan Lundqvist Silins, jonls@kth.se
@date 06-04-2021
@version 1.0
*******************************************************************************/
#include "ESP8266.h"

static char rx_buffer[RX_BUFFER_SIZE];

static return_type selected_return_type;

char* ESP8266_send_command(const char* command, return_type type){

	selected_return_type = type;
	memset(rx_buffer, 0, RX_BUFFER_SIZE);
	HAL_UART_Transmit(&huart4, (uint8_t*) command, strlen(command), 1);
	HAL_UART_Receive(&huart4, (uint8_t*) rx_buffer, RX_BUFFER_SIZE, 100);

	switch (selected_return_type) {
		case return_simple:
			if (strstr(rx_buffer, "OK\r\n") == NULL) {
				return "ERROR";
			}
			return "OK";

		case return_full:
			return rx_buffer;

		case return_cw_mode:
			if (strstr(rx_buffer, "CWMODE_CUR:1") != NULL)
				return "CWMODE:1";
			else if(strstr(rx_buffer, "CWMODE_CUR:2") != NULL)
				return "CWMODE:2";
			else if(strstr(rx_buffer, "CWMODE_CUR:3") != NULL)
				return "CWMODE:3";
			else
				return "CWMODE:?";

		case return_connection:
			if(strstr(rx_buffer, "NO AP") != NULL)
				return "NO AP";
			else if(strstr(rx_buffer, "OK") != NULL)
				return "OK";
			else {

				if (strstr(rx_buffer, "CWJAP:1") != NULL)
					return "CWJAP:1 - connection timeout";
				else if((strstr(rx_buffer, "CWJAP:2") != NULL))
					return "CWJAP:2 - wrong password";
				else if((strstr(rx_buffer, "CWJAP:3") != NULL))
					return "CWJAP:3 - cannot find the target AP";
				else if((strstr(rx_buffer, "CWJAP:4") != NULL))
					return "CWJAP:4 - connection failed";
				else
					return "CWJAP:?";
			}
		default:
			return "No return type";
	}
}

void ESP8266_get_cwjap_command(char* ref){
	strcat(ref, ESP8266_AT_CWJAP_SET);
	strcat(ref,"\"");
	strcat(ref, SSID);
	strcat(ref, "\",\"");
	strcat(ref, PWD);
	strcat(ref, "\"");
	strcat(ref, CRLF);
	//sprintf (ref, "AT+CWJAP=\"%s\",\"%s\"\r\n", SSID, PWD);
}



/*

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart){
	HAL_UART_Receive_IT(&huart2, (uint8_t*) rxx_buffer, 256);
}
*/
