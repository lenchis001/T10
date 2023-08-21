# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("T10")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)

if(UNIX)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wl,--no-undefined")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
SET(CMAKE_CXX_FLAGS -Wl,--no-undefined)
endif()

set(Game_DEFINITIONS _IRR_WCHAR_FILESYSTEM NO_IRR_COMPILE_WITH_DIRECTINPUT_JOYSTICK_ UNICODE _CRT_SECURE_NO_WARNINGS
    CACHE INTERNAL "${PROJECT_NAME}: Definitions" FORCE)
add_compile_definitions(${Game_DEFINITIONS})

include_directories("include" "src")

file(GLOB_RECURSE game_sources_files "*.cpp")
add_library(Game SHARED ${game_sources_files} "src/BLL/Services/Storage/IStorageService.h")

if(MSVC)
    if(NOT EXISTS ${CMAKE_BINARY_DIR}/packages/boost)
        find_program(NUGET_EXE NAMES ${PROJECT_SOURCE_DIR}/tools/nuget)
        exec_program(${NUGET_EXE} ARGS install "boost" -Version 1.82.0 -ExcludeVersion -OutputDirectory ${CMAKE_BINARY_DIR}/packages)
        exec_program(${NUGET_EXE} ARGS install "boost_filesystem-vc143" -Version 1.82.0 -ExcludeVersion -OutputDirectory ${CMAKE_BINARY_DIR}/packages)
        exec_program(${NUGET_EXE} ARGS install "boost_thread-vc143" -Version 1.82.0 -ExcludeVersion -OutputDirectory ${CMAKE_BINARY_DIR}/packages)
        exec_program(${NUGET_EXE} ARGS install "boost_chrono-vc143" -Version 1.82.0 -ExcludeVersion -OutputDirectory ${CMAKE_BINARY_DIR}/packages)
        exec_program(${NUGET_EXE} ARGS install "boost_locale-vc143" -Version 1.82.0 -ExcludeVersion -OutputDirectory ${CMAKE_BINARY_DIR}/packages)
    endif()

    include_directories(${CMAKE_BINARY_DIR}/packages/boost/lib/native/include)
    target_link_directories(Game PUBLIC 
        ${CMAKE_BINARY_DIR}/packages/boost_filesystem-vc143/lib/native
        ${CMAKE_BINARY_DIR}/packages/boost_thread-vc143/lib/native
        ${CMAKE_BINARY_DIR}/packages/boost_chrono-vc143/lib/native
        ${CMAKE_BINARY_DIR}/packages/boost_locale-vc143/lib/native
        ${CMAKE_BINARY_DIR}/packages/boost_iostreams-vc143/lib/native
    )
else()
    include_directories($ENV{BOOST_ROOT})
    file(GLOB external_lib_files $ENV{BOOST_ROOT}/stage/lib/*.a)
endif()

target_link_libraries(Game PUBLIC ${external_lib_files})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Game PROPERTY CXX_STANDARD 17)
endif()

add_custom_command(TARGET Game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Resources ${CMAKE_BINARY_DIR}/Resources)