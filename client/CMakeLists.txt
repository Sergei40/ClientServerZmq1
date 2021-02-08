cmake_minimum_required (VERSION 3.16.3) 

project (client_zmq VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

find_library(ZeroMQ_LIBRARY NAMES zmq)

add_executable(client client.cpp)

target_link_libraries(client  PUBLIC ${ZeroMQ_LIBRARY})
