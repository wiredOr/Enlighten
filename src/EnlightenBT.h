/*
 * EnlightenBT.h
 *
 *  Created on: 02.01.2016
 *      Author: awurf
 */

#ifndef ENLIGHTENBT_H_
#define ENLIGHTENBT_H_

#include <Arduino.h>

class EnlightenBT {

public:
	enum class Mode {
		NA = 0,
		NORMAL = 1,
		COMMAND = 2
	};

	EnlightenBT();
	virtual ~EnlightenBT();

	void turnOn( Mode mode, unsigned baud = 38400 );
	void turnOff();

	Stream& getStream();
	void bridgeStream( Stream& peer );

private:
	Mode _mode;

};

#endif /* ENLIGHTENBT_H_ */
