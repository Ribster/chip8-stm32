/*
 * chip8.c
 *
 *  Created on: 21.08.2012
 *      Author: sasha
 */
#include "chip8.h"
#include "string.h"

struct chip8_cpu_struct chip8_cpu;
byte  memory[CHIP8_RAM];
byte  gfx[64 * 32];
byte  key[16];
bool running;
bool drawFlag;
bool beep;

unsigned long m_w = 1;
unsigned long m_z = 2;

#define read_mem(a)     (memory[(a)&(CHIP8_RAM-1)])
#define write_mem(a,v)  (memory[(a)&(CHIP8_RAM-1)]=(v))

#define get_reg_offset(opcode)          (chip8_cpu.V+(opcode>>8))
#define get_reg_value(opcode)           (*get_reg_offset(opcode))
#define get_reg_offset_2(opcode)        (chip8_cpu.V+((opcode>>4)&0x0f))
#define get_reg_value_2(opcode)         (*get_reg_offset_2(opcode))

typedef void (*opcode_fn) (word opcode);
typedef void (*math_fn) (byte *reg1,byte reg2);

unsigned long xor128(void) {
  static unsigned long x = 123456789;
  static unsigned long y = 362436069;
  static unsigned long z = 521288629;
  static unsigned long w = 88675123;
  unsigned int t;

  t = x ^ (x << 11);
  x = y; y = z; z = w;
  return w = w ^ (w >> 19) ^ (t ^ (t >> 8));
}

static void op_system (word opcode) {
	switch ((byte)opcode) {
	case 0xe0:
	{
		word i;
		for(i = 0; i < 2048; ++i)
			gfx[i] = 0;
		drawFlag =true;
	} break;
	case 0xee:
	{
		--chip8_cpu.sp;
		chip8_cpu.pc = chip8_cpu.stack[chip8_cpu.sp];

	} break;
  }
}
static void op_jmp (word opcode) {
	chip8_cpu.pc = opcode;
}
static void op_call (word opcode) {
	chip8_cpu.stack[chip8_cpu.sp] = chip8_cpu.pc;
	chip8_cpu.sp+=1;
	chip8_cpu.pc = opcode & 0x0FFF;
}
static void op_skeq_const (word opcode) {
	if (get_reg_value(opcode)==(opcode&0xff)) chip8_cpu.pc+=2;
}
static void op_skne_const (word opcode) {
	if (get_reg_value(opcode)!=(opcode&0xff)) chip8_cpu.pc+=2;
}
static void op_skeq_reg (word opcode) {
	if (get_reg_value(opcode)==get_reg_value_2(opcode)) chip8_cpu.pc+=2;
}
static void op_mov_const (word opcode) {
	*get_reg_offset(opcode)=opcode&0xff;
}
static void op_add_const (word opcode) {
	*get_reg_offset(opcode)+=opcode&0xff;
}

static void op_skne_reg (word opcode) {
	if (get_reg_value(opcode)!=get_reg_value_2(opcode)) chip8_cpu.pc+=2;
}
static void op_mvi (word opcode) {
	chip8_cpu.i=opcode;
}
static void op_jmi (word opcode) {
	chip8_cpu.pc=opcode+chip8_cpu.V[0];
}
static void op_rand (word opcode) {
	*get_reg_offset(opcode)= xor128()&(opcode&0xff);
}
static void op_sprite (word opcode) {
	/*word x,y,height,pixel;

	chip8_cpu.V[0xF]=0;*/
	 byte *q;
	 byte n,x,x2,y,collision;
	 word p;
	 x=get_reg_value(opcode)&63;
	 y=get_reg_value_2(opcode)&31;
	 p=chip8_cpu.i;
	 q=gfx+y*64;
	 n=opcode&0x0f;
	 if (n+y>32) n=32-y;
	 for (collision=1;n;--n,q+=64)
	 {
	  for (y=read_mem(p++),x2=x;y;y<<=1,x2=(x2+1)&63)
	   if (y&0x80) collision&=(q[x2]^=0xff);
	 }
	 chip8_cpu.V[15]=collision^1;
	 drawFlag = true;
	/*word x = get_reg_value(opcode);
	word y = get_reg_value_2(opcode);
	word height = opcode & 0x000F;
	word pixel;
	byte xline, yline;
	chip8_cpu.V[0xF] = 0;
	for (yline = 0; yline < height; yline++)
	{
		pixel = memory[chip8_cpu.i + yline];
		for(xline = 0; xline < 8; xline++)
		{
			if((pixel & (0x80 >> xline)) != 0)
			{
				if(gfx[(x + xline + ((y + yline) * 64))] == 1)
				{
					chip8_cpu.V[0xF] = 1;
				}
				gfx[x + xline + ((y + yline) * 64)] ^= 1;
			}
		}
	}

	drawFlag = true;*/

}
static void op_key (word opcode) {
	switch(opcode & 0x00FF) {
	case 0x009E:
		if(key[get_reg_value(opcode)] !=0) chip8_cpu.pc +=2;
	break;

	case 0x00A1:
		if(key[get_reg_value(opcode)] ==0) chip8_cpu.pc +=2;
	}

}
static void op_misc (word opcode)
{
 byte *reg,i,j;
 reg=get_reg_offset(opcode);
 switch ((byte)opcode)
 {
  case 0x07:
   *reg=chip8_cpu.delay;
   break;
  case 0x0a:
  	  {
	  bool chip8_key_pressed =false;
	  for(i = 0; i < 16; ++i) {
			if(key[i] != 0)
			{
				*reg = i;
				chip8_key_pressed = true;
			}
	  }
	  if (!chip8_key_pressed)
		  chip8_cpu.pc-=2;
  	  }
  break;
  case 0x15:
   chip8_cpu.delay=*reg;
   break;
  case 0x18:
  {
   chip8_cpu.sound=*reg;
   //if (chip8_cpu.sound) chip8_sound_on();
  }
   break;
  case 0x1e:
	  chip8_cpu.i+=(*reg);
   break;
  case 0x29:
   chip8_cpu.i=((word)(*reg&0x0f))*5;
   break;
  case 0x33:
   i=*reg;
   for (j=0;i>=100;i-=100) j++;
   write_mem (chip8_cpu.i,j);
   for (j=0;i>=10;i-=10) j++;
   write_mem (chip8_cpu.i+1,j);
   write_mem (chip8_cpu.i+2,i);
   break;
  case 0x55:
  {
   for (i=0,j=(opcode>>8)&0x0f;i<=j;++i)
    write_mem(chip8_cpu.i+i,chip8_cpu.V[i]);
   chip8_cpu.i += ((opcode>>8)&0x0f)+1; // ?
  }
   break;
  case 0x65:
  {
   for (i=0,j=(opcode>>8)&0x0f;i<=j;++i)
    chip8_cpu.V[i]=read_mem(chip8_cpu.i+i);
   chip8_cpu.i += ((opcode>>8)&0x0f)+1; //?
  }
   break;
 }
}

//Math function

static void math_mov (byte *reg1,byte reg2) {
	*reg1=reg2;

}
static void math_or (byte *reg1,byte reg2) {
	*reg1|=reg2;

}
static void math_and (byte *reg1,byte reg2) {
	*reg1&=reg2;

}
static void math_xor (byte *reg1,byte reg2) {
	*reg1^=reg2;

}
static void math_add (byte *reg1,byte reg2) {
	word tmp;
	tmp=*reg1+reg2;
	*reg1=(byte)tmp;
	chip8_cpu.V[15]=tmp>>8;

}
static void math_sub (byte *reg1,byte reg2) {
	word tmp;
	tmp=*reg1-reg2;
	*reg1=(byte)tmp;
	chip8_cpu.V[15]=((byte)(tmp>>8))+1;

}
static void math_shr (byte *reg1,byte reg2) {
	chip8_cpu.V[15]=*reg1&1;
	*reg1>>=1;
}
static void math_rsb (byte *reg1,byte reg2) {
	word tmp;
	tmp=reg2-*reg1;
	*reg1=(byte)tmp;
	chip8_cpu.V[15]=((byte)(tmp>>8))+1;
}
static void math_nop (byte *reg1,byte reg2) {

}
static void math_shl (byte *reg1,byte reg2) {
	chip8_cpu.V[15]=*reg1>>7;
	*reg1<<=1;
}


void init8() {
	word i = 0;

	// Program counter starts at 0x200 (Start adress program)
	chip8_cpu.pc = 0x200;
	chip8_cpu.sp = 0;
	chip8_cpu.i = 0;
	chip8_cpu.delay = 0;
	chip8_cpu.sound =0;

	//Clear display
	for(i = 0; i < 2048; ++i)
		gfx[i] = 0;

	//Clear registers
	for(i = 0; i < 16; ++i)
		chip8_cpu.V[i] = 0;

	//Clear stack
	for(i = 0; i < 16; ++i)
		chip8_cpu.stack[i] = 0;

	//Clear memory
	for(i = 0; i < CHIP8_RAM; ++i)
		memory[i] = 0;

	//Clear status of key
	for(i = 0; i < 16; ++i)
		key[i] = 0;

	// Write font to memory
	for(i = 0; i < 80; ++i)
		write_mem(i,chip8_fontset[i]);

	running=1;
	drawFlag = true;

	//while (running) emulateCycle();

}

static math_fn math_opcodes[16]=
{
 math_mov,
 math_or,
 math_and,
 math_xor,
 math_add,
 math_sub,
 math_shr,
 math_rsb,
 math_nop,
 math_nop,
 math_nop,
 math_nop,
 math_nop,
 math_nop,
 math_shl,
 math_nop
};


static void op_math (word opcode)
{
 (*(math_opcodes[opcode&0x0f]))
        (get_reg_offset(opcode),get_reg_value_2(opcode));
}

static opcode_fn main_opcodes[16]=
{
		 op_system,
		 op_jmp,
		 op_call,
		 op_skeq_const,
		 op_skne_const,
		 op_skeq_reg,
		 op_mov_const,
		 op_add_const,
		 op_math,
		 op_skne_reg,
		 op_mvi,
		 op_jmi,
		 op_rand,
		 op_sprite,
		 op_key,
		 op_misc
};


void emulateCycle() {
	word opcode;
	byte i;
	for (i=30;i;--i) {
	opcode=(read_mem(chip8_cpu.pc)<<8)+read_mem(chip8_cpu.pc+1);
	chip8_cpu.pc+=2;
	(*(main_opcodes[opcode>>12]))(opcode&0x0fff);

	}
	if(chip8_cpu.delay > 0)
		--chip8_cpu.delay;

	if(chip8_cpu.sound > 0)
	{
		if(chip8_cpu.sound == 1)
			beep = true;

		--chip8_cpu.sound;
	}
}



void loadApplication(const byte *programData, word len) {
	//byte i;
	//FLASH_Unlock();
	memcpy(memory+512, programData, len);
/*	word i;

	for (i=0; i<len; ++i, ++programData) {
		write_mem(512+i,pgm_read_byte( programData ));

	}*/
	/*for ( c = pgm_read_byte( programData ), i=0; c; ++programData, c = pgm_read_byte( programData ), ++i) {
		write_mem(512+i,c);

	}*/


}
