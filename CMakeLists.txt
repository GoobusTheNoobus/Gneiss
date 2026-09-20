# =============================================================
#
#                        G N E I S S
#
# =============================================================
#
# Gneiss is a toy programming language developed in C++20
#
# Gneiss is licensed under the MIT license
# Copyright (c) 2026  GoobusTheNoobus

cmake_minimum_required(VERSION 3.20)
project(Gneiss LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

add_subdirectory(gneic) # compiler