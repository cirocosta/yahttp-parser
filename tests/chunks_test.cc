#include "gtest/gtest.h"
#include "yahttp/HTTP.hh"
#include "yahttp/parser/driver.hh"

#include <libgen.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <string>
#include <fstream>

using namespace yahttp;

std::string get_selfdir()
{
  char buff[PATH_MAX];
  ssize_t len = ::readlink("/proc/self/exe", buff, sizeof(buff) - 1);

  if (len != -1) {
    buff[len] = '\0';
    dirname(buff);

    return std::string(buff);
  }

  throw std::runtime_error("get_selfpath: couldn't execute readlink properly");
}

TEST(Chunks, InitialChunk)
{
  bool debug = false;
  unsigned size = 0;
  std::ifstream file(get_selfdir() +
                     "/assets/chunks/chunked_apontador_index.html");

  HTTPDriver driver(debug, debug);
  driver.parse(file);

  ASSERT_EQ(driver.result, 0);
  ASSERT_EQ(driver.message->headers.size(), 7);
  ASSERT_EQ(driver.message->headers["Connection"],
            "keep-alive,Transfer-Encoding");
  ASSERT_EQ(driver.message->headers["Transfer-Encoding"], "chunked");

  std::fstream expected_file(
      get_selfdir() + "/assets/chunks/apontador_index.html", std::ios::in);

  std::stringstream expected_body;

  expected_body << expected_file.rdbuf();

  std::string body_msg(driver.message->body.begin(),
                       driver.message->body.end());

  EXPECT_EQ(body_msg, expected_body.str());
}
