cmake_minimum_required(VERSION 3.24)
project(Corpse)

set(CMAKE_CXX_STANDARD 20)

add_executable(Corpse main.cpp client/client.cpp client/client.hpp encryption/encryptor.cpp encryption/encryptor.hpp)
