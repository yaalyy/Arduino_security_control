#include "fileIO.h"
#include<SPI.h>
#include<SD.h>
#include<Arduino.h>
#include<string>
#include<cstring>
#include<cstdlib>

FileIOHandler::FileIOHandler()
{
    return;
}
void FileIOHandler::init()
{
    Serial.println("Initializing SD card...");
    if(!SD.begin())
    {
        Serial.println("SD card initialisation failed!");
        while(1);
    }
    Serial.println("Initialisation done.");
}

void FileIOHandler::closeFile()
{
    if(myFile)
    {
        myFile.close();
    }
}

char* FileIOHandler::readFile(char* fileName)
{
    this->fileName = fileName;
    std::string newString = "";
    myFile = SD.open(fileName);
    if(myFile)
    {
        while(myFile.available())
        {
            newString.push_back(myFile.read());
        }
        myFile.close();
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

void FileIOHandler::writeFile(char* fileName, char* content)
{
    this->fileName = fileName;
    myFile = SD.open(fileName, FILE_WRITE);
    if(myFile)
    {
        myFile.println(content);
        myFile.close();

    }
}