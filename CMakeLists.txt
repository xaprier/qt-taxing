cmake_minimum_required(VERSION 3.5)

project(qt-taxing VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_PREFIX_PATH "~/Qt/6.4.1/gcc_64/lib/cmake")

set(dir ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
set(LIBRARY_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    cpp-files/main.cpp
    cpp-files/logindialog.cpp
    header-files/logindialog.h
    design-files/logindialog.ui
    cpp-files/managementdialog.cpp
    header-files/managementdialog.h
    design-files/managementdialog.ui
    cpp-files/taxsystem.cpp
    design-files/taxsystem.ui
    header-files/taxsystem.h
    cpp-files/questioning.cpp
    header-files/questioning.h
    design-files/questioning.ui
    design-files/resources.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(qt-taxing
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

# Define target properties for Android with Qt 6 as:
# set_property(TARGET qt-taxing APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
# ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(qt-taxing SHARED
            ${PROJECT_SOURCES}
        )

    # Define properties for Android with Qt 5 after find_package() calls as:
    # set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(qt-taxing
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(qt-taxing PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(qt-taxing PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS qt-taxing
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION build)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(qt-taxing)
endif()

# copy the json files to the executable path
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/ DESTINATION ${dir}/data/)
