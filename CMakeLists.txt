cmake_minimum_required(VERSION 3.10)
project(OpenGLProject)

set(CMAKE_CXX_STANDARD 17)

# 소스 파일
file(GLOB SOURCES "*.cpp" "*.c")
add_executable(${PROJECT_NAME} ${SOURCES})

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)

# GLUT / freeGLUT
if(WIN32)
    # Windows: glut32.lib 또는 freeglut
    find_package(GLUT REQUIRED)
    target_link_libraries(${PROJECT_NAME} GLUT::GLUT)
    target_include_directories(${PROJECT_NAME} PRIVATE ${GLUT_INCLUDE_DIR})

elseif(APPLE)
    # macOS: 내장 GLUT.framework
    find_package(GLUT REQUIRED)
    target_link_libraries(${PROJECT_NAME} GLUT::GLUT "-framework Cocoa")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wno-deprecated)
endif()
