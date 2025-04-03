// SetupBLT.c
// Runs on TM4C123
// This is an example program to setup HC-05 Bluetooth module with no user interface.
// UART0 is used for the TM4C123 to communicate with PC serial terminal, 
// UART1 is used for the TM4C123 to cummunicate with HC-05 Bluetooth module
// U1Rx (PB0) connects to HC-05 TXD pin
// U1Tx (PB1) connects to HC-05 RXD pin
// HC-05 VCC connects to vbus pin on TM4C123
// HC-05 EN connects to +3.3v
// By Min He,10/11/2022

#include "tm4c123gh6pm.h"
#include "UART0.h"
#include "BLT.h"
#include <stdint.h>  // for data type alias

#define MAX_LENGTH  30

uint8_t command[MAX_LENGTH];
uint8_t input[MAX_LENGTH];


// main function for programming BT device with  UI
int main(void) {
	UART0_Init();
	BLT_Init();
	
	//Welcome Prompt
	UART0_NextLine();
	UART0_OutString((uint8_t*)">>> Welcome to Serial Terminal. <<<");
	UART0_NextLine();
	UART0_OutString((uint8_t*)">>> This is the setup program for HC-05 Bluetooth module. <<<");
	UART0_NextLine();
	UART0_OutString((uint8_t*)">>> You are at 'AT' userInput Mode. <<<");
	UART0_NextLine();
	UART0_OutString((uint8_t*)">>> Type 'AT' and followed with a userInput. <<<");
	UART0_NextLine();
	UART0_OutString((uint8_t*)">>> Example: AT+NAME=DH <<<");
	UART0_NextLine();
	
	while(1){
		UART0_InString(command, MAX_LENGTH);
		BLT_OutString(command);
		BLT_OutString((uint8_t*)"\r\n");
		
		while ((UART1_FR_R&UART_FR_BUSY) != 0){};
			
		BLT_InString(input);	
		UART0_NextLine();
		UART0_OutString(input);
	
		if(command[7] == '?'){
			BLT_InString(input);
			UART0_NextLine();
			UART0_OutString(input);
		}
	
		UART0_NextLine();
		UART0_NextLine();
	}
}
