#include "passwordManager.h"

PasswordManager::PasswordManager() 
{
    this->timeOffset = 0;
}
PasswordManager::PasswordManager(const long timeOffset) 
{
    this->timeOffset = timeOffset;
    
}

void PasswordManager::init(const char* pwdFileName, const char* logFileName)
{   
    FileIOHandler passwordHandler;
    passwordHandler.init();
    if((!passwordHandler.exists(pwdFileName))||(!passwordHandler.exists(logFileName)))
    {
        return;
    }
    /* read the password file and store the data into the map  */
    this->pwdFileName = pwdFileName;
    this->logFileName = logFileName;
    JsonDocument pwdJson = passwordHandler.readJson(pwdFileName);
    JsonObject users = pwdJson["Users"];
    for(JsonPair user:users)
    {
        userPwdMap[user.key().c_str()] = user.value().as<const char*>();
    }


}

void PasswordManager::updatePwdFile()
{
    JsonDocument pwdJson;
    JsonObject users = pwdJson.createNestedObject("Users");

    for(const auto& pair: userPwdMap)
    {
        users[pair.first.c_str()] = pair.second.c_str();
    }
    std::string msg;
    serializeJson(pwdJson, msg);

    FileIOHandler passwordHandler;
    passwordHandler.init();
    passwordHandler.cleanFile(pwdFileName.c_str());
    passwordHandler.writeFile(pwdFileName.c_str(), msg.c_str());
    
}

void PasswordManager::login(const char* userName)
{
    if((userName == nullptr)||(userName[0] == '\0'))
    {
        return;
    }
    int day, month, year, hour, minute, second;
    NTPHandler ntpHandler(this->timeOffset);
    ntpHandler.updateNTP();
    day = ntpHandler.getDay();
    month = ntpHandler.getMonth();
    year = ntpHandler.getYear();
    hour = ntpHandler.getHour();
    minute = ntpHandler.getMinute();
    second = ntpHandler.getSecond();
    
    std::string timeStamp = std::to_string(day) \
    + "/" + std::to_string(month) \
    + "/" + std::to_string(year) \
    + " " + std::to_string(hour) \
    + ":" + std::to_string(minute) \
    + ":" + std::to_string(second);

    std::string jsonContent = "{\"userName\": \"" + std::string(userName) + "\", \"time\": \"" + timeStamp + "\"}\n";
    this->latestLoginMsg = jsonContent;

    FileIOHandler logHandler;
    logHandler.init();
    logHandler.writeFile(logFileName.c_str(), jsonContent.c_str());

}

bool PasswordManager::verifyPassword(const char* pwd)
{
    for(const auto& pair: userPwdMap)
    {
        if(pair.second == pwd)
        {
            login(pair.first.c_str());
            return true;
        }
    }

    return false;
}

bool PasswordManager::changePassword(const char* userName, const char* newPwd)
{
    if(userPwdMap.find(userName) != userPwdMap.end())
    {
        userPwdMap[userName] = newPwd;
        updatePwdFile();
        return true;
    }
    
    return false;
}

std::string PasswordManager::getLatestLoginMsg()
{
    return latestLoginMsg;
}

std::string PasswordManager::getPassword(const char* userName)
{
    if(userPwdMap.find(userName) != userPwdMap.end())
    {
        return userPwdMap[userName];
    }
    return "";
}