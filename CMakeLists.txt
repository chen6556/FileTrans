cmake_minimum_required(VERSION 3.22.0)
project(HttpServer VERSION 0.0.1)

if (MSVC)
    add_compile_options("/utf-8")
    add_compile_options("/arch:AVX2")
    add_compile_options("/GL")
    add_link_options("/LTCG")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS)
link_directories(${Boost_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output/)

include_directories(inc)

add_executable(Receiver src/RunReceiver.cpp src/Receiver.cpp src/Session.cpp)
target_link_libraries(Receiver PRIVATE ${Boost_LIBRARIES})

add_executable(Sender src/RunSender.cpp src/Sender.cpp)
target_link_libraries(Sender PRIVATE ${Boost_LIBRARIES})