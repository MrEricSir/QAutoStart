cmake_minimum_required(VERSION 3.16)
project(QAutoStart LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core)

add_library(QAutoStart STATIC
  src/QAutoStart.h
  src/QAutoStart.cpp
)

if(WIN32)
  target_sources(QAutoStart PRIVATE
    src/backends/QAutoStartWin.h
    src/backends/QAutoStartWin.cpp
  )
endif()

if(APPLE)
  target_sources(QAutoStart PRIVATE
    src/backends/QAutoStartMac.h
    src/backends/QAutoStartMac.cpp
  )
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  target_sources(QAutoStart PRIVATE
    src/backends/QAutoStartLinux.h
    src/backends/QAutoStartLinux.cpp
  )
endif()

target_include_directories(QAutoStart PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(QAutoStart PUBLIC Qt6::Core)

add_subdirectory(example)

enable_testing()
add_subdirectory(tests)
