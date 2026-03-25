/*
* Korte beschrijving:
 *Dit stelt onze parser klasse voor.
 *
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 25/03/2026
 * @version 1.5
 */

// Include blok

#ifndef PLANNING_SYSTEM_PROJECT_PARSER_H
#define PLANNING_SYSTEM_PROJECT_PARSER_H
#include "Classes/Meeting/Meeting.h"
#include "Classes/Meetingplanner/Meetingplanner.h"
#include "Classes/Participation/Participation.h"
#include "Classes/Room/Room.h"
#include "tinyxml.h"
#include <iostream>
#include <string>


class Parser {
private:
    string filename;

public:
    [[nodiscard]] string get_filename() const;

    void set_filename(const string &filename);

    TiXmlDocument Xml_to_TiXmlDocument();
    int file_error_check(TiXmlDocument& doc);
    int if_root_exists(TiXmlElement* root);
    TiXmlElement* make_root(TiXmlDocument& doc);
    void run_trough_Element(const char* Element, TiXmlElement* root,  MeetingPlanner planner);
    Room parse_room_element(TiXmlElement* room_element);
    Meeting parse_meeting_element(TiXmlElement* meeting_element);
    Participation parse_participation_element(TiXmlElement* participation_element);

};


#endif //PLANNING_SYSTEM_PROJECT_PARSER_H