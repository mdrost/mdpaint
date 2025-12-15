find_package(PkgConfig QUIET)

if(PkgConfig_FOUND)
  pkg_check_modules(PC_Vips QUIET vips)
endif()

find_path(_Vips_INCLUDE_DIR
  NAMES vips/vips.h
  HINTS
    ${PC_Vips_INCLUDE_DIRS}
  NO_DEFAULT_PATH
)
find_library(_Vips_LIBRARY
  NAMES
    vips
  HINTS
    ${PC_Vips_LIBRARY_DIRS}
  NO_DEFAULT_PATH
)

set(_Vips_VERSION 8.16.1)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Vips
  REQUIRED_VARS
    _Vips_INCLUDE_DIR
    _Vips_LIBRARY
  VERSION_VAR _Vips_VERSION
)

if(Vips_FOUND AND NOT TARGET Vips::Vips)
  add_library(Vips::Vips UNKNOWN IMPORTED)
  set_target_properties(Vips::Vips PROPERTIES
    IMPORTED_LOCATION "${_Vips_LIBRARY}"
    INTERFACE_COMPILE_OPTIONS "${PC_Vips_CFLAGS_OTHER}"
    INTERFACE_INCLUDE_DIRECTORIES "${_Vips_INCLUDE_DIR}"
  )
endif()

unset(_Vips_INCLUDE_DIR)
unset(_Vips_LIBRARY)
unset(_Vips_VERSION)

