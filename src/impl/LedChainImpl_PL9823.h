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

class LedChainImpl_PL9823 : public LedChainImpl {

public:

	LedChainImpl_PL9823( EnlightenLedChain* ledChain );

	virtual void FlingCurrentBuffer() override;

};

#endif /* LEDCHAINIMPL_PL9823_H_ */
