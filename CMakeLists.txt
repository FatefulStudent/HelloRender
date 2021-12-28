cmake_minimum_required( VERSION 3.16 )

project (HelloRender)

find_package(OpenGL REQUIRED)

add_subdirectory(libs)


include_directories(
	libs/glew-2.1.0/include/
	libs/glfw-3.3.5/include/
	src/
	Lessons/
)

set(HEADERS 
	./Lessons/BaseExcercise.h
	./Lessons/HelloTriangle/Ex_SimpleTriangle.h
	./Lessons/Shaders/Ex_2ShaderPrograms.h
	./Lessons/Shaders/Ex_Additionals.h
	./src/Helper/ApplicationHelper.h
	./src/Helper/VertexData.h
	./src/shaderInstance.h
	./src/shaderProgram.h
)
set(SOURCES 
	./Lessons/BaseExcercise.cpp
	./Lessons/HelloTriangle/Ex_SimpleTriangle.cpp
	./Lessons/Shaders/Ex_2ShaderPrograms.cpp
	./Lessons/Shaders/Ex_Additionals.cpp
	./src/Helper/ApplicationHelper.cpp
	./src/shaderInstance.cpp
	./src/shaderProgram.cpp
)

add_executable(HelloRender 
	${HEADERS}
	${SOURCES}
	./src/main.cpp
)
target_link_libraries(HelloRender glew glfw GL)
