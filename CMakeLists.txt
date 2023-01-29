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

# Build Configuration Information
message(STATUS "* ============================== *")
message(STATUS "| OS           : ${CMAKE_SYSTEM_NAME}           |")
message(STATUS "| Build type   : ${CMAKE_BUILD_TYPE}           |")
message(STATUS "| Generator    : ${CMAKE_GENERATOR}  |")
message(STATUS "| CXX standard : ${CMAKE_CXX_STANDARD}              |")
message(STATUS "* ============================== *")