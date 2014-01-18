import processing.serial.*;

Position pos;
Robot robot;
SlideControl velocity;
SerialState ser;

String useSerialPort = "COM17";

void setup() {
  size(800, 600);
  smooth();
  pos = new Position(180, 180, 610, 10);
  robot = new Robot(400, 300, 100);
  velocity = new SlideControl(0, 255, 100);
  velocity.position = new Rectangle(10, 10, 20, 50);
  ser = new SerialState(this, useSerialPort);
  
  frameRate(5);
}

void serialEvent(Serial p) {
  ser.serialEvent(p);
}

void draw() {
  noFill();
  background(0);
  pos.display();
  robot.display();
  velocity.display();
}

void keyPressed() {
  if (key == 'w' || key == 'a' || key == 'd' || key == 's' || key == 'r' || key == 't' || key == 'g' || key == 'i' || key =='k') {
    ser.write(key);
  } else {
    print("Unsupported key: ");
    println((int)key);
  }
}
