#include "thingProperties.h"
#include "buildInRGB.h"
#include "buzzer.h"
#include "led.h"
#include "fileIO.h"
#include "passwordManager.h"


const int ledPin = 0;
const int buzzerPin = 1;
const int buttonPin1 = 2;
const int buttonPin2 = 3;
const int buttonPin3 = 5;

unsigned long prevMillis = 0;
const long interval = 100;
const char* pwdFileName = "pwd.txt";
const char* logFileName = "log.txt";
const int pwdLength = 4;
const int attemptLimit = 3;  // the maximum number of attempts to enter the passcode
int attempts = 0;
const long timeOffset = 0;  // time offset in seconds


Buzzer buzzer(buzzerPin);
Led led(ledPin);
FileIOHandler fileIOHandler;
PasswordManager pwdManager(timeOffset);

bool inputtingPwd = false;
std::string pwdInput = "";
JsonDocument logDocument;

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

  setBuildInRGB(255,0,0);
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information youâll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  //buzzer.entryBeeping();
}

void loop() {
  ArduinoCloud.update();
  //pwdManager.updateNTP();
  if(ArduinoCloud.connected())
  {
    // set RGB to green
    setBuildInRGB(0,255,0); 
    
  }
  else
  {
    // set RGB to yellow
    setBuildInRGB(255,255,0);
  }

  unsigned long currentMillis = millis();
  if(currentMillis - prevMillis >= interval)  // setting up the refresh interval
  {
    prevMillis = currentMillis;
    /* All code should be put in this if statement*/
    
      /* sync local password data with cloud data */
    
    user_login_1 = pwdManager.getPassword("user_1").c_str();
    user_login_2 = pwdManager.getPassword("user_2").c_str();

    if(inputtingPwd)
    {
      led.on();
      inputPassword();
    }
    else
    {
      led.off();
    }

    if(digitalRead(buttonPin3) == HIGH)
    {
      buzzer.buttonPressed();
      inputtingPwd = !inputtingPwd;
    }

   
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

void inputPassword()
{
  while((pwdInput.length() < pwdLength) && (inputtingPwd))
  {
    if(digitalRead(buttonPin1) == HIGH)
    {
      pwdInput += "0";
      buzzer.buttonPressed();
      delay(500);
      
    }
    if(digitalRead(buttonPin2) == HIGH)
    {  
      pwdInput += "1";
      buzzer.buttonPressed();
      delay(500);
      
    }
    if((digitalRead(buttonPin3) == HIGH)&&(pwdInput.length() > 0))
    {
      //buzzer.buttonPressed();
      inputtingPwd = !inputtingPwd;
      
    }
  }

  if(pwdManager.verifyPassword(pwdInput.c_str()))
  {
    attempts = 0;
    buzzer.entryBeeping();
    pwdInput = "";
    inputtingPwd = false;
    std::string loginLog = pwdManager.getLatestLoginMsg();
    deserializeJson(logDocument, loginLog);
    if(logDocument["userName"] == "user_1")
    {
      user1_log = String(loginLog.c_str());
    }
    else if(logDocument["userName"] == "user_2")
    {
      user2_log = String(loginLog.c_str());
    }
    
  }
  else
  {
    attempts++;
    buzzer.buzzerBeeping(1000, 1000);
    pwdInput = "";
    inputtingPwd = false;
  }
  if(attempts >= attemptLimit)
  {
    attempts = 0;
    buzzer.alarm();
  }

}

