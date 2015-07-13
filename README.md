# yahttparser

> A naive C++ HTTP parser implementation using Bison and Flex

**ATTENTION**: this is NOT a conformant parser. It DOES NOT aim to comply with all of the requirements associated with the roles it partakes in the HTTP specification.


## Install

This project is not using CMake at the moment (but it will) so make sure by yourself that you have all the dependencies installed:

- flex
- bison\*
- make
- a modern c++ compiler - targetting c++11 (recommend clang, 3.5)

Then, simply:

```sh
$ cd src
$ make
```

\*: If you've built `bison` from source and in the `make` step it claims that there's a problem with `m4`, try setting the `pkgdata_dir`:

```
export BISON_PKGDATADIR=/usr/local/share/bison/data
```

## HTTP 1.1

If you wish to get in touch with the spec, take a look at:

-   RFC7230 - HTTP/1.1: Message Syntax and Routing - low-level message parsing and connection management
-   RFC7231 - HTTP/1.1: Semantics and Content - methods, status codes and headers
-   RFC7232 - HTTP/1.1: Conditional Requests - e.g., If-Modified-Since
-   RFC7233 - HTTP/1.1: Range Requests - getting partial content
-   RFC7234 - HTTP/1.1: Caching - browser and intermediary caches
-   RFC7235 - HTTP/1.1: Authentication - a framework for HTTP authentication

(see [RFC2616 is Dead](https://www.mnot.net/blog/2014/06/07/rfc2616_is_dead))


## Grammar from HTTP spec

The following notation is extracted from the HTTP1.1 spec with some few modification (removes obsolete stuff). This is written using ABNF ([Augmented Backus-Naur Form](https://tools.ietf.org/html/rfc5234)) with list extension.


### Protocol Versioning

The version is indicated by an HTTP-version field in the first line of the message. It IS case-sesitive:

```
HTTP-version  = HTTP-name "/" DIGIT "." DIGIT
HTTP-name     = %x48.54.54.50 ; "HTTP", case-sensitive
```

### URI

URIs are used as the means for identifying resources.

```
HTTP-URI  = "http:" "//" authority path-abempty [ "?" query ]
            [ "#" fragment ]

HTTPS-URI  = "https:" "//" authority path-abempty [ "?" query ]
            [ "#" fragment ]
```

### Message Format

```
HTTP-message  = start-line
                *( header-field CRLF )
                CRLF
                [ message-body ]

start-line    = request-line / status-line

request-line  = method SP request-target SP HTTP-version CRLF
method        = token

status-line   = HTTP-version SP status-code SP reason-phrase CRLF
status-code   = 3DIGIT
reason-phrase = *( HTAB / SP / VCHAR / obs-text )

header-field  = field-name ":" OWS field-value OWS

field-name    = token
field-value   = *( field-content )
field-content = field-vchar [ 1*( SP/HTAB ) field-vchar ]
field-vchar   = VCHAR

request-target= origin-form
              / absolute-form
              / authority-form
              / asterisk-form
origin-form   = absolute-path [ "?" query ]
absolute-form = absolute-URI
authority-form= authority
asterisk-form = "*"
```


> The normal procedure for parsing an HTTP message is to read the
> start-line into a structure, read each header field into a hash table
> by field name until the empty line, and then use the parsed data to
> determine if a message body is expected.  If a message body has been
> indicated, then it is read as a stream until an amount of octets
> equal to the message body length is read or the connection is closed.


