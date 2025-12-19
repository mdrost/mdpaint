if(POLICY CMP0167)
    if(WIN32)
        cmake_policy(SET CMP0167 OLD)
    else()
        cmake_policy(SET CMP0167 NEW)
    endif()
endif()

find_package(Boost REQUIRED)

set(SOURCES
    include/mdpaint/private/privateapi.h
    include/mdpaint/private/privateboostsignals2signalconnection.h
    privateboostsignals2signalconnection.cpp
    include/mdpaint/private/privatesignalconnection.h
    privatesignalconnection.cpp
)

add_library(mdpaint_private STATIC
    ${SOURCES}
)

target_compile_definitions(mdpaint_private
    INTERFACE
    PUBLIC
    PRIVATE
        MDP_PRIVATE_EXPORTS
        $<$<STREQUAL:$<TARGET_PROPERTY:mdpaint_private,TYPE>,SHARED_LIBRARY>:MDP_PRIVATE_BUILD_SHARED>
)

target_compile_definitions(mdpaint_private
    INTERFACE
    PUBLIC
    PRIVATE
)

target_include_directories(mdpaint_private
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
	PUBLIC
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/mdpaint/private
)

target_link_libraries(mdpaint_private
    INTERFACE
    PUBLIC
        Boost::headers
    PRIVATE
)

set_target_properties(mdpaint_private PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    OUTPUT_NAME mdpaintprivate
)

add_library(mdpaint::private ALIAS mdpaint_private)
