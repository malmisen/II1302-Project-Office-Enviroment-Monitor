/**
******************************************************************************
@brief header for the ESP8266 wifi-module functions
@details This header has all the necessary commands and functions to use the
		 ESP8266 wifi-module, including relevant AT-commands and functions
		 to use them in regards to the Office Environment Monitor project.
@file ESP8266.h
@author  Jonatan Lundqvist Silins, jonls@kth.se
@date 06-04-2021
@version 1.0
*******************************************************************************/

/*----------Includes------------*/
#include <usart.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

/*----------Defines------------*/
#define RX_BUFFER_SIZE 1024

/* djb2 hash keys */
/* TODO: implement as enum */
#define ESP8266_AT_KEY 	 	 				2088901425
#define ESP8266_AT_RST_KEY	 				617536853
#define ESP8266_AT_GMR_KEY	 				604273922
#define ESP8266_AT_CWMODE_STATION_MODE_KEY 	608151977
#define ESP8266_AT_CWMODE_TEST_KEY			4116713283
#define ESP8266_AT_CWQAP_KEY				445513592
#define ESP8266_AT_CWJAP_TEST_KEY			1543153456
#define ESP8266_DEBUG_KEY					217349260
//ESP8266_AT_CWJAP_SET_KEY 			4

/* ssid and password for access point */
static const char SSID[] = "test";
static const char PWD[]  = "test";


static bool ERROR_FLAG = false;
static bool FAIL_FLAG = false;

static const char CRLF[]               = "\r\n";

/* AT Commands for the ESP8266, see
 * https://www.espressif.com/sites/default/files/documentation/4a-esp8266_at_instruction_set_en.pdf
 *
 * Commands are case sensitive and should end with /r/n
 * Commands may use 1 or more of these types:
 * Set = AT+<x>=<...> - Sets the value
 * Inquiry = AT+<x>? - See what the value is set at
 * Test = AT+<x>=? - See the possible options
 * Execute = AT+<x> - Execute a command
 *
 * Some commands seem to be outdated, and COMMAND_CUR and COMMAND_DEF should be used instead.
 * CUR will not write the value to flash, DEF will write the value to flash and be used as the default in the future.
 *
 **/

/*Tests AT startup.
 *
 * Returns: OK
 */
static const char ESP8266_AT[]						= "AT\r\n";


/*Restarts the module.
 *
 * Returns: OK
 */
static const char ESP8266_AT_RST[]					= "AT+RST\r\n";

/*Checks version information.*/
static const char ESP8266_AT_GMR[]					= "AT+GMR\r\n";

/*Checks current wifi-mode.
 *
 * Returns: <mode>
 * 1: Station Mode
 * 2: SoftAP Mode
 * 3: SoftAP+Station Mode
 */
static const char ESP8266_AT_CWMODE_TEST[]			= "AT+CWMODE_CUR?\r\n";

/*Sets the wifi-mode to station.
 * The module will work as client.
 * Note: setting not saved in flash...
 */
static const char ESP8266_AT_CWMODE_STATION_MODE[]	= "AT+CWMODE=1\r\n";

/*Query the AP for connections*/
static const char ESP8266_AT_CWJAP_TEST[]			= "AT+CWJAP?\r\n";

/*Sets a connection to an AP
 *
 * Command format: AT+CWJAP_CUR=<ssid>,<pwd>
 * <ssid>: the SSID of the target AP.
 * <pwd>: password, MAX: 64-byte ASCII.
 * Note: the command needs Station Mode to be enabled.
 *
 * The command returns an error if:
 * connection times out
 * wrong password
 * cannot find the target AP
 * connection failed
 */
static const char ESP8266_AT_CWJAP_SET[]			= "AT+CWJAP="; // add "ssid","pwd" + CRLF

/*Disconnect connected AP*/
static const char ESP8266_AT_CWQAP[]				= "AT+CWQAP\r\n";

/*Disable auto connect to AP*/
static const char ESP8266_AT_CWAUTOCONN[]			= "AT+CWAUTOCONN=0";

/*Set single TCP connection*/
static const char ESP8266_AT_CIPMUX[]				= "AT+CIPMUX=0\r\n";

/*Establishes TCP connection
 *
 * Assumes AT+CIPMUX=0
 * Use following format:
 * AT+CIPSTART=<type>,<remote	IP>,<remote	port>[,<TCP	keep alive>]
 *
 * Example: AT+CIPSTART="TCP","iot.espressif.cn",8000
 */
static const char ESP8266_AT_START[]				= "AT+START=\"TCP\",";

/*Send data of desired length*/
static const char ESP8266_AT_SEND[]					= "AT+CIPSEND=";

static const char ESP8266_DEBUG[]					= "DEBUG";

/*============================================================================
	FUNCTIONS FOR ESP8266
==============================================================================*/

/**
 *
 */
void ESP8266_get_cwjap_command(char*);
/**
 *
 */
void init_uart_interrupt(void);
/**
 *
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
/**
 *
 */
char* uart_send(const char*);

const unsigned long hash(const char*);
