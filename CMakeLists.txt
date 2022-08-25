cmake_minimum_required(VERSION 3.20)
project(verilog_studio)

set(CMAKE_CXX_STANDARD 20)

add_executable(verilog_studio main.cpp rapidjson Parse/Parse.cpp Parse/Parse.hpp Module/Module.cpp Module/Module.hpp)
