if(POLICY CMP0167)
  cmake_policy(SET CMP0167 NEW)
endif()

find_package(Vips REQUIRED)
find_package(Boost REQUIRED)
find_package(GLIB2 REQUIRED)

set(SOURCES
    vipsapi.h
    vipsbackendfactory.h
    vipsbackendfactory.cpp
    vipsellipsetool.h
    vipsellipsetool.cpp
    vipshistoryentry.h
    vipshistoryentry.cpp
    vipsimagemodel.h
    vipsimagemodel.cpp
    vipslinetool.h
    vipslinetool.cpp
    vipsmodel.h
    vipsmodel.cpp
    vipspentool.h
    vipspentool.cpp
    vipsplugin.h
    vipsplugin.cpp
    vipsrectangletool.h
    vipsrectangletool.cpp
    vipsresizescaleskewtool.h
    vipsresizescaleskewtool.cpp
    vipssignalconnectionprivate.h
    vipssignalconnectionprivate.cpp
    vipssvgtemplates.h
    vips.json.in
)

add_library(mdpaint_vips MODULE
    ${SOURCES}
)

target_compile_definitions(mdpaint_vips
    PUBLIC
    PRIVATE
        MDP_VIPS_EXPORTS
        $<$<STREQUAL:$<TARGET_PROPERTY:mdpaint_vips,TYPE>,MODULE_LIBRARY>:MDP_VIPS_BUILD_MODULE>
)

target_include_directories(mdpaint_vips
    PRIVATE
)

set_target_properties(mdpaint_vips PROPERTIES
    OUTPUT_NAME mdpaintvips
)

target_link_libraries(mdpaint_vips
    PUBLIC
        mdpaint::interface
    PRIVATE
        Vips::Vips
        Boost::headers
        GLIB2::GOBJECT
)

add_custom_command(TARGET mdpaint_vips POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            "$<TARGET_FILE:mdpaint_vips>"
            "$<TARGET_FILE_DIR:mdpaint>/backends")

# TODO: Make it more intelligent. Unfortunately generator expression don't seem to work.
if(WIN32)
    set(MDPAINT_VIPS_JSON_PATH mdpaintvips.dll)
elseif(UNIX)
    set(MDPAINT_VIPS_JSON_PATH libmdpaintvips.so)
endif()

configure_file(vips.json.in mdpaintvips.json @ONLY)

add_custom_command(TARGET mdpaint_vips POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_CURRENT_BINARY_DIR}/mdpaintvips.json"
            "$<TARGET_FILE_DIR:mdpaint>/backends/")

add_library(mdpaint::vips ALIAS mdpaint_vips)
