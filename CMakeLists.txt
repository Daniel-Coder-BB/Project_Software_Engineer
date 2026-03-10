cmake_minimum_required(VERSION 3.28)
project(uitproberen)

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

# 3. Bronbestanden
set(SOURCE_FILES
        tinyxml_2_6_2/tinyxml/tinyxml.cpp
        tinyxml_2_6_2/tinyxml/tinyxmlparser.cpp
        tinyxml_2_6_2/tinyxml/tinyxmlerror.cpp
        tinyxml_2_6_2/tinyxml/tinystr.cpp
        Classes/Room/Room.cpp
        Classes/Room/Room.h
        Classes/Meeting/Meeting.cpp
        Classes/Meeting/Meeting.h
        Classes/Participation/Participation.cpp
        Classes/Participation/Participation.h
        Classes/Meeting/Meeting.cpp
        Classes/Meeting/Meeting.h


)

# 4. Target aanmaken (Eén executable waar je alles in doet)
add_executable(uitproberen main.cpp ${SOURCE_FILES}
        Classes/Room/Room.cpp
        Classes/Room/Room.h
        Classes/Meeting/Meeting.cpp
        Classes/Meeting/Meeting.h
        Classes/Participation/Participation.h
        Classes/Participation/Participation.cpp
        Classes/Meeting/Meeting.cpp
        Classes/Meeting/Meeting.h
)

# 5. Linken van bibliotheken
# Je moet gtest EN pthread linken aan je hoofdprogramma om de testen te draaien
target_link_libraries(uitproberen gtest pthread)