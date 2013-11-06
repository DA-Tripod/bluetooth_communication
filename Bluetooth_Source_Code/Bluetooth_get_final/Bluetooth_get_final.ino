#include <SoftwareSerial.h>  
#include <Servo.h>
#include <stdlib.h>
//#include <string.h>

int bluetoothTx = 10;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 11;  // RX-I pin of bluetooth mate, Arduino D3

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
Servo myservo;
int counter = 0;
char x[4];
//String test;
//char sz[] = "hallo";

// plug the pins TX-0 to Arduino D2 and the RX-I to Arduino D3
// before uploading the sketch make sure that the bluetooth mate isn't supplied with voltage.
// after uploading supply the bluetooth module with voltage.
// In order to get the RN-42 into CMD mode, you need to send $$$ but without any CR/LF.

void setup()
{
  myservo.attach(9);
  Serial.begin(9600);  // Begin the serial monitor at 9600bps
  bluetooth.begin(115200);        // The Bluetooth Mate defaults to 115200bps
  delay(320);                     // IMPORTANT DELAY! (Minimum ~276ms)
  bluetooth.print("$$$");         // Enter command mode
  delay(100);                      // IMPORTANT DELAY! (Minimum ~10ms)
  bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  bluetooth.println("---");
  bluetooth.begin(9600);          // Start bluetooth serial at 9600
  /*bluetooth.print("$$$");
  delay(100);
  bluetooth.println("SM,0");*/ 
}

void loop()
{
  Serial.println(bluetooth.read());
  /*int n = 0;
  
 // if(bluetooth.available()){
    n = bluetooth.read();
    if(n == 59){
       Serial.println();
    }else{  
      n = n*4;
      if(n < 1024 && n >= 0){
        Serial.print(n);
        myservo.write(map(n, 0, 1024, 0, 179));
     } 
  }
  */
  if(bluetooth.available() && counter <= 9999)  // If the bluetooth sent any characters
  {
    
    x[counter] = bluetooth.read();
    if(x[counter] != ';'){
      counter++;
    }else{
      int n;
      n = atoi(x);
      Serial.println();
      Serial.print(n);
      
      if(n < 1024 && n >= 0){
        myservo.write(map(n, 0, 1024, 0, 179));
      }
      for(int i = 0; i < 4; i++){
        x[i] = 0;
      }
      counter = 0;
    }    
  }
  
  if(Serial.available())  // If stuff was typed in the serial monitor
  {
    // Send any characters the Serial monitor prints to the bluetooth
    bluetooth.print((char)Serial.read());
  }
  // and loop forever and ever!
  
  //delay(100);
  
 /* if(bluetooth.available()){
    Serial.println((char)bluetooth.read());
  }*/
  
  if(bluetooth.available()){
    temp = (char)bluetooth.read(); 
    
    if(temp != ';'){
      Serial.print(temp)
    }else{
      Serial.println();
    }
  }
}
