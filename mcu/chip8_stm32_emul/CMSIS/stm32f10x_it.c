/**
  ******************************************************************************
  * @file    EXTI/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    09/13/2010
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */



/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "../src/main.h"
/** @addtogroup Examples
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	SysTick_Worker();
}

/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/

/**
  * @brief  This function handles External line0 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI2_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line2) != RESET)
  {
    /* Toggle LED3 */
     //STM32vldiscovery_LEDToggle(LED3);
	  //disp_string = "PD2 B4    ";
	  btn_state[B4] ++;

    /* Clear the User Button EXTI line pending bit */
    EXTI_ClearITPendingBit(EXTI_Line2);
  }
  update_lcd = 1;
}

void EXTI3_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line3) != RESET)
  {
    /* Toggle LED3 */
     //STM32vldiscovery_LEDToggle(LED3);
	  disp_string = "PB3 B5    ";
	  btn_state[B5] ++;
    /* Clear the User Button EXTI line pending bit */
    EXTI_ClearITPendingBit(EXTI_Line3);
  }
  update_lcd = 1;
}

void EXTI4_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line4) != RESET)
  {
    /* Toggle LED3 */
     //STM32vldiscovery_LEDToggle(LED3);
	  disp_string = "PB4 B6    ";
	  btn_state[B6] ++;
    /* Clear the User Button EXTI line pending bit */
    EXTI_ClearITPendingBit(EXTI_Line4);
  }
  update_lcd = 1;
}

void EXTI9_5_IRQHandler(void)
{
	  if(EXTI_GetITStatus(EXTI_Line5) != RESET)
	  {
	    /* Toggle LED3 */
	     //STM32vldiscovery_LEDToggle(LED3);
		  disp_string = "PB5 B3    ";
		  btn_state[B3] ++;
	    /* Clear the User Button EXTI line pending bit */
	    EXTI_ClearITPendingBit(EXTI_Line5);
	  }
	  else if(EXTI_GetITStatus(EXTI_Line6) != RESET)
	  {
	    /* Toggle LED3 */
	     //STM32vldiscovery_LEDToggle(LED3);
		  disp_string = "PB6 B2    ";
		  btn_state[B2] ++;
	    /* Clear the User Button EXTI line pending bit */
	    EXTI_ClearITPendingBit(EXTI_Line6);
	  }
	  else if(EXTI_GetITStatus(EXTI_Line7) != RESET)
	  {
	    /* Toggle LED3 */
	     //STM32vldiscovery_LEDToggle(LED3);
		  disp_string = "PB7 B1    ";
		  btn_state[B1] ++;
	    /* Clear the User Button EXTI line pending bit */
	    EXTI_ClearITPendingBit(EXTI_Line7);
	  }
	  else if(EXTI_GetITStatus(EXTI_Line8) != RESET)
	  {
	    /* Toggle LED3 */
	     //STM32vldiscovery_LEDToggle(LED3);
		  disp_string = "PA8 UP    ";
		  btn_state[UP] ++;
	    /* Clear the User Button EXTI line pending bit */
	    EXTI_ClearITPendingBit(EXTI_Line8);
	  }
	  else if(EXTI_GetITStatus(EXTI_Line9) != RESET)
	  {
	    /* Toggle LED3 */
	     //STM32vldiscovery_LEDToggle(LED3);
		  disp_string = "PC9 RIGHT";
		  btn_state[RIGHT] ++;
	    /* Clear the User Button EXTI line pending bit */
	    EXTI_ClearITPendingBit(EXTI_Line9);
	  }
	  update_lcd = 1;
}

void EXTI15_10_IRQHandler(void)
{
	  if(EXTI_GetITStatus(EXTI_Line12) != RESET)
	  {
	    /* Toggle LED3 */
	     //STM32vldiscovery_LEDToggle(LED3);
		  disp_string = "PC12 DOWN";
		  btn_state[DOWN] ++;
	    /* Clear the User Button EXTI line pending bit */
	    EXTI_ClearITPendingBit(EXTI_Line12);
	  }
	  else if(EXTI_GetITStatus(EXTI_Line11) != RESET)
	  {
	    /* Toggle LED3 */
	     //STM32vldiscovery_LEDToggle(LED3);
		  disp_string = "PC11 LEFT";
		  btn_state[LEFT] ++;
	    /* Clear the User Button EXTI line pending bit */
	    EXTI_ClearITPendingBit(EXTI_Line11);
	  }
	  update_lcd = 1;
}
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
