import processing.serial.*;
Serial port;
float xComponent = 0;
float yComponent = 0;

void setup() {
  size(1000, 1000);
  port = new Serial (this, "COM22", 9600);
  port.bufferUntil('\n');
}

void draw() {
  background(255,255,255);
  //translate (xComponent, xComponent, xComponent);
  int x = 10;
  int y = 10;
  int size = 20;
  
  fill(255,255,255);
  
  for(int i = 0; i < 49; i++){
    for(int k = 0; k < 49; k++){
      rect(x, y, size, size);
      x += size;
    }
    x = 10;
    y += size;
  }
  
  //xComponent ... 0 - 1000
   
  fill(0,0,0);
 
  rect(x+size*xComponent, 49*size-10-yComponent*size, size, size);
  //rect();
  //ellipse(xComponent, (1000-xComponent), 30, 30);
  //line (10, 980, 10, 50);
  //line (10, 980, 960, 980);
}

void serialEvent(Serial port){
  yComponent = float (port.readStringUntil('.'));
  xComponent = float (port.readStringUntil('\n'));
}
