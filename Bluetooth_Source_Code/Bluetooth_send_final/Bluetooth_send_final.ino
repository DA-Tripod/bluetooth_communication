#include <SoftwareSerial.h>  

int bluetoothTx = 10;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 11;  // RX-I pin of bluetooth mate, Arduino D3
char sendThis;

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
 //bluetooth.print("$$$");
 delay(200);
 //bluetooth.println("SM,3");
 //bluetooth.println("CFR");
 /*bluetooth.println("SM,1");
 bluetooth.println("C,000666605063");
 bluetooth.print("1");
 */
}

void loop()
{ 
 if(bluetooth.available())  // If the bluetooth sent any characters
 {
   // Send any characters the bluetooth prints to the serial monitor
   Serial.print((char)bluetooth.read());  
 }
 if(Serial.available())  // If stuff was typed in the serial monitor
 {
   // Send any characters the Serial monitor prints to the bluetooth
   
 } 
 int i = analogRead(0);
 bluetooth.print(i);
 bluetooth.print(';');
 // and loop forever and ever!
 delay(25);
}
