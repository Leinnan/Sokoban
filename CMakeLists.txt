#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 2.6)


# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

set( PROJECT_NAME "SFML_Sokoban" )
project(${PROJECT_NAME})

# Set version information in a config.h file
set(myproject_VERSION_MAJOR 1)
set(myproject_VERSION_MINOR 0)
configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )
include_directories("${PROJECT_BINARY_DIR}")

# Leinnan my test

include_directories(src)
include_directories(src/Arkona)
file(GLOB_RECURSE SOURCES src/*)

set (CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")


# Define sources and executable
set(EXECUTABLE_NAME ${PROJECT_NAME})
add_executable(${EXECUTABLE_NAME} ${SOURCES} main.cpp src/StartMenu.cpp src/StartMenu.h)

set(CMAKE_MODULE_PATH "/usr/share/cmake-3.6/Modules" "${PROJECT_SOURCE_DIR}/SFML-2.4.0/cmake/Modules" "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

# Detect and add SFML
##set(CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()


# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)


# CPack packaging
include(InstallRequiredSystemLibraries)
# set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${myproject_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${myproject_VERSION_MINOR}")
include(CPack)


# copy files
file(COPY "content/gfx" DESTINATION "${CMAKE_BINARY_DIR}")
file(COPY "content/maps" DESTINATION "${CMAKE_BINARY_DIR}")
file(COPY "content/maps_list.txt" DESTINATION "${CMAKE_BINARY_DIR}")
