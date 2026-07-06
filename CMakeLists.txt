# CMakeList.txt : CMake project for GameOfLife, include source and define
# project specific logic here.

cmake_minimum_required (VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("GameOfLife")

# ================================
# Get all dependencies 
# ================================
find_package(imgui REQUIRED)
find_package(glad REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(stb REQUIRED)

# Add source to this project's executable.
add_executable (GameOfLife "GameOfLife.cpp")

target_link_libraries(GameOfLife PRIVATE
    imgui::imgui
    glad::glad
    glfw
    glm::glm-header-only
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GameOfLife PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
