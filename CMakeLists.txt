cmake_minimum_required(VERSION 3.20)
project(Draft C CXX)

# Disabling in-source builds
if (PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
   message(FATAL_ERROR "In-source builds are not allowed!")
endif()

# Default build type
if (NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE "Debug")
endif()

# Setting the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# GTest
if (EXISTS ${CMAKE_CURRENT_LIST_DIR}/Extern/GTest/googletest/CMakeLists.txt)
   add_subdirectory(Extern/GTest)
   set(IS_GOOGLETEST_FOUND TRUE)
else()
   message(STATUS "GTest isn't found in ${CMAKE_CURRENT_LIST_DIR}/Extern")
   message(STATUS "Run the command git submodule update --init --recursive")
endif()

# PVS
include(CMake/SearchPvs.cmake)
is_pvs_available(${CMAKE_CURRENT_LIST_DIR}/Extern)

# Build Configuration Information
message(STATUS "* ============================== *")
message(STATUS "| OS           : ${CMAKE_SYSTEM_NAME}           |")
message(STATUS "| Build type   : ${CMAKE_BUILD_TYPE}           |")
message(STATUS "| Generator    : ${CMAKE_GENERATOR}  |")
message(STATUS "| CXX standard : ${CMAKE_CXX_STANDARD}              |")
if (IS_GOOGLETEST_FOUND)
   message(STATUS "| GTest        : Available       |")
else()
   message(STATUS "| GTest        : Not available   |")
endif()
if (IS_PVS_AVAILABLE)
   message(STATUS "| PVS          : Available       |")
else()
   message(STATUS "| PVS          : Not available   |")
endif()
message(STATUS "* ============================== *")

# Output directories
set(OUTPUT_DEBUG_DIR "${PROJECT_SOURCE_DIR}/Output/Debug")
set(OUTPUT_RELEASE_DIR "${PROJECT_SOURCE_DIR}/Output/Release")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_DEBUG_DIR}/Lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_DEBUG_DIR}/Lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_DEBUG_DIR}/Bin)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_RELEASE_DIR}/Lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_RELEASE_DIR}/Lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_RELEASE_DIR}/Bin)

# Subdirectories
add_subdirectory(Src)