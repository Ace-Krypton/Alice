cmake_minimum_required(VERSION 3.24)
project(Corpse)

set(CMAKE_CXX_STANDARD 20)

add_executable(Corpse src/main.cpp src/client/client.cpp src/client/client.hpp src/encryption/encryptor.cpp src/encryption/encryptor.hpp)
