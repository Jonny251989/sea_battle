set(target computer)

add_library(${target} STATIC computer.cpp)

target_include_directories(${target} PUBLIC .)

target_link_libraries (${target} items gamer game)