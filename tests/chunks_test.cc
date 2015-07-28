#include "gtest/gtest.h"
#include "yahttp/HTTP.hh"
#include "yahttp/parser/driver.hh"

#include <libgen.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <string>

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
  std::string filepath = get_selfdir() + "/assets/chunks/initial_chunk.txt";
  HTTPBody::iterator body_it;
  HTTPDriver driver(debug, debug);

  driver.parse(filepath);

  EXPECT_EQ(driver.result, 0);
  EXPECT_EQ(driver.message->headers.size(), 7);
  EXPECT_EQ(driver.message->headers["Connection"], "keep-alive,Transfer-Encoding");

  body_it = driver.message->body.begin();
  while (*body_it++ != '\n');
  size = std::strtoul(
      std::string(driver.message->body.begin(), body_it).c_str(), NULL, 16);

  EXPECT_EQ(49152, size);

  driver.message->body.erase(driver.message->body.begin(), body_it);
}


