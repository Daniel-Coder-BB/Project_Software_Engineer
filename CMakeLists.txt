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

# 3. Bronbestanden (TinyXML + eventuele andere .cpp files zoals Largest.cpp)
set(SOURCE_FILES
        tinyxml_2_6_2/tinyxml/tinyxml.cpp
        tinyxml_2_6_2/tinyxml/tinyxmlparser.cpp
        tinyxml_2_6_2/tinyxml/tinyxmlerror.cpp
        tinyxml_2_6_2/tinyxml/tinystr.cpp
        Classes/File_Reader/File_Reader.h
        # Voeg hier Largest.cpp of Fighterplane.cpp toe als je die hebt [cite: 169, 186]
)

# 4. Target aanmaken (Eén executable waar je alles in doet)
add_executable(uitproberen main.cpp ${SOURCE_FILES}
        Classes/File_Reader/File_Reader.h)

# 5. Linken van bibliotheken
# Je moet gtest EN pthread linken aan je hoofdprogramma om de testen te draaien
target_link_libraries(uitproberen gtest pthread)