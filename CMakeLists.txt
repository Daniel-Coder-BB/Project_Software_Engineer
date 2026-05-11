cmake_minimum_required(VERSION 3.28)
project(planning_system_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -O2")

# 1. Include Directories
include_directories(
        .
        "${CMAKE_CURRENT_SOURCE_DIR}/gtest-1.7.0/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/tinyxml_2_6_2/tinyxml"
)

# 2. Shared Sources (Core Logic)
set(SHARED_SOURCES
        tinyxml_2_6_2/tinyxml/tinyxml.cpp
        tinyxml_2_6_2/tinyxml/tinyxmlparser.cpp
        tinyxml_2_6_2/tinyxml/tinyxmlerror.cpp
        tinyxml_2_6_2/tinyxml/tinystr.cpp
        Classes/Room/Room.cpp
        Classes/Meeting/Meeting.cpp
        Classes/Participation/Participation.cpp
        Classes/Meetingplanner/Meetingplanner.cpp
        Classes/Parser/Parser.cpp
        Classes/Buildings/Buildings.cpp
        Classes/CateringProviders/Cateringproviders.cpp
        Classes/Renovations/Renovations.cpp
        Classes/Campus/Campus.cpp
)

# 3. Define the Libraries (Direct paths to your .a files)
# This replaces link_directories and is much more stable
set(GTEST_LIB "${CMAKE_CURRENT_SOURCE_DIR}/gtest-1.7.0/lib/libgtest.a")
set(GTEST_MAIN_LIB "${CMAKE_CURRENT_SOURCE_DIR}/gtest-1.7.0/lib/libgtest_main.a")

# 4. TARGET 1: Planning System (The App)
# Removed the .cpp test files from here!
# You shouldn't compile tests into your main production executable.
add_executable(planning_system main.cpp ${SHARED_SOURCES})
target_link_libraries(planning_system PRIVATE pthread)

# 5. TARGET 2: Run Tests
add_executable(run_tests Tests/test_main.cpp ${SHARED_SOURCES}
        Tests/MeetingPlannerDomainTests.cpp
        Tests/MeetingPlannerInputTests.cpp
        Tests/MeetingPlannerOutputTests.cpp
)

# Link EVERYTHING needed for tests
target_link_libraries(run_tests PRIVATE
        ${GTEST_LIB}
        ${GTEST_MAIN_LIB}
        pthread
)