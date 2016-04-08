/*
 * EnlightenLedChain.h
 *
 *  Created on: 16.03.2016
 *      Author: awurf
 */

#ifndef ENLIGHTENLEDCHAIN_H_
#define ENLIGHTENLEDCHAIN_H_

#include <Arduino.h>

#define ENLIGHTEN_R(rgb)					\
 	static_cast<uint8_t>( 					\
 		static_cast<uint32_t>( rgb ) >> 16 	\
 	)

#define ENLIGHTEN_G(rgb)					\
 	static_cast<uint8_t>( 					\
 		static_cast<uint32_t>( rgb ) >> 8 	\
 	)

#define ENLIGHTEN_B(rgb)					\
 	static_cast<uint8_t>( 					\
 		static_cast<uint32_t>( rgb )	 	\
 	)

#define ENLIGHTEN_RGB(r,g,b)				\
 	static_cast<uint32_t> (					\
 		  static_cast<uint32_t>( r ) << 16	\
 		| static_cast<uint32_t>( g ) << 8	\
 		| static_cast<uint32_t>( b ) 		\
 	)

class LedChainImplBase;

class EnlightenLedChain {

public:

	// LED type (tuple order, timing etc.)
	enum class LedType {
		PL9823,
		WS2812B
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

	inline unsigned numLeds() const {
		return( this->_numLeds );
	}

	inline unsigned numBuffers() const {
		return( this->_numBuffers );
	}

	inline unsigned currentBuffer() const {
		return( this->_currentBuffer );
	}

	inline const uint8_t *bytes() const {
		return( this->_bytes );
	}

	inline uint8_t *bytes() {
		return( this->_bytes );
	}

	inline const uint8_t *currentBufferBytes() const {
		return( this->_currentBufferBytes );
	}

	inline uint8_t *currentBufferBytes() {
		return( this->_currentBufferBytes );
	}

	//
	// Buffer handling
	//

	void setCurrentBuffer( unsigned buffer );
	void copyBuffer( unsigned buffer );

	//
	// Implementation-specific
	//

	void flingCurrentBuffer() const;

	uint8_t r( unsigned led ) const;
	uint8_t g( unsigned led ) const;
	uint8_t b( unsigned led ) const;
	uint32_t rgb( unsigned led ) const;

	void setR( unsigned led, uint8_t value );
	void setG( unsigned led, uint8_t value );
	void setB( unsigned led, uint8_t value );
	void setRGB( unsigned led, uint32_t value );

	void setR( unsigned ledFrom, unsigned ledTo, uint8_t value );
	void setG( unsigned ledFrom, unsigned ledTo, uint8_t value );
	void setB( unsigned ledFrom, unsigned ledTo, uint8_t value );
	void setRGB( unsigned ledFrom, unsigned ledTo, uint32_t value );

private:

	void UpdateCurrentBufferBytes();

	LedType _ledType;
	unsigned _numLeds;
	unsigned _numBuffers;
	unsigned _currentBuffer;
	uint8_t *_bytes;
	uint8_t *_currentBufferBytes;
	LedChainImplBase *_impl;
};

#endif /* ENLIGHTENLEDCHAIN_H_ */
