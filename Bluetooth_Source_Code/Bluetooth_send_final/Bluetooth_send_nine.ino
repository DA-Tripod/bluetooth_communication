#include <SoftwareSerial.h>  

int bluetoothTx = 10;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 11;  // RX-I pin of bluetooth mate, Arduino D3

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup()
{
   //Serial.begin(9600);  // Begin the serial monitor at 9600bps
   bluetooth.begin(115200);        // The Bluetooth Mate defaults to 51300bps
   delay(330);                     // IMPORTANT DELAY! (Minimum ~276ms)
   bluetooth.print("$$$");         // Enter command mode
   delay(100);                      // IMPORTANT DELAY! (Minimum ~10ms)
   bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
   bluetooth.println("---");
   bluetooth.begin(9600);          // Start bluetooth serial at 9600
   delay(300);
}

void loop()
{
   bluetooth.print(111);
   delay(5);
   bluetooth.print('d');  //daumen
   delay(5);
   bluetooth.print(222);
   delay(5);
   bluetooth.print('h');  //hauptfinger/zeigefinger
   delay(5);
   bluetooth.print(333);
   delay(5);
   bluetooth.print('m');  //mittelfinger
   delay(5);
   bluetooth.print(444);
   delay(5);
   bluetooth.print('r');  //ringfinger
   delay(5);
   bluetooth.print(555);
   delay(5);
   bluetooth.print('k');  //kleiner finger
   delay(5);
   bluetooth.print(666);
   delay(5);
   bluetooth.print('x');  //x Koordinate (Ort)
   delay(5);
   bluetooth.print(777);
   delay(5);
   bluetooth.print('y');  //y Koordinate (Ort)
   delay(5);
   bluetooth.print(888);
   delay(5);
   bluetooth.print('z');  //z Koordinate (Ort)
   delay(5);
   bluetooth.print(999);
   delay(5);
   bluetooth.print('w');  //Winkel/Drehung der Hand
   delay(5);  
}