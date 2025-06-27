cmake_minimum_required(VERSION 3.28)
project(GAME)

set(GAME_SOURCE_DIR "src")

set(GAME_INCLUDE_DIRS 
    src
)

set(GAME_SOURCES
    src/main.cpp
    src/Playground.hpp
    src/Playground.cpp
)

add_executable(game ${GAME_SOURCES})
include_directories(${GAME_INCLUDE_DIRS})
target_link_libraries(game NJIN::NJIN)


set(GAME_RESOURCE_FILES
resourcefile.txt
appresourcedir/appres.txt)

set_target_properties(game PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:game>"
                                                VS_DEBUGGER_COMMAND           "$<TARGET_FILE:game>"
                                                VS_DEBUGGER_ENVIRONMENT       "PATH=%PATH%;${CMAKE_PREFIX_PATH}/bin"
                                                RESOURCE "${GAME_RESOURCE_FILES}"
)