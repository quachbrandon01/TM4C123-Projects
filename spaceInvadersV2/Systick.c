// SysTick.c
// Runs on TM4C123
// By Dr. Min He
// December 10th, 2018

#include <stdint.h>
#include "SysTick.h"
#include "tm4c123gh6pm.h"
#define period_40Hz 						7999999

void SysTick40Hz(void)
{
    // 1. Clear ENABLE to stop counter
    NVIC_ST_CTRL_R &= ~NVIC_ST_CTRL_ENABLE; 
    // 2. Update Reload Value
    NVIC_ST_RELOAD_R = period_40Hz; 
    // 3. Clear the counter via CURRENT register
    NVIC_ST_CURRENT_R = 0; // writing anything will clear
    // 4. Set interrupt priority
    NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF) | 0x20000000; // priority 1
    // 5. Set CLK_SRC = 1 to use system clock
    // specify interrupt action via INTEN
    // start timer
    NVIC_ST_CTRL_R |= (NVIC_ST_CTRL_CLK_SRC + NVIC_ST_CTRL_INTEN + NVIC_ST_CTRL_ENABLE); 
} 