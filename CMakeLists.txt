# ModelLibrary/CMakeLists.txt

#define minimum CMake version
cmake_minimum_required( VERSION 2.8.11 )

PROJECT( 2D_Platformer )

#include CTest to allow test creation
include(CTest)

#include relevant CMakeLists files
include(Src/CMakeLists.txt)
include(Inc/CMakeLists.txt)

# Lingk openGL
find_package(OpenGL REQUIRED)
message(STATUS "Found OpenGL in ${OpenGL_INCLUDE_DIR}")

add_subdirectory(glfw-cmake)
add_subdirectory(glm-cmake)
#add_subdirectory(SOIL2-cmake)
add_subdirectory(freetype-cmake)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Inc/helpers/RootDir.h.in ${CMAKE_CURRENT_SOURCE_DIR}/Inc/helpers/RootDir.h)
include_directories(${CMAKE_BINARY_DIR}/resource)

#list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/SOIL2-cmake/lib")
add_library(libSoil SHARED IMPORTED GLOBAL)
set_property(TARGET libSoil PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/SOIL2-cmake/lib/soil2-debug.dll")
set_property(TARGET libSoil PROPERTY IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/SOIL2-cmake/lib/libsoil2-debug.a")

add_library(gladLib ${CMAKE_CURRENT_SOURCE_DIR}/glad/glad.c ${CMAKE_CURRENT_SOURCE_DIR}/glad/glad/glad.h)
target_include_directories (gladLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad)
		 
#define minimum C++ version
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#include everything from current directory
set( CMAKE_INCLUDE_CURRENT_DIR ON )

# Make an executable
add_executable(2DPlatformer MACOSX_BUNDLE 
main.cpp
${game_includes}
${game_sources})

target_link_libraries( 2DPlatformer opengl32)
target_link_libraries( 2DPlatformer gladLib)
target_link_libraries( 2DPlatformer glfw)
target_link_libraries( 2DPlatformer glm)
target_link_libraries( 2DPlatformer freetype)
target_link_libraries( 2DPlatformer libSoil)

target_include_directories (2DPlatformer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glfw-cmake/include)
target_include_directories (2DPlatformer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad)
target_include_directories (2DPlatformer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glm-cmake/glm)
target_include_directories (2DPlatformer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/SOIL2-cmake)
target_include_directories (2DPlatformer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/freetype-cmake/include)
target_include_directories (2DPlatformer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Inc)







