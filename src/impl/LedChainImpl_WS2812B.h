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

class LedChainImpl_WS2812B : public LedChainImpl<1, 0, 2> {

public:

	LedChainImpl_WS2812B( EnlightenLedChain* ledChain );

	void flingCurrentBuffer() const override;

};

#endif /* LEDCHAINIMPL_WS2812B_H_ */
