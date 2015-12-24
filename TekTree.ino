/*
  Rick van Lieshout 
  24-12-2015
  LICENSE: MIT
*/

/** Constant value's, these have to be changed manually  **/
const int MAXSEQUENCES= 20;     // number of steps in the largest sequence. Could make it 999 but that would affect performance
const int NUMBEROFPINS = 11;    // number of leds
const int NUMBEROFPATTERNS = 5; // number of patterns specified
const int DELAYPOT = 0;         // number of pin that pot is connected to
const int BUTTONPIN = 12;       // number of pin that button is connected to
const int pinArray[NUMBEROFPINS] = {0,1,2,3,4,5,6,7,8,9,10}; // pins where leds are connected

/** Regular variables, program can alter these **/
int previousbuttonstate = 0;  // used to detect whether button is pressed
int buttonstate = 0;          // used to detect whether button is pressed
int pattern = 0;              // pattern to start with

/** massive array which holds the patterns **/
const byte LEDsequence [NUMBEROFPATTERNS][MAXSEQUENCES][NUMBEROFPINS] = {
  {
  {0,0,0,0,0,0,0,0,0,0,0},
  },
  {
  {1,1,1,1,1,1,1,1,1,1,1},
  },
  {
  {1,0,0,0,0,0,0,0,0,0,1},
  {0,1,0,0,0,0,0,0,0,0,1},
  {0,0,1,0,0,0,0,0,0,0,1},
  {0,0,0,1,0,0,0,0,0,0,1},
  {0,0,0,0,1,0,0,0,0,0,1},
  {0,0,0,0,0,1,0,0,0,0,1},
  {0,0,0,0,0,0,1,0,0,0,1},
  {0,0,0,0,0,0,0,1,0,0,1},
  {0,0,0,0,0,0,0,0,1,0,1},
  {0,0,0,0,0,0,0,0,0,1,1}
  },
  {
  {1,0,0,0,0,0,0,0,0,0,1},
  {0,1,0,0,0,0,0,0,0,0,1},
  {0,0,1,0,0,0,0,0,0,0,1},
  {0,0,0,1,0,0,0,0,0,0,1},
  {0,0,0,0,1,0,0,0,0,0,1},
  {0,0,0,0,0,1,0,0,0,0,1},
  {0,0,0,0,0,0,1,0,0,0,1},
  {0,0,0,0,0,0,0,1,0,0,1},
  {0,0,0,0,0,0,0,0,1,0,1},
  {0,0,0,0,0,0,0,0,0,1,1},
  {0,0,0,0,0,0,0,0,1,0,1},
  {0,0,0,0,0,0,0,1,0,0,1},
  {0,0,0,0,0,0,1,0,0,0,1},
  {0,0,0,0,0,1,0,0,0,0,1},
  {0,0,0,0,1,0,0,0,0,0,1},
  {0,0,0,1,0,0,0,0,0,0,1},
  {0,0,1,0,0,0,0,0,0,0,1},
  {0,1,0,0,0,0,0,0,0,0,1}
  },
  {
  {1,0,0,0,0,0,0,0,0,1,1},
  {0,1,0,0,0,0,0,0,1,0,1},
  {0,0,1,0,0,0,0,1,0,0,1},
  {0,0,0,1,0,0,1,0,0,0,1},
  {0,0,0,0,1,1,0,0,0,0,1},
  {0,0,0,1,0,0,1,0,0,0,1},
  {0,0,1,0,0,0,0,1,0,0,1},
  {0,1,0,0,0,0,0,0,1,0,1},
  {1,0,0,0,0,0,0,0,0,1,1}
  }
};

/** Setup only gets run once **/
void setup(){
  //set all pins as input/output
  initializePins();
}

/** Loop is constantly running **/
void loop() {
  // read button state
  buttonstate = digitalRead(BUTTONPIN);
  // if button state changed
  if(buttonstate != previousbuttonstate){
    previousbuttonstate = buttonstate; 
     // check value and add to pattern
     if(buttonstate == HIGH){
      if(pattern +1 == NUMBEROFPATTERNS){
        pattern = 0;
      }else{
        pattern++;
      }
     }
  }

  // Loop through all the arrays and toggle pins on or off.
  for (int sequence=0;sequence<getSequences(pattern);sequence++) {
    for (int pin=0;pin<NUMBEROFPINS;pin++) {
      digitalWrite(pinArray[pin], LEDsequence[pattern][sequence][pin]);
    }  
    // delay between sequences, should use millis if you want instant response on the button
    delay(getDelay(DELAYPOT));
  }
}

/** Count the number of sequences in a specific pattern **/
int getSequences(int pattern){
  byte amount = 0;
  for(byte i = 0; i<MAXSEQUENCES; i++){
    int total = 0;
    for(int pin=0; pin<NUMBEROFPINS; pin++){
      total+=LEDsequence[pattern][i][pin];  
    }
    if(total>0){
      amount++;
    }
  }
  return amount;
}

/** get value of pot **/
int getDelay(int potnr){
  return analogRead(potnr);
}

/** Set all pins as either output or input **/
void initializePins(){
  pinMode(BUTTONPIN, INPUT);
  for (int pin=0;pin<NUMBEROFPINS;pin++) {
    pinMode(pinArray[pin], OUTPUT);     // we make all the declarations at once 
  }
}

