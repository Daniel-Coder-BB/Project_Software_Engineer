//
// Created by danny on 09-Mar-26.
//

#include "File_Reader.h"
#include "CD.h"
#include <iostream>
#include <string>
using namespace std;


int File_Reader::fout_bij_laden(string const& file_name,TiXmlDocument doc) {
    if (!doc.LoadFile(file_name.c_str())) {
        cerr << "Fout bij laden: " << doc.ErrorDesc() << endl;
        return 1;
    }
    return 0;
}

int File_Reader::if_root_exits(TiXmlElement* root) {
    if (root == NULL) {
        cerr << "Geen root element gevonden." << endl;
        return 1;
    }
    return 0;
}

void File_Reader::pars_file(CD room) {
    room.print();
}


