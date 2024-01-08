cmake_minimum_required(VERSION 3.16)
project(chapter13-Qt LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/Debug)

qt_add_executable(chapter13-Qt
    geometryengine.cpp geometryengine.h
    main.cpp
    mainwidget.cpp mainwidget.h
)

set_target_properties(chapter13-Qt PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(chapter13-Qt PUBLIC
    Qt::Core
    Qt::Gui
    Qt::OpenGL
    Qt::OpenGLWidgets
    Qt::Widgets
)

# Resources:
set(shaders_resource_files
    "fshader.glsl"
    "vshader.glsl"
)

qt6_add_resources(chapter13-Qt "shaders"
    PREFIX
        "/"
    FILES
        ${shaders_resource_files}
)

set(textures_resource_files
    "cube.png"
)

qt6_add_resources(chapter13-Qt "textures"
    PREFIX
        "/"
    FILES
        ${textures_resource_files}
)
