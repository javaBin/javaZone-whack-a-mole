#include <SPI.h> 
#include <MCP23S17.h> 

MCP iochip(0,10); 

void setup() {
  iochip.begin();
  iochip.pinMode(1, OUTPUT); 
  iochip.pinMode(7, OUTPUT); 
  iochip.pinMode(8, OUTPUT);
  iochip.digitalWrite(7, HIGH);
}

void loop() {
  iochip.digitalWrite(1, HIGH);
  delay(1000);
  iochip.digitalWrite(8, HIGH);
  delay(1000);
  iochip.digitalWrite(1, LOW);
  delay(1000);
  iochip.digitalWrite(8, LOW);
  delay(1000);
}
