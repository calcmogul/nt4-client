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

target_compile_features(nt4-client PUBLIC cxx_std_23)
target_include_directories(nt4-client PUBLIC src)

set(BUILD_SHARED_LIBS OFF)
set(WPILIB_NO_WERROR ON)
set(WPILIB_WITH_CSCORE OFF)
set(WPILIB_WITH_GUI OFF)
set(WPILIB_WITH_JAVA OFF)
set(WPILIB_WITH_NTCORE ON)
set(WPILIB_WITH_SIMULATION_MODULES OFF)
set(WPILIB_WITH_TESTS OFF)
set(WPILIB_WITH_WPILIB OFF)
set(WPILIB_WITH_WPIMATH OFF)
FetchContent_Declare(
    wpilib
    GIT_REPOSITORY https://github.com/wpilibsuite/allwpilib.git
    GIT_TAG v2027.0.0-alpha-7
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(wpilib)
target_link_libraries(nt4-client PUBLIC ntcore)
