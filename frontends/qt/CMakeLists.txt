set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES mdpaint_pl_PL.ts)

set(QRC_FILES mdpaint.qrc)

set(SOURCES
    qtapi.h
    qtbackendfactory.h
    qtbackendfactory.cpp
    qtcolorbox.h
    qtcolorbox.cpp
    qtfrontend.h
    qtfrontend.cpp
    qthistoryview.h
    qthistoryview.cpp
    qtimagecontainer.h
    qtimagecontainer.cpp
    qtimageview.h
    qtimageview.cpp
    qtmainwindow.h
    qtmainwindow.cpp
    qtplugin.h
    qtplugin.cpp
    qtresizescaleskewdialog.h
    qtresizescaleskewdialog.cpp
    qtresizescaleskewtoolwrapper.h
    qtresizescaleskewtoolwrapper.cpp
    qtsizegrip.h
    qtsizegrip.cpp
    qtsizeoverlay.h
    qtsizeoverlay.cpp
    qtspinbox.h
    qtspinbox.cpp
    qttoolaction.h
    qttoolaction.cpp
    qttoolbox.h
    qttoolbox.cpp
    backend/qtellipsetool.h
    backend/qtellipsetool.cpp
    backend/qthistoryentry.h
    backend/qthistoryentry.cpp
    backend/qtimagemodel.h
    backend/qtimagemodel.cpp
    backend/qtlinetool.h
    backend/qtlinetool.cpp
    backend/qtmodel.h
    backend/qtmodel.cpp
    backend/qtpentool.h
    backend/qtpentool.cpp
    backend/qtrectangletool.h
    backend/qtrectangletool.cpp
    backend/qtresizescaleskewtool.h
    backend/qtresizescaleskewtool.cpp
    qt.json.in
    ${TS_FILES}
    ${QRC_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_library(mdpaint_qt MODULE
        MANUAL_FINALIZATION
        ${SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET mdpaint APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    add_library(mdpaint_qt MODULE
        ${SOURCES}
    )

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_compile_definitions(mdpaint_qt
    PRIVATE
        MDP_QT_EXPORTS
        $<$<STREQUAL:$<TARGET_PROPERTY:mdpaint_qt,TYPE>,MODULE_LIBRARY>:MDP_QT_BUILD_MODULE>
        QT_NO_KEYWORDS
)

target_include_directories(mdpaint_qt
    PRIVATE
)

set_target_properties(mdpaint_qt PROPERTIES
    OUTPUT_NAME mdpaintqt
)

target_link_libraries(mdpaint_qt
    PRIVATE
        mdpaint::interface
        mdpaint::private
        Qt${QT_VERSION_MAJOR}::Widgets
)

add_custom_command(TARGET mdpaint_qt POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            "$<TARGET_FILE:mdpaint_qt>"
            "$<TARGET_FILE_DIR:mdpaint>/frontends")

# TODO: Make it more intelligent. Unfortunately generator expression don't seem to work.
if(WIN32)
    set(MDPAINT_QT_JSON_PATH mdpaintqt.dll)
elseif(UNIX)
    set(MDPAINT_QT_JSON_PATH libmdpaintqt.so)
endif()

configure_file(qt.json.in mdpaintqt.json @ONLY)

add_custom_command(TARGET mdpaint_qt POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_CURRENT_BINARY_DIR}/mdpaintqt.json"
            "$<TARGET_FILE_DIR:mdpaint>/frontends/")

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_target(mdpaint_qt)
endif()

add_library(mdpaint::qt ALIAS mdpaint_qt)
