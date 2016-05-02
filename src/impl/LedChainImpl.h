/*
 * LedChainImpl.h
 *
 *  Created on: 16.03.2016
 *      Author: awurf
 */

//------------------------------------------------------------------------------

#ifndef _LEDCHAINIMPL_H_
#define _LEDCHAINIMPL_H_

//------------------------------------------------------------------------------

#include <string.h>
#include <avr/pgmspace.h>
#include <Arduino.h>
#include <WString.h>

//------------------------------------------------------------------------------

#define PIN_DATA	9	// 0 = LOW, 1 = HIGH

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

//------------------------------------------------------------------------------

template< unsigned T_OffsetR, unsigned T_OffsetG, unsigned T_OffsetB >
class LedChainImpl {

private:

	unsigned _numLeds;
	unsigned _numBuffers;
	unsigned _currentBuffer;
	uint8_t *_bytes;
	uint8_t *_currentBufferBytes;

public:

	//
	// Life cycle
	//

	LedChainImpl( unsigned numLeds, unsigned numBuffers ) 
	: _numLeds( numLeds )
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
		this->updateCurrentBufferBytes();
	}

	virtual ~LedChainImpl() {
		delete[] this->_bytes;
	}

	// No default construction
	LedChainImpl() = delete;

	// No copying
	LedChainImpl( const LedChainImpl& ) = delete;
	LedChainImpl& operator=( const LedChainImpl& ) = delete;

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
	// Fling current buffer contents to LED chain
	// Needs to be implemented LED-specific.
	//

	virtual void flingCurrentBuffer() const = 0;

	//
	// Pixel access
	//

	uint8_t r( unsigned led ) const {
		if( led >= this->_numLeds ) {
			return( 0 );
		}

		const auto pixel = this->currentBufferBytes() + 3 * led;

		return( *(pixel + T_OffsetR) );
	}

	uint8_t g( unsigned led ) const {
		if( led >= this->_numLeds ) {
			return( 0 );
		}
		
		const auto pixel = this->currentBufferBytes() + 3 * led;

		return( *(pixel + T_OffsetG) );
	}

	uint8_t b( unsigned led ) const {
		if( led >= this->_numLeds ) {
			return( 0 );
		}
		
		const auto pixel = this->currentBufferBytes() + 3 * led;

		return( *(pixel + T_OffsetB) );
	}

	uint32_t rgb( unsigned led ) const {
		if( led >= this->_numLeds ) {
			return( 0 );
		}
		
		const auto pixel = this->currentBufferBytes() + 3 * led;

		return( ENLIGHTEN_RGB( *(pixel + T_OffsetR), *(pixel + T_OffsetG), *(pixel + T_OffsetB) ) );
	}

	void setR( unsigned led, uint8_t value ) {
		if( led >= this->_numLeds ) {
			return;
		}

		*( ( this->currentBufferBytes() + 3 * led ) + T_OffsetR ) = value;
	}

	void setG( unsigned led, uint8_t value ) {
		if( led >= this->_numLeds ) {
			return;
		}

		*( ( this->currentBufferBytes() + 3 * led ) + T_OffsetG ) = value;
	}

	void setB( unsigned led, uint8_t value ) {
		if( led >= this->_numLeds ) {
			return;
		}

		*( ( this->currentBufferBytes() + 3 * led ) + T_OffsetB ) = value;
	}

	void setRGB( unsigned led, uint32_t value ) {
		if( led >= this->_numLeds ) {
			return;
		}

		auto pixel = this->currentBufferBytes() + 3 * led;
		*(pixel + T_OffsetR) = ENLIGHTEN_R( value );
		*(pixel + T_OffsetG) = ENLIGHTEN_G( value );
		*(pixel + T_OffsetB) = ENLIGHTEN_B( value );
	}

	void setR( unsigned ledFrom, unsigned ledTo, uint8_t value ) {
		if( (ledFrom >= this->_numLeds) || (ledTo > this->_numLeds) ) {
			return;
		}

		auto pixelFrom = this->currentBufferBytes() + 3 * ledFrom;
		for( auto led = ledFrom; led < ledTo; led++, pixelFrom++ ) {
			*( pixelFrom + T_OffsetR ) = value;
		}
	}

	void setG( unsigned ledFrom, unsigned ledTo, uint8_t value ) {
		if( (ledFrom >= this->_numLeds) || (ledTo > this->_numLeds) ) {
			return;
		}

		auto pixelFrom = this->currentBufferBytes() + 3 * ledFrom;
		for( auto led = ledFrom; led < ledTo; led++, pixelFrom++ ) {
			*( pixelFrom + T_OffsetG ) = value;
		}
	}

	void setB( unsigned ledFrom, unsigned ledTo, uint8_t value ) {
		if( (ledFrom >= this->_numLeds) || (ledTo > this->_numLeds) ) {
			return;
		}

		auto pixelFrom = this->currentBufferBytes() + 3 * ledFrom;
		for( auto led = ledFrom; led < ledTo; led++, pixelFrom++ ) {
			*( pixelFrom + T_OffsetB ) = value;
		}
	}

	void setRGB( unsigned ledFrom, unsigned ledTo, uint32_t value ) {
		if( (ledFrom >= this->_numLeds) || (ledTo > this->_numLeds) ) {
			return;
		}

		auto pixelFrom = this->currentBufferBytes() + 3 * ledFrom;
		const uint8_t r = ENLIGHTEN_R( value );
		const uint8_t g = ENLIGHTEN_R( value );
		const uint8_t b = ENLIGHTEN_R( value );
		for( auto led = ledFrom; led < ledTo; led++, pixelFrom++ ) {
			*( pixelFrom + T_OffsetR ) = r;
			*( pixelFrom + T_OffsetG ) = g;
			*( pixelFrom + T_OffsetB ) = b;
		}
	}

	//
	// Buffer handling
	//

	void setCurrentBuffer( unsigned buffer ) {
		this->_currentBuffer = ( buffer < this->_numBuffers ? buffer : this->_numBuffers - 1 );
		this->updateCurrentBufferBytes();
	}

	void copyBuffer( unsigned buffer ) {
		const auto srcBuffer = ( buffer < this->_numBuffers ? buffer : this->_numBuffers - 1 );
		if( srcBuffer != this->_currentBuffer ) {
			const auto bufferSize = 3 * this->_numLeds;
			const uint8_t *srcBufferBytes = this->_bytes + ( srcBuffer * bufferSize );
			::memcpy( this->_currentBufferBytes, srcBufferBytes, bufferSize );
		}
	}

private:

	void updateCurrentBufferBytes() {
		this->_currentBufferBytes = this->_bytes + ( this->_currentBuffer * 3 * this->_numLeds );
	}

};

//------------------------------------------------------------------------------

#endif /* _LEDCHAINIMPL_H_ */
