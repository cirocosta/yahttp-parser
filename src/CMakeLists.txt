BISON_TARGET(MyParser yahttp_parser.yy ${CMAKE_CURRENT_BINARY_DIR}/yahttp_parser.cc)
FLEX_TARGET(MyScanner scanner.ll ${CMAKE_CURRENT_BINARY_DIR}/scanner.cc)
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)


set(INCLUDES "${INCLUDES}" "${CMAKE_CURRENT_BINARY_DIR}" PARENT_SCOPE)
include_directories(${INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

add_library(yahttpparser
  ${FLEX_MyScanner_OUTPUTS}
  ${BISON_MyParser_OUTPUTS}
  HTTP.cc
  driver.cc
)

set(BISON_HEADERS_PREFIX yahttp)

configure_file(
  ${PROJECT_SOURCE_DIR}/cmake/fix_bison_headers.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/fix_bison_headers.cmake
  @ONLY
)

add_custom_command(
  TARGET yahttpparser PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/fix_bison_headers.cmake
)

set(LIBS "yahttpparser" PARENT_SCOPE)

