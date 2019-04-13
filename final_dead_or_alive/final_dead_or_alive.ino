/*
 * Author - Group 17

  1) This shows a live human Heartbeat Pulse.
  2) Live visualization in Arduino's "Serial Plotter".
  3) This is the direct Pulse Sensor's Signal.

*
*/


//  Variables
int PulseSensorPurplePin = 0;          // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int LED13 = 13;                        //  The on-board Arduion LED
int t[10];                            // Array to count moving average             
int counter = 0;                      // Counter for calculating number of values added to the array
bool trigger = false;                 // Trigger whether a person is dead or alive

int Signal;                          // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 800;                 // Determine which Signal to "count as a beat", and which to ingore.


// The SetUp Function:
void setup() {

   Serial.begin(9600);         // Set's up Serial Communication at certain speed.

}

// The Main Loop Function
void loop() {

  Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value.
                                              // Assign this value to the "Signal" variable.

   //Serial.println(Signal);                  // Send the Signal value to Serial Plotter.


   // Adding new values to array and removing old values
   t[counter] = Signal;             
   counter++;

   if(counter == 10)
    counter = 0;

   // Calculating moving average for smoothing data
   int sum = 0;
   for(int i = 0; i < 10; i++) {
      sum += t[i];
   }

   // Trigger the event if below conditions are met
   if(sum == 0)
    trigger = true;

   if(sum > 5500)
    trigger = false;

   if(trigger)
    Serial.println("Alive!!");
   else
    Serial.println("Dead..");


   if(Signal > Threshold){          // If the signal is above "800", then "turn-on" Arduino's on-Board LED.
     digitalWrite(LED13,HIGH);
   } else {
     digitalWrite(LED13,LOW);       //  Else, the sigal must be below "800", so "turn-off" this LED.
   }


    delay(20);                     // Delay the thread    


}
