# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Program Files\JetBrains\CLion 2019.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Program Files\JetBrains\CLion 2019.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\Taccen\SimplexJSON

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\Taccen\SimplexJSON\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/simplexJson.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/simplexJson.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/simplexJson.dir/flags.make

CMakeFiles/simplexJson.dir/simplexjson.cpp.obj: CMakeFiles/simplexJson.dir/flags.make
CMakeFiles/simplexJson.dir/simplexjson.cpp.obj: ../simplexjson.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Taccen\SimplexJSON\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/simplexJson.dir/simplexjson.cpp.obj"
	"D:\Program Files\JETBRA~1\CLION2~1.2\mingw64\bin\G__~1.EXE"  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\simplexJson.dir\simplexjson.cpp.obj -c E:\Taccen\SimplexJSON\simplexjson.cpp

CMakeFiles/simplexJson.dir/simplexjson.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simplexJson.dir/simplexjson.cpp.i"
	"D:\Program Files\JETBRA~1\CLION2~1.2\mingw64\bin\G__~1.EXE" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Taccen\SimplexJSON\simplexjson.cpp > CMakeFiles\simplexJson.dir\simplexjson.cpp.i

CMakeFiles/simplexJson.dir/simplexjson.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simplexJson.dir/simplexjson.cpp.s"
	"D:\Program Files\JETBRA~1\CLION2~1.2\mingw64\bin\G__~1.EXE" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Taccen\SimplexJSON\simplexjson.cpp -o CMakeFiles\simplexJson.dir\simplexjson.cpp.s

# Object files for target simplexJson
simplexJson_OBJECTS = \
"CMakeFiles/simplexJson.dir/simplexjson.cpp.obj"

# External object files for target simplexJson
simplexJson_EXTERNAL_OBJECTS =

libsimplexJson.a: CMakeFiles/simplexJson.dir/simplexjson.cpp.obj
libsimplexJson.a: CMakeFiles/simplexJson.dir/build.make
libsimplexJson.a: CMakeFiles/simplexJson.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\Taccen\SimplexJSON\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libsimplexJson.a"
	$(CMAKE_COMMAND) -P CMakeFiles\simplexJson.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\simplexJson.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/simplexJson.dir/build: libsimplexJson.a

.PHONY : CMakeFiles/simplexJson.dir/build

CMakeFiles/simplexJson.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\simplexJson.dir\cmake_clean.cmake
.PHONY : CMakeFiles/simplexJson.dir/clean

CMakeFiles/simplexJson.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\Taccen\SimplexJSON E:\Taccen\SimplexJSON E:\Taccen\SimplexJSON\cmake-build-debug E:\Taccen\SimplexJSON\cmake-build-debug E:\Taccen\SimplexJSON\cmake-build-debug\CMakeFiles\simplexJson.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/simplexJson.dir/depend

