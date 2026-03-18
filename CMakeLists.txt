cmake_minimum_required(VERSION 3.20)

project(engine)

set(CMAKE_CXX_STANDARD 17)

# adicionar engine WIN32 caso eu queira remover o terminal (e tem q adicionar WinMain() no método principal invés de main())
add_executable(engine
	src/main.cc
	src/core/application.cc
	src/core/camera.cc
	src/core/input.cc
	src/graphics/shader.cc
	src/graphics/renderer.cc
	src/graphics/mesh.cc
	src/graphics/texture.cc
	src/graphics/material.cc
	src/math/vec3.cc
	src/math/mat4.cc
	src/core/transform.cc
	src/scene/scene.cc
	src/scene/entity.cc
	src/assets/obj_loader.cc
	src/assets/resource_manager.cc
	external/glad/src/glad.c
)

target_include_directories(engine PRIVATE
	src 
	libs/glfw/include
	libs/stb_image
	external/glad/include
)

target_link_libraries(engine
    ${CMAKE_SOURCE_DIR}/libs/glfw/lib/glfw3.lib
)
