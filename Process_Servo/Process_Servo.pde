import processing.serial.*;
Serial port;
float xComponent = 0;

void setup() {
  size(1084, 230);
  port = new Serial (this, "COM22", 9600);
  port.bufferUntil('\n');
}

void draw() {
  background(100,100,100);
  
  fill(100,255,100);
  rect(30, 100, xComponent, 30);
}

void serialEvent(Serial port){
  xComponent = float (port.readStringUntil('\n'));
}
