if(POLICY CMP0167)
    if(WIN32)
        cmake_policy(SET CMP0167 OLD)
    else()
        cmake_policy(SET CMP0167 NEW)
    endif()
endif()

find_package(Cairo)
find_package(Boost REQUIRED)

set(SOURCES
    cairoapi.h
    cairobackendfactory.h
    cairobackendfactory.cpp
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
    cairoplugin.h
    cairoplugin.cpp
    cairorectangletool.h
    cairorectangletool.cpp
    cairoresizescaleskewtool.h
    cairoresizescaleskewtool.cpp
    cairo.json.in
)

add_library(mdpaint_cairo MODULE
    ${SOURCES}
)

target_compile_definitions(mdpaint_cairo
    PUBLIC
    PRIVATE
        MDP_CAIRO_EXPORTS
        $<$<STREQUAL:$<TARGET_PROPERTY:mdpaint_cairo,TYPE>,MODULE_LIBRARY>:MDP_CAIRO_BUILD_MODULE>
)

target_include_directories(mdpaint_cairo
    PRIVATE
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

add_custom_command(TARGET mdpaint_cairo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            "$<TARGET_FILE:mdpaint_cairo>"
            "$<TARGET_FILE_DIR:mdpaint>/backends")

# TODO: Make it more intelligent. Unfortunately generator expression don't seem to work.
if(WIN32)
    set(MDPAINT_CAIRO_JSON_PATH mdpaintcairo.dll)
elseif(UNIX)
    set(MDPAINT_CAIRO_JSON_PATH libmdpaintcairo.so)
endif()

configure_file(cairo.json.in cairo.json @ONLY)

add_custom_command(TARGET mdpaint_cairo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_CURRENT_BINARY_DIR}/cairo.json"
            "$<TARGET_FILE_DIR:mdpaint>/backends/mdpaintcairo.json")

add_library(mdpaint::cairo ALIAS mdpaint_cairo)
