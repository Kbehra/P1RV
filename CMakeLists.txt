cmake_minimum_required(VERSION 3.00)

set(PROJECT_NAME "P1RV")

project(${PROJECT_NAME})

set (CMAKE_CXX_STANDARD 14)

link_directories( /usr/lib/x86_64-linux-gnu )

set(CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu ")

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(P1RV
        main.cpp
        Sources/loadjpeg.cpp
        Sources/loadjpeg.h
        Sources/pixel.cpp
        Sources/pixel.h
        Sources/createmap.cpp
        Sources/createmap.h
        Sources/camera.cpp
        Sources/camera.h
        Sources/material.cpp
        Sources/material.h
        Sources/vertex.cpp
        Sources/vertex.h
        Sources/interface.cpp
        Sources/interface.h
        Sources/mywindow.cpp
        Sources/mywindow.h Sources/mymainwindow.cpp Sources/mymainwindow.h)

# Qt4
# required packages
find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)
include(${QT_USE_FILE})
set(LIBRARIES ${LIBRARIES} ${QT_LIBRARIES})


# OpenGL
# required packages
find_package ( OpenGL REQUIRED )
find_package ( GLUT REQUIRED )


add_definitions(${QT_DEFINITIONS})

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories( ${CMAKE_BINARY_DIR} )
include_directories(${QT_QTOPENGL_INCLUDE_DIR})
include_directories( ${OPENGL_DIRS} ${GLUT_DIRS} )


# target link
target_link_libraries(  ${PROJECT_NAME}
                        ${OPENGL_LIBRARIES}
                        ${GLUT_LIBRARIES}
                        ${QT_LIBRARIES}
                          libjpeg.so)
