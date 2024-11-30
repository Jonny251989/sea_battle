set(target items)

add_library(${target} STATIC control.cpp ship.cpp)

target_include_directories(${target} PUBLIC .)

target_link_libraries (${target} gamer game )