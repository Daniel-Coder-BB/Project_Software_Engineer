#include <iostream>
#include "tinyxml.h"
#include "CD.h"
#include <gtest/gtest.h>
#include <chrono>

using namespace std;

CD parseCDElement(TiXmlElement* cdElem) {
    CD newCD;
    if (cdElem->FirstChildElement("NAME")) {
        newCD.setartist(cdElem->FirstChildElement("NAME")->GetText());
    }
    if (cdElem->FirstChildElement("IDENTIFIER")) {
        newCD.settitle(cdElem->FirstChildElement("IDENTIFIER")->GetText());
    }
    if (cdElem->FirstChildElement("CAPACITY")) {
        // Omzetten van string naar int
        int y = std::stoi(cdElem->FirstChildElement("CAPACITY")->GetText());
        newCD.setyear(y);
    }

    return newCD;
}


/*
 *This function checks if an error happens with reading the file
 *@param filename The directory where the file is
 *@param doc a TiXmlDocument wich contains our XML file
 *@return if failed (1) or if no errors(0)
 */
int file_error_check(const string& filename,TiXmlDocument& doc) {

    if (!doc.LoadFile(filename.c_str())) {
        cerr << "Fout bij laden: " << doc.ErrorDesc() << endl;
        return 1;
    }
    return 0;
}


int if_root_exists(TiXmlElement* root) {
    if (root == NULL) {
        cerr << "Geen root element gevonden." << endl;
        return 1;
    }
    return 0;
}



int main(int argc, char **argv) {
    TiXmlDocument doc;
    string filename = "../XML_files/Room.xml";
    file_error_check(filename,doc);

    TiXmlElement* root = doc.FirstChildElement(); // Dit is <system>
    if_root_exists(root);

    // Loop over alle <ROOm> elementen binnen  <SYSTEM> [cite: 57, 58]
    for (TiXmlElement* room = root->FirstChildElement("ROOM"); room != NULL; room = room->NextSiblingElement("ROOM")) {
        CD mijnCD = parseCDElement(room);
        mijnCD.print();
    }

    doc.Clear();

    // Netjes opruimen [cite: 107]



    return 0;
}

int maaltafel(int x) {
    return x*2;
}
TEST(maaltafelTest, Happydaytest) {
    int test_number = 5;
    EXPECT_EQ(maaltafel(test_number),10);
}