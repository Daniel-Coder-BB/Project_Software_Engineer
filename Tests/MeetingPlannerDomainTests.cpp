#include <gtest/gtest.h>
#include "../Classes/Room/Room.h"
#include "../Classes/Meeting/Meeting.h"
#include "../Classes/Participation/Participation.h"
#include "../Classes/Meetingplanner/Meetingplanner.h"
#include "../Classes/Parser/Parser.h"
#include "../Classes/Buildings/Buildings.h"
#include "../Classes/Campus/Campus.h"
#include "../Classes/CateringProviders/Cateringproviders.h"
#include "../Classes/Renovations/Renovations.h"

using namespace std;

// ==========================================
// MEETINGPLANNER DOMAIN TESTS
// ==========================================
class MeetingPlannerDomainTest : public ::testing::Test {
protected:
    MeetingPlanner planner;
};

TEST_F(MeetingPlannerDomainTest, CalculateCO2_PhysicalMeeting) {
    Room r;
    r.set_name("Lokaal 1.01");
    r.set_identifier("M1_Room");
    r.set_capacity(50);
    planner.addRoom(r);

    Meeting m;
    m.set_identifier("M1");
    m.set_room("M1_Room");
    m.set_online(false);
    planner.addMeeting(m);

    Participation p;
    p.set_user("Ibrahim");
    p.set_meeting("M1");
    planner.addParticipation(p);

    EXPECT_DOUBLE_EQ(planner.calculateCO2(m), 120.0);
}

TEST_F(MeetingPlannerDomainTest, MeetingCapacity_Check) {
    Room r;
    r.set_name("Lokaal 1");
    r.set_identifier("L.1.01");
    r.set_capacity(50);
    planner.addRoom(r);

    Meeting m;
    m.set_room("L.1.01");

    EXPECT_EQ(planner.meeting_capacity(m), 50);
}

// CONTRACT VIOLATIONS
TEST_F(MeetingPlannerDomainTest, ContractViolations) {
    Meeting m;
    m.set_identifier("M2");
    m.set_online(true);
    
    // Online meetings mogen geen catering hebben
    EXPECT_DEATH(m.set_catering(true), "Online meetings cannot have catering");
    
    Room r;
    EXPECT_DEATH(planner.addRoom(r), "name is not empty");
}

// ==========================================
// BUILDINGS DOMAIN TESTS
// ==========================================
class BuildingsDomainTest : public ::testing::Test {
protected:
    Buildings testBuilding;
};

TEST_F(BuildingsDomainTest, HappyDaySettersGetters) {
    testBuilding.set_name("G-gebouw");
    testBuilding.set_identifier("G.1.01");
    testBuilding.set_campus("Middelheim");

    EXPECT_EQ(testBuilding.get_name(), "G-gebouw");
    EXPECT_EQ(testBuilding.get_identifier(), "G.1.01");
    EXPECT_EQ(testBuilding.get_campus(), "Middelheim");
}

TEST_F(BuildingsDomainTest, ContractViolations) {
    EXPECT_DEATH(testBuilding.set_name(""), "Precondition failure: name cannot be empty");
    EXPECT_DEATH(testBuilding.set_identifier(""), "Precondition failure: identifier cannot be empty");
}

TEST_F(BuildingsDomainTest, TestExtremeStringLength) {
    std::string longName(5000, 'A');
    testBuilding.set_name(longName);
    EXPECT_EQ(testBuilding.get_name().length(), 5000u);
}

// ==========================================
// CAMPUS DOMAIN TESTS
// ==========================================
class CampusDomainTest : public ::testing::Test {
protected:
    Campus testCampus;
};

TEST_F(CampusDomainTest, HappyDaySettersGetters) {
    testCampus.set_name("Middelheim");
    testCampus.set_identifier("CMI");
    EXPECT_EQ(testCampus.get_name(), "Middelheim");
    EXPECT_EQ(testCampus.get_identifier(), "CMI");
}

TEST_F(CampusDomainTest, ContractViolations) {
    EXPECT_DEATH(testCampus.set_name(""), "Precondition failure: name cannot be empty");
}

// ==========================================
// CATERINGPROVIDERS DOMAIN TESTS
// ==========================================
class CateringprovidersDomainTest : public ::testing::Test {
protected:
    Cateringproviders testProvider;
};

TEST_F(CateringprovidersDomainTest, HappyDaySettersGetters) {
    testProvider.set_campus("Campus Middelheim");
    testProvider.set_co2(15.5f);
    EXPECT_EQ(testProvider.get_campus(), "Campus Middelheim");
    EXPECT_FLOAT_EQ(testProvider.get_co2(), 15.5f);
}

TEST_F(CateringprovidersDomainTest, ContractViolations) {
    EXPECT_DEATH(testProvider.set_co2(0.0f), "Precondition failure: Value must be greater then zero");
    EXPECT_DEATH(testProvider.set_co2(-1.0f), "Precondition failure: Value must be greater then zero");
    EXPECT_DEATH(testProvider.set_campus(""), "Precondition failure: campus cannot be empty");
}

// ==========================================
// RENOVATIONS DOMAIN TESTS
// ==========================================
class RenovationsDomainTest : public ::testing::Test {
protected:
    Renovations testRenovation;
};

TEST_F(RenovationsDomainTest, HappyDaySettersGetters) {
    testRenovation.set_room("L.1.01");
    testRenovation.set_start("08:00");
    testRenovation.set_end("17:00");
    EXPECT_EQ(testRenovation.get_room(), "L.1.01");
    EXPECT_EQ(testRenovation.get_start(), "08:00");
    EXPECT_EQ(testRenovation.get_end(), "17:00");
}

TEST_F(RenovationsDomainTest, ContractViolations) {
    EXPECT_DEATH(testRenovation.set_room(""), "Precondition failure: room cannot be empty");
}

// ==========================================
// PARSER DOMAIN TESTS (State testing)
// ==========================================
TEST(ParserDomainTest, SetFilename_GetFilename) {
    Parser p;
    p.set_filename("config.xml");
    EXPECT_EQ(p.get_filename(), "config.xml");

    p.set_filename("nieuw.xml");
    EXPECT_EQ(p.get_filename(), "nieuw.xml");
}

TEST(ParserDomainTest, ContractViolations) {
    Parser p;
    EXPECT_DEATH(p.get_filename(), "Preconditie gefaald: filename mag niet leeg zijn");
    EXPECT_DEATH(p.set_filename(""), "Preconditie gefaald: nieuwe filename mag niet leeg zijn");
}