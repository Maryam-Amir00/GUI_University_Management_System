cmake_minimum_required(VERSION 3.5)

project(GUI_Project VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(GUI_Project
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

        adminauthenticate.h adminauthenticate.cpp adminauthenticate.ui
        studentauthenticate.h studentauthenticate.cpp studentauthenticate.ui
        teacherauthenticate.h teacherauthenticate.cpp teacherauthenticate.ui
        teacherauthenticate.h teacherauthenticate.cpp teacherauthenticate.ui
        admindes.h admindes.cpp admindes.ui
        teacherdes.h teacherdes.cpp teacherdes.ui
        studentdes.h studentdes.cpp studentdes.ui
        addstudent.h addstudent.cpp addstudent.ui
        removestudent.h removestudent.cpp removestudent.ui
        removestudent.h removestudent.cpp removestudent.ui
        struct.h
        checkrecords.h checkrecords.cpp
        addteacher.h addteacher.cpp addteacher.ui
        teacherstruct.h
        removeteacher.h removeteacher.cpp removeteacher.ui
        checkteacher.h checkteacher.cpp
        updatestudent.h updatestudent.cpp
        updateteacher.h updateteacher.cpp
        studentexist.h studentexist.cpp
        checkteacherinfo.h checkteacherinfo.cpp
        teacherexist.h teacherexist.cpp
        checkinfo.h checkinfo.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET GUI_Project APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(GUI_Project SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(GUI_Project
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(GUI_Project PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.GUI_Project)
endif()
set_target_properties(GUI_Project PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS GUI_Project
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(GUI_Project)
endif()
