cmake_minimum_required(VERSION 3.15)
project (SeaBattle CXX)

set(target SeaBattle)
set(CMAKE_PREFIX_PATH $ENV{HOME}/Qt)
set(CMAKE_CXX_STANDARD)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Core Widgets Network REQUIRED)

set(HEADERS
    control.h
    computer.h
    gamer.h
    ship.h
    game.h
    view.h
    widget.h
)
set(SOURCES
    control.cpp
    computer.cpp
    gamer.cpp
    ship.cpp
    game.cpp
    view.cpp
    widget.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} main.cpp)
target_link_libraries ( ${target} Qt6::Widgets Qt6::Core )
