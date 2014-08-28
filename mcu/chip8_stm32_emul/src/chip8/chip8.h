/*
 * chip8.h
 *
 *  Created on: 21.08.2012
 *      Author: sasha
 */

#ifndef CHIP8_H_
#define CHIP8_H_

#define CHIP8_RAM   4096
#define Rand32() (SysTick->VAL &0xF)

#include <stdbool.h>
//#include <stdlib.h>

//#include "main.h"

typedef unsigned char byte;
typedef unsigned short word;
//#define Rand32() rand()

// Chip8
struct chip8_cpu_struct
{
 byte V[16];        		// V-regs (V0-VF)
 word stack[16];			// stack (16 levels)
 byte delay,sound;          //delay and sound timer
 word i;                    //index register
 word pc;                   //program counter
 word sp;                   //stack pointer
};

extern struct chip8_cpu_struct chip8_cpu;

extern byte  gfx[64 * 32];	// Total amount of pixels: 2048
extern byte  key[16];
extern byte  memory[CHIP8_RAM];	// Memory (size = 4k)

extern bool running;

extern bool drawFlag;

extern bool beep;

void init8();
void emulateCycle();
void loadApplication(const byte *programData, word len);

static const byte chip8_fontset[80] =
{
    0xF0, 0x90, 0x90, 0x90, 0xF0, //0
    0x20, 0x60, 0x20, 0x20, 0x70, //1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, //2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, //3
    0x90, 0x90, 0xF0, 0x10, 0x10, //4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, //5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, //6
    0xF0, 0x10, 0x20, 0x40, 0x40, //7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, //8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, //9
    0xF0, 0x90, 0xF0, 0x90, 0x90, //A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, //B
    0xF0, 0x80, 0x80, 0x80, 0xF0, //C
    0xE0, 0x90, 0x90, 0x90, 0xE0, //D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, //E
    0xF0, 0x80, 0xF0, 0x80, 0x80  //F
};

#endif /* CHIP8_H_ */
