
cmake_minimum_required(VERSION 2.8)

project(gluttest)
add_executable(gluttest main.cpp)

# ����� OpenGL
find_package(OpenGL REQUIRED)
# ����� FreeGLUT
find_package(GLUT REQUIRED)

# ������ ����� ��������� ���������� � header-���
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

# � ������� ���������� ��� ��������
target_link_libraries(gluttest ${OPENGL_LIBRARIES} freeglut)