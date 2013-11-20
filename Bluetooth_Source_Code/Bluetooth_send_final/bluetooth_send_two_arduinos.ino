#include <SoftwareSerial.h>  

int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3
#define filterSamples   13              // filterSamples should  be an odd number, no smaller than 3
int sensSmoothArray1 [filterSamples];
int sensSmoothArray2 [filterSamples];
int raw = 0;
int result = 0;
int result_1 = 0;

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
  raw = analogRead(0);
  result = digitalSmooth(raw, sensSmoothArray1);
  bluetooth.print(result);
  delay(20);
  bluetooth.print(';');
  raw = analogRead(5);
  result_1 = digitalSmooth(raw, sensSmoothArray2);
  bluetooth.print(result_1);
  delay(20);
  bluetooth.print(';');
}

int digitalSmooth(int rawIn, int *sensSmoothArray){     // "int *sensSmoothArray" passes an array to the function - the asterisk indicates the array name is a pointer
  int j, k, temp, top, bottom;
  long total;
  static int i;
 // static int raw[filterSamples];
  static int sorted[filterSamples];
  boolean done;

  i = (i + 1) % filterSamples;    // increment counter and roll over if necc. -  % (modulo operator) rolls over variable
  sensSmoothArray[i] = rawIn;                 // input new data into the oldest slot

  // Serial.print("raw = ");

  for (j=0; j<filterSamples; j++){     // transfer data array into anther array for sorting and averaging
    sorted[j] = sensSmoothArray[j];
  }

  done = 0;                // flag to know when we're done sorting              
  while(done != 1){        // simple swap sort, sorts numbers from lowest to highest
    done = 1;
    for (j = 0; j < (filterSamples - 1); j++){
      if (sorted[j] > sorted[j + 1]){     // numbers are out of order - swap
        temp = sorted[j + 1];
        sorted [j+1] =  sorted[j] ;
        sorted [j] = temp;
        done = 0;
      }
    }
  }
/*
  for (j = 0; j < (filterSamples); j++){    // print the array to debug
    Serial.print(sorted[j]); 
    Serial.print("   "); 
  }
  Serial.println();
*/
  // throw out top and bottom 15% of samples - limit to throw out at least one from top and bottom
  bottom = max(((filterSamples * 15)  / 100), 1); 
  top = min((((filterSamples * 85) / 100) + 1  ), (filterSamples - 1));   // the + 1 is to make up for asymmetry caused by integer rounding
  k = 0;
  total = 0;
  for ( j = bottom; j< top; j++){
    total += sorted[j];  // total remaining indices
    k++; 
    // Serial.print(sorted[j]); 
    // Serial.print("   "); 
  }

//  Serial.println();
//  Serial.print("average = ");
//  Serial.println(total/k);
  return total / k;    // divide by number of samples
}
