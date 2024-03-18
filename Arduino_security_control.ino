#include "thingProperties.h"
#include "buildInRGB.h"
#include "buzzer.h"
#include "led.h"


const int ledPin = 1;
const int buzzerPin = 2;
const int buttonPin1 = 3;
const int buttonPin2 = 4;
const int buttonPin3 = 5;

unsigned long prevMillis = 0;
const long interval = 100;


Buzzer buzzer(buzzerPin);
Led led(ledPin);

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  delay(1500); 

  /* Initialise all sensors and actuators */
  pinMode(buttonPin1, INPUT);    // passcode button 1
  pinMode(buttonPin2, INPUT);    // passcode button 2
  pinMode(buttonPin3, INPUT);  // used to clear passcode input
  buzzer.initBuzzer();
  led.init();
  initBuildInRGB();
 
  
  
  // Defined in thingProperties.h
  //initProperties();

  // Connect to Arduino IoT Cloud
  //ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information youâll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  //setDebugMessageLevel(2);
  //ArduinoCloud.printDebugInfo();
}

void loop() {
  //ArduinoCloud.update();
  unsigned long currentMillis = millis();
  if(currentMillis - prevMillis >= interval)  // setting up the refresh interval
  {
    prevMillis = currentMillis;
    /* All code should be put in this if statement*/


    if(digitalRead(buttonPin1) == HIGH)
    {
      buzzer.buttonPressed();
    }
    
  }
  


}

