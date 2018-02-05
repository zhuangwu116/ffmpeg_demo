cmake_minimum_required(VERSION 3.5)
project(zmq_demo)

MESSAGE(STATUS "Project Directory: ${PROJECT_SOURCE_DIR}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#find_package( OpenCV REQUIRED )
#find_package( OpenCV HINTS /usr/local/opencv3 )


include_directories(/usr/include/
    /usr/local/include/
    ${PROJECT_SOURCE_DIR}/src/)
link_directories(/usr/lib/
    /usr/local/lib/
    /usr/lib/x86_64-linux-gnu/
    )

add_executable(server
    ./zmq.hpp
    ./server.cpp
    )
add_executable(client
    ./zmq.hpp
    ./client.cpp
    )
target_link_libraries(server
    #        ${OpenCV_LIBS}
    glog zmq pthread
    #        x264 pthread dl freetype z postproc va ass fdk-aac mp3lame opus vpx
    #        vorbis vorbisenc lzma vdpau X11 va-x11 va-drm theora theoraenc theoradec
    )

target_link_libraries(client
    glog zmq pthread)

