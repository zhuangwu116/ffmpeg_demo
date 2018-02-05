cmake_minimum_required(VERSION 3.5)
project(manage)

MESSAGE(STATUS "Project Directory: ${PROJECT_SOURCE_DIR}")
set(CMAKE_CXX_FLASS "${CMAKE_CXX_FLASS} -std=c++11")
FIND_PACKAGE(Protobuf REQUIRED)

include_directories(/usr/include/
    /usr/local/include/
    ${PROJECT_SOURCE_DIR})
link_directories(/usr/lib/
    /usr/local/lib/
    /usr/lib/x86_64-linux-gnu/)
add_executable(add_person
    ./add_person.cpp
    ./Person.pb.h
    ./Person.pb.cc
    )
add_executable(list_cpp
    ./list.cpp
    ./Person.pb.h
    ./Person.pb.cc
    )
target_link_libraries(add_person
    protobuf
    )

target_link_libraries(list_cpp
    protobuf
    )
