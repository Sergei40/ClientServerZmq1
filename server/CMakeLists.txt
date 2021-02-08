cmake_minimum_required(VERSION 3.16.3)

project(server_zmq VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_FALGS "${CMAKE_CXX_FLAGS} -Wall")

message("\n WARNIIIIIING \n") 

find_library(ZeroMQ_LIBRARY NAMES zmq)

add_executable(server server.cpp)

target_link_libraries(server PUBLIC ${ZeroMQ_LIBRARY})
