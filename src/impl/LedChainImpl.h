/*
 * LedChainImpl.h
 *
 *  Created on: 16.03.2016
 *      Author: awurf
 */

#ifndef LEDCHAINIMPL_H_
#define LEDCHAINIMPL_H_

#include <Arduino.h>

class EnlightenLedChain;

class LedChainImpl {

public:

	LedChainImpl( EnlightenLedChain* ledChain );
	virtual ~LedChainImpl();

	virtual void FlingCurrentBuffer() = 0;

protected:

	const EnlightenLedChain *LedChain() const {
		return( this->_ledChain );
	}

	EnlightenLedChain *LedChain() {
		return( this->_ledChain );
	}

private:

	EnlightenLedChain* _ledChain;

};

#endif /* LEDCHAINIMPL_H_ */
