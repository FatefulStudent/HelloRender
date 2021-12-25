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
	./src/Helper/ApplicationHelper.h
	./src/Helper/VertexData.h
	./src/Tests/BaseTest.h
	./src/Tests/Test_2ShaderPrograms.h
	./src/Tests/Test_SimpleTriangle.h
	./src/shaderInstance.h
	./src/shaderProgram.h

	./src/Tests/BaseTest.cpp
	./src/Helper/ApplicationHelper.cpp
	./src/Tests/Test_SimpleTriangle.cpp
	./src/Tests/Test_2ShaderPrograms.cpp
	./src/shaderInstance.cpp
	./src/main.cpp
	./src/shaderProgram.cpp
	)

target_link_libraries(HelloRender glew glfw GL)
