cmake_minimum_required(VERSION 3.15)
project (SeaBattle CXX)

set(target SeaBattle)

set(CMAKE_AUTOMOC ON) # Автоматически запускает moc
set(CMAKE_AUTORCC ON) # Для ресурсов Qt
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

find_package(Qt6 REQUIRED COMPONENTS Core Widgets )

add_subdirectory(Ship)
add_subdirectory(Game)
add_subdirectory(View)
add_subdirectory(Players)

add_executable(${target} main.cpp)
    
target_link_libraries (${target} widget view Qt6::Widgets)