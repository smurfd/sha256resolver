# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/rumrogers/Code/Github/smurfd/sha256resolver/8_cuda/libnvvm-samples

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rumrogers/Code/Github/smurfd/sha256resolver/8_cuda/libnvvm-samples/build

# Include any dependencies generated for this target.
include simple/CMakeFiles/simple.dir/depend.make

# Include the progress variables for this target.
include simple/CMakeFiles/simple.dir/progress.make

# Include the compile flags for this target's objects.
include simple/CMakeFiles/simple.dir/flags.make

simple/CMakeFiles/simple.dir/simple.c.o: simple/CMakeFiles/simple.dir/flags.make
simple/CMakeFiles/simple.dir/simple.c.o: ../simple/simple.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rumrogers/Code/Github/smurfd/sha256resolver/8_cuda/libnvvm-samples/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object simple/CMakeFiles/simple.dir/simple.c.o"
	cd /home/rumrogers/Code/Github/smurfd/sha256resolver/8_cuda/libnvvm-samples/build/simple && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/simple.dir/simple.c.o   -c /home/rumrogers/Code/Github/smurfd/sha256resolver/8_cuda/libnvvm-samples/simple/simple.c

simple/CMakeFiles/simple.dir/simple.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/simple.dir/simple.c.i"
	cd /home/rumrogers/Code/Github/smurfd/sha256resolver/8_cuda/libnvvm-samples/build/simple && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/rumrogers/Code/Github/smurfd/sha256resolver/8_cuda/libnvvm-samples/simple/simple.c > CMakeFiles/simple.dir/simple.c.i

simple/CMakeFiles/simple.dir/simple.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/simple.dir/simple.c.s"
	cd /home/rumrogers/Code/Github/smurfd/sha256resolver/8_cuda/libnvvm-samples/build/simple && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/rumrogers/Code/Github/smurfd/sha256resolver/8_cuda/libnvvm-samples/simple/simple.c -o CMakeFiles/simple.dir/simple.c.s

# Object files for target simple
simple_OBJECTS = \
"CMakeFiles/simple.dir/simple.c.o"

# External object files for target simple
simple_EXTERNAL_OBJECTS =

simple/simple: simple/CMakeFiles/simple.dir/simple.c.o
simple/simple: simple/CMakeFiles/simple.dir/build.make
simple/simple: /usr/local/cuda-11.4/nvvm/lib64/libnvvm.so
simple/simple: /usr/lib64/libcuda.so
simple/simple: simple/CMakeFiles/simple.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/rumrogers/Code/Github/smurfd/sha256resolver/8_cuda/libnvvm-samples/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable simple"
	cd /home/rumrogers/Code/Github/smurfd/sha256resolver/8_cuda/libnvvm-samples/build/simple && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/simple.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
simple/CMakeFiles/simple.dir/build: simple/simple

.PHONY : simple/CMakeFiles/simple.dir/build

simple/CMakeFiles/simple.dir/clean:
	cd /home/rumrogers/Code/Github/smurfd/sha256resolver/8_cuda/libnvvm-samples/build/simple && $(CMAKE_COMMAND) -P CMakeFiles/simple.dir/cmake_clean.cmake
.PHONY : simple/CMakeFiles/simple.dir/clean

simple/CMakeFiles/simple.dir/depend:
	cd /home/rumrogers/Code/Github/smurfd/sha256resolver/8_cuda/libnvvm-samples/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rumrogers/Code/Github/smurfd/sha256resolver/8_cuda/libnvvm-samples /home/rumrogers/Code/Github/smurfd/sha256resolver/8_cuda/libnvvm-samples/simple /home/rumrogers/Code/Github/smurfd/sha256resolver/8_cuda/libnvvm-samples/build /home/rumrogers/Code/Github/smurfd/sha256resolver/8_cuda/libnvvm-samples/build/simple /home/rumrogers/Code/Github/smurfd/sha256resolver/8_cuda/libnvvm-samples/build/simple/CMakeFiles/simple.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : simple/CMakeFiles/simple.dir/depend

