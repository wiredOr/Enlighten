/*
 * EnlightenLedChain.cpp
 *
 *  Created on: 16.03.2016
 *      Author: awurf
 */

#include <string.h>

#include "EnlightenLedChain.h"
#include "impl/LedChainImpl.h"
#include "impl/LedChainImpl_PL9823.h"
#include "impl/LedChainImpl_WS2812B.h"

/////////////////////////////////////////////////

EnlightenLedChain::EnlightenLedChain( LedType ledType, unsigned numLeds, unsigned numBuffers /*= 1*/ )
: _ledType( ledType )
, _numLeds( numLeds )
, _numBuffers( numBuffers )
, _currentBuffer( 0 )
, _bytes( 0 )
{ 
	digitalWrite( PIN_DATA, LOW );
	pinMode( PIN_DATA, OUTPUT );

	const auto size = this->_numBuffers * this->_numLeds * 3;

	this->_bytes = new uint8_t[ size ];
	::memset( this->_bytes, 0, size );

	// TODO: Construct LED chain implementation based on LED type
	if( this->_ledType == LedType::PL9823 ) {
		this->_impl = new LedChainImpl_PL9823( this );
	}
	else if( this->_ledType == LedType::WS2812B ) {
		this->_impl = new LedChainImpl_WS2812B( this );
	}
}

EnlightenLedChain::~EnlightenLedChain() {
	delete this->_impl;
	delete[] this->_bytes;
}

void EnlightenLedChain::SetCurrentBuffer( unsigned buffer ) {
	this->_currentBuffer = ( buffer < this->_numBuffers ? buffer : this->_numBuffers - 1 );
}

void EnlightenLedChain::FlingCurrentBuffer() const {
	this->_impl->FlingCurrentBuffer();
}
