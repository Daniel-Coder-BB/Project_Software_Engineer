cmake_minimum_required(VERSION 3.28)
project(planning_system_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -O2")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")

# 1. Zoek de headers
include_directories(
        .
        ./gtest-1.7.0/include
        ./tinyxml_2_6_2/tinyxml
)

# 2. Zoek de gtest bibliotheek
link_directories(./gtest-1.7.0/lib)

# 3. Gedeelde Bronbestanden (Kernlogica)
# Hier staan alle klassen die zowel de app als de tests nodig hebben.
set(SHARED_SOURCES
        tinyxml_2_6_2/tinyxml/tinyxml.cpp
        tinyxml_2_6_2/tinyxml/tinyxmlparser.cpp
        tinyxml_2_6_2/tinyxml/tinyxmlerror.cpp
        tinyxml_2_6_2/tinyxml/tinystr.cpp
        Classes/Room/Room.cpp
        Classes/Parser/Parser.cpp
        Classes/Meetinggit/Meeting.cpp
        Classes/Meetingplanner/Meetingplanner.cpp
        Classes/Participation/Participation.cpp

)

# 4. TARGET 1: Je echte applicatie (Planning System)
# Gebruikt main.cpp + de gedeelde logica
 add_executable(planning_system main.cpp ${SHARED_SOURCES}
        Classes/Buildings/Buildings.cpp
        Classes/CateringProviders/Cateringproviders.cpp
        Classes/Renovations/Renovations.cpp
        Classes/Campus/Campus.cpp

 )
target_link_libraries(planning_system pthread)

# 5. TARGET 2: Je Google Tests
# Gebruikt nu test_main.cpp in plaats van de specifieke element test
add_executable(run_tests Tests/test_main.cpp ${SHARED_SOURCES}
        Classes/Buildings/Buildings.cpp
        Classes/CateringProviders/Cateringproviders.cpp
        Classes/Renovations/Renovations.cpp
        Classes/Campus/Campus.cpp
)

target_link_libraries(run_tests gtest pthread)