/*
 * EnlightenBT.h
 *
 *  Created on: 02.01.2016
 *      Author: awurf
 */

#ifndef ENLIGHTENBT_H_
#define ENLIGHTENBT_H_

#include <Arduino.h>

#define ENLIGHTEN_BT_MAX_RESPONSE_ITEMS	16
#define ENLIGHTEN_BT_MAX_RESPONSE_SIZE	256

class EnlightenBT {

public:
	enum class Mode {
		NA = 0,
		NORMAL = 1,
		COMMAND = 2
	};

	EnlightenBT();
	virtual ~EnlightenBT();

	// Turn BT module on/off:
	void turnOn( Mode mode, unsigned baud = 38400 );
	void turnOff();

	// Send / receive data through the BT module:
	Stream& getStream();
	void bridgeStream( Stream& peer );

private:
	Mode _mode;
	char** _responseItems;
	char* _response;

	void allocResponseBuffer();
	void freeResponseBuffer();

};

#endif /* ENLIGHTENBT_H_ */
