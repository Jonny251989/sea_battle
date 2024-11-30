set(target gamer)

add_library(${target} STATIC gamer.cpp)

target_include_directories(${target} PUBLIC .)

target_link_libraries (${target} items computer game)