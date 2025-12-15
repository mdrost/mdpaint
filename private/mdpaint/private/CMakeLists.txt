find_package(Boost REQUIRED)

set(SOURCES
    api.h
    boostsignals2signalconnectionprivate.h
    boostsignals2signalconnectionprivate.cpp
    signalconnectionprivate.h
    signalconnectionprivate.cpp
)

add_library(mdpaint_private STATIC
    ${SOURCES}
)

target_compile_definitions(mdpaint_interface
    PUBLIC
    PRIVATE
        MDP_PRIVATE_EXPORTS
)

target_compile_definitions(mdpaint_private
    PUBLIC
    PRIVATE
)

target_include_directories(mdpaint_private
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../..
    PRIVATE
)

target_link_libraries(mdpaint_private
    PUBLIC
        Boost::headers
    PRIVATE
)

set_target_properties(mdpaint_private PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    OUTPUT_NAME mdpaintprivate
)

add_library(mdpaint::private ALIAS mdpaint_private)
