#include <SoftwareSerial.h>  
#include <Servo.h>
#include <stdlib.h>

int bluetoothTx = 10;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 11;  // RX-I pin of bluetooth mate, Arduino D3

#define num (2)
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
Servo myservo;
Servo myservo_1;
int counter = 0;
char x[10];
int numOfFinger = 0;
int val[2];

// plug the pins TX-0 to Arduino D2 and the RX-I to Arduino D3
// before uploading the sketch make sure that the bluetooth mate isn't supplied with voltage.
// after uploading supply the bluetooth module with voltage.
// In order to get the RN-42 into CMD mode, you need to send $$$ but without any CR/LF.

void setup()
{
  myservo.attach(9);
  myservo_1.attach(8);
  Serial.begin(9600);  // Begin the serial monitor at 9600bps
  bluetooth.begin(9600);        // The Bluetooth Mate defaults to 115200bps
  delay(320);                     // IMPORTANT DELAY! (Minimum ~276ms)
  bluetooth.print("$$$");         // Enter command mode
  delay(100);                      // IMPORTANT DELAY! (Minimum ~10ms)
  bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  bluetooth.println("---");
  bluetooth.begin(9600);          // Start bluetooth serial at 9600
  delay(1000);
}

void loop()
{
  if(bluetooth.available() && counter <= 9999)  // If the bluetooth sent any characters
  {
    
    x[counter] = bluetooth.read();
    //Serial.print(x[counter]);
   //a bunch of \0s is sent at the beginning
    if(x[counter] != ';' && x[counter] != '\0'){
      counter++;
    }else if(x[counter] == '\0'){
      // do nothing
    }else{
      if(numOfFinger < 2){
        val[numOfFinger] = atoi(x);
        
      }else{
        Serial.print(val[0]);
        Serial.print('.');
        Serial.print(val[1]);
        Serial.println();
        
        numOfFinger = 0;
        val[numOfFinger] = atoi(x);
      }
 
      for(int i = 0; i < 10; i++){
        x[i] = 0;
      }
      counter = 0;
      numOfFinger++;
    }   
    //myservo.write(val[0]);
    //myservo_1.write(val[1]);
  }
}
