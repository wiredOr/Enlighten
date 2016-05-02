/*
 * EnlightenLedChain_PL9823.h
 *
 *  Created on: 16.03.2016
 *      Author: awurf
 */

#ifndef _ENLIGHTENLEDCHAIN_PL9823_H_
#define _ENLIGHTENLEDCHAIN_PL9823_H_

#include "impl/LedChainImpl.h"

class EnlightenLedChain_PL9823 : public LedChainImpl<0, 1, 2> {

public:

	EnlightenLedChain_PL9823( unsigned numLeds, unsigned numBuffers = 1 )
	: LedChainImpl( numLeds, numBuffers )
	{ }

	void flingCurrentBuffer() const override;

};

#endif /* _ENLIGHTENLEDCHAIN_PL9823_H_ */
