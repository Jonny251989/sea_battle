set(target game)

add_library(${target} STATIC game.cpp)

target_include_directories(${target} PUBLIC .)

target_link_libraries (${target} items computer gamer view widget)