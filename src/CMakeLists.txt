cmake_minimum_required(VERSION 3.19)
project(sauerkraut)

add_subdirectory(sub/libcubescript)
include_directories(sub/enet/include)
add_subdirectory(sub/enet)

set(CMAKE_CXX_STANDARD 20)
option(RELEASE_BUILD "Enable release build" ON) #OFF by default

SET(CMAKE_INCLUDE_DIRECTORIES_BEFORE ON)



add_executable(sauerkraut main.cpp config/Config.h config/Config.cpp log/iLogger.h log/LogHandler.h log/LogHandler.cpp log/loggers/FileLogger.h log/loggers/FileLogger.cpp utils/LockedQueue.h engine/engine.h engine/engine.cpp utils/FileSystem.h scripting/ScriptingHandler.cpp scripting/ScriptingHandler.h scripting/bindings/LibCubeScript.cpp scripting/bindings/LibCubeScript.h utils/stringhelper.h config/ConfigSection.h engine/screen.h engine/screen.cpp engine/state.h log/loggers/OutLogger.cpp log/loggers/OutLogger.h engine/hal/HalHandler.cpp engine/hal/HalHandler.h engine/hal/video/Sdl2VideoHandler.cpp engine/hal/video/Sdl2VideoHandler.h engine/hal/iVideo.h network/NetworkHandler.cpp network/NetworkHandler.h game/client/GameClient.cpp game/client/GameClient.h game/GameState.cpp game/GameState.h engine/entities/Player.cpp engine/entities/Player.h game/Auth.cpp game/Auth.h engine/hal/sound/Sdl2SoundHandler.cpp engine/hal/sound/Sdl2SoundHandler.h engine/hal/iSound.h game/Weapon.cpp game/Weapon.h game/GameData.cpp game/GameData.h engine/entities/Phys.cpp engine/entities/Phys.h engine/entities/States.h engine/entities/Dynamic.cpp engine/entities/Dynamic.h engine/physics/Ragdoll.cpp engine/physics/Ragdoll.h engine/entities/Base.cpp engine/entities/Base.h engine/entities/Light.h engine/entities/Light.cpp game/PlayerState.cpp game/PlayerState.h engine/entities/AnimInfo.h game/Ai.cpp game/Ai.h game/items.h engine/entities/enttypes.h game/gamemodes.h game/sounds.h engine/particles/particles.h engine/hal/video/iHardwareAccel.h engine/hal/video/hardwareaccel/Opengl.cpp engine/hal/video/hardwareaccel/Opengl.h engine/hal/video/hardwareaccel/glexts.h)
get_target_property(TEMP_COMPILE_FLAGS sauerkraut COMPILE_FLAGS)
if(TEMP_COMPILE_FLAGS STREQUAL "TEMP_COMPILE_FLAGS-NOTFOUND")
    SET(TEMP_COMPILE_FLAGS "") # Set to empty string
else()
    SET(TEMP_COMPILE_FLAGS "${TEMP_COMPILE_FLAGS} ") # A space to cleanly separate from existing content
endif()

if(RELEASE_BUILD)
    SET(TEMP_LINK_FLAGS "-lrt -lpthread flto -lX11 -lSDL2 -lSDL2_image -lSDL2_mixer -lz -lGLU -lGL")
    SET(TEMP_COMPILE_FLAGS "${TEMP_COMPILE_FLAGS} -D_REENTRANT -fno-rtti -fno-exceptions -Wall -Wno-unused-function -Wno-unused-variable -Wno-unused-but-set-variable -fomit-frame-pointer -Wall -O2 -ftree-loop-vectorize -flto" )
else()
    SET(TEMP_LINK_FLAGS "-lrt -lpthread -lX11 -lSDL2  -lSDL2_image -lSDL2_mixer -lz -lGLU -lGL")
    SET(TEMP_COMPILE_FLAGS "${TEMP_COMPILE_FLAGS} -D_REENTRANT -fno-rtti -fexceptions -Wall -Wno-unused-function -Wno-unused-variable -Wno-unused-but-set-variable -Wall -O0 -g3 -D_FORTIFY_SOURCE=1 -fasynchronous-unwind-tables -Werror=format-security -DDEBUG=1 -D_DEBUG=1" )
endif(RELEASE_BUILD)
set_target_properties(sauerkraut PROPERTIES COMPILE_FLAGS ${TEMP_COMPILE_FLAGS} )
target_link_libraries(sauerkraut libcubescript enet "${TEMP_LINK_FLAGS}")
