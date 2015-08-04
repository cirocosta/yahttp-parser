# yahttp-parser

> A naive C++ HTTP parser implementation using Bison and Flex

**ATTENTION**: this is NOT a full spec conformant parser. It DOES NOT aim to comply with all of the requirements associated with the roles it partakes in the HTTP specification.

[![Build Status](https://travis-ci.org/cirocosta/yahttp-parser.svg?branch=master)](https://travis-ci.org/cirocosta/yahttp-parser)

## Install

Make sure that you have all the dependencies installed:

- flex
- bison\*
- make
- cmake
- a modern c++ compiler - targetting c++11 (i recommend clang, 3.5 is good)

Then, simply:

```sh
$ mkdir build
$ cd build
$ cmake ..
$ make && make test
```

\*: If you've built `bison` from source and in the `make` step it claims that there's a problem with `m4`, try setting the `pkgdata_dir`:
```
export BISON_PKGDATADIR=/usr/local/share/bison/data
```

## CMake

```
yahtml-parser_INCLUDES  : include directories
yahtml-parser_LIBS      : libs to link against
```

## HTTP 1.1

If you wish to get in touch with the spec, take a look at

-   RFC7230 - HTTP/1.1: Message Syntax and Routing - low-level message parsing and connection management
-   RFC7231 - HTTP/1.1: Semantics and Content - methods, status codes and headers
-   RFC7232 - HTTP/1.1: Conditional Requests - e.g., If-Modified-Since
-   RFC7233 - HTTP/1.1: Range Requests - getting partial content
-   RFC7234 - HTTP/1.1: Caching - browser and intermediary caches
-   RFC7235 - HTTP/1.1: Authentication - a framework for HTTP authentication

(see [RFC2616 is Dead](https://www.mnot.net/blog/2014/06/07/rfc2616_is_dead))


## LICENSE

GPLv2


