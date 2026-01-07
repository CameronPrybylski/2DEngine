cmake_minimum_required(VERSION 3.15)
project(Engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ----------------------------
# SDL2 + SDL2_ttf (modern way)
# ----------------------------
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

# ------------------------------------
# Normalize SDL2 targets (macOS vs WSL)
# ------------------------------------
if (TARGET SDL2::SDL2)
    set(SDL2_TARGET SDL2::SDL2)
else()
    add_library(SDL2::SDL2 INTERFACE IMPORTED)
    target_include_directories(SDL2::SDL2 INTERFACE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(SDL2::SDL2 INTERFACE ${SDL2_LIBRARIES})
    set(SDL2_TARGET SDL2::SDL2)
endif()

if (TARGET SDL2_ttf::SDL2_ttf)
    set(SDL2_TTF_TARGET SDL2_ttf::SDL2_ttf)
else()
    add_library(SDL2_ttf::SDL2_ttf INTERFACE IMPORTED)
    target_include_directories(SDL2_ttf::SDL2_ttf INTERFACE ${SDL2_TTF_INCLUDE_DIRS})
    target_link_libraries(SDL2_ttf::SDL2_ttf INTERFACE ${SDL2_TTF_LIBRARIES})
    set(SDL2_TTF_TARGET SDL2_ttf::SDL2_ttf)
endif()

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
    src/Renderer/TextTexture.cpp
    src/Engine.cpp
    external/glad/src/glad.c
    # Add all other .cpp engine files here
)

# Include directories
target_include_directories(Engine
    PUBLIC
        #${SDL2_INCLUDE_DIRS}
        #/opt/homebrew/include/SDL2
        ${CMAKE_CURRENT_SOURCE_DIR}/include           # Engine headers
        ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include
        ${CMAKE_CURRENT_SOURCE_DIR}/external/stb
        ${CMAKE_CURRENT_SOURCE_DIR}/external/glm
        ${CMAKE_CURRENT_SOURCE_DIR}/external/nlohmann
)

# Link SDL2 (and other system libs if needed)
target_link_libraries(Engine
    PUBLIC 
        #${SDL2_LIBRARIES}
        #/opt/homebrew/lib/libSDL2_ttf.dylib
        ${SDL2_TARGET}
        ${SDL2_TTF_TARGET}
)
