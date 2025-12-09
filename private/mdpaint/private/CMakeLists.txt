set(SOURCES
    boostsignals2signalconnectionprivate.h
    boostsignals2signalconnectionprivate.cpp
    signalconnectionprivate.h
    signalconnectionprivate.cpp
)

add_library(mdpaint_private
    ${SOURCES}
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

add_library(mdpaint::private ALIAS mdpaint_private)
