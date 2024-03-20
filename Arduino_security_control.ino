#include "thingProperties.h"
#include "buildInRGB.h"
#include "buzzer.h"
#include "led.h"
#include "fileIO.h"


const int ledPin = 1;
const int buzzerPin = 2;
const int buttonPin1 = 3;
const int buttonPin2 = 4;
const int buttonPin3 = 5;

unsigned long prevMillis = 0;
const long interval = 100;
const char* pwdFileName = "pwd.txt";
const char* logFileName = "log.txt";
const int pwdLength = 4;


Buzzer buzzer(buzzerPin);
Led led(ledPin);
FileIOHandler fileIOHandler;

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

 
  fileIOHandler.init();
  char* testMsg = fileIOHandler.readFile(pwdFileName);
  Serial.print("The original json: ");
  Serial.println(testMsg);
  free(testMsg);
  JsonDocument doc;
  doc = fileIOHandler.readJson(pwdFileName);
  Serial.print("User_1: ");
  Serial.println(doc["Users"]["user_1"].as<const char*>());
  Serial.print("User_2: ");
  Serial.println(doc["Users"]["user_2"].as<const char*>());

  
  
  
  
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
      led.on();
    }
    else
    {
      led.off();
    }
    
  }
  
}

/*
  Since UserLogin1 is READ_WRITE variable, onUserLogin1Change() is
  executed every time a new value is received from IoT Cloud.
*/
void onUserLogin1Change()  {
  // Add your code here to act upon UserLogin1 change
}

/*
  Since UserLogin2 is READ_WRITE variable, onUserLogin2Change() is
  executed every time a new value is received from IoT Cloud.
*/
void onUserLogin2Change()  {
  // Add your code here to act upon UserLogin2 change
}

