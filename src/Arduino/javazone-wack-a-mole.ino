tatic const uint8_t buttonPins[] = {32, 33};

uint8_t sizeOfArray = 2;
// Addresses for the LEDs. We have 30 LEDs (one in each button).
uint8_t ledPins[2];

uint8_t score = 0;
uint8_t previousValue = -1;
bool gameIsRunning = false;

//time in seconds for how long a game lasts is set in Python code.

//here we store the value for a random button
uint8_t randomNum = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing...");
  
  for (int i = 0; i < sizeOfArray; i++) {
    ledPins[i] = i;
    pinMode(ledPins[i], OUTPUT);
  }

  // Get new button to light up
  randomNum = random(sizeOfArray);
  // Reset all buttons' LEDs
  resetLEDs();
  
  for (int i = 0; i < sizeOfArray; i++) {
    pinMode(buttonPins[i], INPUT);
  }

  //get some random noise from a pin that is not set to anything and set it as a seed
  randomSeed(analogRead(A10));
}

void loop() {
  checkGameStateFromSerial();
  
  if (gameIsRunning) {
    //checks if correct button was clicked
    uint8_t pinStatus = digitalRead(buttonPins[randomNum]);
    //Serial.println(pinStatus);
  
    //if correct button clicked, increments score and lights up new button
    if (pinStatus) {
      score++;
      Serial.println("Hit!");
      digitalWrite(ledPins[randomNum], LOW);
      previousValue = randomNum;
      do {
        randomNum = random(sizeOfArray);
        Serial.println(randomNum);
      } while (randomNum == previousValue);
      digitalWrite(ledPins[randomNum], HIGH);
    }
  }
}

void resetLEDs() {
  for (int i = 0; i < sizeOfArray; i++) {
    ledPins[i] = i;
    digitalWrite(ledPins[i], LOW);
  }
}

void beginGame() {
  gameIsRunning = true;
}

void endGame() {
  //reset values
    writeToSerial(score);
  gameIsRunning = false;
  score = 0;
  previousValue = -1;
  randomNum = random(sizeOfArray);
}


void writeToSerial(int data) {
  Serial.println(data);
}


void checkGameStateFromSerial() {
  //char serialListener = Serial.read();
  //if(serialListener == 'Y') {
    gameIsRunning = true;
  //}
}

