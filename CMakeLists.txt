cmake_minimum_required(VERSION 3.15)
project(Engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL2
find_package(SDL2 REQUIRED)

# Define the Engine static library
add_library(Engine STATIC
    src/stb_image.cpp
    src/Core/Window.cpp
    src/Core/Input.cpp
    src/Physics/PhysicsSystem.cpp
    src/Scene/Camera.cpp
    src/Scene/GameObject.cpp
    src/Scene/Scene.cpp
    src/Scene/Application.cpp
    src/Scene/SceneManager.cpp
    src/Renderer/Vao.cpp
    src/Renderer/Vbo.cpp
    src/Renderer/Ibo.cpp
    src/Renderer/QuadMesh.cpp
    src/Renderer/Renderer.cpp
    src/Renderer/Shader.cpp
    src/Renderer/Texture.cpp
    src/Engine.cpp
    external/glad/src/glad.c
    # Add all other .cpp engine files here
)

# Include directories
target_include_directories(Engine
    PUBLIC
        ${SDL2_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/include           # Engine headers
        ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include
        ${CMAKE_CURRENT_SOURCE_DIR}/external/stb
        ${CMAKE_CURRENT_SOURCE_DIR}/external/glm
)

# Link SDL2 (and other system libs if needed)
target_link_libraries(Engine
    PRIVATE ${SDL2_LIBRARIES}
)


