# !!! WARNING !!! AUTO-GENERATED FILE, PLEASE DO NOT MODIFY IT AND USE
# https://docs.platformio.org/page/projectconf/section_env_build.html#build-flags
#
# If you need to override existing CMake configuration or add extra,
# please create `CMakeListsUser.txt` in the root of project.
# The `CMakeListsUser.txt` will not be overwritten by PlatformIO.

cmake_minimum_required(VERSION 3.13)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

project("ArduChronoSveglia" C CXX)

include(CMakeListsPrivate.txt)
include_directories(F:/SyncFiles/Informatica/Arduino/libraries/ArduWin)
include_directories(F:/SyncFiles/Informatica/Arduino/libraries/Alarm)
include_directories(F:/SyncFiles/Informatica/Arduino/libraries/LiquidCrystal_I2C)
include_directories(F:/SyncFiles/Informatica/Arduino/libraries/RTClib)
include_directories(F:/SyncFiles/Informatica/Arduino/libraries/SimpleDHT)
include_directories(F:/SyncFiles/Informatica/Arduino/libraries/TEA5767Radio)
include_directories(F:/SyncFiles/Informatica/Arduino/libraries/TimeDate)
include_directories(F:/SyncFiles/Informatica/Arduino/libraries/Tone)
include_directories(F:/SyncFiles/Informatica/Arduino/libraries/SD)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CMakeListsUser.txt)
include(CMakeListsUser.txt)
endif()

add_custom_target(
    Production ALL
    COMMAND platformio -c clion run "$<$<NOT:$<CONFIG:All>>:-e${CMAKE_BUILD_TYPE}>"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    Debug ALL
    COMMAND platformio -c clion run --target debug "$<$<NOT:$<CONFIG:All>>:-e${CMAKE_BUILD_TYPE}>"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(Z_DUMMY_TARGET ${SRC_LIST} src/mode.cpp)
