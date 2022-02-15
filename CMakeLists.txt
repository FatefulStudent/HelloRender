cmake_minimum_required( VERSION 3.16 )

set (CMAKE_CXX_STANDARD 17)

project (HelloRender)

find_package(OpenGL REQUIRED)

add_subdirectory(libs)


include_directories(
	libs/glew-2.1.0/include/
	libs/glfw-3.3.5/include/
	libs/glm-0.9.8/
	libs/stb/
	src/
	Lessons/
)

set(HEADERS  
	./libs/stb/stb_image.h
	./Lessons/BaseExcercise.h
	./Lessons/6.\ Camera/Ex_Camera.h
	./src/Helper/Application.h
	./src/Helper/VertexData.h
	./src/shaderInstance.h
	./src/shaderProgram.h
	./src/texture.h
	./src/mesh.h
	./src/camera.h
)
set(SOURCES 
	./libs/stb/stb_image.cpp
	./Lessons/BaseExcercise.cpp
	./Lessons/6.\ Camera/Ex_Camera.cpp
	./src/Helper/Application.cpp
	./src/shaderInstance.cpp
	./src/shaderProgram.cpp
	./src/texture.cpp
	./src/mesh.cpp
	./src/camera.cpp
)

add_executable(HelloRender 
	${HEADERS}
	${SOURCES}
	./src/main.cpp
)
target_link_libraries(HelloRender glew glfw GL)
