#ifndef FILEIO_H
#define FILEIO_H
#include<SD.h>
#include<SPI.h>
#include<string>
#include<ArduinoJson.h>
#include<Arduino.h>
#include<cstring>
#include<cstdlib>


/* the file IO depends on the SD cart slot of MKR Env Shield*/
class FileIOHandler
{
    public:
        FileIOHandler();
        void init();
        void closeFile();
        char* readFile(const char* fileName);
        void writeFile(const char* fileName, const char* content);    // this will not overwrite the file, only append to it
        JsonDocument readJson(const char* fileName);  // this can read json object from a JSON file
        const char* getFileName();
        void deleteFile(const char* fileName);
        void cleanFile(const char* fileName);  // this is usually called before writing data into a file
        bool exists(const char* fileName);
        
    private:
        std::string fileName="";
        File myFile;
        JsonDocument jsonObject;
};
#endif