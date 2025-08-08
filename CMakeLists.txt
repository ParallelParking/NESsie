cmake_minimum_required(VERSION 3.31)
project(NESsie)

set(CMAKE_CXX_STANDARD 20)

add_executable(NESsie main.cpp
        Bus.cpp
        Bus.h
        Emu6502.cpp
        Emu6502.h
)
