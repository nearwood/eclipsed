cmake_minimum_required(VERSION 2.8)
project(eclipsed)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

#SET(CMAKE_AUTOMOC ON)
#find_package(Qt5Widgets REQUIRED)
#find_package(Qt5Core REQUIRED)

find_package(jsoncpp REQUIRED)

INCLUDE_DIRECTORIES(${JSONCPP_INCLUDE_DIRS})
#qt5_wrap_ui(UISRC ui/mainwindow.ui)
#qt5_wrap_cpp(MOCSRC src/mainwindow.cpp)

#SET(INCLUDES src/.h)
SET(SOURCES src/main.cpp
			src/Action.cpp
			src/GameState.cpp
			src/galacticcenter.cpp
			src/planet.cpp
			src/ring1.cpp
			src/sector.cpp
			src/ship.cpp
			src/game.cpp
			src/player.cpp
			src/ring2.cpp
			src/sectorlink.cpp
			src/startingsector.cpp
			#src/mainwindow.cpp
			src/resource.cpp
			src/ring3.cpp
			src/shipblueprint.cpp
			src/tech.cpp)

#source_group("Source Files" FILES ${SOURCES})
#source_group(includes FILES ${INCLUDES})

add_executable(eclipsed ${SOURCES})# ${MOCSRC} ${UISRC})
#add_executable(eclipsed-trainer ${TRAINER_SOURCES})

target_link_libraries(eclipsed ${JSONCPP_LIBRARIES})# Qt5::Widgets)
#target_link_libraries(eclipsed-trainer ${OpenCV_LIBS} Qt5::Widgets)
