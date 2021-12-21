cmake_minimum_required(VERSION 3.21)
project(boost_websockets)

set(CMAKE_CXX_STANDARD 14)

include(conan_3rdp/conanbuildinfo.cmake)
conan_basic_setup(TARGETS KEEP_RPATHS)

add_executable(boost_websockets main.cpp)

target_link_libraries(boost_websockets PUBLIC
        CONAN_PKG::boost
        )



