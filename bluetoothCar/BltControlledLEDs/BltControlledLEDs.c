// BLTControlledLEDs.c
// Runs on LM4F120/TM4C123
// This is an example program which shows how to use Bluetooth to received commands from a Bluetooth terminal
// and use the received command to control the onboard LEDs.
// U1Rx (PB0)
// U1Tx (PB1)
// Ground connected ground in the USB cable


// Header files 
#include "tm4c123gh6pm.h"
#include "PWM.h"
#include "UART.h"
#include "LED.h"

void forward(void);
void backward(void);
void left(void);
void right(void);
void stop (void);
void backward_left(void);
void backward_right(void);

int CURRENT_SPEED;

int main(void) {
	unsigned char control_symbol; // for bluetooth controlled LEDs
  CURRENT_SPEED = 1600;
	
	PortE_Init();	// MOTOR Init
  LED_Init(); // Initialize onboard LEDs
	PWM_PB76_Init();
	PWM_PB76_Duty(CURRENT_SPEED, CURRENT_SPEED);
	UART_Init(); // Initialize UART1
	LED = Dark;
	UART0_OutString((unsigned char *)">>> Welcome to Bluetooth Controlled LED App <<<\n\r");
    
  // Bluetooth Controlled LEDs
	while(1) {
    control_symbol = UART1_InChar();
    UART0_OutChar(control_symbol);
		UART0_OutChar(CR);
    UART0_OutChar(LF);

    switch (control_symbol){
      case 'f':
			case 'F': 
				forward();
        break; 
      case 'B':
			case 'b':
        backward();
        break; 
      case 'l':
			case 'L':
				if(DIRECTION == BACKWARD)
					backward_left();
				else
					left();
        break; 
      case 'r':
			case 'R':
				if(DIRECTION == BACKWARD)
					backward_right();
				else
					right();
        break; 
      case 's':
			case 'S':
				stop();
        break; 
      case 'u':
			case 'U':
				if(CURRENT_SPEED < PERIOD - STEP)
					CURRENT_SPEED += STEP;
				PWM_PB76_Duty(CURRENT_SPEED, CURRENT_SPEED);
        break; 
      case 'd':
			case 'D':
				if(CURRENT_SPEED > STEP)
					CURRENT_SPEED -= STEP;
				PWM_PB76_Duty(CURRENT_SPEED, CURRENT_SPEED);
        break; 
      default:
        break;
    }
	}
}

void forward(void){
	LED = Green;
	DIRECTION = FORWARD;
	PWM0_ENABLE_R |= 0x00000003; // enable both wheels
}

void backward(void){
	LED = Blue;
	DIRECTION = BACKWARD;
	PWM0_ENABLE_R |= 0x00000003; // enable both wheels
}
void left(void){
	LED = Yellow;
	DIRECTION=FORWARD;
	PWM0_ENABLE_R &= ~0x00000002; // Enable right wheel
	PWM0_ENABLE_R |= 0x00000001; // Disable left wheel
}
void right(void){
	LED = Purple;
	DIRECTION=FORWARD;
	PWM0_ENABLE_R |= 0x00000002; // Enable right wheel
	PWM0_ENABLE_R &= ~0x00000001; // Disable left wheel
}
	
void stop (void){
	LED = Dark;
	PWM0_ENABLE_R &= ~0x00000003; // stop both wheels
}
void backward_left(void){
	LED = Yellow;
	PWM0_ENABLE_R |= 0x00000002; // Enable right wheel
	PWM0_ENABLE_R &= ~0x00000001; // Disable left wheel
}

void backward_right(void){
	LED = Purple;
	PWM0_ENABLE_R &= ~0x00000002; // Enable right wheel
	PWM0_ENABLE_R |= 0x00000001; // Disable left wheel
}