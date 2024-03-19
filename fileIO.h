#ifndef FILEIO_H
#define FILEIO_H
#include<SD.h>
#include<SPI.h>
#include<string>
#include<ArduinoJson.h>


/* the file IO depends on the SD cart slot of MKR Env Shield*/
class FileIOHandler
{
    public:
        FileIOHandler();
        void init();
        void closeFile();
        char* readFile(char* fileName);
        void writeFile(char* fileName, char* content);  
        JsonDocument readJson(char* fileName);  // this can read json object from a JSON file
        const char* getFileName();
        void deleteFile(char* fileName);
        void cleanFile(char* fileName);  // this is usually called before writing data into a file
        
    private:
        std::string fileName="";
        File myFile;
        JsonDocument jsonObject;
};
#endif