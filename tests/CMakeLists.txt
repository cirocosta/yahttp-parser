# Configure GTEST

find_package(Threads REQUIRED)
include(ExternalProject)
ExternalProject_Add(
  gtest
  GIT_REPOSITORY https://github.com/cirocosta/googletest.git
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
  UPDATE_COMMAND ""
  INSTALL_COMMAND ""
)

add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

ExternalProject_Get_Property(gtest source_dir binary_dir)
set_target_properties(libgtest PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)
include_directories("${source_dir}/include")


#  --  HTTP DEFS

add_executable(http_test main_test.cc http_test.cc)
target_link_libraries(http_test libgtest
  http
)
add_test(NAME http_test COMMAND http_test)


#  --  PARSER

add_executable(parser_test main_test.cc parser_test.cc)
target_link_libraries(parser_test libgtest
  yahttpparser
)

add_test(NAME parser_test COMMAND parser_test)


#  --  CHUNKS

add_executable(chunks_test main_test.cc chunks_test.cc)
target_link_libraries(chunks_test libgtest
  yahttpparser
)
add_test(NAME chunks_test COMMAND chunks_test)


add_custom_command(
  TARGET chunks_test PRE_BUILD
  COMMAND ${CMAKE_COMMAND}
  -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:chunks_test>/assets
)

