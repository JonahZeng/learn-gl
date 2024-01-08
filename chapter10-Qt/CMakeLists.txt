cmake_minimum_required(VERSION 3.5)

project(chapter10-Qt VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/Debug)

set(PROJECT_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/myWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/shader.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(chapter10-Qt
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET chapter10-Qt APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(chapter10-Qt SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(chapter10-Qt
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(chapter10-Qt PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc ${CMAKE_SOURCE_DIR}/third-party/glm)
target_link_libraries(chapter10-Qt PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::OpenGLWidgets)# Qt${QT_VERSION_MAJOR}::DataVisualization Qt${QT_VERSION_MAJOR}::Network)
# if(WIN32)
#     target_compile_options(chapter10-Qt PRIVATE /W4)
# elseif(UNIX)
#    target_compile_options(chapter10-Qt PRIVATE -Wall)
# endif()

set_target_properties(chapter10-Qt PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

set_property(TARGET chapter10-Qt PROPERTY CXX_STANDARD 17)

install(TARGETS chapter10-Qt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(chapter10-Qt)
endif()
