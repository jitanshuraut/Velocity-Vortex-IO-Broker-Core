cmake_minimum_required(VERSION 3.10)
project(IOBroker)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_library(HIREDIS_LIB hiredis REQUIRED)
find_library(SQLITE3_LIB sqlite3 REQUIRED)


add_executable(publisher src/publisher.cpp)
add_executable(subscriber src/subscriber.cpp)

target_link_libraries(publisher ${HIREDIS_LIB} ${SQLITE3_LIB})
target_link_libraries(subscriber ${HIREDIS_LIB} ${SQLITE3_LIB})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)
