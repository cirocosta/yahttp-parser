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

std::string get_selfdir ()
{
  char buff[PATH_MAX];
  ssize_t len = ::readlink("/proc/self/exe", buff, sizeof(buff)-1);
  if (len != -1) {
    buff[len] = '\0';
    dirname(buff);

    return std::string(buff);
  }

  throw std::runtime_error("get_selfpath: couldn't execute readlink properly");
}

TEST(Chunks, InitialChunk) {
  bool debug = false;
  unsigned size = 0;
  std::string path_chunked =
    get_selfdir() + "/assets/chunks/chunked_apontador_index.html";
  std::string path_expected =
    get_selfdir() + "/assets/chunks/apontador_index.html";

  HTTPBody::iterator body_it;
  HTTPDriver driver(debug, debug);

  driver.parse(path_chunked);

  ASSERT_EQ(driver.result, 0);
  ASSERT_EQ(driver.message->headers.size(), 7);
  ASSERT_EQ(driver.message->headers["Connection"],
            "keep-alive,Transfer-Encoding");
  ASSERT_EQ(driver.message->headers["Transfer-Encoding"], "chunked");

  std::ifstream expected_file (path_expected.c_str());
  std::stringstream expected_body;

  expected_body << expected_file.rdbuf();

  std::string body_msg (driver.message->body.begin(),
                        driver.message->body.end());

  EXPECT_EQ(body_msg, expected_body.str());
}


