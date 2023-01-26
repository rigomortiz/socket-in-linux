cmake_minimum_required(VERSION 3.6)
project(socket_in_linux)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES server/run-server.c  server/server.h server/server.c client/client.h client/run-client.c client/client.c)
add_executable(socket_in_linux ${SOURCE_FILES})