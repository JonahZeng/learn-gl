cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(learn-gl VERSION 0.1.0 LANGUAGES CXX C)

if(WIN32)
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/third-party/glfw3_win")
endif()

# if(UNIX)
#     find_package(OpenGL REQUIRED)
# endif()

find_package(glfw3 REQUIRED)

add_subdirectory(${CMAKE_SOURCE_DIR}/chapter1)
add_subdirectory(${CMAKE_SOURCE_DIR}/chapter2)
add_subdirectory(${CMAKE_SOURCE_DIR}/chapter3)
add_subdirectory(${CMAKE_SOURCE_DIR}/chapter4)
add_subdirectory(${CMAKE_SOURCE_DIR}/chapter5)
add_subdirectory(${CMAKE_SOURCE_DIR}/chapter6)
add_subdirectory(${CMAKE_SOURCE_DIR}/chapter7)
add_subdirectory(${CMAKE_SOURCE_DIR}/chapter8)
add_subdirectory(${CMAKE_SOURCE_DIR}/chapter9)

if(USE_QT)
    message(STATUS "enable Qt example")
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)

    find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Gui OpenGLWidgets )# DataVisualization Network)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Gui OpenGLWidgets)# DataVisualization Network)
    
    add_subdirectory(${CMAKE_SOURCE_DIR}/chapter1-Qt)
    add_subdirectory(${CMAKE_SOURCE_DIR}/chapter2-Qt)
    add_subdirectory(${CMAKE_SOURCE_DIR}/chapter3-Qt)
    add_subdirectory(${CMAKE_SOURCE_DIR}/chapter4-Qt)
    add_subdirectory(${CMAKE_SOURCE_DIR}/chapter5-Qt)
endif()