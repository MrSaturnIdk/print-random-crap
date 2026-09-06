cmake_minimum_required(VERSION 3.12)
project(PrintRandomCrap
    VERSION 3.0.1
    DESCRIPTION "Infinitely print random letters"
    HOMEPAGE_URL "https://github.com/MrSaturnIdk/print-random-crap"
    LANGUAGES C
)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

include(GNUInstallDirs)

if(NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "CMake build type (what do you think)" FORCE)
endif()
message(STATUS "CMAKE_BUILD_TYPE is set to: ${CMAKE_BUILD_TYPE}")

add_executable(printrandomcrap
    src/arrayhelp.c
    src/main.c
    src/random.c
)
target_include_directories(printrandomcrap PRIVATE include)
target_compile_definitions(printrandomcrap PRIVATE
    HOMEPAGE="${PROJECT_HOMEPAGE_URL}"
    PROJECT_VER="${PROJECT_VERSION}"
)

message(STATUS "Installing to: ${CMAKE_INSTALL_FULL_BINDIR}")
install(TARGETS printrandomcrap
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
