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
    MeetingPlanner planner;
    TiXmlDocument doc;
    string filename = "../XML_files/Room.xml";
    Parser Xmlparser ;
    Xmlparser.set_filename(filename);
    Xmlparser.file_error_check(doc);

    doc.Clear();

    planner.simpleOutput();
    return 0;
}


