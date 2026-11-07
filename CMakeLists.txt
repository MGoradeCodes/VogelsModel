cmake_minimum_required(VERSION 3.15)
project(PatternCreator VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Add GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(libs/glfw)

# 2. Define your executable (including all source and wrapper files)
add_executable(PatternCreator 
    src/main.cpp
    libs/glad/src/gl.c
    src/VAO.cpp
    src/VBO.cpp
    src/EBO.cpp
    src/ShaderProgram.cpp
)

# 3. Compile definitions
target_compile_definitions(PatternCreator PRIVATE GLM_ENABLE_EXPERIMENTAL)

# 4. Include directories (pointing to your headers folder)
target_include_directories(PatternCreator PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/headers"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/glm"
)

# 5. Link libraries
target_link_libraries(PatternCreator PRIVATE
    glfw
    opengl32
)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/shaders" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")