/*

Cody Rogers, CSC 2700

Simon Says type game with some analog sensors in addition to typical buttons. Such analog. Much voltage. Wow.

*/

// Pins for all LEDS
const int LEFT_LED = 10;
const int RIGHT_LED = 9;
const int TOP_LED = 7;
const int BOTTOM_LED = 8;
const int GOAL = 13;

// Pin for piezo buzzer and note frequencies in hertz of tones used.
const int BUZZER = 11;
const int D = 294;
const int E = 330;
const int F = 349;
const int G = 392;
const int HIGH_D = 588;
const int HIGH_E = 660;
const int HIGH_F = 698;
const int HIGH_G = 784;
const int FIZZ = 297;
const int BUZZ = 303;

// Pins for input components
const int TOP_BUTTON = 2;
const int BOTTOM_BUTTON = 4;
const int FSR = A0;
const int POT = A1;

// Constants are used to divide the analog voltage in order to be more compatible with the maximum LED value of 255.
// Triggers are thresholds for activation
const int FSR_CONSTANT = 2.22;
const int FSR_TRIGGER = 150;
const int POT_CONSTANT = 4.0117647059;
const int POT_TRIGGER = 90;

// Fields
int simonFlag = 0;
int fsr = 0;
int pot = 0;
int topState = 0;
int bottomState = 0;
int inputsMatched = -1;
String patternString = "";
String inputString = "";

// Set all pin modes and generate a random seed to make the game interesting
void setup()  { 
  pinMode(LEFT_LED, OUTPUT);
  pinMode(RIGHT_LED, OUTPUT);
  pinMode(TOP_LED, OUTPUT);
  pinMode(BOTTOM_LED, OUTPUT);
  pinMode(GOAL, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(TOP_BUTTON, INPUT);
  pinMode(BOTTOM_BUTTON, INPUT);
  randomSeed(analogRead(A4));  
} 

void loop()  {

  // If game is just beginning or pattern has been matched, Simon Says...
  if (simonFlag == 0) {
    simonSays();
    simonFlag = 1;
  }
  
  //Reading from sensors, doing necessary arithmetic, writing to LEDs...
  fsr = analogRead(FSR);
  pot = analogRead(POT);
  topState = digitalRead(TOP_BUTTON);
  bottomState = digitalRead(BOTTOM_BUTTON);
  fsr = (fsr / FSR_CONSTANT);
  pot = (pot / POT_CONSTANT);
  analogWrite(LEFT_LED, fsr);
  analogWrite(RIGHT_LED, pot); 

  // This is reversed, oddly. Initially, LEDs were lit until button was pressed. DON'T CARE IT WORKS NOW LOLOLOLOL
  // ...Ahem, if button(s) pressed, write to corresponding LED(s)
  if (topState == LOW) {   
    digitalWrite(TOP_LED, HIGH);
  }
  else {
    digitalWrite(TOP_LED, LOW);
  }

  if (bottomState == LOW) {   
    digitalWrite(BOTTOM_LED, HIGH);
  } 
  else {
    digitalWrite(BOTTOM_LED, LOW);
  }

  // For the sake of not rushing things. Life's too short, you know?
  delay(50);


  // Listen for sensors and buttons.
  // If sensors are above threshold OR buttons are activated...
  // Signal that it was triggered, increment input matched field, compare to established pattern
  if (fsr > FSR_TRIGGER) {
    triggerFSR();
    inputsMatched += 2;
    compareToPattern();
  }
  if (topState == LOW) {
    triggerTopButton();
    inputsMatched += 2;
    compareToPattern();
  }
  if (pot > POT_TRIGGER) {
    triggerPot();
    inputsMatched += 2;
    compareToPattern();
  }
  if (bottomState == LOW) {
    triggerBottomButton();
    inputsMatched += 2;
    compareToPattern();
  }
}

// Main game logic
void simonSays() {
  
  // Initialize a random number between 0 and 3
  int ref = random(4);
  
  // Append this number to pattern string plus a space. In retrospect, the space was a stupid idea and complicated things.
  patternString = patternString + ref+" ";

  // Iterate through the pattern, increment by each number PLUS the space that follows it
  // 0 corresponds to left, 1 to top, 2 to right, 3 to bottom. The directional methods are Simon lighting the LEDs
  for (int i=0; i<patternString.length(); i += 2) {
    if (patternString.substring(i, i+1) == "0") {
      left();
    }
    else if (patternString.substring(i, i+1) == "1") {
      top();
    } 
    else if (patternString.substring(i, i+1) == "2") {
      right();
    } 
    else if (patternString.substring(i, i+1) == "3") {
      bottom();
    }
  }
}

// Compare input vs pattern
void compareToPattern() {
  // If the input and pattern totally match, turn off active LEDs, reset fields, LIGHT YOUR BEACON OF VICTORY, and return to loop
  if (patternString.equals(inputString)) {
    turnOffLeds();
    inputString = "";
    inputsMatched = -1;
    beaconOfVictory();
    simonFlag = 0;
    return;
  }

  // If the input is a substring of the pattern... Nothing happens anymore. I did some logging here initially.
  if ((patternString.substring(0, inputsMatched))+" " == inputString) {} 
  
  // Reset fields and return to loop while Simon mocks you
  else {
    FAILURELOL();
    inputString = "";
    patternString = "";
    inputsMatched = -1;
    simonFlag = 0;
    return;
  }
}

// Light left LED, activate piezo
void left() {
  tone(BUZZER, G, 1000);
  
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=15) { 
    // sets the value (range from 0 to 255)
    analogWrite(LEFT_LED, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);                            
  } 

  // fade out from max to min in increments of 5 points:
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=15) { 
    // sets the value (range from 0 to 255)
    analogWrite(LEFT_LED, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);
  }  
}

// Light right LED, activate piezo
void right() {
  tone(BUZZER, E, 1000);
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=15) { 
    // sets the value (range from 0 to 255)
    analogWrite(RIGHT_LED, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);                            
  } 

  // fade out from max to min in increments of 5 points:
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=15) { 
    // sets the value (range from 0 to 255)
    analogWrite(RIGHT_LED, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);
  }
}

// Top, piezo
void top() {
  tone(BUZZER, D, 1000);
  digitalWrite(TOP_LED, HIGH);
  delay(700);
  digitalWrite(TOP_LED, LOW);
  delay(300);
}

// You get the idea
void bottom() {
  tone(BUZZER, F, 1000);
  digitalWrite(BOTTOM_LED, HIGH);
  delay(700);
  digitalWrite(BOTTOM_LED, LOW);
  delay(300);
}

// Method activated when fsr threshold reached. Increments input string with left corresponding number and buzzes piezo
void triggerFSR() {
  tone(BUZZER, HIGH_G, 1000);
  delay(1000);
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=15) { 
    // sets the value (range from 0 to 255)
    analogWrite(LEFT_LED, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);
  }
  inputString = inputString+"0 ";
}

// Method activated when pot threshold reached. Increments input string with right corresponding number and buzzes piezo
void triggerPot() {
  tone(BUZZER, HIGH_E, 1000);
  delay(1000);
  for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=15) { 
    // sets the value (range from 0 to 255):
    analogWrite(RIGHT_LED, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);
  }
  inputString = inputString+"2 ";
}

// Method for top button, increments input string
void triggerTopButton() {
  tone(BUZZER, HIGH_D, 1000);
  inputString = inputString+"1 ";
  delay(1000);
}

// Method for bottom button, increments input string
void triggerBottomButton() {
  tone(BUZZER, HIGH_F, 1000);
  Serial.println("BOTTOM TRIGGERED");
  inputString = inputString+"3 ";
  Serial.print(inputString);
  Serial.println(" input string");
  delay(1000);
}

// Turn off any stray LEDs
void turnOffLeds() {
  digitalWrite(LEFT_LED, LOW);
  digitalWrite(TOP_LED, LOW); 
  digitalWrite(RIGHT_LED, LOW); 
  digitalWrite(BOTTOM_LED, LOW);
  delay(1000); 
}

// BATHE IN GLORY
void beaconOfVictory() {
  digitalWrite(GOAL, HIGH);
  victoryScreeeeeech();
  delay(2000);
  digitalWrite(GOAL, LOW);
  delay(1000);
}

// https://www.youtube.com/watch?v=MdN0NXgjsn8
void victoryScreeeeeech() {
  tone(BUZZER, D, 100);
  delay(100);
  tone(BUZZER, E, 100);
  delay(100);
  tone(BUZZER, F, 100); 
  delay(100);
  tone(BUZZER, G, 100); 
  delay(100);
  tone(BUZZER, D, 100);
  delay(100);
  tone(BUZZER, E, 100);
  delay(100);
  tone(BUZZER, F, 100); 
  delay(100);
  tone(BUZZER, G, 100);
  delay(100);
  tone(BUZZER, G, 100);
  delay(100); 
  tone(BUZZER, D, 100);
  delay(100);
  tone(BUZZER, E, 100);
  delay(100); 
  tone(BUZZER, G, 100);
  delay(100); 
  tone(BUZZER, D, 300); 
 
}

// HAHA YOU MESSED UP
void FAILURELOL() {
  for (int i=0; i<15; i++) {
    digitalWrite(LEFT_LED, HIGH);
    digitalWrite(TOP_LED, HIGH); 
    digitalWrite(RIGHT_LED, HIGH); 
    digitalWrite(BOTTOM_LED, HIGH);
    tone(BUZZER, FIZZ, 20);
    delay(30);
    digitalWrite(LEFT_LED, LOW);
    digitalWrite(TOP_LED, LOW); 
    digitalWrite(RIGHT_LED, LOW); 
    digitalWrite(BOTTOM_LED, LOW);
    tone(BUZZER, BUZZ, 20);
    delay(30);
  }
  delay(2000);
}



