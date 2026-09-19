# FindXrender.cmake - Locate the X Render Extension client library.
#
# The ClanLib `cmake` branch calls find_package(Xrender REQUIRED), but neither
# CMake nor libxrender-dev ships a finder for it, so Linux configure fails.
# This module fills the gap (found via CMAKE_MODULE_PATH, which already
# includes <repo>/cmake). Requires pkg-config plus libxrender-dev.
#
# Defines:
#   Xrender_FOUND
#   Xrender_INCLUDE_DIRS
#   Xrender_LIBRARIES
#   Xrender::Xrender (imported target)

find_package( PkgConfig QUIET )
if( PKG_CONFIG_FOUND )
    pkg_check_modules( PC_XRENDER QUIET xrender )
endif()

find_path( Xrender_INCLUDE_DIRS
    NAMES X11/extensions/Xrender.h
    HINTS ${PC_XRENDER_INCLUDE_DIRS}
)
find_library( Xrender_LIBRARIES
    NAMES Xrender
    HINTS ${PC_XRENDER_LIBRARY_DIRS}
)

include( FindPackageHandleStandardArgs )
find_package_handle_standard_args( Xrender
    REQUIRED_VARS Xrender_LIBRARIES Xrender_INCLUDE_DIRS
)

if( Xrender_FOUND AND NOT TARGET Xrender::Xrender )
    add_library( Xrender::Xrender UNKNOWN IMPORTED )
    set_target_properties( Xrender::Xrender PROPERTIES
        IMPORTED_LOCATION "${Xrender_LIBRARIES}"
        INTERFACE_INCLUDE_DIRECTORIES "${Xrender_INCLUDE_DIRS}"
    )
endif()

mark_as_advanced( Xrender_INCLUDE_DIRS Xrender_LIBRARIES )
