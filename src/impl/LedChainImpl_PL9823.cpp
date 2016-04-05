/*
 * LedChainImpl_PL9823.cpp
 *
 *  Created on: 16.03.2016
 *      Author: awurf
 */

#include "LedChainImpl_PL9823.h"

#define	OFFSET_R	0
#define	OFFSET_G	1
#define	OFFSET_B	2

LedChainImpl_PL9823::LedChainImpl_PL9823( EnlightenLedChain* ledChain )
: LedChainImpl( ledChain )
{ }

void LedChainImpl_PL9823::flingCurrentBuffer() const {
	//
	//	fCPU = 16e6 [Hz] (Arduino Micro)
	//	fPWM_MAX = 714e3 [Hz]
	//	=> nCYC_MIN = 23 [cycles]
	//	rONE = 4:1 (H:L)
	//	rZERO = 1:4 (H:L)
	//
	//	=> nCYC = 25 (5 * 5)
	//	=> fPWM = 640 [KHz]
	//
	const auto ledChain = this->ledChain();
	const auto bufferSize = static_cast<uint16_t>( 3 * ledChain->numLeds() );
	__attribute__((unused)) const auto bufferStart = ledChain->currentBufferBytes();
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

		// One case: H:L = 4:1
		// PB5 has been HIGH now for 3 cycles
		"L_bitIsOne:							\n\t"
		"nop									\n\t"	//	1
		"nop									\n\t"	//	1
		"nop									\n\t"	//	1
		"nop									\n\t"	//	1
		"nop									\n\t"	//	1
		"nop									\n\t"	//	1
		"nop									\n\t"	//	1
		"nop									\n\t"	//	1
		"nop									\n\t"	//	1
		"nop									\n\t"	//	1
		"nop									\n\t"	//	1
		"nop									\n\t"	//	1
		"nop									\n\t"	//	1
		"nop									\n\t"	//	1
		"nop									\n\t"	//	1
		"nop									\n\t"	//	1
		"cbi		%[port], 5					\n\t"	//	2		(LOW)
		"rjmp		L_shiftMask					\n\t"	//	2

		// Zero case: H:L = 1:4
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
		"nop									\n\t"	//	1
		"nop									\n\t"	//	1
		"nop									\n\t"	//	1
		"nop									\n\t"	//	1
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

uint8_t LedChainImpl_PL9823::r( unsigned led ) const {
	const auto ledChain = this->ledChain();
	const auto pixel = ledChain->currentBufferBytes() + 3 * led;

	return( *(pixel + OFFSET_R) );
}

uint8_t LedChainImpl_PL9823::g( unsigned led ) const {
	const auto ledChain = this->ledChain();
	const auto pixel = ledChain->currentBufferBytes() + 3 * led;

	return( *(pixel + OFFSET_G) );
}

uint8_t LedChainImpl_PL9823::b( unsigned led ) const {
	const auto ledChain = this->ledChain();
	const auto pixel = ledChain->currentBufferBytes() + 3 * led;

	return( *(pixel + OFFSET_B) );
}

uint32_t LedChainImpl_PL9823::rgb( unsigned led ) const {
	const auto ledChain = this->ledChain();
	const auto pixel = ledChain->currentBufferBytes() + 3 * led;

	return( ENLIGHTEN_RGB( *(pixel + OFFSET_R), *(pixel + OFFSET_G), *(pixel + OFFSET_B) ) );
}

void LedChainImpl_PL9823::setR( unsigned led, uint8_t value ) {
	const auto ledChain = this->ledChain();

	*( ( ledChain->currentBufferBytes() + 3 * led ) + OFFSET_R ) = value;
}

void LedChainImpl_PL9823::setG( unsigned led, uint8_t value ) {
	const auto ledChain = this->ledChain();

	*( ( ledChain->currentBufferBytes() + 3 * led ) + OFFSET_G ) = value;
}

void LedChainImpl_PL9823::setB( unsigned led, uint8_t value ) {
	const auto ledChain = this->ledChain();

	*( ( ledChain->currentBufferBytes() + 3 * led ) + OFFSET_B ) = value;
}

void LedChainImpl_PL9823::setRGB( unsigned led, uint32_t value ) {
	const auto ledChain = this->ledChain();

	auto pixel = ledChain->currentBufferBytes() + 3 * led;
	*(pixel + OFFSET_R) = ENLIGHTEN_R( value );
	*(pixel + OFFSET_G) = ENLIGHTEN_G( value );
	*(pixel + OFFSET_B) = ENLIGHTEN_B( value );
}
