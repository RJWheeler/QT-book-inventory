cmake_minimum_required(VERSION 3.5)

project(QTBook VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets )
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        qtbookinventory.h
        qtbookinventory.cpp
        Log_file.h
        log.h
        log.cpp
        loginwindow2.h
        loginwindow2.cpp
        loginwindow2.ui
        dialog.cpp
        dialog.h
        dialog.ui
        admin.h
        admin.cpp
        admin.ui
        adduser.h
        adduser.cpp
        adduser.ui
        addbook.h
        addbook.cpp
        addbook.ui
        updatebook.h
        updatebook.cpp
        updatebook.ui
        updateuser.h
        updateuser.cpp
        updateuser.ui
        profile.h
        profile.cpp
        profile.ui


)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QTBook
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET QTBook APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(QTBook SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(QTBook
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(QTBook PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::Sql)


set_target_properties(QTBook PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS QTBook
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QTBook)
endif()
