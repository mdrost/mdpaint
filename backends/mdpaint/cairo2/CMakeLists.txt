find_package(Cairo2)

set(SOURCES
    cairo2backendplugin.h
    cairo2backendplugin.cpp
    cairo2ellipsetool.h
    cairo2ellipsetool.cpp
    cairo2historyentry.h
    cairo2historyentry.cpp
    cairo2imagemodel.h
    cairo2imagemodel.cpp
    cairo2linetool.h
    cairo2linetool.cpp
    cairo2model.h
    cairo2model.cpp
    cairo2pentool.h
    cairo2pentool.cpp
    cairo2rectangletool.h
    cairo2rectangletool.cpp
    cairo2resizescaleskewtool.h
    cairo2resizescaleskewtool.cpp
)

add_library(mdpaint_cairo2
    ${SOURCES}
)

target_include_directories(mdpaint_cairo2
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../..
    PRIVATE
)

target_link_libraries(mdpaint_cairo2
    PUBLIC
        mdpaint::interface
        Cairo2::Cairo2
    PRIVATE
        mdpaint::private
)

add_library(mdpaint::cairo2 ALIAS mdpaint_cairo2)
