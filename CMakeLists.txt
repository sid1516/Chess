cmake_minimum_required(VERSION 3.14)
project(CHESS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set( CMAKE_BUILD_TYPE Debug )
set(SOURCE_FILES src/main.cpp headers/Piece.h headers/Bishop.h src/Bishop.cpp headers/Queen.h src/Queen.cpp src/Piece.cpp headers/Knight.h src/Knight.cpp headers/Board.h headers/King.h src/King.cpp headers/Rook.h src/Rook.cpp headers/Pawn.h src/Pawn.cpp src/Board.cpp)
add_executable(HelloSFML ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(HelloSFML sfml-system sfml-window sfml-graphics sfml-audio sfml-network)