set(target widget)

add_library(${target} STATIC widget.cpp)

target_include_directories(${target} PUBLIC .)

target_link_libraries (${target} items view gamer game computer )