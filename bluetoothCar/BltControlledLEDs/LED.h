

#define LED (*((volatile unsigned long *)0x40025038))  // use onboard three LEDs: PF321

#define Dark    	0x00
#define Red     	0x02
#define Blue    	0x04
#define Green   	0x08
#define Yellow  	0x0A
#define Cran      0x0C
#define White   	0x0E
#define Purple  	0x06

void LED_Init(void);