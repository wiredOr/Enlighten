/*
 * EnlightenLedChain.cpp
 *
 *  Created on: 16.03.2016
 *      Author: awurf
 */

#include <string.h>

#include "EnlightenLedChain.h"
#include "impl/LedChainImplBase.h"
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
, _currentBufferBytes( 0 )
{ 
	digitalWrite( PIN_DATA, LOW );
	pinMode( PIN_DATA, OUTPUT );

	const auto size = this->_numBuffers * this->_numLeds * 3;

	this->_bytes = new uint8_t[ size ];
	::memset( this->_bytes, 0, size );
	this->UpdateCurrentBufferBytes();

	// Construct LED chain implementation based on LED type
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

void EnlightenLedChain::UpdateCurrentBufferBytes() {
	this->_currentBufferBytes = this->_bytes + ( this->_currentBuffer * 3 * this->_numLeds );
}

void EnlightenLedChain::setCurrentBuffer( unsigned buffer ) {
	this->_currentBuffer = ( buffer < this->_numBuffers ? buffer : this->_numBuffers - 1 );
	this->UpdateCurrentBufferBytes();
}

void EnlightenLedChain::copyBuffer( unsigned buffer ) {
	const auto srcBuffer = ( buffer < this->_numBuffers ? buffer : this->_numBuffers - 1 );
	if( srcBuffer != this->_currentBuffer ) {
		const auto bufferSize = 3 * this->_numLeds;
		const uint8_t *srcBufferBytes = this->_bytes + ( srcBuffer * bufferSize );
		::memcpy( this->_currentBufferBytes, srcBufferBytes, bufferSize );
	}
}

void EnlightenLedChain::flingCurrentBuffer() const {
	this->_impl->flingCurrentBuffer();
}

uint8_t EnlightenLedChain::r( unsigned led ) const {
	return( led < this->_numLeds ? this->_impl->r( led ) : 0 );
}

uint8_t EnlightenLedChain::g( unsigned led ) const {
	return( led < this->_numLeds ? this->_impl->g( led ) : 0 );
}

uint8_t EnlightenLedChain::b( unsigned led ) const {
	return( led < this->_numLeds ? this->_impl->b( led ) : 0 );
}

uint32_t EnlightenLedChain::rgb( unsigned led ) const {
	return( led < this->_numLeds ? this->_impl->rgb( led ) : 0 );
}

void EnlightenLedChain::setR( unsigned led, uint8_t value ) {
	if( led < this->_numLeds ) {
		this->_impl->setR( led, value );
	}
}

void EnlightenLedChain::setG( unsigned led, uint8_t value ) {
	if( led < this->_numLeds ) {
		this->_impl->setG( led, value );
	}
}

void EnlightenLedChain::setB( unsigned led, uint8_t value ) {
	if( led < this->_numLeds ) {
		this->_impl->setB( led, value );
	}
}

void EnlightenLedChain::setRGB( unsigned led, uint32_t value ) {
	if( led < this->_numLeds ) {
		this->_impl->setRGB( led, value );
	}
}

void EnlightenLedChain::setR( unsigned ledFrom, unsigned ledTo, uint8_t value ) {
	if( (ledFrom < this->_numLeds) && (ledTo <= this->_numLeds) ) {
		this->_impl->setR( ledFrom, ledTo, value );
	}
}

void EnlightenLedChain::setG( unsigned ledFrom, unsigned ledTo, uint8_t value ) {
	if( (ledFrom < this->_numLeds) && (ledTo <= this->_numLeds) ) {
		this->_impl->setG( ledFrom, ledTo, value );
	}
}

void EnlightenLedChain::setB( unsigned ledFrom, unsigned ledTo, uint8_t value ) {
	if( (ledFrom < this->_numLeds) && (ledTo <= this->_numLeds) ) {
		this->_impl->setB( ledFrom, ledTo, value );
	}
}

void EnlightenLedChain::setRGB( unsigned ledFrom, unsigned ledTo, uint32_t value ) {
	if( (ledFrom < this->_numLeds) && (ledTo <= this->_numLeds) ) {
		this->_impl->setR( ledFrom, ledTo, value );
	}
}
