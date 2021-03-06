cmake_minimum_required(VERSION 2.8)
project(eclipsed)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

#SET(CMAKE_AUTOMOC ON)
#find_package(Qt5Widgets REQUIRED)
#find_package(Qt5Core REQUIRED)

#set(THREADS_PREFER_PTHREAD_FLAG ON) #prefer? required

SET(CMAKE_CXX_STANDARD 11)

find_package(Threads REQUIRED)
find_package(jsoncpp REQUIRED)

INCLUDE_DIRECTORIES(${JSONCPP_INCLUDE_DIRS})
#qt5_wrap_ui(UISRC ui/mainwindow.ui)
#qt5_wrap_cpp(MOCSRC src/mainwindow.cpp)

#SET(INCLUDES src/.h)
SET(SOURCES src/Action.cpp
			src/game.cpp
			src/GameState.cpp
			src/main.cpp
			#src/mainwindow.cpp
			src/map.cpp
			#src/planet.cpp
			src/PlayerBoard.cpp
			src/race.cpp
			src/resource.cpp
			src/sector.cpp
			src/sectorlink.cpp
			src/ship.cpp
			src/shipblueprint.cpp
			src/tech.cpp)


# Set a default build type for single-configuration
# CMake generators if no build type is set.
IF(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
   SET(CMAKE_BUILD_TYPE Debug)
ENDIF(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)

# Select flags.
SET(CMAKE_CXX_FLAGS "-Wall -fno-rtti")
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
SET(CMAKE_CXX_FLAGS_RELEASE "-O2")
SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")

#source_group("Source Files" FILES ${SOURCES})
#source_group(includes FILES ${INCLUDES})

add_executable(eclipsed ${SOURCES})# ${MOCSRC} ${UISRC})

target_link_libraries(eclipsed Threads::Threads ${JSONCPP_LIBRARIES})# Qt5::Widgets)
