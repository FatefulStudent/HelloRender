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
	libs/assimp-5.2.3/include/
	libs/glm-0.9.8/
	libs/stb/
	src/
	examples/
)

add_subdirectory(libs)
add_subdirectory(libs/assimp-5.2.3)

if( MSVC )
	file(GLOB ResourceFiles "res/*") 
	file(COPY ${ResourceFiles} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res)

	file(GLOB ShaderFiles "shaders/*") 
	file(COPY ${ShaderFiles} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shaders)

	SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

set(HEADERS  
	./libs/stb/stb_image.h
	
	./examples/Excercise.h
	./examples/BaseExcercise.h
	./examples/ArkanoidProject/Arkanoid.h
	
	./src/Helper/MeshData.h
	./src/Helper/ShaderData.h
	./src/Helper/Application.h
	./src/Helper/FileHelper.h
	./src/Helper/ShaderHelper.h
	
	./src/Legacy/camera3d.h
	./src/Legacy/camera2d.h	
	
	./src/Entity/Entity.h
	./src/World/World.h
	./src/Components/Component.h
	./src/Components/ModelComponent.h
	./src/Components/ShaderComponent.h
	./src/Systems/System.h
	./src/Systems/RenderingSystem.h
	./src/Systems/ShaderSystem.h
)
set(SOURCES 
	./libs/stb/stb_image.cpp
	./examples/BaseExcercise.cpp
	./examples/ArkanoidProject/Arkanoid.cpp

	./src/Helper/MeshData.cpp
	./src/Helper/ShaderData.cpp
	./src/Helper/Application.cpp
	./src/Helper/ShaderHelper.cpp
	./src/Helper/FileHelper.cpp
	
	./src/Legacy/camera3d.cpp
	./src/Legacy/camera2d.cpp
	
	./src/Entity/Entity.cpp
	./src/World/World.cpp
	./src/Components/Component.cpp
	./src/Components/ModelComponent.cpp
	./src/Components/ShaderComponent.cpp
	./src/Systems/System.cpp
	./src/Systems/RenderingSystem.cpp
	./src/Systems/ShaderSystem.cpp
)

add_executable(${PROJECT_NAME} 
	${HEADERS}
	${SOURCES}
	./src/main.cpp
)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} assimp glew glfw)

if( MSVC )
    set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME} )
endif()
