/*
 * EnlightenBT.cpp
 *
 *  Created on: 02.01.2016
 *      Author: awurf
 */

#include <avr/pgmspace.h>

#include "EnlightenBT.h"

#define PIN_BT_ON	11	// 0 = ON, 1 = OFF
#define PIN_BT_KEY	10	// 1 = Command mode, 0 = BT mode

#define BT_SERIAL	Serial1
#define BT_ON_OFF_DELAY_MS	250
#define BT_OFF_ON_DELAY_MS	250

EnlightenBT::EnlightenBT() 
: _mode( Mode::NA ) 
, _response(0)
, _responseItems(0)
{
	digitalWrite( PIN_BT_ON, HIGH );
	digitalWrite( PIN_BT_KEY, LOW );

	pinMode( PIN_BT_ON, OUTPUT );
	pinMode( PIN_BT_KEY, OUTPUT );
}

EnlightenBT::~EnlightenBT() {
	this->turnOff();
}

void EnlightenBT::turnOn( Mode mode, unsigned baud /*= 38400*/ ) {
	if( (this->_mode == Mode::NA) && (mode != Mode::NA) ) {
		digitalWrite( PIN_BT_KEY, (mode == Mode::COMMAND ? 1 : 0) );
		digitalWrite( PIN_BT_ON, LOW );
		delay(BT_OFF_ON_DELAY_MS);

		this->allocResponseBuffer();

		BT_SERIAL.begin( baud );

		this->_mode = mode;
	}
}

void EnlightenBT::turnOff() {
	if( this->_mode != Mode::NA ) {
		BT_SERIAL.end();

		this->freeResponseBuffer();

		digitalWrite( PIN_BT_ON, HIGH );
		delay(BT_ON_OFF_DELAY_MS);

		this->_mode = Mode::NA;
	}
}

Stream& EnlightenBT::getStream() {
	return( BT_SERIAL );
}

void EnlightenBT::bridgeStream( Stream& peer ) {
	auto& bt = this->getStream();

	if( peer.available() ) {
		bt.write(peer.read());
	}
	if( bt.available() ) {
		peer.write(bt.read());
	}

}

void EnlightenBT::allocResponseBuffer() {
	if( !this->_response ) {
		this->_response = new char[ENLIGHTEN_BT_MAX_RESPONSE_SIZE];
	}
	if( !this->_responseItems ) {
		this->_responseItems = new char*[ENLIGHTEN_BT_MAX_RESPONSE_ITEMS];
	}
}

void EnlightenBT::freeResponseBuffer() {
	if( this->_response ) {
		delete[] this->_response;
		this->_response = 0;
	}
	if( this->_responseItems ) {
		delete[] this->_responseItems;
		this->_responseItems = 0;
	}
}
