#include <SoftwareSerial.h>  
#include <Servo.h>
#include <stdlib.h>

int bluetoothTx = 10;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 11;  // RX-I pin of bluetooth mate, Arduino D3

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
Servo myservo;
int counter = 0;
char x[4];

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
  delay(1000);
}

void loop()
{  
  if(bluetooth.available() && counter <= 9999)  // If the bluetooth sent any characters
  {
    // falls nicht funktioniert -> "Serial.println("Hallo");
    x[counter] = bluetooth.read();
   
   //a bunch of \0s is sent at the beginning
   
    if(x[counter] != ';' && x[counter] != '\0'){
      counter++;
    }else if(x[counter] == '\0'){
    }else{
      int n;
      n = atoi(x);
      Serial.println(n);
      
      if(n < 1024 && n >= 0){
        myservo.write(map(n, 0, 1023, 0, 179));
      }
      
      for(int i = 0; i < 4; i++){
        x[i] = 0;
      }
      counter = 0;
    }   
  }
}
