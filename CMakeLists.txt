# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("T10")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wl,--no-undefined")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
SET(CMAKE_CXX_FLAGS -Wl,--no-undefined)

set(Game_DEFINITIONS _IRR_WCHAR_FILESYSTEM NO_IRR_COMPILE_WITH_DIRECTINPUT_JOYSTICK_ UNICODE _CRT_SECURE_NO_WARNINGS
    CACHE INTERNAL "${PROJECT_NAME}: Definitions" FORCE)
add_compile_definitions(${Game_DEFINITIONS})

include_directories("include" "src")
if(MSVC)
    include_directories(${CMAKE_BINARY_DIR}/packages/boost/lib/native/include)
else()
    include_directories($ENV{BOOST_ROOT})
    file(GLOB external_lib_files $ENV{BOOST_ROOT}/stage/lib/*.a)
endif()


file(GLOB_RECURSE game_sources_files "*.cpp")
add_library(Game SHARED ${game_sources_files})

target_link_libraries(Game PUBLIC ${external_lib_files})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Game PROPERTY CXX_STANDARD 17)
endif()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})