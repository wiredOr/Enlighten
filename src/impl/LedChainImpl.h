/*
 * LedChainImpl.h
 *
 *  Created on: 16.03.2016
 *      Author: awurf
 */

#ifndef LEDCHAINIMPL_H_
#define LEDCHAINIMPL_H_

#include <Arduino.h>

#include "LedChainImplBase.h"
#include "../EnlightenLedChain.h"

#define PIN_DATA	9	// 0 = LOW, 1 = HIGH

template< unsigned T_OffsetR, unsigned T_OffsetG, unsigned T_OffsetB >
class LedChainImpl : public LedChainImplBase {

public:

	LedChainImpl( EnlightenLedChain* ledChain ) 
	: LedChainImplBase( ledChain ) 
	{ }

	uint8_t r( unsigned led ) const override {
		const auto ledChain = this->ledChain();
		const auto pixel = ledChain->currentBufferBytes() + 3 * led;

		return( *(pixel + T_OffsetR) );
	}

	uint8_t g( unsigned led ) const override {
		const auto ledChain = this->ledChain();
		const auto pixel = ledChain->currentBufferBytes() + 3 * led;

		return( *(pixel + T_OffsetG) );
	}

	uint8_t b( unsigned led ) const override {
		const auto ledChain = this->ledChain();
		const auto pixel = ledChain->currentBufferBytes() + 3 * led;

		return( *(pixel + T_OffsetB) );
	}

	uint32_t rgb( unsigned led ) const override {
		const auto ledChain = this->ledChain();
		const auto pixel = ledChain->currentBufferBytes() + 3 * led;

		return( ENLIGHTEN_RGB( *(pixel + T_OffsetR), *(pixel + T_OffsetG), *(pixel + T_OffsetB) ) );
	}

	void setR( unsigned led, uint8_t value ) override {
		const auto ledChain = this->ledChain();

		*( ( ledChain->currentBufferBytes() + 3 * led ) + T_OffsetR ) = value;
	}

	void setG( unsigned led, uint8_t value ) override {
		const auto ledChain = this->ledChain();

		*( ( ledChain->currentBufferBytes() + 3 * led ) + T_OffsetG ) = value;
	}

	void setB( unsigned led, uint8_t value ) override {
		const auto ledChain = this->ledChain();

		*( ( ledChain->currentBufferBytes() + 3 * led ) + T_OffsetB ) = value;
	}

	void setRGB( unsigned led, uint32_t value ) override {
		const auto ledChain = this->ledChain();

		auto pixel = ledChain->currentBufferBytes() + 3 * led;
		*(pixel + T_OffsetR) = ENLIGHTEN_R( value );
		*(pixel + T_OffsetG) = ENLIGHTEN_G( value );
		*(pixel + T_OffsetB) = ENLIGHTEN_B( value );
	}

	void setR( unsigned ledFrom, unsigned ledTo, uint8_t value ) override {
		const auto ledChain = this->ledChain();

		auto pixelFrom = ledChain->currentBufferBytes() + 3 * ledFrom;
		for( auto led = ledFrom; led < ledTo; led++, pixelFrom++ ) {
			*( pixelFrom + T_OffsetR ) = value;
		}
	}

	void setG( unsigned ledFrom, unsigned ledTo, uint8_t value ) override {
		const auto ledChain = this->ledChain();

		auto pixelFrom = ledChain->currentBufferBytes() + 3 * ledFrom;
		for( auto led = ledFrom; led < ledTo; led++, pixelFrom++ ) {
			*( pixelFrom + T_OffsetG ) = value;
		}
	}

	void setB( unsigned ledFrom, unsigned ledTo, uint8_t value ) override {
		const auto ledChain = this->ledChain();

		auto pixelFrom = ledChain->currentBufferBytes() + 3 * ledFrom;
		for( auto led = ledFrom; led < ledTo; led++, pixelFrom++ ) {
			*( pixelFrom + T_OffsetB ) = value;
		}
	}

	void setRGB( unsigned ledFrom, unsigned ledTo, uint32_t value ) override {
		const auto ledChain = this->ledChain();

		auto pixelFrom = ledChain->currentBufferBytes() + 3 * ledFrom;
		const uint8_t r = ENLIGHTEN_R( value );
		const uint8_t g = ENLIGHTEN_R( value );
		const uint8_t b = ENLIGHTEN_R( value );
		for( auto led = ledFrom; led < ledTo; led++, pixelFrom++ ) {
			*( pixelFrom + T_OffsetR ) = r;
			*( pixelFrom + T_OffsetG ) = g;
			*( pixelFrom + T_OffsetB ) = b;
		}
	}

};

#endif /* LEDCHAINIMPL_H_ */
