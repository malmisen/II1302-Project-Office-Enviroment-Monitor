/**
******************************************************************************
@brief Header for the project unit test
@file unit_test.h
@author Jonatan Lundqvist Silins, jonls@kth.se
******************************************************************************
*/

#include <unity.h>

void unit_test(void);
void setUp(void);
void tearDown(void);

void test_ESP8266_AT(void);
void test_ESP8266_AT_GMR(void);
void test_ESP8266_AT_CWMODE_1(void);
void test_ESP8266_AT_CWMODE_1_VERIFY(void);
void test_ESP8266_AT_CWJAP_SET(void);
void test_ESP8266_AT_CWJAP_VERIFY(void);
