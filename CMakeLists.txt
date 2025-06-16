cmake_minimum_required(VERSION 3.21)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds are not allowed.")
endif()

project(nt4-client)

# Generate compile_commands.json by default
if(NOT CMAKE_EXPORT_COMPILE_COMMANDS)
    set(CMAKE_EXPORT_COMPILE_COMMANDS "YES" CACHE STRING "" FORCE)
endif()

# Place libraries in lib and binaries in bin
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE cpp_src src/*.cpp)
add_executable(nt4-client ${cpp_src})

target_compile_features(nt4-client PUBLIC cxx_std_20)
if(NOT MSVC)
    target_compile_options(nt4-client PRIVATE -Wall -pedantic -Wextra -Werror)
else()
    # Suppress the following warnings:
    #   * C4244: lossy conversion
    target_compile_options(nt4-client PRIVATE /wd4244 /WX)
endif()
target_include_directories(nt4-client PUBLIC src)

include(FetchContent)

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
fetchcontent_declare(
    wpilib
    GIT_REPOSITORY https://github.com/wpilibsuite/allwpilib.git
    GIT_TAG v2025.3.2
    EXCLUDE_FROM_ALL
    SYSTEM
)
fetchcontent_makeavailable(wpilib)
target_link_libraries(nt4-client PUBLIC ntcore)
