cmake_minimum_required(VERSION 3.31)
project(Tower_defence)

set(CMAKE_CXX_STANDARD 14)

include_directories(includes)
include_directories(includes/logic)
include_directories(includes/logic/controllers)
include_directories(includes/logic/models)
include_directories(source)

add_executable(Tower_defence
        includes/logic/controllers/SettingsController.hpp
        includes/logic/models/ScoreManager.hpp
        includes/logic/models/tower.hpp
        source/logic/controllers/SettingsController.cpp
        source/logic/models/ScoreManager.cpp
        source/logic/models/tower.cpp
        includes/utils/Position.h
        includes/utils/Level.h
        includes/utils/LevelLoader.h
        includes/utils/Pathnode.h

        )
