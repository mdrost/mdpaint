find_package(PkgConfig QUIET)

if(PkgConfig_FOUND)
  pkg_check_modules(PC_Cairo QUIET cairo)
endif()

find_path(_Cairo_INCLUDE_DIR
  NAMES cairo/cairo.h
  HINTS
    ${PC_Cairo_INCLUDE_DIRS}
    ${CAIRO_ROOT}/include
  NO_DEFAULT_PATH
)
find_library(_Cairo_LIBRARY
  NAMES
    cairo
  HINTS
    ${PC_Cairo_LIBRARY_DIRS}
    ${CAIRO_ROOT}/lib
  NO_DEFAULT_PATH
)

set(_Cairo_VERSION 1.18.4)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Cairo
  REQUIRED_VARS
    _Cairo_INCLUDE_DIR
    _Cairo_LIBRARY
  VERSION_VAR _Cairo_VERSION
)

if(Cairo_FOUND AND NOT TARGET Cairo::Cairo)
  add_library(Cairo::Cairo UNKNOWN IMPORTED)
  set_target_properties(Cairo::Cairo PROPERTIES
    IMPORTED_LOCATION "${_Cairo_LIBRARY}"
    INTERFACE_COMPILE_OPTIONS "${PC_Cairo_CFLAGS_OTHER}"
    INTERFACE_INCLUDE_DIRECTORIES "${_Cairo_INCLUDE_DIR}"
  )
endif()

unset(_Cairo_INCLUDE_DIR)
unset(_Cairo_LIBRARY)
unset(_Cairo_VERSION)

