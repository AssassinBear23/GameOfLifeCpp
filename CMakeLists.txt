# CMakeList.txt : CMake project for GameOfLife, include source and define
# project specific logic here.

cmake_minimum_required (VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_TOOLCHAIN_FILE "C:\\Users\\beerh\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake")

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("GameOfLife")

# ================================
# Get all dependencies 
# ================================
find_package(imgui CONFIG REQUIRED)

# Add source to this project's executable.
add_executable (GameOfLife "GameOfLife.cpp" "GameOfLife.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GameOfLife PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
