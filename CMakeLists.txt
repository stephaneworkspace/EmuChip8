cmake_minimum_required(VERSION 3.26)
project(EmuChip8 VERSION 0.0.1)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

include(FetchContent)

FetchContent_Declare(
        libsdl-org
        URL https://github.com/libsdl-org/SDL/releases/download/release-2.28.4/SDL2-2.28.4.tar.gz
)

FetchContent_MakeAvailable(libsdl-org)
if(NOT libsdl-org_POPULATED)
    FetchContent_Populate(libsdl-org)
    add_subdirectory(${libsdl-org_SOURCE_DIR} ${libsdl-org_BINARY_DIR})
endif()

add_executable(EmuChip8 src/main.c
        src/chip8memory.c
        src/chip8stack.c
        src/chip8keyboard.c
        src/chip8.c
        src/chip8screen.c)

target_include_directories(EmuChip8 PUBLIC include)
target_link_libraries(EmuChip8 PRIVATE SDL2::SDL2)