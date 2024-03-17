#include "thingProperties.h"
#include "buildInRGB.h"

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  
  delay(1500); 
 
  initBuildInRGB();
  setBuildInRGB(255,0,0);
  
  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
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


}

