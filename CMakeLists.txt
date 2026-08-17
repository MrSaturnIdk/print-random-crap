cmake_minimum_required(VERSION 3.14)

project(printrandomcrap
    VERSION 1.3.1
    DESCRIPTION "Infinitely print random letters"
    HOMEPAGE_URL "https://github.com/MrSaturnIdk/print-random-crap"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(GNUInstallDirs)

if(NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "CMake build type (what do you think)" FORCE)
endif()

find_program(CACHE_PROGRAM ccache)
if(CACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CACHE_PROGRAM}")
endif()

add_executable(printrandomcrap src/main.cpp)

target_compile_definitions(printrandomcrap PRIVATE
    HOMEPAGE="${PROJECT_HOMEPAGE_URL}"
    PROJECT_VER="${PROJECT_VERSION}"
)

install(TARGETS printrandomcrap
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
