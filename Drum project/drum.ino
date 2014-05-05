
const int ledPin = 13;      // led connected to digital pin 13
const int snareSensor = A0;
const int fsr = A2;
const int bassSensor = A3;
const int hatSensor = A5;
const int threshold = 75;  // threshold value to decide when the detected sound is a knock or not
const int hiHatClosed = 120; // fsr threshold for hi hat foot switch

int hiHatState = 3; // default int flag for hi hat foot switch

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //Detects if FSR that determines hi hat open or closed is pressed
  if (map(analogRead(fsr), 0, 1023, 0, 255) > hiHatClosed) {
    hiHatState = 2;
  } 
  else {
    hiHatState = 3;
  }
  
  //Snare drum logic. t is time spent over threshhold. Delays by that amount. t is also volume of hit sent to Pd.
  if (analogRead(snareSensor) >= threshold) {
    int t=0;
    while (analogRead(snareSensor) >= threshold) {
      t++;
    }
    //limit volume to 120
    if (t > 120) {
      t=120;
    }
    //t always greater than 15
    if (t < 15) {
      t=15;
    }
    
    //1 is flag for detecting snare hit in Pd.
    Serial.write(1);
    Serial.write(t);

    //never delay more than 50 ms
    if (t>50) {
      delay(50);
    }
    else {
      delay(t);
    }
  }

  //hi hat logic. Same as snare except hi hat state is also included in Serial.write()
  if (analogRead(hatSensor) >= threshold) {
    int t=0;  
    while (analogRead(hatSensor) >= threshold) {
      t++;
    }
    if (t > 120) {
      t=120;
    }
    if (t < 15) {
      t=15;
    }
    
    //flag in Pd for hihat is 0.
    Serial.write(0);
    Serial.write(hiHatState);
    Serial.write(t);

    if (t>50) {
      delay(50);
    }
    else {
      delay(t);
    }
  }
  
  //Same logic as snare.
  if (analogRead(bassSensor) >= threshold) {
    int t=0;  
    while (analogRead(bassSensor) >= threshold) {
      t++;
    }
    if (t > 120) {
      t=120;
    }
    if (t < 15) {
      t=15;
    }
    
    //flag for bass drum in Pd is 4.
    Serial.write(4);
    Serial.write(t);

    if (t>50) {
      delay(50);
    }
    else {
      delay(t);
    }
  }
}



