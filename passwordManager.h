#ifndef PWD_MANAGER_H
#define PWD_MANAGER_H
#include<unordered_map>
#include<string>
#include "fileIO.h"
#include<ArduinoJson.h>
#include <ArduinoIoTCloud.h>
#include "ntp.h"


class PasswordManager
{
private:
    std::unordered_map<std::string, std::string> userPwdMap;
    std::string pwdFileName;
    std::string logFileName;
    std::string latestLoginMsg;   // JSON format {"userName": "xxx", "time": "xxx"}
    void updatePwdFile();
    void login(const char* userName);
    long timeOffset;
public:
    PasswordManager();
    PasswordManager(const long timeOffset);
    void init(const char* pwdFileName, const char* logFileName);
    bool verifyPassword(const char* pwd);
    bool changePassword(const char* userName, const char* newPwd);
    std::string getLatestLoginMsg();
    std::string getPassword(const char* userName);
};


#endif