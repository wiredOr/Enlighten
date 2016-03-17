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

	virtual void FlingCurrentBuffer() const override;
	virtual uint8_t R( unsigned led ) const override;
	virtual uint8_t G( unsigned led ) const override;
	virtual uint8_t B( unsigned led ) const override;
	virtual	uint32_t RGB( unsigned led ) const override;

	virtual void SetR( unsigned led, uint8_t value ) override;
	virtual void SetG( unsigned led, uint8_t value ) override;
	virtual void SetB( unsigned led, uint8_t value ) override;
	virtual	void SetRGB( unsigned led, uint32_t value ) override;

};

#endif /* LEDCHAINIMPL_WS2812B_H_ */
