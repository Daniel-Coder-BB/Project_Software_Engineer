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
#include "Classes/Campus/Campus.h"
#include "Classes/Buildings/Buildings.h"
#include "tinyxml.h"
#include <iostream>
#include <string>


class Parser {
private:
    string filename;

public:
    /*
     *This function gets the filename attribute
     *@param None
     *@return the filename of the Parser object
     *precondition filename is not empty
     *REQUIRE(!filename.empty(), "Preconditie gefaald: filename mag niet leeg zijn")
     *postcondition returns this->filename
     *ENSURE(result == filename, "Postconditie gefaald: de geretourneerde filename is niet gelijk aan de attribuutwaarde")
     */
    string get_filename() const;

    /*
    *This function changes the filename attribute
    *@param the filename you want to change it to
    *@return None
    *precondition filename is not empty
    *REQUIRE(!filename.empty(), "Preconditie gefaald: nieuwe filename mag niet leeg zijn")
    *postcondition the input filename is equal to filename of Parser object
    *ENSURE(this->filename == filename, "Postconditie gefaald: filename attribuut is niet correct aangepast")
    */
    void set_filename(const string &filename);

    /*
    *This function takes the filename and turns the XML document into a TiXmlDocument element
    *@param None
    *@return document of type TiXmlElement
    *precondition filename is not empty
    * REQUIRE(!filename.empty(), "Preconditie gefaald: filename mag niet leeg zijn")
    *postcondition You have a TiXmlDocument ready to be parsed
    */
    TiXmlDocument Xml_to_TiXmlDocument();

    /*
    *This function checks if there was an error in loading the file into TiXmlDocument
    *@param document an TiXmlDocument wich you will load the content of a file
    *@return 0 for succes 1, 1 for failure.
    *precondition filename is not empty
    *REQUIRE(!filename.empty(), "Preconditie gefaald: filename mag niet leeg zijn om file error check uit te voeren")
    *postcondition the content of the file has been loaded into doc
    *ENSURE(result == 0 || result == 1, "Postconditie gefaald: resultaat moet 0 of 1 zijn")
    */
    int file_error_check(TiXmlDocument& doc);

    /*
    *This function checks if the root is not NULL
    *@param root, an TiXmlElement adress wich contains the adress of the root.
    *@return 0 for succes 1, 1 for failure.
    *precondition None
    *postcondition you know if your TIXmlDocument has a root.
    */
    int if_root_exists(TiXmlElement* root);

    /*
    *This function makes a root with type TiXmlElement.
    *@param doc, a TIXmlDocument value of an object
    *@return root, a TiXmlElement object
    *precondition No file error happened beforehand.
    *postcondition a root has been created wich you can extract info about the XML document
    *ENSURE(root != NULL || true, "Postconditie: root is aangemaakt (indien aanwezig)")
    */
    TiXmlElement* make_root(TiXmlDocument& doc);

    /*
    *This function runs through every header of the XML file and puts the FirstChildElment in the MeetingPlanner
    *@param Element, a const char pointer wich represent the FirstChildElement of the root you want to find
    *@param root, a TiXmlElement pointer wich represents the root of the XML file
    *@param planner, a Meetingplanner value wich represents the meetingplanner where you will put all the FirstChildElements of your Element.
    *@return None
    *precondition Elment is "MEETING","ROOM" or "PARTICIPATION"
    *REQUIRE(elStr == "MEETING" || elStr == "ROOM" || elStr == "PARTICIPATION" || elStr == "CAMPUS" || elStr == "BUILDING" || elStr == "RENOVATION" || elStr == "CATERING",
    *"Preconditie gefaald: Element moet MEETING, ROOM, PARTICIPATION,CAMPUS of BUILDING element zijn")
    *precondition root exists
    *REQUIRE(root != NULL, "Preconditie gefaald: root moet bestaan")
    *postcondition the Meeting,room and Participation objects have succesfully been added to the planner
    */
    void run_trough_Element(const char* Element, TiXmlElement* root,  MeetingPlanner& planner);

    /*
     *This function parses the room tag of an XML file
     *@param room_element an XML element with the ROOM tag
     *@return new_room a room of the type ROOM with all the details
     *precondition None
     * REQUIRE(room_element != NULL, "Preconditie gefaald: room_element mag niet NULL zijn")
     *postcondition you get a Room object back
     */
    Room parse_room_element(TiXmlElement* room_element);

    /*
     *This function parses the meeting tag of an XML file
     *@param meeting_element an XML element with the MEETING tag
     *@return new_meeting a meeting of the type MEETING with all the details
     *precondition None
     *REQUIRE(meeting_element != NULL, "Preconditie gefaald: meeting_element mag niet NULL zijn")
     *postcondition you get a Meeting object
     */
    Meeting parse_meeting_element(TiXmlElement* meeting_element);


   /*
    *This function parses the participation tag of an XML file
    *@param participation_element an XML element with the PARTICIPATION tag
    *@return new_participation a participation of the type PARTICIPATION with all the details
    *preconditon None.
    * REQUIRE(participation_element != NULL, "Preconditie gefaald: participation_element mag niet NULL zijn")
    *postcondition you get a Participation object.
    */
    Participation parse_participation_element(TiXmlElement* participation_element);

 /*
* This function parses the campus tag of an XML file
* @param campus_element an XML element with the CAMPUS tag
* @return new_campus a campus of the type CAMPUS with all the details
* precondition None.
* REQUIRE(campus_element != NULL, "Preconditie gefaald: campus_element mag niet NULL zijn")
* postcondition you get a Campus object.
*/
 Campus parse_campus_element(TiXmlElement* campus_element);

 /*
    * This function parses the building tag of an XML file
    * @param building_element an XML element with the BUILDING tag
    * @return new_building a building of the type BUILDING with all the details
    * precondition None.
    * REQUIRE(building_element != NULL, "Preconditie gefaald: building_element mag niet NULL zijn")
    * postcondition you get a Building object.
    */
 Buildings parse_building_element(TiXmlElement* building_element);

 /*
    * This function parses the renovation tag of an XML file
    * @param renovation_element an XML element with the RENOVATION tag
    * @return new_renovation a renovation of the type RENOVATION with all the details
    * precondition None.
    * REQUIRE(renovation_element != NULL, "Preconditie gefaald: renovation_element mag niet NULL zijn")
    * postcondition you get a Renovation object.
    */
Renovations parse_renovation_element(TiXmlElement* renovation_element);

 /*
    * This function parses the catering tag of an XML file
    * @param catering_element an XML element with the CATERING tag
    * @return new_catering a catering provider of the type Cateringproviders with all the details
    * precondition None.
    * REQUIRE(catering_element != NULL, "Preconditie gefaald: catering_element mag niet NULL zijn")
    * postcondition you get a Cateringproviders object.
    */
 Cateringproviders parse_catering_element(TiXmlElement* catering_element);
};







#endif //PLANNING_SYSTEM_PROJECT_PARSER_H