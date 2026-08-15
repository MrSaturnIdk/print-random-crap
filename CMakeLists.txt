cmake_minimum_required(VERSION 3.14)

project(printrandomcrap
    VERSION 1.2.1
    DESCRIPTION "Infinitely print random letters"
    HOMEPAGE_URL "https://github.com/MrSaturnIdk/print-random-crap"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(GNUInstallDirs)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "CMake build type (what do you think)")
endif()

add_executable(printrandomcrap src/main.cpp)

target_compile_definitions(printrandomcrap PRIVATE
    HOMEPAGE="${PROJECT_HOMEPAGE_URL}"
    PROJECT_VER="${PROJECT_VERSION}"
)

install(TARGETS printrandomcrap
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
