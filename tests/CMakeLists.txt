add_executable(parser_test parser_test.cc)
target_link_libraries(parser_test gtest gtest_main
  yahttpparser
)

add_test(NAME parser COMMAND parser)

