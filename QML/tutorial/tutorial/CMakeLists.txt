cmake_minimum_required(VERSION 3.16)

project(tutorial VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(apptutorial
    main.cpp
    HelloWorld.cpp
    HelloWorld.h
)

qt_add_qml_module(apptutorial
    URI tutorial
    VERSION 1.0
    QML_FILES Main.qml Cell.qml
)

set_target_properties(apptutorial PROPERTIES
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(apptutorial
    PRIVATE Qt6::Quick
)

install(TARGETS apptutorial
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
