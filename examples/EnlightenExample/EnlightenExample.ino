#include <EnlightenBT.h>
#include <EnlightenCanvas.h>

EnlightenBT bt;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);

  // Turn on the on-board Bluetooth module
  // in command mode:
  bt.turnOn( EnlightenBT::Mode::COMMAND );
}

void loop() {
  // print data from the BT module 
  // to the Arduino Micro USB serial port, 
  // and vice versa.
  //
  // Call this method in a loop:
  bt.bridgeStream( Serial );
}

