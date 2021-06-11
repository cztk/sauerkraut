cmake_minimum_required(VERSION 3.19)
project(sauerkraut)

set(CMAKE_CXX_STANDARD 20)
option(RELEASE_BUILD "Enable release build" OFF) #OFF by default

if (RELEASE_BUILD)
    SET(GCC_COVERAGE_COMPILE_FLAGS "-D_REENTRANT -fno-rtti -fno-exceptions -Wall -Wno-unused-function -Wno-unused-variable -Wno-unused-but-set-variable -fomit-frame-pointer -Wall -O2 -ftree-loop-vectorize -flto")
    SET(GCC_COVERAGE_LINK_FLAGS "-pthread -flto -lSDL2")
else ()
    SET(GCC_COVERAGE_COMPILE_FLAGS "-D_REENTRANT -fno-rtti -fexceptions -Wall -Wno-unused-function -Wno-unused-variable -Wno-unused-but-set-variable -Wall -O0 -g3 -D_FORTIFY_SOURCE=1 -fasynchronous-unwind-tables -Werror=format-security -DDEBUG=1 -D_DEBUG=1 ")
    SET(GCC_COVERAGE_LINK_FLAGS "-pthread -lSDL2 ")
endif (RELEASE_BUILD)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

add_subdirectory(sub/libcubescript)
add_subdirectory(sub/enet)

add_executable(sauerkraut main.cpp config/Config.h config/Config.cpp log/iLogger.h log/LogHandler.h log/LogHandler.cpp log/loggers/FileLogger.h log/loggers/FileLogger.cpp utils/LockedQueue.h engine/engine.h engine/engine.cpp utils/FileSystem.h scripting/ScriptingHandler.cpp scripting/ScriptingHandler.h scripting/bindings/LibCubeScript.cpp scripting/bindings/LibCubeScript.h utils/stringhelper.h config/ConfigSection.h engine/screen.h engine/screen.cpp engine/state.h log/loggers/OutLogger.cpp log/loggers/OutLogger.h engine/hal/HalHandler.cpp engine/hal/HalHandler.h engine/hal/handler/Sdl2Handler.cpp engine/hal/handler/Sdl2Handler.h engine/hal/iHandler.h)
target_link_libraries(sauerkraut libcubescript enet SDL2main SDL2)