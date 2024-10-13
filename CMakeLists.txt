cmake_minimum_required(VERSION 3.26)
project(DSAProject3)

set(CMAKE_CXX_STANDARD 17)

add_executable(DSAProject3 main.cpp
        hashMap.cpp
        hashMap.h)

set(SFML_STATIC_LIBRARIES_TRUE)
set(SFML_DIR "C:/Libraries/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

target_link_libraries(DSAProject3 sfml-system sfml-window sfml-graphics sfml-audio)