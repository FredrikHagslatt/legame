# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = "C:/Program Files/CMake/bin/cmake.exe"

# The command to remove a file.
RM = "C:/Program Files/CMake/bin/cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:/stuff/c++/gameengine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:/stuff/c++/gameengine/build

# Include any dependencies generated for this target.
include CMakeFiles/highnoon.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/highnoon.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/highnoon.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/highnoon.dir/flags.make

CMakeFiles/highnoon.dir/src/AssetStore/AssetStore.cpp.obj: CMakeFiles/highnoon.dir/flags.make
CMakeFiles/highnoon.dir/src/AssetStore/AssetStore.cpp.obj: CMakeFiles/highnoon.dir/includes_CXX.rsp
CMakeFiles/highnoon.dir/src/AssetStore/AssetStore.cpp.obj: ../src/AssetStore/AssetStore.cpp
CMakeFiles/highnoon.dir/src/AssetStore/AssetStore.cpp.obj: CMakeFiles/highnoon.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:/stuff/c++/gameengine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/highnoon.dir/src/AssetStore/AssetStore.cpp.obj"
	C:/msys64/mingw64/bin/x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/highnoon.dir/src/AssetStore/AssetStore.cpp.obj -MF CMakeFiles/highnoon.dir/src/AssetStore/AssetStore.cpp.obj.d -o CMakeFiles/highnoon.dir/src/AssetStore/AssetStore.cpp.obj -c C:/stuff/c++/gameengine/src/AssetStore/AssetStore.cpp

CMakeFiles/highnoon.dir/src/AssetStore/AssetStore.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/highnoon.dir/src/AssetStore/AssetStore.cpp.i"
	C:/msys64/mingw64/bin/x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:/stuff/c++/gameengine/src/AssetStore/AssetStore.cpp > CMakeFiles/highnoon.dir/src/AssetStore/AssetStore.cpp.i

CMakeFiles/highnoon.dir/src/AssetStore/AssetStore.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/highnoon.dir/src/AssetStore/AssetStore.cpp.s"
	C:/msys64/mingw64/bin/x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:/stuff/c++/gameengine/src/AssetStore/AssetStore.cpp -o CMakeFiles/highnoon.dir/src/AssetStore/AssetStore.cpp.s

CMakeFiles/highnoon.dir/src/ECS/ECS.cpp.obj: CMakeFiles/highnoon.dir/flags.make
CMakeFiles/highnoon.dir/src/ECS/ECS.cpp.obj: CMakeFiles/highnoon.dir/includes_CXX.rsp
CMakeFiles/highnoon.dir/src/ECS/ECS.cpp.obj: ../src/ECS/ECS.cpp
CMakeFiles/highnoon.dir/src/ECS/ECS.cpp.obj: CMakeFiles/highnoon.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:/stuff/c++/gameengine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/highnoon.dir/src/ECS/ECS.cpp.obj"
	C:/msys64/mingw64/bin/x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/highnoon.dir/src/ECS/ECS.cpp.obj -MF CMakeFiles/highnoon.dir/src/ECS/ECS.cpp.obj.d -o CMakeFiles/highnoon.dir/src/ECS/ECS.cpp.obj -c C:/stuff/c++/gameengine/src/ECS/ECS.cpp

CMakeFiles/highnoon.dir/src/ECS/ECS.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/highnoon.dir/src/ECS/ECS.cpp.i"
	C:/msys64/mingw64/bin/x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:/stuff/c++/gameengine/src/ECS/ECS.cpp > CMakeFiles/highnoon.dir/src/ECS/ECS.cpp.i

CMakeFiles/highnoon.dir/src/ECS/ECS.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/highnoon.dir/src/ECS/ECS.cpp.s"
	C:/msys64/mingw64/bin/x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:/stuff/c++/gameengine/src/ECS/ECS.cpp -o CMakeFiles/highnoon.dir/src/ECS/ECS.cpp.s

CMakeFiles/highnoon.dir/src/Game/Game.cpp.obj: CMakeFiles/highnoon.dir/flags.make
CMakeFiles/highnoon.dir/src/Game/Game.cpp.obj: CMakeFiles/highnoon.dir/includes_CXX.rsp
CMakeFiles/highnoon.dir/src/Game/Game.cpp.obj: ../src/Game/Game.cpp
CMakeFiles/highnoon.dir/src/Game/Game.cpp.obj: CMakeFiles/highnoon.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:/stuff/c++/gameengine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/highnoon.dir/src/Game/Game.cpp.obj"
	C:/msys64/mingw64/bin/x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/highnoon.dir/src/Game/Game.cpp.obj -MF CMakeFiles/highnoon.dir/src/Game/Game.cpp.obj.d -o CMakeFiles/highnoon.dir/src/Game/Game.cpp.obj -c C:/stuff/c++/gameengine/src/Game/Game.cpp

CMakeFiles/highnoon.dir/src/Game/Game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/highnoon.dir/src/Game/Game.cpp.i"
	C:/msys64/mingw64/bin/x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:/stuff/c++/gameengine/src/Game/Game.cpp > CMakeFiles/highnoon.dir/src/Game/Game.cpp.i

CMakeFiles/highnoon.dir/src/Game/Game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/highnoon.dir/src/Game/Game.cpp.s"
	C:/msys64/mingw64/bin/x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:/stuff/c++/gameengine/src/Game/Game.cpp -o CMakeFiles/highnoon.dir/src/Game/Game.cpp.s

CMakeFiles/highnoon.dir/src/Logger/Logger.cpp.obj: CMakeFiles/highnoon.dir/flags.make
CMakeFiles/highnoon.dir/src/Logger/Logger.cpp.obj: CMakeFiles/highnoon.dir/includes_CXX.rsp
CMakeFiles/highnoon.dir/src/Logger/Logger.cpp.obj: ../src/Logger/Logger.cpp
CMakeFiles/highnoon.dir/src/Logger/Logger.cpp.obj: CMakeFiles/highnoon.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:/stuff/c++/gameengine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/highnoon.dir/src/Logger/Logger.cpp.obj"
	C:/msys64/mingw64/bin/x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/highnoon.dir/src/Logger/Logger.cpp.obj -MF CMakeFiles/highnoon.dir/src/Logger/Logger.cpp.obj.d -o CMakeFiles/highnoon.dir/src/Logger/Logger.cpp.obj -c C:/stuff/c++/gameengine/src/Logger/Logger.cpp

CMakeFiles/highnoon.dir/src/Logger/Logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/highnoon.dir/src/Logger/Logger.cpp.i"
	C:/msys64/mingw64/bin/x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:/stuff/c++/gameengine/src/Logger/Logger.cpp > CMakeFiles/highnoon.dir/src/Logger/Logger.cpp.i

CMakeFiles/highnoon.dir/src/Logger/Logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/highnoon.dir/src/Logger/Logger.cpp.s"
	C:/msys64/mingw64/bin/x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:/stuff/c++/gameengine/src/Logger/Logger.cpp -o CMakeFiles/highnoon.dir/src/Logger/Logger.cpp.s

CMakeFiles/highnoon.dir/src/Main.cpp.obj: CMakeFiles/highnoon.dir/flags.make
CMakeFiles/highnoon.dir/src/Main.cpp.obj: CMakeFiles/highnoon.dir/includes_CXX.rsp
CMakeFiles/highnoon.dir/src/Main.cpp.obj: ../src/Main.cpp
CMakeFiles/highnoon.dir/src/Main.cpp.obj: CMakeFiles/highnoon.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:/stuff/c++/gameengine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/highnoon.dir/src/Main.cpp.obj"
	C:/msys64/mingw64/bin/x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/highnoon.dir/src/Main.cpp.obj -MF CMakeFiles/highnoon.dir/src/Main.cpp.obj.d -o CMakeFiles/highnoon.dir/src/Main.cpp.obj -c C:/stuff/c++/gameengine/src/Main.cpp

CMakeFiles/highnoon.dir/src/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/highnoon.dir/src/Main.cpp.i"
	C:/msys64/mingw64/bin/x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:/stuff/c++/gameengine/src/Main.cpp > CMakeFiles/highnoon.dir/src/Main.cpp.i

CMakeFiles/highnoon.dir/src/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/highnoon.dir/src/Main.cpp.s"
	C:/msys64/mingw64/bin/x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:/stuff/c++/gameengine/src/Main.cpp -o CMakeFiles/highnoon.dir/src/Main.cpp.s

# Object files for target highnoon
highnoon_OBJECTS = \
"CMakeFiles/highnoon.dir/src/AssetStore/AssetStore.cpp.obj" \
"CMakeFiles/highnoon.dir/src/ECS/ECS.cpp.obj" \
"CMakeFiles/highnoon.dir/src/Game/Game.cpp.obj" \
"CMakeFiles/highnoon.dir/src/Logger/Logger.cpp.obj" \
"CMakeFiles/highnoon.dir/src/Main.cpp.obj"

# External object files for target highnoon
highnoon_EXTERNAL_OBJECTS =

highnoon.exe: CMakeFiles/highnoon.dir/src/AssetStore/AssetStore.cpp.obj
highnoon.exe: CMakeFiles/highnoon.dir/src/ECS/ECS.cpp.obj
highnoon.exe: CMakeFiles/highnoon.dir/src/Game/Game.cpp.obj
highnoon.exe: CMakeFiles/highnoon.dir/src/Logger/Logger.cpp.obj
highnoon.exe: CMakeFiles/highnoon.dir/src/Main.cpp.obj
highnoon.exe: CMakeFiles/highnoon.dir/build.make
highnoon.exe: ../third-party/SDL_Bundle_Mingw/lib/libSDL2main.a
highnoon.exe: ../third-party/SDL_Bundle_Mingw/lib/libSDL2.dll.a
highnoon.exe: ../third-party/SDL_Bundle_Mingw/lib/libSDL2_image.dll.a
highnoon.exe: ../third-party/SDL_Bundle_Mingw/lib/libSDL2_mixer.dll.a
highnoon.exe: ../third-party/SDL_Bundle_Mingw/lib/libSDL2_ttf.dll.a
highnoon.exe: CMakeFiles/highnoon.dir/linklibs.rsp
highnoon.exe: CMakeFiles/highnoon.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:/stuff/c++/gameengine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable highnoon.exe"
	"C:/Program Files/CMake/bin/cmake.exe" -E rm -f CMakeFiles/highnoon.dir/objects.a
	C:/msys64/mingw64/bin/ar.exe qc CMakeFiles/highnoon.dir/objects.a @CMakeFiles/highnoon.dir/objects1.rsp
	C:/msys64/mingw64/bin/x86_64-w64-mingw32-g++.exe  -std=c++17 -g -Wl,--whole-archive CMakeFiles/highnoon.dir/objects.a -Wl,--no-whole-archive -o highnoon.exe -Wl,--out-implib,libhighnoon.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/highnoon.dir/linklibs.rsp

# Rule to build all files generated by this target.
CMakeFiles/highnoon.dir/build: highnoon.exe
.PHONY : CMakeFiles/highnoon.dir/build

CMakeFiles/highnoon.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/highnoon.dir/cmake_clean.cmake
.PHONY : CMakeFiles/highnoon.dir/clean

CMakeFiles/highnoon.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" C:/stuff/c++/gameengine C:/stuff/c++/gameengine C:/stuff/c++/gameengine/build C:/stuff/c++/gameengine/build C:/stuff/c++/gameengine/build/CMakeFiles/highnoon.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/highnoon.dir/depend
