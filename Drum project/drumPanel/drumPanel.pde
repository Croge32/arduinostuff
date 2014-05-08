import oscP5.*;
import netP5.*;

OscP5 oscP5;
NetAddress myRemoteLocation;
int drum = 0;
int power = 0;
int a = 0;
int b = 0;
int reached = 0;
int varietyFarm;

void setup() {
  size(800, 600);
  ellipseMode(CENTER);
  noStroke();
  oscP5 = new OscP5(this, 9001);
  myRemoteLocation = new NetAddress("127.0.0.1", 9001);
  
}

void draw() {
  
  if (varietyFarm == 0) {
    varietyFarm = (int)random(3)+1;
  }
  
  if (varietyFarm == 1) {
  
    if (power != 0) {
      background(power-a, 255-drum*3+a, (power*1.5)+30);
      fill(power, power/2, (int)random(power));
      ellipse(power*2+(drum*3)+random(250), (power/(drum+5))+random(500), a, a);
      fill(power/2, (int)random(power), power);
      triangle((int)random(800), (int)random(600), (int)random(800), (int)random(600), (int)random(800), (int)random(600));
      if (reached == 0) {
        a = a + drum*15;     
      } else {
        a = a - drum*6;
      }
      if (a > power) {
        reached = 1;
      }
      if (a <= 0 && reached == 1) {
        reached = 0;
        power = 0;
        varietyFarm = 0;
      }
    }
  
  } else if (varietyFarm == 2) {
    if (power != 0) {
      background(power+100, a, (drum*6)+(power/3));
      fill(a, power, (int)random(a*2));
      ellipse(random(600), power+random(500), drum*26, drum*26);
      if (reached == 0) {
        a = a + drum*4;     
      } else {
        a = a - drum*7;
      }
      if (a > power) {
        reached = 1;
      }
      if (a <= 0 && reached == 1) {
        reached = 0;
        power = 0;
        varietyFarm = 0;
      }
    }
  } else if (varietyFarm == 3) {
    if (power != 0) {
      background(120+a, power-a+30, a+90);
      fill((int)random(a+power), a, (int)random(a*2));
      ellipse(600-power, power+random(500), a*2, a*2);
      if (reached == 0) {
        a = a + drum*4;     
      } else {
        a = a - drum*7;
      }
      if (a > power) {
        reached = 1;
      }
      if (a <= 0 && reached == 1) {
        reached = 0;
        power = 0;
        varietyFarm = 0;
      }
    }
  }
  println(varietyFarm);
}

void mousePressed() {  
  println(mouseX+" mouse X");
  println(mouseY+" mouse Y");
  
//  if (mouseX > 10 && mouseX < 110 && mouseY > 10 && mouseY < 30) {
//    println("one");
//    OscMessage myMessage = new OscMessage("/one");
//    myMessage.add(1);
//    oscP5.send(myMessage, myRemoteLocation);
//  }
//  else if (mouseX > 10 && mouseX < 110 && mouseY > 40 && mouseY < 60) {
//    println("two");
//    OscMessage myMessage = new OscMessage("/two");
//    myMessage.add(2);
//    oscP5.send(myMessage, myRemoteLocation);
//  }
//  else if (mouseX > 10 && mouseX < 110 && mouseY > 70 && mouseY < 90) {
//    println("three");
//    OscMessage myMessage = new OscMessage("/three");
//    myMessage.add(3);
//    oscP5.send(myMessage, myRemoteLocation);
//  }
//  else if (mouseX > 10 && mouseX < 110 && mouseY > 100 && mouseY < 120) {
//    println("four");
//    OscMessage myMessage = new OscMessage("/four");
//    myMessage.add(4);
//    oscP5.send(myMessage, myRemoteLocation);
//  }
//  else {
//    println("other");
//    OscMessage myMessage = new OscMessage("/other");
//    oscP5.send(myMessage, myRemoteLocation);
//  }
}

void oscEvent(OscMessage theOscMessage) 
{ 
  
  if (theOscMessage.addrPattern().equals("/drum")) {
    drum = theOscMessage.get(0).intValue();
  } else if (theOscMessage.addrPattern().equals("/power")) {
    power = theOscMessage.get(0).intValue();
  }
  // print out the message
  //print("OSC Message Recieved: ");
  println(theOscMessage.addrPattern() + " ");
  
}
 
