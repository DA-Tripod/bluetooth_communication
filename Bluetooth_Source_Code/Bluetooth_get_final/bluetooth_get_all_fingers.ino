#include <SoftwareSerial.h>  
#include <Servo.h>
#include <stdlib.h>

#define bluetoothTx = 10  // TX-O pin of bluetooth mate, Arduino D10 (~PWM)
#define bluetoothRx = 11  // RX-I pin of bluetooth mate, Arduino D11 (~PWM)

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

Servo myservo_1;
Servo myservo_2;
Servo myservo_3;
Servo myservo_4;
Servo myservo_5;

int counter = 0;
char x[5];
int result_1;
int result_2;
int numOfFinger = 1;
int val[5];

// plug the pins TX-0 to Arduino D2 and the RX-I to Arduino D3
// before uploading the sketch make sure that the bluetooth mate isn't supplied with voltage.
// after uploading supply the bluetooth module with voltage.
// In order to get the RN-42 into CMD mode, you need to send $$$ but without any CR/LF.

void setup()
{
	myservo_1.attach(9);
	myservo_2.attach(8);
	myservo_3.attach(7);
	myservo_4.attach(6);
	myservo_5.attach(5);
	Serial.begin(9600);                                // Begin the serial monitor at 9600bps
	bluetooth.begin(115200);        // The Bluetooth Mate defaults to 115200bps
	delay(320);                     // IMPORTANT DELAY! (Minimum ~276ms)
	bluetooth.print("$$$");         // Enter command mode
	delay(100);                                                // IMPORTANT DELAY! (Minimum ~10ms)
	bluetooth.println("U,9600,N");        // Temporarily Change the baudrate to 9600, no parity
	bluetooth.println("---");
	bluetooth.begin(9600);                        // Start bluetooth serial at 9600
	delay(1000);
}

void loop()
{
	if (bluetooth.available() && counter <= 9999)  // If the bluetooth sent any characters
	{
		x[counter] = bluetooth.read();

		//a bunch of \0s is sent at the beginning
		if (x[counter] != ';' && x[counter] != '\0'){
			counter++;
		}
		else if (x[counter] == '\0'){
			// do nothing
		}
		else{
			if (numOfFinger <= 5){
				//make an integer out of an array of characters (0-9)
				val[numOfFinger] = atoi(x);
			}
			else{
				numOfFinger = 0;
				val[numOfFinger] = atoi(x);
			}
			// uncomment for debugging
			//Serial.println(val[numOfFinger]);

			//delete the content of the array
			//maybe this code is not needed
			for (int i = 0; i < 5; i++){
				x[i] = 0;
			}

			counter = 0;
			numOfFinger++;
		}
		driveServos(val[0], val[1], val[2], val[3], val[4]);
	}
}

void driveServos(int d, int z, int m, int r, int k){
	//values in the map have to be edited!!!
	myservo_1.write(map(d, 0, 230, 89, 179);		//daumen
	myservo_2.write(map(z, 0, 245, 50, 104);		//zeigefinger
	myservo_3.write(map(m, 0, 280, 50, 102);		//mittelfinger
	myservo_4.write(map(r, 0, 170, 88, 122);		//ringfinger
	myservo_5.write(map(k, 0, 230, 103, 120);		//kleiner finger
}
