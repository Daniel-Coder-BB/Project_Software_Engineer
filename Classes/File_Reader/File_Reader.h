//
// Created by danny on 09-Mar-26.
//

#ifndef FILE_READER_H
#define FILE_READER_H
#include "tinyxml.h"
#include "string"
using namespace std;

class File_Reader {
private:
    TiXmlDocument file;

public:
    int fout_bij_laden(string file_name);

};

#endif //FILE_READER_H
