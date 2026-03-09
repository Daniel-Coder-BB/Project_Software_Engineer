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
    /*
     * This function check if there is a error with reading a file
     * @param file_name a string that contains the name of the file
     * @return if failed (1) or succeeded (0)
     */
    int fout_bij_laden(string file_name);
    /*
     * This function check if the root exist
     * @param root the FirstChildElement() of the document
     * @return if failed (1) or succeeded (0)
     */
    int if_root_exits(TiXmlElement* root);
    /*
     * This function prints out the room, identifier, capacity
     *  @param root
     *  @return none
     */
    void pars_file(TiXmlElement* root);


};

#endif //FILE_READER_H
