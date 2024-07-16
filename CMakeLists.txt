cmake_minimum_required(VERSION 3.28)


set(PROJECT_NAME maZe)	 
project("${PROJECT_NAME}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

FILE( COPY "${CMAKE_CURRENT_SOURCE_DIR}/src"
    DESTINATION "${CMAKE_CURRENT_BINARY_DIR}" )

add_definitions(-DSFML_STATIC)

include_directories("/src")
include_directories("SFML/include/")
include_directories("inc/")
link_directories("SFML/lib/")

add_executable("${PROJECT_NAME}" main.cpp map.hpp ray.hpp texturing.hpp)
											
target_link_libraries("${PROJECT_NAME}" sfml-graphics-s-d
						  sfml-window-s-d
						  sfml-system-s-d
						  opengl32
						  freetype
						  winmm
						  gdi32
						  sfml-audio-s-d
						  openal32
						  flac
						  vorbisenc
						  vorbisfile
						  vorbis
						  ogg)