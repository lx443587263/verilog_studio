cmake_minimum_required(VERSION 3.20)
project(verilog_studio)

set(CMAKE_CXX_STANDARD 20)

MESSAGE(STATUS "operation system is ${CMAKE_SYSTEM}")

if(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(STATUS "current platform: Darwin ")
    set(LINK_DIR /usr/local/Cellar/graphviz/5.0.1/lib)
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")
    set(LINK_DIR /tmp/tmp.kJAYo8kAht/lib)
endif()

include_directories(${INC_DIR})
link_directories(${LINK_DIR})

add_executable(verilog_studio main.cpp rapidjson graphviz
        Services/Parse/Parse.cpp
        Services/Parse/Parse.hpp
        Services/Module/Module.cpp
        Services/Module/Module.hpp
        Common/Foundation/B_Object.hpp
        IService.hpp
        Common/Supporting/Tree.hpp
        Services/Hierarchy/Hierarchy.hpp Services/Hierarchy/Hierarchy.cpp Services/ChangeLine/ChangeLine.cpp Services/ChangeLine/ChangeLine.hpp Services/DrawTree/DrawTree.cpp Services/DrawTree/DrawTree.hpp)

if(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    target_link_libraries(verilog_studio cdt gvc cgraph)
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_link_libraries(verilog_studio ${LINK_DIR}/libcdt.so.5.0.0 ${LINK_DIR}/libgvc.so.6.0.0 ${LINK_DIR}/libcgraph.so.6.0.0)
endif()