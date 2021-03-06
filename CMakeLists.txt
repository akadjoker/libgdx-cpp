project(gdx-cpp)

cmake_minimum_required(VERSION 2.8)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

include(cmake/gdx.cmake)
include(cmake/cotire.cmake)

set(ANDROID_NDK $ENV{ANDROID_NDK})

initialize_gdx()

include_directories(src)

link_directories(${LIBRARY_OUTPUT_PATH})

option(BUILD_BOX2D "Builds Box2D" TRUE)
option(BUILD_AS_SHARED_LIBRARIES "Build libraries as shared libraries instead of static" FALSE)

if(CMAKE_COMPILER_IS_GNUCXX)
    # get gnu compiler version number
    exec_program(${CMAKE_C_COMPILER} ARGS --version OUTPUT_VARIABLE _gcc_version_info)

    string (REGEX MATCH " [34]\\.[0-9]" _gcc_version "${_gcc_version_info}")
    string(REGEX REPLACE "[^0-9]*([0-9]+)\\.[0-9]+.*" "\\1" gcc_major_vers "${_gcc_version}")
    string(REGEX REPLACE "[^0-9]*[0-9]+\\.([0-9]+).*" "\\1" gcc_minor_vers "${_gcc_version}")
    # g++' -Wdouble-promotion needs at least version 4.6
    
    if(${gcc_major_vers} LESS 4 AND ${gcc_minor_vers} LESS 6)
        message(FATAL_ERROR "gdx++ requires a gcc that's newer than 4.5 to fully support the new c++11 standard. Please upgrade your ndk to r8b or newer if using android.")
    endif()
    
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wreorder")
endif()

if (BUILD_BOX2D)
    set(BOX2D_INSTALL TRUE)

    add_subdirectory(src/Box2D)
    add_subdirectory(src/gdx-cpp/physics/box2d)
endif()

if (GDX_BACKEND_IOS)
    add_subdirectory(src/gdx-cpp/backends/ios)
    SET(BUILD_AGG TRUE)
elseif(GDX_BACKEND_ANDROID)
    add_subdirectory(src/gdx-cpp/backends/android)
    SET(CMAKE_SHARED_LINKER_FLAGS -Wl,--allow-shlib-undefined)
    SET(BUILD_AGG TRUE)
elseif(GDX_BACKEND_WIN32)
    add_subdirectory(src/gdx-cpp/backends/windows)
elseif(GDX_BACKEND_LINUX)
  SET(BUILD_AGG TRUE)
  add_subdirectory(src/gdx-cpp/backends/linux)
endif()

if (BUILD_AGG)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/agg/include ${CMAKE_CURRENT_SOURCE_DIR}/src/agg/svg)
  add_subdirectory(src/agg)
endif()

add_subdirectory(src/gdx-cpp)

install(FILES cmake/finders/FindGdxCpp.cmake
        DESTINATION share/gdx/cmake)

install(FILES cmake/gdx.cmake
        DESTINATION share/gdx/cmake)

install(FILES cmake/cotire.cmake
        DESTINATION share/gdx/cmake)