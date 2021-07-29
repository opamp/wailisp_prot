cmake_minimum_required(VERSION 3.20.0)
project(WaiLisp VERSION 0.1.0 LANGUAGES CXX)
#set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_SOURCE_DIR}/cmake/")

# Qt6
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(PkgConfig)

# Guile
pkg_check_modules(GUILE3 REQUIRED guile-3.0)
include_directories(${GUILE3_INCLUDE_DIRS})

set(EXEFILE_NAME wailisp)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
