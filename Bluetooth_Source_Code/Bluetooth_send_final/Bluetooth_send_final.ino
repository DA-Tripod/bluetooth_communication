#include <SoftwareSerial.h>  

int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup()
{
   Serial.begin(9600);  // Begin the serial monitor at 9600bps
   bluetooth.begin(115200);        // The Bluetooth Mate defaults to 115200bps
   delay(320);                     // IMPORTANT DELAY! (Minimum ~276ms)
   bluetooth.print("$$$");         // Enter command mode
   delay(100);                      // IMPORTANT DELAY! (Minimum ~10ms)
   bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
   bluetooth.println("---");
   bluetooth.begin(9600);          // Start bluetooth serial at 9600
   delay(200);
}

void loop()
{
   int i = analogRead(0);
   bluetooth.print(i);
   delay(25);
   bluetooth.print(';');
}
