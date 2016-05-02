/*
 * EnlightenLedChain_WS2812B.cpp
 *
 *  Created on: 16.03.2016
 *      Author: awurf
 */

#include "EnlightenLedChain_WS2812B.h"

void EnlightenLedChain_WS2812B::flingCurrentBuffer() const {
	//
	//	fCPU = 16e6 [Hz] (Arduino Micro)
	//	tH + tL = 1.25 [us] +/- 600 [ns] // see WS2812B datasheet
	//	fPWM_MAX = 1 / ( 1.25 [us] - 600 [ns] ) = 1 / 650 [ns] = 1.538 [Mhz]
	//	=> nCYC_MIN = 11 [cycles]
	//	rONE = 2:1 (H:L)
	//	rZERO = 1:2 (H:L)
	//
	//	=> nCYC = 15 (3 * 5) (chosen)
	//	=> fPWM = 1.067 [MHz]
	//
	const auto bufferSize = static_cast<uint16_t>( 3 * this->numLeds() );
	__attribute__((unused)) const auto bufferStart = this->currentBufferBytes();
	__attribute__((unused)) uint8_t sreg, mask, byte;

	asm volatile(
		"in			%[sreg], __SREG__			\n\t"	//	1
		"cli									\n\t"	//	1

		// Outer loop:
		"L_nextByte:							\n\t"
		"ld			%[byte], %a[buffer]+		\n\t"	//	2
		"ldi		%[mask], 0x80				\n\t"	//	1

		// Inner loop:
		"L_nextBit:								\n\t"
		"sbi		%[port], 5					\n\t"	//	2		(HIGH)
		"mov		__tmp_reg__, %[byte]		\n\t"	//	1
		"and		__tmp_reg__, %[mask]		\n\t"	//	1
		"breq		L_bitIsZero					\n\t"	//	1 / 2

		// One case: H:L = 2:1 = 10 [cycles] : 5 [cycles]
		// PB5 has been HIGH now for 3 cycles
		"L_bitIsOne:							\n\t"
		"nop									\n\t"	//	1
		"nop									\n\t"	//	1
		"nop									\n\t"	//	1
		"nop									\n\t"	//	1
		"nop									\n\t"	//	1
		"nop									\n\t"	//	1
		"cbi		%[port], 5					\n\t"	//	2		(LOW)
		"rjmp		L_shiftMask					\n\t"	//	2

		// Zero case: H:L = 1:2 = 5 [cycles] : 10 [cycles]
		// PB5 has been HIGH now for 5 cycles 
		// (including one cycle from cbi instruction below)
		"L_bitIsZero:							\n\t"
		"cbi		%[port], 5					\n\t"	//	2		(LOW)
		"nop									\n\t"	//	1
		"nop									\n\t"	//	1
		"nop									\n\t"	//	1
		"nop									\n\t"	//	1
		"nop									\n\t"	//	1
		"nop									\n\t"	//	1

		"L_shiftMask:							\n\t"
		"lsr		%[mask]						\n\t"	//	1
		"brcc		L_nextBit					\n\t"	//	1 / 2
		"sbiw		%[size], 1					\n\t"	//	2
		"brne		L_nextByte					\n\t"	//	1 / 2

		// Finish, keep LOW for at least 50 microseconds

		"ldi		%[byte], 0xc8				\n\t"	//	1
		"L_wait:								\n\t"
		"nop									\n\t"	//	1
		"dec		%[byte]						\n\t"	//	1
		"brne		L_wait						\n\t"	//	1 / 2

		"out		__SREG__, %[sreg]			\n\t"	//	1
		:	// output operands
		[sreg]		"=&r"	(sreg),
		[mask]		"=&d"	(mask),
		[byte]		"=&d"	(byte)
		:	// input operands
		[port]		"I"		(_SFR_IO_ADDR(PORTB)),
		[buffer]	"e"		(bufferStart),
		[size]		"w"		(bufferSize)
		:	// clobber
		"cc"
	);
}
