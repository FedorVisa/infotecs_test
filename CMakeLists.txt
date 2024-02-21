cmake_minimum_required(VERSION 3.22)
project(infotecs)

set(CMAKE_CXX_STANDARD 17)

add_executable(program_1
        programs/program_1/sender.hpp
        programs/program_1/sender.cpp
        programs/program_1/parser.hpp)

add_executable( program_2
        programs/program_2/receiver.cpp
        programs/program_2/receiver.hpp
)
