/*
 * EnlightenBT.cpp
 *
 *  Created on: 02.01.2016
 *      Author: awurf
 */

#include "EnlightenBT.h"

#define PIN_BT_ON	11	// 0 = ON, 1 = OFF
#define PIN_BT_KEY	10	// 1 = Command mode, 0 = BT mode

#define BT_SERIAL	Serial1

EnlightenBT::EnlightenBT() : _mode( Mode::NA ) {
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
		this->_mode = mode;

		digitalWrite( PIN_BT_KEY, (this->_mode == Mode::COMMAND ? 1 : 0) );
		digitalWrite( PIN_BT_ON, LOW );
		delay(100);

		BT_SERIAL.begin( baud );
	}
}

void EnlightenBT::turnOff() {
	if( this->_mode != Mode::NA ) {
		BT_SERIAL.end();

		digitalWrite( PIN_BT_ON, HIGH );
		delay(100);
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
