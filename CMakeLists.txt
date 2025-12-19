cmake_minimum_required(VERSION 3.24)

project(mdpaint VERSION 0.1 LANGUAGES CXX)

find_package(ECM NO_MODULE)
list(APPEND CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)

if(POLICY CMP0167)
    if(WIN32)
        cmake_policy(SET CMP0167 OLD)
    else()
        cmake_policy(SET CMP0167 NEW)
    endif()
endif()

if(WIN32)
    set(Boost_USE_STATIC_LIBS ON)
endif()
find_package(Boost REQUIRED COMPONENTS json)

add_subdirectory(private)

add_subdirectory(interface)

set(SOURCES
    main.cpp
)

add_executable(mdpaint
    ${SOURCES}
)

target_compile_definitions(mdpaint
    PRIVATE
        $<$<BOOL:${WIN32}>:UNICODE>
        $<$<BOOL:${WIN32}>:_UNICODE>
)

target_link_libraries(mdpaint
    PRIVATE
        mdpaint::interface
        Boost::headers
        Boost::json
)

if(MDPAINT_WITH_QT)
    add_subdirectory(frontends/qt)
    add_dependencies(mdpaint mdpaint::qt)
endif()

if(MDPAINT_WITH_CAIRO)
    add_subdirectory(backends/cairo)
    add_dependencies(mdpaint mdpaint::cairo)
endif()

if(MDPAINT_WITH_VIPS)
    add_subdirectory(backends/vips)
    add_dependencies(mdpaint mdpaint::vips)
endif()

set_target_properties(mdpaint PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_GUI_IDENTIFIER com.mdrost.mdpaint
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

include(GNUInstallDirs)
install(TARGETS mdpaint
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
