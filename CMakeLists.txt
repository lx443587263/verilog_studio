cmake_minimum_required(VERSION 3.20)
project(verilog_studio)

set(CMAKE_CXX_STANDARD 20)

add_executable(verilog_studio main.cpp rapidjson
        Services/Parse/Parse.cpp
        Services/Parse/Parse.hpp
        Services/Module/Module.cpp
        Services/Module/Module.hpp
        Common/Foundation/B_Object.hpp
        IService.hpp
        Common/Supporting/Tree.hpp
        Services/Hierarchy/Hierarchy.hpp Services/Hierarchy/Hierarchy.cpp Services/ChangeLine/ChangeLine.cpp Services/ChangeLine/ChangeLine.hpp)
