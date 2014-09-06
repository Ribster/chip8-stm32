/*
 * main.c
 *
 *  Created on: 25.08.2014
 *      Author: sasha
 */

#include "main.h"

GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;
USART_ClockInitTypeDef USART_ClockInitStruct;
EXTI_InitTypeDef EXTI_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;

volatile uint32_t timer;
volatile unsigned int SysTickDelay;

char test[] = "test";
char *disp_string;
char update_lcd;


//Main menu
char select_b;
uint8_t press, current, quit;
volatile uint8_t btn_old_state[10];
volatile uint8_t btn_state[10];


void EnableExti(uint32_t line)
{
	EXTI_InitStructure.EXTI_Line = line;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);


	/*NVIC_InitStructure.NVIC_IRQChannel = irq;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);*/

}

void initButtons(void)
{
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);


	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//Button b1,b2,b3,b5,b6
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource3);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource4);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource6);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource7);
	//Button b4
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource2);

	//Button down, left, up
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource8);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource11);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource12);
	//button right
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource9);

	EnableExti(EXTI_Line2);
	EnableExti(EXTI_Line3);
	EnableExti(EXTI_Line4);
	EnableExti(EXTI_Line5);
	EnableExti(EXTI_Line6);
	EnableExti(EXTI_Line7);
	EnableExti(EXTI_Line8);
	EnableExti(EXTI_Line9);
	EnableExti(EXTI_Line11);
	EnableExti(EXTI_Line12);

	NVIC_EnableIRQ(EXTI2_IRQn);
	NVIC_EnableIRQ(EXTI3_IRQn);
	NVIC_EnableIRQ(EXTI4_IRQn);
	NVIC_EnableIRQ(EXTI9_5_IRQn);
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	//EnableIRQ(EXTI2_IRQn, EXTI_Line2);
}

void main(void)
{
	  SysTick_Config(SystemCoreClock /1000);

	  /* Включаем тактирование порта C */
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC |
			  	  	  	  	 RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOB |
			  	  	  	  	 RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);

	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 , ENABLE);


	  initButtons();


	  /* Init usart spi */
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_4;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;

	  GPIO_Init( GPIOA , &GPIO_InitStructure);

	  /*USART_Cmd(USART2, ENABLE);
	  USART_InitStructure.USART_BaudRate = 9600;
	  USART_InitStructure.USART_WordLength = USART_WordLength_9b;
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;
	  USART_InitStructure.USART_Parity = USART_Parity_No ;
	  USART_InitStructure.USART_Mode = USART_Mode_Tx;
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;*/
	  /* Configure USART2 */
	  //USART_Init(USART2, &USART_InitStructure);

	  //USART1->BRR = 0x0010;

	  /* Configure USART2 clock*/
	  /*USART_ClockStructInit(&USART_ClockInitStruct);
	  USART_ClockInitStruct.USART_Clock = USART_Clock_Enable;
	  USART_ClockInitStruct.USART_LastBit = USART_LastBit_Enable;
	  USART_ClockInit(USART2, &USART_ClockInitStruct);*/


	  /* Init lcd led control pin */
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	  GPIO_Init(GPIOC, &GPIO_InitStructure);


	  /* Init lcd controll CS signal */
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);


	  /* ON LED backlight */
	  GPIO_SetBits(GPIOC, GPIO_Pin_0);


	  uint8_t i;
	  for (i=0;i<10;i++) {
			btn_old_state[i] = btn_state[i] = 0;
	  }

	  press=1;
	  quit=0;
	  current=1;
	  select_b=0;


	  disp_string = test;
	  update_lcd = 1;

	  /*-----------------*/
	  	lcd_init();
	  	//lcd_segment_direction(1);
	  	lcd_column_direction(1);
	  	//lcd_flags.inverse_char = -1;
	  	lcd_image(0, 0, 8, 96, CHIP8);
	  	delay_ms(1000);
	  	//do __NOP(); while (1); // зависаем
	  	lcd_clr();
	    lcd_str_center(lcdRows()-1, "chip8 emulator");

	    //int cnt = 0;
	    //int i = 0;
	    //uint8_t okeys = 0xFF;

	for(;;) {
	    while(1)
	    {
	        //int n = cnt;
	        //uint8_t keys = (~GPIOB->IDR) & 0x1F;
	        //uint8_t keys = GPIOB->IDR & 0b11111111;


			if(!press) break;

			if(current!=select_b){
				lcd_clr();
				lcd_image(lcdRows()/2, lcdWidth()-15, 1, 4, menu_cursor);
				if(select_b!=0) {
					lcd_str(lcdRows()/2-1, 20, menu_table[select_b-1]);
				}
				lcd_str(lcdRows()/2, 20, menu_table[select_b]);
				if(select_b<MENU_LEN) {
					lcd_str(lcdRows()/2+1, 20, menu_table[select_b+1]);
				}

				current=select_b;

				//lcd_str(0, 0, disp_string);
			}

	    	if(update_lcd)
	    	{
	        //lcd_str(0, 0, disp_string);
	        update_lcd = 0;
	    	}

	    	//delay_ms(100);
			update_controll_button();

	  	    //disp_string = test;
	  	    //update_lcd = 1;

	        /*for(i=6; i>=0; i--)
	        {
	            //ledOn();
	            lcd_big_char(1, 2+i*13, (n % 10)+'0');
	            //ledOff();
	            n /= 10;

	            if(keys != okeys)
	            {
	                if(keys & (1<<i))
	                    lcd_big_char(4, 2+i*13, i+'0');
	                else
	                    lcd_big_char(4, 2+i*13, '0'+14);
	            }
	        }*/
	        //okeys = keys;
	        // lcd_start_line(cnt>>8);

	        //cnt++;
	        //if(cnt>9999999) cnt = 0;
	    }

		init8();
		loadApplication(prog_table[current],prog_size[current]);
		//loadApplication(MAZE,38);
		uint8_t x,y;
		while(1) {
			emulateCycle();
			delay_ms(5);
			if(drawFlag) {
				//lcd_clr();
				for(y = 18; y < 50; ++y)
				{
					for(x = 20; x < 84; ++x)
					{
						if(gfx[((y-18)*64) + (x-20)] == 0)
							lcd_pixel(100-x,y,PIXEL_OFF);
						else
							lcd_pixel(100-x,y,PIXEL_ON);
					}
				}
				/*for(y = 0; y < 32; y++)
				{
					for(x = 0; x < 64; x++)
					{
						if(gfx[(y*64) + x] == 0)
							lcd_pixel(x,y,PIXEL_OFF);
						else
							lcd_pixel(x,y,PIXEL_ON);
					}
				}*/
				drawFlag = false;
				lcd_update();
				//lcd_str(0, 0, disp_string);
			}
			update_game_button();

			if(quit)
			{
				press=1;
				quit = 0;
				current=1;
				select_b=0;
				break;
			}

		}

	}
/*-----------------*/
	  do __NOP(); while (1); // зависаем
}


void update_controll_button()
{
	if (btn_state[UP] && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8))
	{
		select_b--;
		//delay_ms(200);
		btn_state[UP] = 0;
	}
	if (btn_state[DOWN] && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12))
	{
		select_b++;
		//delay_ms(200);
		btn_state[DOWN] = 0;
	}
	if (btn_state[B4]&& GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2))
	{
		press=0;
		//delay_ms(200);
		btn_state[B4] = 0;
	}

	if (btn_state[B5]&& GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3))
	{
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0))
			GPIO_ResetBits(GPIOC, GPIO_Pin_0);
		else
			GPIO_SetBits(GPIOC, GPIO_Pin_0);
		//delay_ms(200);
		btn_state[B5] = 0;
	}
	//egg
	if (btn_state[B6]&& GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4))
	{
		lcd_image(0, 0, 8, 96, BAW);
		btn_state[B6] = 0;
	}

	if(select_b == 255) select_b=MENU_LEN;
	if(select_b > MENU_LEN) select_b=0;

}

void update_game_button() {
	byte i[5];
	i[0] = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8);
	i[1] = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12);
	i[3] = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_11);
	i[2] = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_9);
	i[4] = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2);

	if (btn_state[UP] && i[0])
	{
		key[0x4] =1;
		btn_state[UP] = 0;
	}
	else if (!btn_state[UP])
		key[0x4] =0;
	if (btn_state[DOWN] && i[1])
	{
		key[0xD] =1;
		btn_state[DOWN] = 0;
	}
	else if (!btn_state[DOWN])
		key[0xD] =0;
	if (btn_state[RIGHT] && i[2])
	{
		key[0x6] =1;
		btn_state[RIGHT] = 0;
	}
	else if (!btn_state[RIGHT])
		key[0x6] =0;
	if (btn_state[LEFT] && i[3])
	{
		key[0x5] =1;
		btn_state[LEFT] = 0;
	}
	else if (!btn_state[btn_state[LEFT]])
		key[0x5] =0;

	//quit
	if (btn_state[B4] && i[4])
	{
		quit =1;
		btn_state[B4] = 0;
	}
	else if (!btn_state[btn_state[B4]])
		quit =0;
}

void SysTick_Worker(void) {
	timer++;
	if (SysTickDelay != 0) {
		SysTickDelay--;
	}

}

void delay_ms(unsigned int nCount) {
	SysTickDelay = nCount;
	while (SysTickDelay != 0) {};
}
