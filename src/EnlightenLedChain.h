/*
 * EnlightenLedChain.h
 *
 *  Created on: 16.03.2016
 *      Author: awurf
 */

#ifndef ENLIGHTENLEDCHAIN_H_
#define ENLIGHTENLEDCHAIN_H_

#include <Arduino.h>

class LedChainImpl;

class EnlightenLedChain {

public:

	// LED type (tuple order, timing etc.)
	enum class LedType {
		WS2812B
	};

	// RGB tupel type
	union RGBTupel {
		struct {
			unsigned char R;
			unsigned char G;
			unsigned char B;
			unsigned char X;
		} components;
		unsigned long compound;
	};

	//
	// Life cycle and initialization
	//

	// No default construction
	EnlightenLedChain() = delete;

	// No copying
	EnlightenLedChain( const EnlightenLedChain& ) = delete;
	EnlightenLedChain& operator=( const EnlightenLedChain& ) = delete;

	EnlightenLedChain( LedType ledType, unsigned numLeds, unsigned numBuffers = 1 );
	virtual ~EnlightenLedChain();

	//
	// Member access
	//

	unsigned NumLeds() const {
		return( this->_numLeds );
	}

	unsigned NumBuffers() const {
		return( this->_numBuffers );
	}

	unsigned CurrentBuffer() const {
		return( this->_currentBuffer );
	}

	void SetCurrentBuffer( unsigned buffer );

private:

	LedType _ledType;
	unsigned _numLeds;
	unsigned _numBuffers;
	unsigned _currentBuffer;
	unsigned char* _bytes;
	LedChainImpl *_impl;
};

#endif /* ENLIGHTENLEDCHAIN_H_ */
