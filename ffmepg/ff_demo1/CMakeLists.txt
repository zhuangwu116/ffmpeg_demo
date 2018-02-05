cmake_minimum_required(VERSION 3.5)
project(manage)

MESSAGE(STATUS "Project Directory: ${PROJECT_SOURCE_DIR}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CUDA_USE_STATIC_CUDA_RUNTIME OFF)

#FIND_PACKAGE(Protobuf REQUIRED)
#find_package( OpenCV REQUIRED )
#find_package( OpenCV HINTS /usr/local/opencv3 )

#EXECUTE_PROCESS(
#        COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} configure/config.proto --proto_path=configure --cpp_out=src
#)

include_directories(/usr/include/
        /usr/local/include/
        ${OpenCV_INCLUDE_DIRS}
        #${PROJECT_SOURCE_DIR}/src/
        )
link_directories(/usr/lib/
        /usr/local/lib/
        /usr/lib/x86_64-linux-gnu/
)

add_executable(vca
    ./vca.cpp
        )

target_link_libraries(vca
        opencv_core opencv_highgui opencv_imgproc
#        ${OpenCV_LIBS}
        glog zmq pthread mysqlcppconn protobuf curl
        avformat avcodec swscale swresample avutil
#        x264 pthread dl freetype z postproc va ass fdk-aac mp3lame opus vpx
#        vorbis vorbisenc lzma vdpau X11 va-x11 va-drm theora theoraenc theoradec
        )

