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

/* */
#include <usart.h>
#include <string.h>
#include <stdio.h>

#define RX_BUFFER_SIZE 1280

/* return types/settings for ESP8266_send_command */
typedef enum{
	return_simple,		// return either "OK" or "ERROR"
	return_full,		// return full rx buffer
	return_cw_mode,		// return set cw mode
	return_connection
} return_type;

/* ssid and password for access point */
static const char SSID[] = "test";
static const char PWD[]  = "test";

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

uint8_t return_22(void);
char* return_char(void);

/**
 * doc
 */
char* ESP8266_send_command(const char*, return_type);
void ESP8266_get_cwjap_command(char* ref);
