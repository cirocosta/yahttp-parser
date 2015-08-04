cmake_minimum_required(VERSION 2.8.11)

# Turn it ON: -Dtest=ON
option(test "Include Tests." OFF)

set(PROJECT_NAME yahttp-parser)
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CC_COMPILER "clang")
project(${PROJECT_NAME} C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-register")

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support.")
    message(STATUS "Please use a different C++ compiler.")
endif()

find_package(BISON)
find_package(FLEX)


include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}/src
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/includes
)

add_subdirectory(src/)

if (test)
  enable_testing()
  add_subdirectory(tests/)
endif(test)

