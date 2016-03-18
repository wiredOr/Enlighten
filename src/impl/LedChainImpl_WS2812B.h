/*
 * LedChainImpl_WS2812B.h
 *
 *  Created on: 16.03.2016
 *      Author: awurf
 */

#ifndef LEDCHAINIMPL_WS2812B_H_
#define LEDCHAINIMPL_WS2812B_H_

#include <Arduino.h>

#include "LedChainImpl.h"

class LedChainImpl_WS2812B : public LedChainImpl {

public:

	LedChainImpl_WS2812B( EnlightenLedChain* ledChain );

	virtual void flingCurrentBuffer() const override;
	virtual uint8_t r( unsigned led ) const override;
	virtual uint8_t g( unsigned led ) const override;
	virtual uint8_t b( unsigned led ) const override;
	virtual	uint32_t rgb( unsigned led ) const override;

	virtual void setR( unsigned led, uint8_t value ) override;
	virtual void setG( unsigned led, uint8_t value ) override;
	virtual void setB( unsigned led, uint8_t value ) override;
	virtual	void setRGB( unsigned led, uint32_t value ) override;

};

#endif /* LEDCHAINIMPL_WS2812B_H_ */
