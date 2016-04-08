/*
 * LedChainImpl_PL9823.h
 *
 *  Created on: 16.03.2016
 *      Author: awurf
 */

#ifndef LEDCHAINIMPL_PL9823_H_
#define LEDCHAINIMPL_PL9823_H_

#include <Arduino.h>

#include "LedChainImpl.h"

class LedChainImpl_PL9823 : public LedChainImpl<0, 1, 2> {

public:

	LedChainImpl_PL9823( EnlightenLedChain* ledChain );

	void flingCurrentBuffer() const override;

};

#endif /* LEDCHAINIMPL_PL9823_H_ */
