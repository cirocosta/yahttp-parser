# HTTP DEFS

add_executable(http_test http_test.cc)
target_link_libraries(http_test gtest gtest_main
  http
)
add_test(NAME http_test COMMAND http_test)


# PARSER

add_executable(parser_test parser_test.cc)
target_link_libraries(parser_test gtest gtest_main
  yahttpparser
)

add_test(NAME parser_test COMMAND parser_test)

add_custom_command(
  TARGET parser_test PRE_BUILD
  COMMAND ${CMAKE_COMMAND}
  -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:parser_test>/assets
)

