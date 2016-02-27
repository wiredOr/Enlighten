#include <EnlightenBT.h>
#include <EnlightenCanvas.h>

EnlightenBT bt;

static bool testCommand( EnlightenBT& bt, const char cmd[] ) {
  unsigned count;
  Serial.print( "Command \"" );
  Serial.print( cmd );
  Serial.print( "\": " );
  const auto result = bt.command( cmd, &count );
  if( result ) { 
    Serial.print( "Success" );
  }
  else {
    Serial.print( "Failure" );
  }
  if( count > 0 ) {
    Serial.print( " (" );
    auto responses = bt.getResponseItems();
    for( unsigned i = 0; i < count; i++ ) {
      Serial.print( " \"" );
      Serial.print( responses[ i ] );
      Serial.print( "\" " );
    }
    Serial.print( ")" );
  }
  Serial.println();

  return( result );
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin( 38400 );
  while( !Serial );

  // Give me some time to activate serial monitor ;-)
  delay( 5000 );

  // Turn on the on-board Bluetooth module
  // in command mode:
  bt.turnOn( EnlightenBT::Mode::COMMAND );

  // Issue some commands:
  do {
    if( !testCommand(bt, "") ) {
      break;
    }
    if( !testCommand(bt, "+NAME?") ) {
      break;
    }
    Serial.println("All OK.");
    
  } while(false);
}

void loop() {
  // print data from the BT module 
  // to the Arduino Micro USB serial port, 
  // and vice versa.
  //
  // Call this method in a loop:
  bt.bridgeStream( Serial );
}

