/*
 * Nokia 1202/1203/1280 LCD display driver
 * MCU depend part
 *
 * (CC) 2011 Ivan A-R <ivan@tuxotronic.org>
 *
 * This driver use USART (9-bit) mode write to display.
 * Thanx for idea
 *     http://we.easyelectronics.ru/OlegG/ispolzovanie-usart-stm32-dlya-upravleniya-lcd-nokia-1202.html
 */

#ifndef _LCD1202_HW_H_
#define _LCD1202_HW_H_

#ifndef _LCD1202_C_
#error Must be included only from lcd1202.c
#endif

/*
void lcd_init_gpio(void);
void lcd_reset(void);
void lcd_write_byte(uint8_t data, uint8_t rc);
*/
#include <stm32f10x_gpio.h>



/* MCU Hardware depend functions */
/* STM32 USART 1 */

#define lcd_rst_mark()
#define lcd_rst_release()

#define lcd_cs_mark()    GPIOA->BRR  = GPIO_Pin_1
#define lcd_cs_release() do { \
        while ( (USART2->SR & USART_SR_TC) == 0) ; /* Wait while transfer */ \
        GPIOA->BSRR = GPIO_Pin_1; \
    } while(0)


#define lcd_delay_us(ms) do { uint32_t d = (ms)*11; while(--d) asm volatile(""); } while(0)

static void lcd_init_gpio(void)
{
    /* Init pins before call init */
#ifdef USE_MCU_USART
    USART1->BRR = 0x0010; /* MAX speed */
    USART1->CR2 =
        USART_CR2_CLKEN |     // Enable SCLK
        // USART_CR2_STOP_0 | // 1 stop bit (don't use 0.5 stopbit!!!)
        // USART_CR2_CPOL |   // Normal polarity
        // USART_CR2_CPHA |   // Normal phase
        USART_CR2_LBCL;       //clock fpr last bit
    USART1->CR1 = USART_CR1_OVER8 |
        USART_CR1_M |       // 9-bit
        USART_CR1_TE | USART_CR1_UE;
#else
    GPIOA->BRR = (1<<4);
#endif
}

static void lcd_reset(void)
{
    /*
    lcd_rst_mark();
    lcd_delay_us(10);
    lcd_rst_release();
    lcd_delay_us(10);
    */
}

static void lcd_write_byte(uint8_t data, uint8_t rc)
{
#ifdef USE_MCU_USART
    uint16_t d = data;
    if (rc) /* If data */
        d |= 0x100;

    d = __RBIT(d) >> 23;
    while ( (USART2->SR & USART_SR_TXE) == 0 ) /* Transmitter registar is not empty */
        ; /* BLANK */

    USART1->DR = d;

#else
    if(rc)
        GPIOA->BSRR = (1<<2);
    else
        GPIOA->BRR = (1<<2);

    GPIOA->BSRR = (1<<4);
    GPIOA->BRR = (1<<4);

    int i;
    for(i=0; i<8; i++)
    {
        if(data & 0x80)
            GPIOA->BSRR = (1<<2);
        else
            GPIOA->BRR = (1<<2);
        GPIOA->BSRR = (1<<4);
        GPIOA->BRR = (1<<4);
        data <<= 1;
    }
#endif
}

#endif /* _LCD1202_HW_H_ */

