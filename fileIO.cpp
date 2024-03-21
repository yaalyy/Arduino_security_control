#include "fileIO.h"

FileIOHandler::FileIOHandler()
{
    return;
}
void FileIOHandler::init()
{
    // Serial.println("Initializing SD card...");
    if(!SD.begin())
    {
        // Serial.println("SD card initialisation failed!");
        while(1);
    }
    // Serial.println("Initialisation done.");
}

void FileIOHandler::closeFile()
{
    if(myFile)
    {
        myFile.close();
    }
}

char* FileIOHandler::readFile(const char* fileName)   // this memory needs to be freed after use
{
    std::string newString = "";
    if((fileName != nullptr)&&(fileName[0] != '\0'))
    {
        this->fileName = fileName;
        
        if(SD.exists(this->fileName.c_str()))
        {
            myFile = SD.open(this->fileName.c_str());
            while(myFile.available())
            {
                newString.push_back(myFile.read());
            }
            myFile.close();
        }
    }

    // Allocate memory for the C-string
    char* cString = (char*)malloc(newString.length() + 1); // +1 for the null terminator
    if (cString == nullptr) {
        // Allocation failed
        return nullptr;
    }

    // Copy the contents of the std::string to the newly allocated C-string
    strcpy(cString, newString.c_str());

    // Return the dynamically allocated copy
    return cString;
}

void FileIOHandler::writeFile(const char* fileName, const char* content)  // this will not overwrite the file, only append to it
{
    if((fileName != nullptr)&&(fileName[0] != '\0'))
    {
        this->fileName = fileName;
        myFile = SD.open(fileName, FILE_WRITE);
        if(myFile)
        {
            myFile.println(content);
            myFile.close();

        }
    }
    
   

}

JsonDocument FileIOHandler::readJson(const char* fileName)
{
    if((fileName != nullptr)&&(fileName[0] != '\0'))
    {
        this->fileName = fileName;
        char* jsonMSG = readFile(fileName);
        // Deserialize the JSON 
        DeserializationError error = deserializeJson(jsonObject, jsonMSG);
        // Test if parsing succeeds
        if (error) 
        {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            JsonDocument tempJson;
            deserializeJson(tempJson, "{}");
            return tempJson;
        }
    }
    else
    {
        JsonDocument tempJson;
        deserializeJson(tempJson, "{}");
        return tempJson;
    }
    
    return jsonObject;
    
}

const char* FileIOHandler::getFileName()
{

    return this->fileName.c_str();
}

void FileIOHandler::deleteFile(const char* fileName)
{
    if((fileName != nullptr)&&(fileName[0] != '\0'))
    {
        this->fileName = fileName;
        if(SD.exists(fileName))
        {
            SD.remove(fileName);
        }
    }
    
    
    
}

void FileIOHandler::cleanFile(const char* fileName)  // delete the old one and create a new one with the same name
{
    if((fileName != nullptr)&&(fileName[0] != '\0'))
    {
        this->fileName = fileName;
        if(SD.exists(fileName))
        {
            SD.remove(fileName);
            myFile = SD.open(fileName, FILE_WRITE);
            myFile.close();
        }
    }
    
}

bool FileIOHandler::exists(const char* fileName)
{
    if((fileName != nullptr)&&(fileName[0] != '\0'))
    {
        
        return SD.exists(fileName);
    }
    return false;
    
}
    