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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = F:\SyncFiles\Informatica\Arduino\Progetti\SvegliaArduino\ArduChronoSveglia

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = F:\SyncFiles\Informatica\Arduino\Progetti\SvegliaArduino\ArduChronoSveglia\cmake-build-megaatmega2560

# Utility rule file for Production.

# Include the progress variables for this target.
include CMakeFiles/Production.dir/progress.make

CMakeFiles/Production:
	cd /d F:\SyncFiles\Informatica\Arduino\Progetti\SvegliaArduino\ArduChronoSveglia && platformio -c clion run -emegaatmega2560

Production: CMakeFiles/Production
Production: CMakeFiles/Production.dir/build.make

.PHONY : Production

# Rule to build all files generated by this target.
CMakeFiles/Production.dir/build: Production

.PHONY : CMakeFiles/Production.dir/build

CMakeFiles/Production.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Production.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Production.dir/clean

CMakeFiles/Production.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" F:\SyncFiles\Informatica\Arduino\Progetti\SvegliaArduino\ArduChronoSveglia F:\SyncFiles\Informatica\Arduino\Progetti\SvegliaArduino\ArduChronoSveglia F:\SyncFiles\Informatica\Arduino\Progetti\SvegliaArduino\ArduChronoSveglia\cmake-build-megaatmega2560 F:\SyncFiles\Informatica\Arduino\Progetti\SvegliaArduino\ArduChronoSveglia\cmake-build-megaatmega2560 F:\SyncFiles\Informatica\Arduino\Progetti\SvegliaArduino\ArduChronoSveglia\cmake-build-megaatmega2560\CMakeFiles\Production.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Production.dir/depend

