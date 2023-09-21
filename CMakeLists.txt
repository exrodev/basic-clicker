cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME "basic-clicker")

project(${PROJECT_NAME} C)
include_directories(src)

if(NOT DEFINED SOURCES_LIST)
    file(GLOB_RECURSE SOURCES_LIST CONFIGURE_DEPENDS src/*.c)
endif()

add_executable(${PROJECT_NAME} ${SOURCES_LIST})
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")
