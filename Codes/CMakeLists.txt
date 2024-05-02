cmake_minimum_required(VERSION 3.0.0)
project(my_opengl2_project )
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

add_executable(my_opengl2_project
                src/Construction4.cpp)

target_link_libraries(my_opengl2_project
                        glfw
                        glut
                        GLU
                        OpenGL::GL)

