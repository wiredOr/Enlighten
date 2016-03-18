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

void LedChainImpl_WS2812B::flingCurrentBuffer() const {
	// TODO: Implement
}

uint8_t LedChainImpl_WS2812B::r( unsigned led ) const {
	// TODO: Implement
	(void)led;
	return( 0 );
}

uint8_t LedChainImpl_WS2812B::g( unsigned led ) const {
	// TODO: Implement
	(void)led;
	return( 0 );
}

uint8_t LedChainImpl_WS2812B::b( unsigned led ) const {
	// TODO: Implement
	(void)led;
	return( 0 );
}

uint32_t LedChainImpl_WS2812B::rgb( unsigned led ) const {
	// TODO: Implement
	(void)led;
	return( 0 );
}

void LedChainImpl_WS2812B::setR( unsigned led, uint8_t value ) {
	(void)led;
	(void)value;
	// TODO: Implement
}

void LedChainImpl_WS2812B::setG( unsigned led, uint8_t value ) {
	(void)led;
	(void)value;
	// TODO: Implement
}

void LedChainImpl_WS2812B::setB( unsigned led, uint8_t value ) {
	(void)led;
	(void)value;
	// TODO: Implement
}

void LedChainImpl_WS2812B::setRGB( unsigned led, uint32_t value ) {
	(void)led;
	(void)value;
	// TODO: Implement
}
