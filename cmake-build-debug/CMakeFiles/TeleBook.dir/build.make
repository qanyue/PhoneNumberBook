# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.19

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


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = G:\JetBrains\Toolbox\apps\CLion\ch-0\211.7142.21\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = G:\JetBrains\Toolbox\apps\CLion\ch-0\211.7142.21\bin\cmake\win\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\qanyu\CLionProjects\TeleBook

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\qanyu\CLionProjects\TeleBook\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TeleBook.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TeleBook.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TeleBook.dir/flags.make

CMakeFiles/TeleBook.dir/main.c.obj: CMakeFiles/TeleBook.dir/flags.make
CMakeFiles/TeleBook.dir/main.c.obj: CMakeFiles/TeleBook.dir/includes_C.rsp
CMakeFiles/TeleBook.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\qanyu\CLionProjects\TeleBook\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/TeleBook.dir/main.c.obj"
	G:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\TeleBook.dir\main.c.obj -c C:\Users\qanyu\CLionProjects\TeleBook\main.c

CMakeFiles/TeleBook.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TeleBook.dir/main.c.i"
	G:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\qanyu\CLionProjects\TeleBook\main.c > CMakeFiles\TeleBook.dir\main.c.i

CMakeFiles/TeleBook.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TeleBook.dir/main.c.s"
	G:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\qanyu\CLionProjects\TeleBook\main.c -o CMakeFiles\TeleBook.dir\main.c.s

# Object files for target TeleBook
TeleBook_OBJECTS = \
"CMakeFiles/TeleBook.dir/main.c.obj"

# External object files for target TeleBook
TeleBook_EXTERNAL_OBJECTS =

TeleBook.exe: CMakeFiles/TeleBook.dir/main.c.obj
TeleBook.exe: CMakeFiles/TeleBook.dir/build.make
TeleBook.exe: CMakeFiles/TeleBook.dir/linklibs.rsp
TeleBook.exe: CMakeFiles/TeleBook.dir/objects1.rsp
TeleBook.exe: CMakeFiles/TeleBook.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\qanyu\CLionProjects\TeleBook\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable TeleBook.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\TeleBook.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TeleBook.dir/build: TeleBook.exe

.PHONY : CMakeFiles/TeleBook.dir/build

CMakeFiles/TeleBook.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\TeleBook.dir\cmake_clean.cmake
.PHONY : CMakeFiles/TeleBook.dir/clean

CMakeFiles/TeleBook.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\qanyu\CLionProjects\TeleBook C:\Users\qanyu\CLionProjects\TeleBook C:\Users\qanyu\CLionProjects\TeleBook\cmake-build-debug C:\Users\qanyu\CLionProjects\TeleBook\cmake-build-debug C:\Users\qanyu\CLionProjects\TeleBook\cmake-build-debug\CMakeFiles\TeleBook.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TeleBook.dir/depend

