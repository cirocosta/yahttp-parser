include_directories(${yahttp-parser_INCLUDES})

add_executable(http_test http_test.cc)
add_executable(chunks_test chunks_test.cc)
add_executable(parser_test parser_test.cc)

target_link_libraries(http_test gtest gtest_main ${yahttp-parser_LIBS})
target_link_libraries(parser_test gtest gtest_main ${yahttp-parser_LIBS})
target_link_libraries(chunks_test gtest gtest_main ${yahttp-parser_LIBS})

add_test(NAME http_test COMMAND http_test)
add_test(NAME parser_test COMMAND parser_test)
add_test(NAME chunks_test COMMAND chunks_test)

add_custom_command(
  TARGET chunks_test PRE_BUILD
  COMMAND ${CMAKE_COMMAND}
  -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:chunks_test>/assets
)

