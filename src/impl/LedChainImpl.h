/*
 * LedChainImpl.h
 *
 *  Created on: 16.03.2016
 *      Author: awurf
 */

#ifndef LEDCHAINIMPL_H_
#define LEDCHAINIMPL_H_

#include <Arduino.h>

#define PIN_DATA	9	// 0 = LOW, 1 = HIGH

class EnlightenLedChain;

class LedChainImpl {

public:

	LedChainImpl( EnlightenLedChain* ledChain );
	virtual ~LedChainImpl();

	virtual void flingCurrentBuffer() const = 0;
	virtual uint8_t r( unsigned led ) const = 0;
	virtual uint8_t g( unsigned led ) const = 0;
	virtual uint8_t b( unsigned led ) const = 0;
	virtual	uint32_t rgb( unsigned led ) const = 0;

	virtual void setR( unsigned led, uint8_t value ) = 0;
	virtual void setG( unsigned led, uint8_t value ) = 0;
	virtual void setB( unsigned led, uint8_t value ) = 0;
	virtual	void setRGB( unsigned led, uint32_t value ) = 0;

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

#endif /* LEDCHAINIMPL_H_ */
