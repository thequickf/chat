cmake_minimum_required(VERSION 3.0.0)
project(server)

set(CMAKE_CXX_STANDARD 11)

# third party
find_package(websocketpp REQUIRED)
include_directories(${WEBSOCKETPP_INCLUDE_DIR})
find_package(Boost REQUIRED system)
include_directories(${Boost_INCLUDE_DIR})

set(SERVER_SOURCES
        src/main.cpp
        src/user.h src/user.cpp
        src/userlist.h src/userlist.cpp
        src/server.h src/server.cpp)

add_executable(server ${SERVER_SOURCES})

target_link_libraries (server ${Boost_LIBRARIES})
