#include <EnlightenBT.h>
#include <EnlightenCanvas.h>

EnlightenBT bt;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  bt.turnOn( EnlightenBT::Mode::COMMAND );
}

void loop() {
  // print data from the BT module 
  // to the Arduino Micro USB serial port, 
  // and vice versa:
  
  bt.bridgeStream( Serial );
}

