import oscP5.*;
import netP5.*;

OscP5 oscP5;
NetAddress myRemoteLocation;

void setup() {
  size(800, 600);
  
  oscP5 = new OscP5(this, 9001);
  myRemoteLocation = new NetAddress("127.0.0.1", 9001);
  
}

void draw() {
  textSize(28);
  fill(0);
  text("Change Snare", 10, 30);
  
  textSize(28);
  text("Change Hi-Hat (Closed)", 10, 60);
  
  textSize(28);
  text("Change Hi-Hat (Open)", 10, 90);
  
  textSize(28);
  text("Change Hi-Hat (Foot)", 10, 120);
  
  textSize(28);
  text("Change Bass Drum", 10, 150);
  
  textSize(28);
  text("Change Left Tom", 10, 180);
  
  textSize(28);
  text("Change Right Tom", 10, 210);
  
  textSize(28);
  text("Change Desk Tom", 10, 240);
  
  textSize(28);
  text("Change Left Cymbal", 10, 270);
  
  textSize(28);
  text("Change Middle Cymbal", 10, 300);
  
  textSize(28);
  text("Change Right Cymbal", 10, 330);
}

void mousePressed() {  
  println(mouseX+" mouse X");
  println(mouseY+" mouse Y");
  
  if (mouseX > 10 && mouseX < 110 && mouseY > 10 && mouseY < 30) {
    println("one");
    OscMessage myMessage = new OscMessage("/one");
    myMessage.add(1);
    oscP5.send(myMessage, myRemoteLocation);
  }
  else if (mouseX > 10 && mouseX < 110 && mouseY > 40 && mouseY < 60) {
    println("two");
    OscMessage myMessage = new OscMessage("/two");
    myMessage.add(2);
    oscP5.send(myMessage, myRemoteLocation);
  }
  else if (mouseX > 10 && mouseX < 110 && mouseY > 70 && mouseY < 90) {
    println("three");
    OscMessage myMessage = new OscMessage("/three");
    myMessage.add(3);
    oscP5.send(myMessage, myRemoteLocation);
  }
  else if (mouseX > 10 && mouseX < 110 && mouseY > 100 && mouseY < 120) {
    println("four");
    OscMessage myMessage = new OscMessage("/four");
    myMessage.add(4);
    oscP5.send(myMessage, myRemoteLocation);
  }
  else {
     println("other");
    OscMessage myMessage = new OscMessage("/other");
    oscP5.send(myMessage, myRemoteLocation);
  }
}
