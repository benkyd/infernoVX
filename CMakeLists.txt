cmake_minimum_required(VERSION 3.7)
project(InfernoVX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} CMakeModules/)

set(executable output)
set(SrcDIR ./src)
set(IncludeDIR ./include)

# Setting resource path
add_definitions(-D_RESOURCES="${CMAKE_SOURCE_DIR}/resources/")
message(${CMAKE_SOURCE_DIR}/resources)

if (UNIX)
	# set(CMAKE_BUILD_TYPE Debug)
	# set(CMAKE_CXX_FLAGS "-Ofast")
	find_package(SDL2 REQUIRED)
endif(UNIX)

if (WIN32)
	set(CMAKE_CXX_FLAGS "/Ox")
	include_directories(${executable}
		"C:/dev/glm"
		"C:/dev/SDL2/include/"
		"C:/dev/SDL2_image/include/"
	)
endif (WIN32)

set(THREADS_PREFER_PTHREAD_FLAD ON)
find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)

if (UNIX)
	include_directories(${executable}
		${SDL2_INCLUDE_DIR}
	)
endif (UNIX)

include_directories(${executable}
	${IncludeDIR}
)

file(GLOB SourceFiles 
	${SrcDIR}/*
)

add_executable(${executable} ${SourceFiles})

set_target_properties(${executable} PROPERTIES
	CXX_STANDARD 20
	CXX_EXTENSIONS ON
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

if (UNIX)
	target_link_libraries(${executable}
		SDL2
		OpenGL::OpenGL
		OpenGL::GL
		Threads::Threads
	)
endif (UNIX)

if (WIN32)
	target_link_libraries(${executable}
		"C:/dev/SDL2/lib/x64/SDL2.lib"
		"C:/dev/SDL2/lib/x64/SDL2main.lib"
		"C:/dev/SDL2/lib/x64/SDL2test.lib"
		${WinSDK}
	)
endif (WIN32)

target_link_libraries(${executable}
	${CMAKE_DL_LIBS}
)
