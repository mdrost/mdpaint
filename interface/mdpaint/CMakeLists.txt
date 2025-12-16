set(SOURCES
    api.h
    backendplugin.h
    backendplugin.cpp
    history.h
    history.cpp
    historyentry.h
    historyentry.cpp
    imagemodel.h
    imagemodel.cpp
    resizescaleskewtool.h
    resizescaleskewtool.cpp
    signalconnection.h
    signalconnection.cpp
    tool.h
    tool.cpp
)

add_library(mdpaint_interface SHARED
    ${SOURCES}
)

target_compile_definitions(mdpaint_interface
    PUBLIC
    PRIVATE
        MDP_INTERFACE_EXPORTS
        $<$<STREQUAL:$<TARGET_PROPERTY:mdpaint_interface,TYPE>,SHARED_LIBRARY>:MDP_INTERFACE_BUILD_SHARED>
)

target_include_directories(mdpaint_interface
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/..
    PRIVATE
)

set_target_properties(mdpaint_interface PROPERTIES
    OUTPUT_NAME mdpaint
)

target_link_libraries(mdpaint_interface
    PUBLIC
    PRIVATE
        mdpaint::private
)

add_library(mdpaint::interface ALIAS mdpaint_interface)
