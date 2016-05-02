/*
 * EnlightenLedChain_WS2812B.h
 *
 *  Created on: 16.03.2016
 *      Author: awurf
 */

#ifndef _ENLIGHTENLEDCHAIN_WS2812B_H_
#define _ENLIGHTENLEDCHAIN_WS2812B_H_

#include "impl/LedChainImpl.h"

class EnlightenLedChain_WS2812B : public LedChainImpl<1, 0, 2> {

public:

	EnlightenLedChain_WS2812B( unsigned numLeds, unsigned numBuffers = 1 )
	: LedChainImpl( numLeds, numBuffers )
	{ }

	void flingCurrentBuffer() const override;

};

#endif /* _ENLIGHTENLEDCHAIN_WS2812B_H_ */
