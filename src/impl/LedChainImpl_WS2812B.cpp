/*
 * LedChainImpl_WS2812B.cpp
 *
 *  Created on: 16.03.2016
 *      Author: awurf
 */

#include "../EnlightenLedChain.h"
#include "LedChainImpl_WS2812B.h"

LedChainImpl_WS2812B::LedChainImpl_WS2812B( EnlightenLedChain* ledChain )
: LedChainImpl( ledChain )
{ }

void LedChainImpl_WS2812B::FlingCurrentBuffer() const {
	// TODO: Implement
}

uint8_t LedChainImpl_WS2812B::R( unsigned led ) const {
	// TODO: Implement
	(void)led;
	return( 0 );
}

uint8_t LedChainImpl_WS2812B::G( unsigned led ) const {
	// TODO: Implement
	(void)led;
	return( 0 );
}

uint8_t LedChainImpl_WS2812B::B( unsigned led ) const {
	// TODO: Implement
	(void)led;
	return( 0 );
}

uint32_t LedChainImpl_WS2812B::RGB( unsigned led ) const {
	// TODO: Implement
	(void)led;
	return( 0 );
}

void LedChainImpl_WS2812B::SetR( unsigned led, uint8_t value ) {
	(void)led;
	(void)value;
	// TODO: Implement
}

void LedChainImpl_WS2812B::SetG( unsigned led, uint8_t value ) {
	(void)led;
	(void)value;
	// TODO: Implement
}

void LedChainImpl_WS2812B::SetB( unsigned led, uint8_t value ) {
	(void)led;
	(void)value;
	// TODO: Implement
}

void LedChainImpl_WS2812B::SetRGB( unsigned led, uint32_t value ) {
	(void)led;
	(void)value;
	// TODO: Implement
}
