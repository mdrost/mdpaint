find_package(PkgConfig QUIET)

if(PkgConfig_FOUND)
  pkg_check_modules(PC_MagickCore QUIET GraphicsMagick)
endif()

find_program(_GraphicsMagick_PROGRAM
  NAMES gm
  HINTS
	"[HKEY_LOCAL_MACHINE\\SOFTWARE\\GraphicsMagick\\Current;BinPath]"
  NO_DEFAULT_PATH
)
find_path(_GraphicsMagick_MagickCore_INCLUDE_DIR
  NAMES magick/api.h
  HINTS
    ${PC_MagickCore_INCLUDE_DIRS}
	"[HKEY_LOCAL_MACHINE\\SOFTWARE\\GraphicsMagick\\Current;BinPath]/include"
  NO_DEFAULT_PATH
)
find_library(_GraphicsMagick_MagickCore_LIBRARY
  NAMES
    GraphicsMagick
	CORE_RL_magick_
  HINTS
    ${PC_MagickCore_LIBRARY_DIRS}
	"[HKEY_LOCAL_MACHINE\\SOFTWARE\\GraphicsMagick\\Current;BinPath]/lib"
  NO_DEFAULT_PATH
)

if(_GraphicsMagick_PROGRAM)
  execute_process(COMMAND ${_GraphicsMagick_PROGRAM} -version
                  OUTPUT_VARIABLE _GraphicsMagick_VERSION
                  ERROR_QUIET
                  OUTPUT_STRIP_TRAILING_WHITESPACE)
  if(_GraphicsMagick_VERSION MATCHES "^GraphicsMagick ([-0-9\\.]+)")
    set(_GraphicsMagick_VERSION "${CMAKE_MATCH_1}")
  endif()
endif()

set(_GraphicsMagick_MagickCore_VERSION ${_GraphicsMagick_VERSION})

if(_GraphicsMagick_MagickCore_INCLUDE_DIR AND _GraphicsMagick_MagickCore_LIBRARY AND _GraphicsMagick_MagickCore_VERSION)
  set(_GraphicsMagick_MagickCore_FOUND TRUE)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GraphicsMagick
  REQUIRED_VARS
    _GraphicsMagick_MagickCore_FOUND
    _GraphicsMagick_MagickCore_INCLUDE_DIR
    _GraphicsMagick_MagickCore_LIBRARY
  VERSION_VAR _GraphicsMagick_MagickCore_VERSION
)

if(_GraphicsMagick_MagickCore_FOUND AND NOT TARGET GraphicsMagick::MagickCore)
  add_library(GraphicsMagick::MagickCore UNKNOWN IMPORTED)
  set_target_properties(GraphicsMagick::MagickCore PROPERTIES
    IMPORTED_LOCATION "${_GraphicsMagick_MagickCore_LIBRARY}"
    INTERFACE_COMPILE_OPTIONS "${PC_MagickCore_CFLAGS_OTHER}"
    INTERFACE_INCLUDE_DIRECTORIES "${_GraphicsMagick_MagickCore_INCLUDE_DIR}"
  )
endif()

unset(_GraphicsMagick_PROGRAM)
unset(_GraphicsMagick_MagickCore_FOUND)
unset(_GraphicsMagick_MagickCore_INCLUDE_DIR)
unset(_GraphicsMagick_MagickCore_LIBRARY)
unset(_GraphicsMagick_MagickCore_VERSION)

