if(POLICY CMP0167)
  cmake_policy(SET CMP0167 NEW)
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
            $<TARGET_FILE:mdpaint_cairo>
            "$<TARGET_FILE_DIR:mdpaint>/backends")

add_library(mdpaint::cairo ALIAS mdpaint_cairo)
