cmake_minimum_required(VERSION 3.10)
project(Galapoo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

include_directories(include)
add_executable(Galapoo src/main.cpp src/jugador.cpp src/bala.cpp src/enemigo.cpp src/explosion.cpp src/jefeFinal.cpp)
target_link_libraries(Galapoo sfml-graphics sfml-window sfml-system sfml-audio)
