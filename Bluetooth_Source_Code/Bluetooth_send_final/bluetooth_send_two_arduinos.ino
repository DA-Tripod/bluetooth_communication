// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>
#include <SoftwareSerial.h>  

#define TRIGGER_PIN_1  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define TRIGGER_PIN_2  8
#define ECHO_PIN_1     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define ECHO_PIN_2     9
#define MAX_DISTANCE   200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
NewPing sonar(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
   //Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
   bluetooth.begin(9600);        // The Bluetooth Mate defaults to 115200bps
   delay(320);                     // IMPORTANT DELAY! (Minimum ~276ms)
   bluetooth.print("$$$");         // Enter command mode
   delay(100);                      // IMPORTANT DELAY! (Minimum ~10ms)
   bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
   bluetooth.println("---");
   bluetooth.begin(9600);          // Start bluetooth serial at 9600
   delay(200);
}

void loop() {                    // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  unsigned int uS_2 = sonar2.ping(); // Send ping, get ping time in microseconds (uS).
  
 // Serial.print("Ping: ");
  bluetooth.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  delay(30);
  bluetooth.print(';');
  delay(10);
  bluetooth.print(uS_2 / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  delay(30);
  bluetooth.print(';');
  delay(29);
  //Serial.print(uS / US_ROUNDTRIP_CM);
  //Serial.print("   ");
  //Serial.println(uS_2 / US_ROUNDTRIP_CM);
  //Serial.println("cm");
}
