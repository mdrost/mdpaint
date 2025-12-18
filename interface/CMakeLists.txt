set(SOURCES
    include/mdpaint/api.h
    include/mdpaint/backendfactory.h
    backendfactory.cpp
    include/mdpaint/frontend.h
    frontend.cpp
    include/mdpaint/history.h
    history.cpp
    include/mdpaint/historyentry.h
    historyentry.cpp
    include/mdpaint/imagemodel.h
    imagemodel.cpp
    include/mdpaint/loader.h
    loader.cpp
    include/mdpaint/plugin.h
    plugin.cpp
    include/mdpaint/resizescaleskewtool.h
    resizescaleskewtool.cpp
    include/mdpaint/signalconnection.h
    signalconnection.cpp
    include/mdpaint/tool.h
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
        mdpaint::private
)

add_library(mdpaint::interface ALIAS mdpaint_interface)
