set(target view)

add_library(${target} STATIC view.cpp)

target_include_directories(${target} PUBLIC .)

target_link_libraries (${target} items widget gamer game computer Qt6::Widgets)