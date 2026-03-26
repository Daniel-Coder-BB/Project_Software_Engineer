/*
* Korte beschrijving:
 *Dit stelt onze main voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 11/03/2026
 * @version 1.0
 */

// Include blok
 #include <iostream>
#include "tinyxml.h"
#include "Classes/Room/Room.h"
#include "Classes/Meeting/Meeting.h"
#include <gtest/gtest.h>
#include <chrono>
#include "Classes/Meeting/Meeting.h"
#include "Classes/Meetingplanner/Meetingplanner.h"
#include "Classes/Participation/Participation.h"
#include "Classes/Parser/Parser.h"

// Globale using statements
using namespace std;

//body-gedeelte

int main(int argc, char **argv) {
    // create planner where meetings,rooms and Participation get saved in

    MeetingPlanner planner;
    // create document where XML file gets saved in
    TiXmlDocument doc;
    string filename = "../XML_files/Room.xml";
    // Parser wich reads the xml file and transfers to Meetingplanner
    Parser Xmlparser ;
    Xmlparser.set_filename(filename);
    Xmlparser.file_error_check(doc);

    TiXmlElement* root = Xmlparser.make_root(doc);
    Xmlparser.run_trough_Element("ROOM",root,planner);
    Xmlparser.run_trough_Element("MEETING",root,planner);
    Xmlparser.run_trough_Element("PARTICIPATION",root,planner);


    doc.Clear();

    planner.simpleOutput();
    return 0;
}


