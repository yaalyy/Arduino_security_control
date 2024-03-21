#include "thingProperties.h"
#include "buildInRGB.h"
#include "buzzer.h"
#include "led.h"
#include "fileIO.h"
#include "passwordManager.h"


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
const int attemptLimit = 3;  // the maximum number of attempts to enter the passcode
const long timeOffset = 0;  // time offset in seconds


Buzzer buzzer(buzzerPin);
Led led(ledPin);
FileIOHandler fileIOHandler;
PasswordManager pwdManager(timeOffset);

JsonDocument pwdDocument;
void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();
  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /* Initialise all sensors and actuators */
  pinMode(buttonPin1, INPUT);    // passcode button 1
  pinMode(buttonPin2, INPUT);    // passcode button 2
  pinMode(buttonPin3, INPUT);  // used to clear passcode input
  buzzer.initBuzzer();
  led.init();
  initBuildInRGB();
  pwdManager.init(pwdFileName, logFileName);  // import password into the password manager
  fileIOHandler.init();

  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information youâll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

}

void loop() {
  ArduinoCloud.update();

  unsigned long currentMillis = millis();
  if(currentMillis - prevMillis >= interval)  // setting up the refresh interval
  {
    prevMillis = currentMillis;
    /* All code should be put in this if statement*/
    
      /* sync local password data with cloud data */
    
    user_login_1 = pwdManager.getPassword("user_1").c_str();
    user_login_2 = pwdManager.getPassword("user_2").c_str();

    
  }
  
}

/*
  Since UserLogin1 is READ_WRITE variable, onUserLogin1Change() is
  executed every time a new value is received from IoT Cloud.
*/
void onUserLogin1Change(){
  pwdManager.changePassword("user_1", user_login_1.c_str());
}

/*
  Since UserLogin2 is READ_WRITE variable, onUserLogin2Change() is
  executed every time a new value is received from IoT Cloud.
*/
void onUserLogin2Change(){
  pwdManager.changePassword("user_2", user_login_2.c_str());
}

