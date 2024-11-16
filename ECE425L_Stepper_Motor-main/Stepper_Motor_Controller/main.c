/*
 * @file main.c
 *
 * @brief Main source code for the Stepper_Motor_Controller program.
 *
 * This file contains the main entry point and function definitions for the Stepper_Motor_Controller program.
 * This lab demonstrates how to control a stepper motor using GPIO.
 *
 * The following components are used:
 *	- PMOD BTN module
 *	-	28BYJ-48 5V Stepper Motor
 *  - ULN2003 Stepper Motor Driver
 *  - 3.3V / 5V Breadboard Power Supply Module (External Power Source)
 *
 * It configures the pins used by the PMOD BTN module to generate interrupts on rising edges.
 * The PMOD BTN module will be used to control the rotation of the stepper motor.
 *
 * @Katherine Poz
 */

#include "TM4C123GH6PM.h"

#include "SysTick_Delay.h"
#include "Stepper_Motor.h"
#include "PMOD_BTN_Interrupt.h"

//Declare the user-defined function prototype for PMOD_BTN_Interrupt
void PMOD_BTN_Handler(uint8_t pmod_btn_status);

static uint8_t enable = 0;
static uint8_t direction_select = 0;

int main(void)
{
	//Initialize the SysTick timer used to provide blocking delay functions
	SysTick_Delay_Init();
	
	//Initialize the pins used by the 28BYJ-48 Stepper Motor and the ULN2003 Stepper Motor Driver
	Stepper_Motor_Init();
	
	//Initialize the push buttons on the PMOD BTN module (Port A)
	PMOD_BTN_Interrupt_Init(&PMOD_BTN_Handler);
	
	int step_index = 0;
	const uint8_t half_step[] = {0x01, 0x03, 0x02, 0x06, 0x0C, 0x08, 0x09};
	
	while(1)
	{
		if (enable)
		{
			if (direction_select)
			{
				Stepper_Motor_Init(step_index);
				
			}
			else
			{
				Stepper_Motor_Init(step_index);
			}
		}
	}
}

/**
* @brief This function will be able to control the stepper motor's rotation using PMOD BTN module
*				 By implementing the switch loop which will allow each button to operate differently when pressed
*
* @param uint8_t pmod_btn_status Indicates the status of the buttons on the PMOD BTN module
*
* @return None
*/
void PMOD_BTN_Handler(uint8_t pmod_btn_status)
{
	switch(pmod_btn_status)
	{
		//PMOD BTN0 (PA2) is pressed
		case 0x04:
		{
			enable = 1;
			
			break;
		}
		
		//PMOD BTN1 (PA3) is pressed
		case 0x08:
		{
			enable = 0;
			
			break;
		}
		
		//PMOD BTN2 (PA4) is pressed
		case 0x10:
		{
			direction_select ^= 1;
			
			break;
		}
		
		//PMOD BTN3 (PA5) is pressed
		case 0x20:
		{
			
			break;
		}
		
		default:
		{
			
			break;
		}
	}
}