cmake_minimum_required(VERSION 3.28)

project(nt4-client)

include(FetchContent)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Place libraries in lib and binaries in bin
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE cpp_src src/*.cpp)
add_executable(nt4-client ${cpp_src})

if(NOT MSVC)
    target_compile_options(nt4-client PRIVATE -Wall -Wextra -pedantic)
else()
    # Suppress the following warnings:
    #   * C4244: lossy conversion
    target_compile_options(nt4-client PRIVATE /wd4244)
endif()
set_property(TARGET nt4-client PROPERTY COMPILE_WARNING_AS_ERROR ON)

target_compile_features(nt4-client PUBLIC cxx_std_20)
target_include_directories(nt4-client PUBLIC src)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(WITH_CSCORE OFF CACHE INTERNAL "With CSCore")
set(WITH_GUI OFF CACHE INTERNAL "With GUI")
set(WITH_JAVA OFF CACHE INTERNAL "With Java")
set(WITH_NTCORE ON CACHE INTERNAL "With NTCore")
set(WITH_PROTOBUF OFF CACHE BOOL "" FORCE)
set(WITH_SIMULATION_MODULES OFF CACHE INTERNAL "With Simulation Modules")
set(WITH_TESTS OFF CACHE INTERNAL "With Tests")
set(WITH_WPILIB OFF CACHE INTERNAL "With WPILib")
set(WITH_WPIMATH OFF CACHE INTERNAL "With WPIMath")
FetchContent_Declare(
    wpilib
    GIT_REPOSITORY https://github.com/wpilibsuite/allwpilib.git
    GIT_TAG v2025.3.2
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(wpilib)
target_link_libraries(nt4-client PUBLIC ntcore)
