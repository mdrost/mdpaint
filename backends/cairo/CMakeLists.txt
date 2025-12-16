find_package(Cairo)
find_package(Boost REQUIRED)

set(SOURCES
    include/mdpaint/cairo/api.h
    include/mdpaint/cairo/cairobackendplugin.h
    cairobackendplugin.cpp
    cairoellipsetool.h
    cairoellipsetool.cpp
    cairohistoryentry.h
    cairohistoryentry.cpp
    cairoimagemodel.h
    cairoimagemodel.cpp
    cairolinetool.h
    cairolinetool.cpp
    cairomodel.h
    cairomodel.cpp
    cairopentool.h
    cairopentool.cpp
    cairorectangletool.h
    cairorectangletool.cpp
    cairoresizescaleskewtool.h
    cairoresizescaleskewtool.cpp
)

add_library(mdpaint_cairo SHARED
    ${SOURCES}
)

target_compile_definitions(mdpaint_cairo
    PUBLIC
    PRIVATE
        MDP_CAIRO_EXPORTS
        $<$<STREQUAL:$<TARGET_PROPERTY:mdpaint_cairo,TYPE>,SHARED_LIBRARY>:MDP_CAIRO_BUILD_SHARED>
)

target_include_directories(mdpaint_cairo
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/mdpaint/cairo
)

set_target_properties(mdpaint_cairo PROPERTIES
    OUTPUT_NAME mdpaintcairo
)

target_link_libraries(mdpaint_cairo
    PUBLIC
        mdpaint::interface
    PRIVATE
        Cairo::Cairo
        mdpaint::private
        Boost::headers
)

add_library(mdpaint::cairo ALIAS mdpaint_cairo)
