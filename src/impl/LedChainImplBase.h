/*
 * LedChainImplBase.h
 *
 *  Created on: 08.04.2016
 *      Author: awurf
 */

#ifndef LEDCHAINIMPLBASE_H_
#define LEDCHAINIMPLBASE_H_

#include "../EnlightenLedChain.h"

class LedChainImplBase {

public:

	LedChainImplBase( EnlightenLedChain* ledChain ) 
	: _ledChain( ledChain ) 
	{ }

	virtual ~LedChainImplBase() 
	{ }

	virtual void flingCurrentBuffer() const = 0;

	virtual uint8_t r( unsigned led ) const = 0;
	virtual uint8_t g( unsigned led ) const = 0;
	virtual uint8_t b( unsigned led ) const = 0;
	virtual uint32_t rgb( unsigned led ) const = 0;

	virtual void setR( unsigned led, uint8_t value ) = 0;
	virtual void setG( unsigned led, uint8_t value ) = 0;
	virtual void setB( unsigned led, uint8_t value ) = 0;
	virtual void setRGB( unsigned led, uint32_t value ) = 0;

	virtual void setR( unsigned ledFrom, unsigned ledTo, uint8_t value ) = 0;
	virtual void setG( unsigned ledFrom, unsigned ledTo, uint8_t value ) = 0;
	virtual void setB( unsigned ledFrom, unsigned ledTo, uint8_t value ) = 0;
	virtual void setRGB( unsigned ledFrom, unsigned ledTo, uint32_t value ) = 0;

protected:

	const EnlightenLedChain *ledChain() const {
		return( this->_ledChain );
	}

	EnlightenLedChain *ledChain() {
		return( this->_ledChain );
	}

private:

	EnlightenLedChain* _ledChain;

};

#endif /* LEDCHAINIMPLBASE_H_ */
