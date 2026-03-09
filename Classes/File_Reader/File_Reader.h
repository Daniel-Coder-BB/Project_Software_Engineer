//
// Created by danny on 09-Mar-26.
//

#ifndef FILE_READER_H
#define FILE_READER_H
#include "tinyxml.h"
#include "string"
#include "CD.h"
using namespace std;

class File_Reader {
private:
    TiXmlDocument file;

public:
    /*
     * This function check if there is a error with reading a file
     * @param file_name a string that contains the name of the file
     * @param doc the document wich contains the xml_file data
     * @return if failed (1) or succeeded (0)
     */
    static int fout_bij_laden(const string& file_name,TiXmlDocument doc);
    /*
     * This function check if the root exist
     * @param root the FirstChildElement() of the document
     * @return if failed (1) or succeeded (0)
     */
    int if_root_exits(TiXmlElement* root);
    /*
     * This function prints out the room, identifier, capacity
     *  @param room contains the room it is in
     *  @return none
     */
    void pars_file(CD room);




};

#endif //FILE_READER_H
