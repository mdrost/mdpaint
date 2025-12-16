find_package(Vips REQUIRED)
find_package(Boost REQUIRED)
find_package(GLIB2 REQUIRED)

set(SOURCES
    include/mdpaint/vips/api.h
    include/mdpaint/vips/vipsbackendplugin.h
    vipsbackendplugin.cpp
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
    vipsrectangletool.h
    vipsrectangletool.cpp
    vipsresizescaleskewtool.h
    vipsresizescaleskewtool.cpp
    vipssvgtemplates.h
)

add_library(mdpaint_vips SHARED
    ${SOURCES}
)

target_compile_definitions(mdpaint_vips
    PUBLIC
    PRIVATE
        MDP_VIPS_EXPORTS
        $<$<STREQUAL:$<TARGET_PROPERTY:mdpaint_vips,TYPE>,SHARED_LIBRARY>:MDP_VIPS_BUILD_SHARED>
)

target_include_directories(mdpaint_vips
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/mdpaint/vips
)

set_target_properties(mdpaint_vips PROPERTIES
    OUTPUT_NAME mdpaintvips
)

target_link_libraries(mdpaint_vips
    PUBLIC
        mdpaint::interface
    PRIVATE
        Vips::Vips
        mdpaint::private
        Boost::headers
        GLIB2::GOBJECT
)

add_library(mdpaint::vips ALIAS mdpaint_vips)
