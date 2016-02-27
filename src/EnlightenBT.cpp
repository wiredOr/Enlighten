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
#define BT_ON_OFF_DELAY_MS	1000
#define BT_OFF_ON_DELAY_MS	1000

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

		BT_SERIAL.begin( baud );
		while( !BT_SERIAL );
		BT_SERIAL.setTimeout( 1000 );

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
		this->_responseItems = new char*[ENLIGHTEN_BT_MAX_RESPONSE_ITEMS + 1];
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

bool EnlightenBT::readCommandResponse( unsigned* responseItemCount ) {
	static const char sOK[] PROGMEM = "OK";
	static const char sERROR[] PROGMEM = "ERROR";

	this->allocResponseBuffer();

	unsigned itemCount = 0;
	auto result = false;

	const auto bufferSentinel = this->_response + ENLIGHTEN_BT_MAX_RESPONSE_SIZE;
	auto bufferItem = this->_response;
	while( (itemCount < ENLIGHTEN_BT_MAX_RESPONSE_ITEMS) && (bufferItem < bufferSentinel) ) {
		const auto bytesLeft = bufferSentinel - bufferItem;
		const auto bytesRead = BT_SERIAL.readBytesUntil( '\n', bufferItem, bytesLeft );
		if( bytesRead == 0 ) {	// time out
			break;
		}

		*(bufferItem + bytesRead - 1) = '\0';
		this->_responseItems[itemCount++] = bufferItem;

		if( !strcmp_P(bufferItem, sOK) ) {
			result = true;
			break;
		}
		else if( !strncmp_P(bufferItem, sERROR, 5) ) {
			break;
		}

		bufferItem += bytesRead;
	}

	this->_responseItems[itemCount] = 0;

	if( responseItemCount ) {
		*responseItemCount = itemCount;
	}

	return( result );
}

void EnlightenBT::sendCommand( const __FlashStringHelper *command ) {
	BT_SERIAL.print(F("AT"));
	BT_SERIAL.print(command);
	BT_SERIAL.print(F("\r\n"));
}

void EnlightenBT::sendCommand(  const String& command) {
	BT_SERIAL.print(F("AT"));
	BT_SERIAL.print(command);
	BT_SERIAL.print(F("\r\n"));
}

void EnlightenBT::sendCommand( const char command[] ) {
	BT_SERIAL.print(F("AT"));
	BT_SERIAL.print(command);
	BT_SERIAL.print(F("\r\n"));
}

bool EnlightenBT::command( const __FlashStringHelper* command, unsigned* responseItemCount /*= nullptr */ ) {
	this->sendCommand( command );
	return( this->readCommandResponse( responseItemCount ) );
}

bool EnlightenBT::command( const String& command, unsigned* responseItemCount /*= nullptr */ ) {
	this->sendCommand( command );
	return( this->readCommandResponse( responseItemCount ) );
}

bool EnlightenBT::command( const char command[], unsigned* responseItemCount /*= nullptr */ ) {
	this->sendCommand( command );
	return( this->readCommandResponse( responseItemCount ) );
}
