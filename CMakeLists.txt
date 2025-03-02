cmake_minimum_required(VERSION 3.15)
project(qr_reader LANGUAGES C CXX)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_C_COMPILER "clang")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

if(WIN32)
    set(OpenCV_DIR "C:/opencv2")
elseif(UNIX)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(OpenCV REQUIRED opencv4)
endif()

find_package(OpenCV REQUIRED)

MESSAGE(STATUS "Include dirs: ${OpenCV_INCLUDE_DIRS}")
MESSAGE(STATUS "Link libraries: ${OpenCV_LIBS}")

include_directories(${OpenCV_INCLUDE_DIRS})

set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/qr_reader.cpp
)

add_executable(qr_reader ${SOURCES})

target_link_libraries(qr_reader ${OpenCV_LIBS})
