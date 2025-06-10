cmake_minimum_required(VERSION 3.31)
project(Tower_defence)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_PREFIX_PATH "C:/msys64/mingw64")

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(includes)
include_directories(includes/logic)
include_directories(includes/logic/controllers)
include_directories(includes/logic/models)
include_directories(source)

add_executable(Tower_defence
        includes/logic/controllers/SettingsController.h
        includes/logic/models/ScoreManager.h
        includes/logic/models/Tower.h
        source/logic/controllers/SettingsController.cpp
        source/logic/models/ScoreManager.cpp
        source/logic/models/tower.cpp
        includes/utils/Position.h
        includes/utils/Level.h
        includes/utils/LevelLoader.h
        includes/utils/Pathnode.h
        includes/logic/models/scoreEntry.h
        source/logic/models/Economy.cpp
        source/logic/models/Economy.h
        source/logic/models/Enemy.cpp
)

target_link_libraries(Tower_defence sfml-graphics sfml-window sfml-system)