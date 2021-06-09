cmake_minimum_required(VERSION 3.19)
project(sauerkraut)

set(CMAKE_CXX_STANDARD 20)
option(RELEASE_BUILD "Enable release build" OFF) #OFF by default

if (RELEASE_BUILD)
    SET(GCC_COVERAGE_COMPILE_FLAGS "-fno-rtti -fno-exceptions -Wall -Wno-unused-function -Wno-unused-variable -Wno-unused-but-set-variable -fomit-frame-pointer -Wall -O2 -ftree-loop-vectorize -flto")
    SET(GCC_COVERAGE_LINK_FLAGS "-pthread -flto")
else ()
    SET(GCC_COVERAGE_COMPILE_FLAGS "-fno-rtti -fexceptions -Wall -Wno-unused-function -Wno-unused-variable -Wno-unused-but-set-variable -Wall -O0 -g3 -D_FORTIFY_SOURCE=1 -fasynchronous-unwind-tables -Werror=format-security -DDEBUG=1 -D_DEBUG=1 ")
    SET(GCC_COVERAGE_LINK_FLAGS "-pthread")
endif (RELEASE_BUILD)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

add_executable(sauerkraut main.cpp config/Config.h config/Config.cpp log/Logger.h log/LogHandler.h log/LogHandler.cpp log/loggers/FileLogger.h log/loggers/FileLogger.cpp utils/LockedQueue.h)