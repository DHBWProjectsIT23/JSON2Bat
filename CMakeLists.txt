cmake_minimum_required(VERSION 3.27)

if (WIN32)
  message(FATAL_ERROR "This project is not supported on Windows")
endif()

set(PROJECT_NAME "jsonToBatch")

project(${PROJECT_NAME} VERSION 0.1.0)

set(SOURCES
  src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
  ${PROJECT_SOURCE_DIR}/include
)


