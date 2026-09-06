cmake_minimum_required(VERSION 3.12)
project(PrintRandomCrap
    VERSION 2.0.0
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
message(STATUS "CMAKE_BUILD_TYPE is set to: ${CMAKE_BUILD_TYPE}")

add_executable(printrandomcrap
    src/helpers/conversion.cpp
    src/helpers/random.cpp
    src/main.cpp
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
