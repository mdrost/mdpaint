cmake_minimum_required(VERSION 3.24)

project(mdpaint VERSION 0.1 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

add_subdirectory(interface/mdpaint)
add_subdirectory(private/mdpaint/private)
if(MDPAINT_WITH_CAIRO)
    add_subdirectory(backends/cairo)
endif()
if(MDPAINT_WITH_VIPS)
    add_subdirectory(backends/vips)
endif()

set(TS_FILES mdpaint_pl_PL.ts)

set(QRC_FILES mdpaint.qrc)

set(PROJECT_SOURCES
    colorbox.h
    colorbox.cpp
    historyview.h
    historyview.cpp
    imagecontainer.h
    imagecontainer.cpp
    imageview.h
    imageview.cpp
    main.cpp
    mainwindow.h
    mainwindow.cpp
    resizescaleskewdialog.h
    resizescaleskewdialog.cpp
    resizescaleskewtoolwrapper.h
    resizescaleskewtoolwrapper.cpp
    sizegrip.h
    sizegrip.cpp
    sizeoverlay.h
    sizeoverlay.cpp
    spinbox.h
    spinbox.cpp
    toolaction.h
    toolaction.cpp
    toolbox.h
    toolbox.cpp
    ${TS_FILES}
    ${QRC_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(mdpaint
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET mdpaint APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(mdpaint SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(mdpaint
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_compile_definitions(mdpaint PRIVATE QT_NO_KEYWORDS)
target_link_libraries(mdpaint
    PUBLIC
    PRIVATE
        mdpaint::interface
        Qt${QT_VERSION_MAJOR}::Widgets
)

if(MDPAINT_WITH_QT)
    add_subdirectory(frontends/qt)
    add_dependencies(mdpaint mdpaint::qt)
endif()

if(MDPAINT_WITH_CAIRO)
    add_subdirectory(backends/cairo)
    add_dependencies(mdpaint mdpaint::cairo)
    target_link_libraries(mdpaint
        PUBLIC
        PRIVATE
            mdpaint::cairo
    )
endif()
if(MDPAINT_WITH_VIPS)
    find_package(Vips REQUIRED)
    find_package(GLIB2 REQUIRED)
    target_link_libraries(mdpaint
        PUBLIC
        PRIVATE
            mdpaint::vips
            Vips::Vips
            GLIB2::GLIB2
    )
endif()

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.mdrost.mdpaint)
endif()
set_target_properties(mdpaint PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS mdpaint
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(mdpaint)
endif()
