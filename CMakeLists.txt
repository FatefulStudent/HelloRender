cmake_minimum_required( VERSION 3.16 )

set (CMAKE_CXX_STANDARD 17)
set (PROJECT_NAME HelloRender)

project (${PROJECT_NAME})

find_package(OpenGL REQUIRED)

add_definitions(-DGLEW_STATIC)

include_directories(
	${OPENGL_INCLUDE_DIRS}
	libs/glew-2.1.0/include/
	libs/glfw-3.3.5/include/
	libs/glm-0.9.8/
	libs/stb/
	src/
	examples/
)

add_subdirectory(libs)

if( MSVC )
	file(GLOB ResourceFiles "res/*") 
	file(COPY ${ResourceFiles} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res)

	file(GLOB ShaderFiles "shaders/*") 
	file(COPY ${ShaderFiles} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shaders)

	SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

set(HEADERS  
	./libs/stb/stb_image.h
	./src/Excercise.h
	./examples/BaseExcercise.h
	./examples/ArkanoidProject/Arkanoid.h
	./src/Helper/Application.h
	./src/Helper/VertexData.h
	./src/shaderInstance.h
	./src/shaderProgram.h
	./src/texture.h
	./src/mesh.h
	./src/camera3d.h
	./src/camera2d.h
	./src/Entity.h
	./src/World.h
	./src/Component.h
)
set(SOURCES 
	./libs/stb/stb_image.cpp
	./examples/BaseExcercise.cpp
	./examples/ArkanoidProject/Arkanoid.cpp
	./src/Helper/Application.cpp
	./src/shaderInstance.cpp
	./src/shaderProgram.cpp
	./src/texture.cpp
	./src/mesh.cpp
	./src/camera3d.cpp
	./src/camera2d.cpp
	./src/Entity.cpp
	./src/World.cpp
	./src/Component.cpp
)

add_executable(${PROJECT_NAME} 
	${HEADERS}
	${SOURCES}
	./src/main.cpp
)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glew glfw)

if( MSVC )
    set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME} )
endif()
