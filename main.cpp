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



int file_error_check(const string& filename,TiXmlDocument doc) {

    if (!doc.LoadFile(filename.c_str())) {
        cerr << "Fout bij laden: " << doc.ErrorDesc() << endl;
        return 1;
    }
    return 0;
}

int main(int argc, char **argv) {
    TiXmlDocument doc;
    string filename = "../XML_files/Room.xml";
    file_error_check(filename,doc);

    TiXmlElement* root = doc.FirstChildElement(); // Dit is <CATALOG>
    if (root == NULL) {
        cerr << "Geen root element gevonden." << endl;
        return 1;
    }


    // Loop over alle <CD> elementen binnen de <CATALOG> [cite: 57, 58]
    for (TiXmlElement* cd = root->FirstChildElement("ROOM"); cd != NULL; cd = cd->NextSiblingElement("ROOM")) {
        CD mijnCD = parseCDElement(cd);
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