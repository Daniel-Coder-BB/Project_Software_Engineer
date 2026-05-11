#ifndef MEETINGPLANNER_H
#define MEETINGPLANNER_H

/**
 * @file Meetingplanner.h
 * @brief Beschrijving van de MeetingPlanner klasse voor het beheren van kamers, meetings en participaties.
 * @authors Bruno Luango en Ibrahim Akiyev
 * @date 30/04/2026
 * @version 2.1
 */

#include <vector>
#include <string>

#include "Classes/Room/Room.h"
#include "Classes/Meeting/Meeting.h"
#include "Classes/Participation/Participation.h"
#include "Classes/Campus/Campus.h"
#include "Classes/Buildings/Buildings.h"
#include "Classes/CateringProviders/Cateringproviders.h"
#include "Classes/Renovations/Renovations.h"

/**
 * @class MeetingPlanner
 * @brief Klasse die het centrale systeem beheert voor het plannen van meetings en middelen.
 */
class MeetingPlanner {

private:

    std::vector<Room> rooms; ///< Lijst met beschikbare kamers.

    std::vector<Meeting> meetings; ///< Lijst met geplande meetings.

    std::vector<Participation> participations; ///< Lijst met participaties van gebruikers.

    std::vector<std::string> occupied_rooms; ///< Lijst met identifiers van bezette kamers.

    std::vector<Meeting> conflicting_meetings; ///< Lijst met meetings die een conflict veroorzaken.

    std::vector<Campus> campuses; ///< Lijst met campussen in het systeem.

    std::vector<Buildings> buildings; ///< Lijst met gebouwen in het systeem.

    std::vector<Renovations> renovations; ///< Lijst met actieve renovaties.

    std::vector<Cateringproviders> catering; ///< Lijst met cateringproviders.

    double totalCateringCost = 0.0; ///< Houdt de totale kosten voor catering bij.

public:

    /**
     * @brief Voegt een kamer toe aan de planner.
     * @param room De toe te voegen Room-object.
     * @pre De naam van de kamer mag niet leeg zijn.
     * REQUIRE(!room.get_name().empty(), "room is not empty")
     * @post Het aantal kamers is met 1 toegenomen en de kamer is opgeslagen.
     * ENSURE(rooms.back() == room, "the input room is equal to label room of Meetingplanner object")
     * ENSURE(rooms.size() == old_size + 1, "room was successfully added")
     */
    void addRoom(const Room& room);

    /**
     * @brief Voegt een meeting toe aan de planner.
     * @param meeting Het toe te voegen Meeting-object.
     * @pre De identifier van de meeting mag niet leeg zijn.
     * REQUIRE(!meeting.get_identifier().empty(), "meeting is not empty")
     * @post De meeting is toegevoegd aan de lijst met meetings.
     * ENSURE(meetings.back() == meeting, "the input meeting is equal to label meeting of Meetingplanner object")
     */
    void addMeeting(const Meeting& meeting);

    /**
     * @brief Voegt een participatie toe aan de planner.
     * @param participation Het toe te voegen Participation-object.
     * @pre De gebruiker in de participatie mag niet leeg zijn.
     * REQUIRE(!participation.get_user().empty(), "participation is not empty")
     * @post De participatie is toegevoegd aan de lijst.
     * ENSURE(participations.back() == participation, "the input participation is equal to label participation of Meetingplanner object")
     */
    void addParticipation(const Participation& participation);

    /**
     * @brief Geeft de lijst met kamers terug.
     * @return Referentie naar de vector met Room-objecten.
     * @pre None
     * @post Returns rooms vector
     */
    std::vector<Room>& getRooms();

    /**
     * @brief Geeft de lijst met meetings terug.
     * @return Referentie naar de vector met Meeting-objecten.
     * @pre None
     * @post Returns meetings vector
     */
    std::vector<Meeting>& getMeetings();

    /**
     * @brief Geeft de lijst met participaties terug.
     * @return Referentie naar de vector met Participation-objecten.
     * @pre None
     * @post Returns participations vector
     */
    std::vector<Participation>& getParticipations();

    /**
     * @brief Geeft de lijst met bezette kamer-identifiers terug.
     * @return Vector van strings met kamer-identifiers.
     * @pre None
     * @post Returns occupied rooms vector
     */
    std::vector<std::string> get_occupied_rooms() const;

    /**
     * @brief Voegt een identifier toe aan de lijst van bezette kamers.
     * @param occupied_room De identifier van de kamer.
     * @pre De identifier string mag niet leeg zijn.
     * REQUIRE(!occupied_room.empty(), "occupied room is not empty")
     * @post De identifier is toegevoegd aan de lijst.
     */
    void set_occupied_rooms(const std::string &occupied_room);

    /**
     * @brief Geeft alle campussen terug.
     * @return Vector van Campus-objecten.
     */
    std::vector<Campus> get_campuses() const;

    /**
     * @brief Voegt een campus toe.
     * @param campus Het Campus-object.
     * @post De campus is toegevoegd aan de interne lijst.
     * ENSURE(campuses.size() == old_size + 1, "the campus is added to the list of campuses")
     */
    void set_campuses(const Campus &campus);

    /**
     * @brief Geeft alle gebouwen terug.
     * @return Vector van Buildings-objecten.
     */
    std::vector<Buildings> get_buildings() const;

    /**
     * @brief Voegt een gebouw toe.
     * @param building Het Buildings-object.
     * @post ENSURE(buildings.size() == old_size + 1, "the building is added to the list of buildings")
     */
    void set_buildings(const Buildings &building);

    /**
     * @brief Geeft alle renovaties terug.
     * @return Vector van Renovations-objecten.
     */
    std::vector<Renovations> get_renovations();

    /**
     * @brief Voegt een renovatie toe.
     * @param renovation Het Renovations-object.
     * @post ENSURE(renovations.size() == old_size + 1, "the renovation is added to the list of renovations")
     */
    void set_renovations(const Renovations &renovation);

    /**
     * @brief Geeft alle cateringproviders terug.
     * @return Vector van Cateringproviders-objecten.
     */
    std::vector<Cateringproviders> get_catering() const;

    /**
     * @brief Voegt een cateringprovider toe.
     * @param catering Het Cateringproviders-object.
     * @post ENSURE(catering.size() == old_size + 1, "the catering provider is added to the list of catering providers")
     */
    void set_catering(const Cateringproviders &catering);

    /**
     * @brief Genereert een tekstueel rapport van de systeemstatus.
     * @pre Kamers of meetings mogen niet leeg zijn.
     * REQUIRE(!rooms.empty() || !meetings.empty(),
     * "attributes of meetingplanner are not Empty")
     * @post Een bestand 'output.txt' is aangemaakt met de rapportage.
     */
    void simpleOutput();

    /**
     * @brief Genereert een DOT-bestand voor visualisatie van de structuur.
     * @pre De lijst met kamers mag niet leeg zijn.
     * REQUIRE(!rooms.empty(), "rooms must not be empty")
     * @post Een bestand 'structure.dot' is aangemaakt.
     */
    void exportGraphviz();

    /**
     * @brief Verwerkt de geplande meetings en controleert op bezetting of renovaties.
     * @pre Er moeten meetings aanwezig zijn om te verwerken.
     * REQUIRE(!meetings.empty(), "there must be meetings to process")
     * @post De status van meetings is bijgewerkt en cateringkosten zijn berekend.
     * ENSURE(true, "meetings processed correctly")
     */
    void processMeetings();
};

#endif