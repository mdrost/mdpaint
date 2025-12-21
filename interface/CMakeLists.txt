set(SOURCES
    include/mdpaint/api.h
    include/mdpaint/backendfactory.h
    include/mdpaint/ellipse.h
    include/mdpaint/frontend.h
    include/mdpaint/history.h
    include/mdpaint/historyentry.h
    include/mdpaint/imagemodel.h
    include/mdpaint/imagereader.h
    include/mdpaint/imagewriter.h
    include/mdpaint/plugin.h
    include/mdpaint/point.h
    include/mdpaint/rectangle.h
    include/mdpaint/resizescaleskewtool.h
    include/mdpaint/selectiontool.h
    include/mdpaint/signalconnection.h
    include/mdpaint/signalconnectionprivate.h
    include/mdpaint/tool.h
    backendfactory.cpp
    frontend.cpp
    history.cpp
    historyentry.cpp
    imagemodel.cpp
    imagereader.cpp
    imagewriter.cpp
    plugin.cpp
    resizescaleskewtool.cpp
    selectiontool.cpp
    signalconnection.cpp
    signalconnectionprivate.cpp
    tool.cpp
)

add_library(mdpaint_interface SHARED
    ${SOURCES}
)

target_compile_definitions(mdpaint_interface
    INTERFACE
    PUBLIC
    PRIVATE
        MDP_INTERFACE_EXPORTS
        $<$<STREQUAL:$<TARGET_PROPERTY:mdpaint_interface,TYPE>,SHARED_LIBRARY>:MDP_INTERFACE_BUILD_SHARED>
)

target_include_directories(mdpaint_interface
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PUBLIC
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/mdpaint
)

set_target_properties(mdpaint_interface PROPERTIES
    OUTPUT_NAME mdpaint
)

target_link_libraries(mdpaint_interface
    INTERFACE
    PUBLIC
    PRIVATE
)

add_library(mdpaint::interface ALIAS mdpaint_interface)
