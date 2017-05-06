#include <SPI.h> 
#include <MCP23S17.h> 

MCP iochip(0,10); 
  int button2PreviousValue=-1;
  int button2Clicks=0;

void setup() {
  iochip.begin();
  iochip.pinMode(1, OUTPUT); 
  iochip.pinMode(7, OUTPUT); 
  iochip.pinMode(8, OUTPUT);
  iochip.pinMode(9, INPUT);
  iochip.pinMode(10, INPUT);
  
 int BlinkingLightID;
 int ButtonClickedID;
}

void loop() {

  int button1Value;
  button1Value = iochip.digitalRead(9);
  iochip.digitalWrite(7, button1Value);

  int button2Value;
  button2Value = iochip.digitalRead(10);
  iochip.digitalWrite(8, button2Value);

  if (button2Value == 1 && button2PreviousValue == 0){
    button2Clicks +=1;
  }
  button2PreviousValue = button2Value;
  if( button2Clicks > 2){
    iochip.digitalWrite(1, HIGH);
  }

}
