/*
 * main.h
 *
 *  Created on: 26.08.2014
 *      Author: sasha
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stm32f10x_conf.h>

#include <inttypes.h>
#include "lcd1202/utils.h"

#include "lcd1202/lcd1202.h"
#include "chip8/chip8.h"

#include "emu_data.h"


#define MENU_LEN   22

#define ledOn() GPIOC->BRR = GPIO_Pin_0
#define ledOff() GPIOC->BSRR = GPIO_Pin_0

enum Button
{
	UP = 0,
	RIGHT,
	DOWN,
	LEFT,
	B1,
	B2,
	B3,
	B4,
	B5,
	B6
};

///
char select_b;
extern uint8_t press;
extern volatile uint8_t btn_old_state[10];
extern volatile uint8_t btn_state[10];

extern char *disp_string;
extern char update_lcd;

void SysTick_Worker(void);

#endif /* MAIM_H_ */
