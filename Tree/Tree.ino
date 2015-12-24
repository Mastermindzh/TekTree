/*
  Rick van Lieshout 
  24-12-2015
  LICENSE: MIT
*/

const int DELAYTIME = 100;
const int NUMBEROFPINS = 11; 
const int pinArray[NUMBEROFPINS] = {0,1,2,3,4,5,6,7,8,9,10};

void setup() {
  //initiate pins
  for (int thisPin = 0; thisPin < NUMBEROFPINS; thisPin++) {
    pinMode(pinArray[thisPin], OUTPUT);
  }
}

void loop() {
  // loop from the lowest pin to the highest:
  for (int thisPin = 0; thisPin < NUMBEROFPINS; thisPin++) {
    // turn the led on:
    digitalWrite(pinArray[thisPin], HIGH);
    // wait for a bit
    delay(DELAYTIME);
    // turn the led off:
    digitalWrite(pinArray[thisPin], LOW);

  }
  // loop from the highest pin to the lowest:
  for (int thisPin = NUMBEROFPINS - 1; thisPin >= 0; thisPin--) {
    // turn the led on:
    digitalWrite(pinArray[thisPin], HIGH);
    // wait for a bit
    delay(DELAYTIME);
    // turn the led off:
    digitalWrite(pinArray[thisPin], LOW);
  }
}
