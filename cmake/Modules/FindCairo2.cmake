find_package(PkgConfig QUIET)

if(PkgConfig_FOUND)
  pkg_check_modules(PC_Cairo2 QUIET cairo)
endif()

find_path(_Cairo2_INCLUDE_DIR
  NAMES cairo/cairo.h
  HINTS
    ${PC_Cairo2_INCLUDE_DIRS}
    ${CAIRO2_ROOT}/include
  NO_DEFAULT_PATH
)
find_library(_Cairo2_LIBRARY
  NAMES
    cairo
  HINTS
    ${PC_Cairo2_LIBRARY_DIRS}
    ${CAIRO2_ROOT}/lib
  NO_DEFAULT_PATH
)

set(_Cairo2_VERSION 1.18.4)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Cairo2
  REQUIRED_VARS
    _Cairo2_INCLUDE_DIR
    _Cairo2_LIBRARY
  VERSION_VAR _Cairo2_VERSION
)

if(Cairo2_FOUND AND NOT TARGET Cairo2::Cairo2)
  add_library(Cairo2::Cairo2 UNKNOWN IMPORTED)
  set_target_properties(Cairo2::Cairo2 PROPERTIES
    IMPORTED_LOCATION "${_Cairo2_LIBRARY}"
    INTERFACE_COMPILE_OPTIONS "${PC_Cairo2_CFLAGS_OTHER}"
    INTERFACE_INCLUDE_DIRECTORIES "${_Cairo2_INCLUDE_DIR}"
  )
endif()

unset(_Cairo2_INCLUDE_DIR)
unset(_Cairo2_LIBRARY)
unset(_Cairo2_VERSION)
