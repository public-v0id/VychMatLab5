# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/Petrign/Проги/CPP/vychMat/lab2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/Petrign/Проги/CPP/vychMat/lab2/cmake

# Include any dependencies generated for this target.
include CMakeFiles/lab.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/lab.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/lab.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lab.dir/flags.make

CMakeFiles/lab.dir/src/main.cpp.o: CMakeFiles/lab.dir/flags.make
CMakeFiles/lab.dir/src/main.cpp.o: /home/Petrign/Проги/CPP/vychMat/lab2/src/main.cpp
CMakeFiles/lab.dir/src/main.cpp.o: CMakeFiles/lab.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/Petrign/Проги/CPP/vychMat/lab2/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lab.dir/src/main.cpp.o"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/lab.dir/src/main.cpp.o -MF CMakeFiles/lab.dir/src/main.cpp.o.d -o CMakeFiles/lab.dir/src/main.cpp.o -c /home/Petrign/Проги/CPP/vychMat/lab2/src/main.cpp

CMakeFiles/lab.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/lab.dir/src/main.cpp.i"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Petrign/Проги/CPP/vychMat/lab2/src/main.cpp > CMakeFiles/lab.dir/src/main.cpp.i

CMakeFiles/lab.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/lab.dir/src/main.cpp.s"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Petrign/Проги/CPP/vychMat/lab2/src/main.cpp -o CMakeFiles/lab.dir/src/main.cpp.s

CMakeFiles/lab.dir/src/methods.cpp.o: CMakeFiles/lab.dir/flags.make
CMakeFiles/lab.dir/src/methods.cpp.o: /home/Petrign/Проги/CPP/vychMat/lab2/src/methods.cpp
CMakeFiles/lab.dir/src/methods.cpp.o: CMakeFiles/lab.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/Petrign/Проги/CPP/vychMat/lab2/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/lab.dir/src/methods.cpp.o"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/lab.dir/src/methods.cpp.o -MF CMakeFiles/lab.dir/src/methods.cpp.o.d -o CMakeFiles/lab.dir/src/methods.cpp.o -c /home/Petrign/Проги/CPP/vychMat/lab2/src/methods.cpp

CMakeFiles/lab.dir/src/methods.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/lab.dir/src/methods.cpp.i"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Petrign/Проги/CPP/vychMat/lab2/src/methods.cpp > CMakeFiles/lab.dir/src/methods.cpp.i

CMakeFiles/lab.dir/src/methods.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/lab.dir/src/methods.cpp.s"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Petrign/Проги/CPP/vychMat/lab2/src/methods.cpp -o CMakeFiles/lab.dir/src/methods.cpp.s

CMakeFiles/lab.dir/src/window.cpp.o: CMakeFiles/lab.dir/flags.make
CMakeFiles/lab.dir/src/window.cpp.o: /home/Petrign/Проги/CPP/vychMat/lab2/src/window.cpp
CMakeFiles/lab.dir/src/window.cpp.o: CMakeFiles/lab.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/Petrign/Проги/CPP/vychMat/lab2/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/lab.dir/src/window.cpp.o"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/lab.dir/src/window.cpp.o -MF CMakeFiles/lab.dir/src/window.cpp.o.d -o CMakeFiles/lab.dir/src/window.cpp.o -c /home/Petrign/Проги/CPP/vychMat/lab2/src/window.cpp

CMakeFiles/lab.dir/src/window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/lab.dir/src/window.cpp.i"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Petrign/Проги/CPP/vychMat/lab2/src/window.cpp > CMakeFiles/lab.dir/src/window.cpp.i

CMakeFiles/lab.dir/src/window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/lab.dir/src/window.cpp.s"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Petrign/Проги/CPP/vychMat/lab2/src/window.cpp -o CMakeFiles/lab.dir/src/window.cpp.s

# Object files for target lab
lab_OBJECTS = \
"CMakeFiles/lab.dir/src/main.cpp.o" \
"CMakeFiles/lab.dir/src/methods.cpp.o" \
"CMakeFiles/lab.dir/src/window.cpp.o"

# External object files for target lab
lab_EXTERNAL_OBJECTS =

lab: CMakeFiles/lab.dir/src/main.cpp.o
lab: CMakeFiles/lab.dir/src/methods.cpp.o
lab: CMakeFiles/lab.dir/src/window.cpp.o
lab: CMakeFiles/lab.dir/build.make
lab: /usr/lib64/libQt5Widgets.so.5.15.15
lab: /usr/lib64/libQt5Gui.so.5.15.15
lab: /usr/lib64/libQt5Core.so.5.15.15
lab: CMakeFiles/lab.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/Petrign/Проги/CPP/vychMat/lab2/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable lab"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lab.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lab.dir/build: lab
.PHONY : CMakeFiles/lab.dir/build

CMakeFiles/lab.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lab.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lab.dir/clean

CMakeFiles/lab.dir/depend:
	cd /home/Petrign/Проги/CPP/vychMat/lab2/cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/Petrign/Проги/CPP/vychMat/lab2 /home/Petrign/Проги/CPP/vychMat/lab2 /home/Petrign/Проги/CPP/vychMat/lab2/cmake /home/Petrign/Проги/CPP/vychMat/lab2/cmake /home/Petrign/Проги/CPP/vychMat/lab2/cmake/CMakeFiles/lab.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/lab.dir/depend

