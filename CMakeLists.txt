# Minimum required version for modern CMake features
cmake_minimum_required(VERSION 3.10)

# 1. DEFINE PROJECT NAME
project(dot-engine C CXX)

# Set the standard to C++17 and enable useful compiler warnings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
add_compile_options(-Wall -Wextra -g)

# --- Define Source Files and Executable (CREATION FIRST) ---
file(GLOB_RECURSE SOURCE_FILES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.c"
)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# --- Modify Target Properties (MODIFICATION SECOND) ---

# 2. SET INCLUDE DIRECTORIES
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

# 3. FIND DEPENDENCIES
# We still find the package with the modern name 'glfw3' to get all necessary flags.
find_package(glfw3 REQUIRED)

# 4. LINK LIBRARIES (Platform-Specific)
if (UNIX)
    # *** MODIFIED LINE HERE ***
    # Using 'glfw' instead of 'glfw3' to link against the aliased library name.
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw GL dl)
elseif (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw3 opengl32)
endif()
