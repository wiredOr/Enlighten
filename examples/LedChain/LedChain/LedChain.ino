#include <EnlightenBT.h>
#include <EnlightenLedChain_WS2812B.h>

#include <math.h>

EnlightenLedChain_WS2812B chain( 64 );

void sparkle() {
  static float f1 = 0.0f, f2 = 0.0f;
  
  const auto s1 = static_cast<uint8_t>( (::sinf( f1 ) + 1.0f) * 127.0f );
  const auto s2 = static_cast<uint8_t>( (::sinf( f2 ) + 1.0f) * 127.0f );
  const auto c1 = static_cast<uint8_t>( (::cosf( f1 ) + 1.0f) * 127.0f );
  const auto c2 = static_cast<uint8_t>( (::cosf( f2 ) + 1.0f) * 127.0f );

  chain.setRGB( 0, ENLIGHTEN_RGB( s1, s2, c1 ) );
  chain.setRGB( 1, ENLIGHTEN_RGB( s2, c1, c2 ) );
  chain.setRGB( 2, ENLIGHTEN_RGB( c1, c2, s1 ) );
  chain.setRGB( 3, ENLIGHTEN_RGB( c2, s1, s2 ) );

  chain.flingCurrentBuffer();
   
  f1 += 0.01;
  f2 += 0.017;
}

void setup() {
  delay(250);
}

void loop() {

  for( unsigned testLed = 0; testLed < chain.numLeds(); testLed++ ) {
    for( int color = 0; color < 3; color++ ) {

      for( unsigned led = 0; led < chain.numLeds(); led++ ) {
        if( led == testLed ) {
          switch( color ) {
            case 0: chain.setRGB( led, ENLIGHTEN_RGB( 255, 0, 0 ) ); break;
            case 1: chain.setRGB( led, ENLIGHTEN_RGB( 0, 255, 0 ) ); break;
            case 2: chain.setRGB( led, ENLIGHTEN_RGB( 0, 0, 255 ) ); break;
          }
        }
        else {
          chain.setRGB( led, 0 );
        }
      }
      
      chain.flingCurrentBuffer();
      //delay(333);
      
    }
  }
  
}
