# Arduino_security_control 
This is a low-cost security control system deployed on **Arduino MKR WiFi 1010** and **Arduino MKR ENV Shield**. The system is designed to securely monitor the people entrying and leaving the building/room, and it is able to send real-time data to the cloud server. The system is also able to alarm when the unauthorised access is detected.

## Hardware
### Arduino MKR WiFi 1010:
- Send/Receive cloud data
- Authentication
- Alarm
- LED indicator
- Network connection
  
### Arduino MKR ENV Shield
- SD card slot for data storage

## Reminders for developers
The passcode and login logs are stored in two individual files in the SD card, which are "pwd.txt" and "log.txt" respectively.    
Also, in the demostration, we only used two buttons to simulate the 4-digit passcode input, but in fact you can extend them by your needs, increasing the number of passcode combinations and improving the security level.  
By the way, the cloud platform we used in this project is Arduino IoT Cloud, so there is no a lot of code for cloud connection, but you can also add relavant configurations to connect to other cloud platforms, such as AWS, Azure, etc.  

