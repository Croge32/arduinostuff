const int ledPin = 13;
const int snareSensor = A0;
const int bassSensor = A1;
const int hatSensor = A2;
const int leftTom = A3;
const int rightTom = A4;
const int crash = A5;
const int button = 12;
const int threshold = 100;  // threshold value to decide when the detected sound is a knock or not

int hiHatState = 3; // default int flag for hi hat foot switch
int aboveBass = 0;
int aboveSnare = 0;
int aboveHat = 0;
int aboveLeft = 0;
int aboveRight = 0;
int aboveCrash = 0;

int t = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);
}

void loop() {
  //Push button input for foot switch
  if (digitalRead(button) == HIGH) {
    hiHatState = 3;
    //Serial.println(hiHatState);
  } 
  else {
    hiHatState = 2;
    //Serial.println(hiHatState);
  }

  //bass drum
  if (analogRead(bassSensor) >= threshold) {
    aboveBass = 1;
    t+=4;
  }

  if (aboveBass == 1 && analogRead(bassSensor) <= threshold/2) {
    if (t < 20) {
      t = 20;
    }
    if (t > 150) {
      t = 150;
    }
    Serial.write(4);
    Serial.write(t);
    aboveBass = 0;
    t = 0;
  }

  //snare drum
  if (analogRead(snareSensor) > threshold) {
    aboveSnare = 1;
    t+=4;
  }

  if (aboveSnare == 1 && analogRead(snareSensor) < threshold/2) {
    if (t < 20) {
      t = 20;
    }
    if (t > 150) {
      t = 150;
    }
    Serial.write(1);
    Serial.write(t);
    aboveSnare = 0;
    t = 0;
  }

  //hi hat
  if (analogRead(hatSensor) > threshold) {
    aboveHat = 1;
    t+=4;
  }

  if (aboveHat == 1 && analogRead(hatSensor) < threshold/2) {
    if (t < 20) {
      t = 20;
    }
    if (t > 150) {
      t = 150;
    }
    Serial.write(0);
    Serial.write(hiHatState);
    Serial.write(t);
    aboveHat = 0;
    t = 0;
  }

  //left tom
  if (analogRead(leftTom) >= threshold) {
    aboveLeft = 1;
    t+=4;
  }

  if (aboveLeft == 1 && analogRead(leftTom) <= threshold/2) {
    if (t < 20) {
      t = 20;
    }
    if (t > 150) {
      t = 150;
    }
    Serial.write(5);
    Serial.write(t);
    aboveLeft = 0;
    t = 0;
  }

  //right tom
  if (analogRead(rightTom) >= threshold) {
    aboveRight = 1;
    t+=4;
  }

  if (aboveRight == 1 && analogRead(rightTom) <= threshold/2) {
    if (t < 20) {
      t = 20;
    }
    if (t > 150) {
      t = 150;
    }
    Serial.write(6);
    Serial.write(t);
    aboveRight = 0;
    t = 0;
  }

  //crash/other cymbal
  if (analogRead(crash) >= threshold) {
    aboveCrash = 1;
    t+=4;
  }

  if (aboveCrash == 1 && analogRead(crash) <= threshold/2) {
    if (t < 20) {
      t = 20;
    }
    if (t > 150) {
      t = 150;
    }
    Serial.write(7);
    Serial.write(t);
    aboveCrash = 0;
    t = 0;
  }
}


