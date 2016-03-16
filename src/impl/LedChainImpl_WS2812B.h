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

	virtual void FlingCurrentBuffer() override;

};

#endif /* LEDCHAINIMPL_WS2812B_H_ */
