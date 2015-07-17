# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ciro/Development/CPP/yahttp-parser

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ciro/Development/CPP/yahttp-parser/build

# Include any dependencies generated for this target.
include src/CMakeFiles/yahttpparser.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/yahttpparser.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/yahttpparser.dir/flags.make

src/parser.cc: ../src/parser.yy
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ciro/Development/CPP/yahttp-parser/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "[BISON][MyParser] Building parser with bison 3.0.4"
	cd /home/ciro/Development/CPP/yahttp-parser/src && /usr/local/bin/bison -y -d -o /home/ciro/Development/CPP/yahttp-parser/build/src/parser.cc parser.yy

src/parser.hh: src/parser.cc

src/scanner.cc: ../src/scanner.ll
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ciro/Development/CPP/yahttp-parser/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "[FLEX][MyScanner] Building scanner with flex 2.5.35"
	cd /home/ciro/Development/CPP/yahttp-parser/src && /usr/bin/flex -o/home/ciro/Development/CPP/yahttp-parser/build/src/scanner.cc scanner.ll

src/CMakeFiles/yahttpparser.dir/scanner.cc.o: src/CMakeFiles/yahttpparser.dir/flags.make
src/CMakeFiles/yahttpparser.dir/scanner.cc.o: src/scanner.cc
src/CMakeFiles/yahttpparser.dir/scanner.cc.o: src/parser.hh
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ciro/Development/CPP/yahttp-parser/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/yahttpparser.dir/scanner.cc.o"
	cd /home/ciro/Development/CPP/yahttp-parser/build/src && /usr/bin/clang++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/yahttpparser.dir/scanner.cc.o -c /home/ciro/Development/CPP/yahttp-parser/build/src/scanner.cc

src/CMakeFiles/yahttpparser.dir/scanner.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/yahttpparser.dir/scanner.cc.i"
	cd /home/ciro/Development/CPP/yahttp-parser/build/src && /usr/bin/clang++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ciro/Development/CPP/yahttp-parser/build/src/scanner.cc > CMakeFiles/yahttpparser.dir/scanner.cc.i

src/CMakeFiles/yahttpparser.dir/scanner.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/yahttpparser.dir/scanner.cc.s"
	cd /home/ciro/Development/CPP/yahttp-parser/build/src && /usr/bin/clang++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ciro/Development/CPP/yahttp-parser/build/src/scanner.cc -o CMakeFiles/yahttpparser.dir/scanner.cc.s

src/CMakeFiles/yahttpparser.dir/scanner.cc.o.requires:
.PHONY : src/CMakeFiles/yahttpparser.dir/scanner.cc.o.requires

src/CMakeFiles/yahttpparser.dir/scanner.cc.o.provides: src/CMakeFiles/yahttpparser.dir/scanner.cc.o.requires
	$(MAKE) -f src/CMakeFiles/yahttpparser.dir/build.make src/CMakeFiles/yahttpparser.dir/scanner.cc.o.provides.build
.PHONY : src/CMakeFiles/yahttpparser.dir/scanner.cc.o.provides

src/CMakeFiles/yahttpparser.dir/scanner.cc.o.provides.build: src/CMakeFiles/yahttpparser.dir/scanner.cc.o

src/CMakeFiles/yahttpparser.dir/parser.cc.o: src/CMakeFiles/yahttpparser.dir/flags.make
src/CMakeFiles/yahttpparser.dir/parser.cc.o: src/parser.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ciro/Development/CPP/yahttp-parser/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/yahttpparser.dir/parser.cc.o"
	cd /home/ciro/Development/CPP/yahttp-parser/build/src && /usr/bin/clang++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/yahttpparser.dir/parser.cc.o -c /home/ciro/Development/CPP/yahttp-parser/build/src/parser.cc

src/CMakeFiles/yahttpparser.dir/parser.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/yahttpparser.dir/parser.cc.i"
	cd /home/ciro/Development/CPP/yahttp-parser/build/src && /usr/bin/clang++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ciro/Development/CPP/yahttp-parser/build/src/parser.cc > CMakeFiles/yahttpparser.dir/parser.cc.i

src/CMakeFiles/yahttpparser.dir/parser.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/yahttpparser.dir/parser.cc.s"
	cd /home/ciro/Development/CPP/yahttp-parser/build/src && /usr/bin/clang++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ciro/Development/CPP/yahttp-parser/build/src/parser.cc -o CMakeFiles/yahttpparser.dir/parser.cc.s

src/CMakeFiles/yahttpparser.dir/parser.cc.o.requires:
.PHONY : src/CMakeFiles/yahttpparser.dir/parser.cc.o.requires

src/CMakeFiles/yahttpparser.dir/parser.cc.o.provides: src/CMakeFiles/yahttpparser.dir/parser.cc.o.requires
	$(MAKE) -f src/CMakeFiles/yahttpparser.dir/build.make src/CMakeFiles/yahttpparser.dir/parser.cc.o.provides.build
.PHONY : src/CMakeFiles/yahttpparser.dir/parser.cc.o.provides

src/CMakeFiles/yahttpparser.dir/parser.cc.o.provides.build: src/CMakeFiles/yahttpparser.dir/parser.cc.o

src/CMakeFiles/yahttpparser.dir/driver.cc.o: src/CMakeFiles/yahttpparser.dir/flags.make
src/CMakeFiles/yahttpparser.dir/driver.cc.o: ../src/driver.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ciro/Development/CPP/yahttp-parser/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/yahttpparser.dir/driver.cc.o"
	cd /home/ciro/Development/CPP/yahttp-parser/build/src && /usr/bin/clang++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/yahttpparser.dir/driver.cc.o -c /home/ciro/Development/CPP/yahttp-parser/src/driver.cc

src/CMakeFiles/yahttpparser.dir/driver.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/yahttpparser.dir/driver.cc.i"
	cd /home/ciro/Development/CPP/yahttp-parser/build/src && /usr/bin/clang++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ciro/Development/CPP/yahttp-parser/src/driver.cc > CMakeFiles/yahttpparser.dir/driver.cc.i

src/CMakeFiles/yahttpparser.dir/driver.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/yahttpparser.dir/driver.cc.s"
	cd /home/ciro/Development/CPP/yahttp-parser/build/src && /usr/bin/clang++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ciro/Development/CPP/yahttp-parser/src/driver.cc -o CMakeFiles/yahttpparser.dir/driver.cc.s

src/CMakeFiles/yahttpparser.dir/driver.cc.o.requires:
.PHONY : src/CMakeFiles/yahttpparser.dir/driver.cc.o.requires

src/CMakeFiles/yahttpparser.dir/driver.cc.o.provides: src/CMakeFiles/yahttpparser.dir/driver.cc.o.requires
	$(MAKE) -f src/CMakeFiles/yahttpparser.dir/build.make src/CMakeFiles/yahttpparser.dir/driver.cc.o.provides.build
.PHONY : src/CMakeFiles/yahttpparser.dir/driver.cc.o.provides

src/CMakeFiles/yahttpparser.dir/driver.cc.o.provides.build: src/CMakeFiles/yahttpparser.dir/driver.cc.o

src/CMakeFiles/yahttpparser.dir/http_defs.cc.o: src/CMakeFiles/yahttpparser.dir/flags.make
src/CMakeFiles/yahttpparser.dir/http_defs.cc.o: ../src/http_defs.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ciro/Development/CPP/yahttp-parser/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/yahttpparser.dir/http_defs.cc.o"
	cd /home/ciro/Development/CPP/yahttp-parser/build/src && /usr/bin/clang++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/yahttpparser.dir/http_defs.cc.o -c /home/ciro/Development/CPP/yahttp-parser/src/http_defs.cc

src/CMakeFiles/yahttpparser.dir/http_defs.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/yahttpparser.dir/http_defs.cc.i"
	cd /home/ciro/Development/CPP/yahttp-parser/build/src && /usr/bin/clang++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ciro/Development/CPP/yahttp-parser/src/http_defs.cc > CMakeFiles/yahttpparser.dir/http_defs.cc.i

src/CMakeFiles/yahttpparser.dir/http_defs.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/yahttpparser.dir/http_defs.cc.s"
	cd /home/ciro/Development/CPP/yahttp-parser/build/src && /usr/bin/clang++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ciro/Development/CPP/yahttp-parser/src/http_defs.cc -o CMakeFiles/yahttpparser.dir/http_defs.cc.s

src/CMakeFiles/yahttpparser.dir/http_defs.cc.o.requires:
.PHONY : src/CMakeFiles/yahttpparser.dir/http_defs.cc.o.requires

src/CMakeFiles/yahttpparser.dir/http_defs.cc.o.provides: src/CMakeFiles/yahttpparser.dir/http_defs.cc.o.requires
	$(MAKE) -f src/CMakeFiles/yahttpparser.dir/build.make src/CMakeFiles/yahttpparser.dir/http_defs.cc.o.provides.build
.PHONY : src/CMakeFiles/yahttpparser.dir/http_defs.cc.o.provides

src/CMakeFiles/yahttpparser.dir/http_defs.cc.o.provides.build: src/CMakeFiles/yahttpparser.dir/http_defs.cc.o

# Object files for target yahttpparser
yahttpparser_OBJECTS = \
"CMakeFiles/yahttpparser.dir/scanner.cc.o" \
"CMakeFiles/yahttpparser.dir/parser.cc.o" \
"CMakeFiles/yahttpparser.dir/driver.cc.o" \
"CMakeFiles/yahttpparser.dir/http_defs.cc.o"

# External object files for target yahttpparser
yahttpparser_EXTERNAL_OBJECTS =

src/libyahttpparser.a: src/CMakeFiles/yahttpparser.dir/scanner.cc.o
src/libyahttpparser.a: src/CMakeFiles/yahttpparser.dir/parser.cc.o
src/libyahttpparser.a: src/CMakeFiles/yahttpparser.dir/driver.cc.o
src/libyahttpparser.a: src/CMakeFiles/yahttpparser.dir/http_defs.cc.o
src/libyahttpparser.a: src/CMakeFiles/yahttpparser.dir/build.make
src/libyahttpparser.a: src/CMakeFiles/yahttpparser.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libyahttpparser.a"
	cd /home/ciro/Development/CPP/yahttp-parser/build/src && $(CMAKE_COMMAND) -P CMakeFiles/yahttpparser.dir/cmake_clean_target.cmake
	cd /home/ciro/Development/CPP/yahttp-parser/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/yahttpparser.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/yahttpparser.dir/build: src/libyahttpparser.a
.PHONY : src/CMakeFiles/yahttpparser.dir/build

src/CMakeFiles/yahttpparser.dir/requires: src/CMakeFiles/yahttpparser.dir/scanner.cc.o.requires
src/CMakeFiles/yahttpparser.dir/requires: src/CMakeFiles/yahttpparser.dir/parser.cc.o.requires
src/CMakeFiles/yahttpparser.dir/requires: src/CMakeFiles/yahttpparser.dir/driver.cc.o.requires
src/CMakeFiles/yahttpparser.dir/requires: src/CMakeFiles/yahttpparser.dir/http_defs.cc.o.requires
.PHONY : src/CMakeFiles/yahttpparser.dir/requires

src/CMakeFiles/yahttpparser.dir/clean:
	cd /home/ciro/Development/CPP/yahttp-parser/build/src && $(CMAKE_COMMAND) -P CMakeFiles/yahttpparser.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/yahttpparser.dir/clean

src/CMakeFiles/yahttpparser.dir/depend: src/parser.cc
src/CMakeFiles/yahttpparser.dir/depend: src/parser.hh
src/CMakeFiles/yahttpparser.dir/depend: src/scanner.cc
	cd /home/ciro/Development/CPP/yahttp-parser/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ciro/Development/CPP/yahttp-parser /home/ciro/Development/CPP/yahttp-parser/src /home/ciro/Development/CPP/yahttp-parser/build /home/ciro/Development/CPP/yahttp-parser/build/src /home/ciro/Development/CPP/yahttp-parser/build/src/CMakeFiles/yahttpparser.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/yahttpparser.dir/depend
