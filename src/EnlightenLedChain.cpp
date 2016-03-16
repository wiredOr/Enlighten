/*
 * EnlightenLedChain.cpp
 *
 *  Created on: 16.03.2016
 *      Author: awurf
 */

#include <string.h>

#include "EnlightenLedChain.h"
#include "impl/LedChainImpl.h"

/////////////////////////////////////////////////

EnlightenLedChain::EnlightenLedChain( LedType ledType, unsigned numLeds, unsigned numBuffers /*= 1*/ )
: _ledType( ledType )
, _numLeds( numLeds )
, _numBuffers( numBuffers )
, _currentBuffer( 0 )
, _bytes( 0 )
{ 
	const auto size = this->_numBuffers * this->_numLeds * 3;

	this->_bytes = new unsigned char[ size ];
	::memset( this->_bytes, 0, size );

	// TODO: Construct LED chain implementation based on LED type
	this->_impl = new LedChainImpl( this );
}

EnlightenLedChain::~EnlightenLedChain() {
	delete this->_impl;
	delete[] this->_bytes;
}

void EnlightenLedChain::SetCurrentBuffer( unsigned buffer ) {
	this->_currentBuffer = ( buffer < this->_numBuffers ? buffer : this->_numBuffers - 1 );
}
