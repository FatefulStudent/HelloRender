cmake_minimum_required( VERSION 3.16 )

project (HelloRender)

find_package(OpenGL REQUIRED)

add_subdirectory(libs)


include_directories(
	libs/glew-2.1.0/include/
	libs/glfw-3.3.5/include/
	src/
)

add_executable(HelloRender 
	./src/Lessons/BaseExcercise.h
	./src/Lessons/HelloTriangle/Ex_SimpleTriangle.h
	./src/Lessons/Shaders/Ex_2ShaderPrograms.h
	./src/Helper/ApplicationHelper.h
	./src/Helper/VertexData.h
	./src/shaderInstance.h
	./src/shaderProgram.h

	./src/main.cpp

	./src/Lessons/BaseExcercise.cpp
	./src/Lessons/HelloTriangle/Ex_SimpleTriangle.cpp
	./src/Lessons/Shaders/Ex_2ShaderPrograms.cpp
	./src/Helper/ApplicationHelper.cpp
	./src/shaderInstance.cpp
	./src/shaderProgram.cpp
	)

target_link_libraries(HelloRender glew glfw GL)
