cmake_minimum_required(VERSION 3.10)
project(OpenGLCourse)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "src/*.cpp")

foreach(SOURCE ${SOURCES})
    get_filename_component(TARGET_NAME ${SOURCE} NAME_WE)
    add_executable(${TARGET_NAME} ${SOURCE})

    find_package(OpenGL REQUIRED)
    target_link_libraries(${TARGET_NAME} OpenGL::GL)

    if(APPLE)
        find_package(GLUT REQUIRED)
        target_link_libraries(${TARGET_NAME} GLUT::GLUT "-framework Cocoa")
        target_compile_options(${TARGET_NAME} PRIVATE -Wno-deprecated)
    elseif(WIN32)
        find_package(GLUT REQUIRED)
        target_link_libraries(${TARGET_NAME} GLUT::GLUT)
        target_include_directories(${TARGET_NAME} PRIVATE ${GLUT_INCLUDE_DIR})
    endif()
endforeach()
