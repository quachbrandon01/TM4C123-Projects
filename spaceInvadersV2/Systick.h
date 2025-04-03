// SysTick.h

 
#include <stdint.h>

// Time delay using busy wait.
void SysTick_Wait1us(uint8_t delay);
void SysTick_Start(void);
void SysTick_Stop(void);
uint32_t SysTick_Get_MC_Elapsed(void);
void SysTick40Hz(void);