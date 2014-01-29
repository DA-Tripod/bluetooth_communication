#include <SoftwareSerial.h>

// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define TRIGGER_PIN_1  5  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_1     4  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN_2  7  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_2     6  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN_3  9  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_3     8  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar_1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar_2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar_3(TRIGGER_PIN_3, ECHO_PIN_3, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D10
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D11

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup() {
   Serial.begin(9600);
   bluetooth.begin(115200);        // The Bluetooth Mate defaults to 115200bps
   delay(320);                     // IMPORTANT DELAY! (Minimum ~276ms)
   bluetooth.print("$$$");         // Enter command mode
   delay(100);                      // IMPORTANT DELAY! (Minimum ~10ms)
   bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
   bluetooth.println("---");
   bluetooth.begin(9600);          // Start bluetooth serial at 9600
   delay(200);
}

void loop() {   
  delay(50);
  // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar_1.ping(); // Send ping, get ping time in microseconds (uS).
  unsigned int uS_2 = sonar_2.ping(); // Send ping, get ping time in microseconds (uS).
  unsigned int uS_3 = sonar_3.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print(uS_2 / US_ROUNDTRIP_CM);
  Serial.print(".");
  bluetooth.print(uS_2 / US_ROUNDTRIP_CM);
  delay(20);
  bluetooth.print(";");
  delay(20);
  Serial.print(uS_3 / US_ROUNDTRIP_CM);
  Serial.print(".");
  bluetooth.print(uS_3 / US_ROUNDTRIP_CM);
  delay(20);
  bluetooth.print(";");
  delay(20);
  Serial.print(uS / US_ROUNDTRIP_CM);
  Serial.println("");
  bluetooth.print(uS / US_ROUNDTRIP_CM);
  delay(20);
  bluetooth.print(";");
  delay(20);
 }
