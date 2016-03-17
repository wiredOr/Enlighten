#include <EnlightenBT.h>
#include <EnlightenLedChain.h>

EnlightenLedChain chain( EnlightenLedChain::LedType::PL9823, 4 );

void setup() {
  // put your setup code here, to run once:
  delay(2000);
  chain.FlingCurrentBuffer();

}

void loop() {
  // put your main code here, to run repeatedly:

}
