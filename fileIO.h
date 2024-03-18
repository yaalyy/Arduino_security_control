#ifndef FILEIO_H
#define FILEIO_H
#include<SD.h>
#include<string>



/* the file IO depends on the SD cart slot of MKR Env Shield*/
class FileIOHandler
{
    public:
        FileIOHandler();
        void init();
        void closeFile();
        char* readFile(char* fileName);
        void writeFile(char* fileName, char* content);
    private:
        std::string fileName="";
        File myFile;
};
#endif