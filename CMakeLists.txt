cmake_minimum_required(VERSION 3.19)
project(sauerkraut)

set(CMAKE_CXX_STANDARD 20)

add_executable(sauerkraut main.cpp config/Config.h config/Config.cpp log/Logger.h log/LogHandler.h log/LogHandler.cpp log/loggers/FileLogger.h log/loggers/FileLogger.cpp)