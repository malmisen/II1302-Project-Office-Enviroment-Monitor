/**
******************************************************************************
@brief unit test for the office environment monitor project.
@details bla bla bla
@file unit_test.c
@author  Jonatan Lundqvist Silins, jonls@kth.se
@author  Sebastian Divander,       sdiv@kth.se
@date 29-03-2021
@version 1.0
******************************************************************************
*/

#include "unit_test.h"
#include "usart.h"
#include "stdio.h"
#include "ESP8266.h"
#include "CCS811_BME280.h"


void setUp(void){
}

void tearDown(void){
}

void test_esp8266_init(void){
	TEST_ASSERT_EQUAL_STRING(ESP8266_AT_OK, esp8266_init());
}

void test_esp8266_wifi_connect(void){
	TEST_ASSERT_EQUAL_STRING(ESP8266_AT_WIFI_CONNECTED, esp8266_wifi_init());
}

void test_esp8266_web_connection(void){
	char connection_command[256] = {0};
	char remote_ip[] = "ii1302-project-office-enviroment-monitor.eu-gb.mybluemix.net";
	char type[] = "TCP";
	char remote_port[] = "80";
	esp8266_get_connection_command(connection_command, type, remote_ip, remote_port);
	TEST_ASSERT_EQUAL_STRING(ESP8266_AT_CONNECT, esp8266_send_command(connection_command));
}

void test_esp8266_web_request(void){
	//"GET /api/sensor HTTP/1.1\r\nHost: ii1302-project-office-enviroment-monitor.eu-gb.mybluemix.net\r\nConnection: close\r\n\r\n";
	char request[256] = {0};
	char init_send[64] = {0};
	char uri[] = "/api/sensor/airquality?data=22335";
	//char uri[] = "/api/sensor";
	char host[] = "ii1302-project-office-enviroment-monitor.eu-gb.mybluemix.net";

//	uint8_t len = esp8266_http_get_request(request, HTTP_GET, uri, host);
	uint8_t len = esp8266_http_get_request(request, HTTP_POST, uri, host);
	esp8266_get_at_send_command(init_send, len);

	test_esp8266_at_send(init_send);
	test_esp8266_send_data(request);
}

void unit_test(void){

	/* Set up */
	init_uart_interrupt();

	/* Test begin */
	UNITY_BEGIN();
	/*
	/* Test initiation of ESP8266 */
	//RUN_TEST(test_esp8266_init);
	//HAL_Delay(2000);

	/* Test connecting to wifi */
	//RUN_TEST(test_esp8266_wifi_connect);

	/* Test connecting to a website */
	//RUN_TEST(test_esp8266_web_connection);

	/* Test making a http web request to connected website */
	//RUN_TEST(test_esp8266_web_request);

	/* Test end*/
	UNITY_END();
}

void test_esp8266_at_cwjap_verify(void){
	TEST_ASSERT_EQUAL_STRING(ESP8266_AT_WIFI_CONNECTED, esp8266_send_command(ESP8266_AT_CWJAP_TEST));
}

void test_esp8266_at_send(char* init_send){
	TEST_ASSERT_EQUAL_STRING(ESP8266_AT_SEND_OK, esp8266_send_command(init_send));
}

void test_esp8266_send_data(char* request) {
	TEST_ASSERT_EQUAL_STRING(ESP8266_AT_CLOSED, esp8266_send_data(request));
}
