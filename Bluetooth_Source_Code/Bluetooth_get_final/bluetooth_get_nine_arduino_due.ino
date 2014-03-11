#include <SoftwareSerial.h>
#include <stdlib.h>

int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3

#define num (9)
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
int counter = 0;
char x[10];
int numOfFinger = 0;
int val[num];

// plug the pins TX-0 to Arduino D2 and the RX-I to Arduino D3
// before uploading the sketch make sure that the bluetooth mate isn't supplied with voltage.
// after uploading supply the bluetooth module with voltage.
// In order to get the RN-42 into CMD mode, you need to send $$$ but without any CR/LF.

void setup()
{
  Serial.begin(9600);  // Begin the serial monitor at 9600bps
  bluetooth.begin(115200);        // The Bluetooth Mate defaults to 115200bps
  delay(320);                     // IMPORTANT DELAY! (Minimum ~276ms)
  bluetooth.print("$$$");         // Enter command mode
  delay(120);                      // IMPORTANT DELAY! (Minimum ~10ms)
  bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  delay(120);
  bluetooth.println("---");
  bluetooth.begin(9600);          // Start bluetooth serial at 9600
  delay(1000);
}

void loop()
{
  //Serial.println("NEIN");
  if(bluetooth.available() && counter <= 9999)  // If the bluetooth sent any characters
  {
    //Serial.println("Hallo");
    x[counter] = bluetooth.read();
    //Serial.print(x[counter]);
    //a bunch of \0s is sent at the beginning
    // d...Daumen, h...Hauptfinger, m...Mittelfinger, r...Ringfinger, k...kleiner Finger, x...X-Position, y...Y-Position, z...Z-Position, w...Winkellage
    if(x[counter] != 'd' && x[counter] != 'h' && x[counter] != 'm' && x[counter] != 'r' && x[counter] != 'k' && x[counter] != 'x' && x[counter] != 'y' && x[counter] != 'z' && x[counter] != 'w' && x[counter] != '\0'){
      counter++;
    }else if(x[counter] == '\0'){
      // do nothing
      Serial.println("Nothing");
    }else if(x[counter] == 'd'){
      val[0] = atoi(x);
      Serial.print(val[0]);
      Serial.print('.');
      for(int i = 0; i < 10; i++){
        x[i] = 0;
      }
      counter=0;
    }else if(x[counter] == 'h'){
      val[1] = atoi(x);
      Serial.print(val[1]);
      Serial.print('.');
      for(int i = 0; i < 10; i++){
        x[i] = 0;
      }
      counter=0;
    }else if(x[counter] == 'm'){
      val[2] = atoi(x);
      Serial.print(val[2]);
      Serial.print('.');
      for(int i = 0; i < 10; i++){
        x[i] = 0;
      }
      counter=0;
    }else if(x[counter] == 'r'){
      val[3] = atoi(x);
      Serial.print(val[3]);
      Serial.print('.');
      for(int i = 0; i < 10; i++){
        x[i] = 0;
      }
      counter=0;
    }else if(x[counter] == 'k'){
      val[4] = atoi(x);
      Serial.print(val[4]);
      Serial.print('.');
      for(int i = 0; i < 10; i++){
        x[i] = 0;
      }
      counter=0;
    }else if(x[counter] == 'x'){
      val[5] = atoi(x);
      Serial.print(val[5]);
      Serial.print('.');
      for(int i = 0; i < 10; i++){
        x[i] = 0;
      }
      counter=0;
    }else if(x[counter] == 'y'){
      val[6] = atoi(x);
      Serial.print(val[6]);
      Serial.print('.');
      for(int i = 0; i < 10; i++){
        x[i] = 0;
      }
      counter=0;
    }else if(x[counter] == 'z'){
      val[7] = atoi(x);
      Serial.print(val[7]);
      Serial.print('.');
      for(int i = 0; i < 10; i++){
        x[i] = 0;
      }
      counter=0;
    }else if(x[counter] == 'w'){
      val[8] = atoi(x);
      Serial.print(val[8]);
      Serial.println("");
      for(int i = 0; i < 10; i++){
        x[i] = 0;
      }
      counter=0;
    }
  }
}
