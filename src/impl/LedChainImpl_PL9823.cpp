/*
 * LedChainImpl_PL9823.cpp
 *
 *  Created on: 16.03.2016
 *      Author: awurf
 */

#include "../EnlightenLedChain.h"
#include "LedChainImpl_PL9823.h"

LedChainImpl_PL9823::LedChainImpl_PL9823( EnlightenLedChain* ledChain )
: LedChainImpl( ledChain )
{ }

void LedChainImpl_PL9823::FlingCurrentBuffer() {
	const auto ledChain = this->LedChain();
	const auto bufferSize = 3 * ledChain->NumLeds();
	const auto bufferStart = ledChain->Bytes() + ( ledChain->CurrentBuffer() * bufferSize );
	const auto bufferSentinel = bufferStart + bufferSize;

	uint8_t sreg;
	asm volatile(
		"in		%[sreg], __SREG__		\n\t"	//	1
		"cli							\n\t"	//	1
		// TODO: Continue
		"out	__SREG__, %[sreg]		\n\t"	//	1
		:	// output operands
		[sreg]				"=&r"	(sreg)
		:	// input operands
		[bufferStart]		"e"		(bufferStart),
		[bufferSentinel]	"e"		(bufferSentinel)
		:	// clobber
		"cc"
	);
}
