# - Find ClanLib
# ClanLib is a cross platform SDK geared toward making games. It is
# available from http://clanlib.org.
#
# Please define the following before starting this module
#  ClanLib_MAJOR_VERSION (default 3)
#  ClanLib_MINOR_VERSION (default 0)
#
# The following are defined by this module:
#  ClanLib_FOUND - TRUE if ClanLib was found
#  ClanLib_INCLUDE_DIRS - Directory containing the ClanLib headers
#  ClanLib_LIBRARIES - If invoked via FIND_PACKAGE(ClanLib COMPONENTS ...),
#                      will only contain the libraries matching each component.
#                      otherwise, it will contain all ClanLib libraries found.

if(NOT ClanLib_MAJOR_VERSION)
  set(ClanLib_MAJOR_VERSION 3)
endif()
if(NOT ClanLib_MINOR_VERSION)
  set(ClanLib_MINOR_VERSION 0)
endif()

if(ClanLib_INCLUDE_DIRS)
  set(ClanLib_FIND_QUIETLY TRUE)
endif(ClanLib_INCLUDE_DIRS)

if(NOT ClanLib_FIND_COMPONENTS)
  set(ClanLib_FIND_COMPONENTS
    App
    Display
    GL
    GUI
    GUIStyleSilver
    MikMod
    Network
    SDL
    Signals
    Sound
    Vorbis)
endif(NOT ClanLib_FIND_COMPONENTS)

macro(ClanLib_MSG MSG)
  if(NOT ClanLib_FIND_QUIETLY)
    message(STATUS "${MSG}")
  endif()
endmacro(ClanLib_MSG)

# Search paths candidate list
set(_CLANLIB_SEARCH_PATHS
  ${CLANLIB_ROOT_DIR}
  ${ClanLib_ROOT_DIR}
  ${ClanLib_DIR}
  ${CMAKE_SOURCE_DIR}/dependencies/clanlib
  ${CMAKE_SOURCE_DIR}/dependencies/clanlib/install
  ${CMAKE_SOURCE_DIR}/../dependencies/clanlib
  ${CMAKE_SOURCE_DIR}/../dependencies/clanlib/install
  /usr/local
  /usr
)

macro(ClanLib_FIND_COMPONENT COMPONENT)
  ClanLib_MSG("Checking for Clan${COMPONENT}")
  find_library(ClanLib_${COMPONENT}_LIBRARY
    NAMES
      clan${ClanLib_MAJOR_VERSION}${ClanLib_MINOR_VERSION}${COMPONENT}
      clan${COMPONENT}
      clan${COMPONENT}-static-mt
      clan${COMPONENT}-static-mt-debug
      clan${COMPONENT}-dll
      clan${COMPONENT}-dll-debug
      clan${COMPONENT}d
    PATHS
      ${_CLANLIB_SEARCH_PATHS}
    PATH_SUFFIXES
      lib
      lib/Win32
      lib/x64
      Release
      Debug
      x64/Release
      x64/Debug
      Win32/Release
      Win32/Debug
      install/lib
      build/lib
    DOC "Library name for clan${COMPONENT}."
  )
  if(ClanLib_${COMPONENT}_LIBRARY)
    set(ClanLib_${COMPONENT}_FOUND TRUE)
    ClanLib_MSG("Checking for Clan${COMPONENT} -- ${ClanLib_${COMPONENT}_LIBRARY}")
  else()
    set(ClanLib_${COMPONENT}_FOUND FALSE)
    if(ClanLib_FIND_REQUIRED_${COMPONENT})
      ClanLib_MSG("Checking for Clan${COMPONENT} -- not found (required)")
    else()
      ClanLib_MSG("Checking for Clan${COMPONENT} -- not found")
    endif()
  endif()
endmacro(ClanLib_FIND_COMPONENT)

ClanLib_MSG("Checking for ClanLib")
find_path(ClanLib_INCLUDE_DIRS ClanLib/core.h
  PATHS
    ${_CLANLIB_SEARCH_PATHS}
  PATH_SUFFIXES
    include
    include/ClanLib-${ClanLib_MAJOR_VERSION}.${ClanLib_MINOR_VERSION}
    Sources/API
    Sources
    install/include
  DOC "Where to find the ClanLib includes."
)

if(ClanLib_INCLUDE_DIRS)
  ClanLib_MSG("Checking for ClanLib -- headers found at ${ClanLib_INCLUDE_DIRS}")
else()
  ClanLib_MSG("Checking for ClanLib -- headers not found")
endif()

ClanLib_FIND_COMPONENT(Core)
if(ClanLib_INCLUDE_DIRS AND ClanLib_Core_LIBRARY)
  set(ClanLib_FOUND TRUE)
  set(ClanLib_LIBRARIES ${ClanLib_Core_LIBRARY})
else()
  set(ClanLib_FOUND FALSE)
endif()

ClanLib_MSG("Checking for other ClanLib components")
foreach(COMPONENT ${ClanLib_FIND_COMPONENTS})
  ClanLib_FIND_COMPONENT(${COMPONENT})
  if(ClanLib_${COMPONENT}_LIBRARY)
    list(APPEND ClanLib_LIBRARIES ${ClanLib_${COMPONENT}_LIBRARY})
  endif()
endforeach(COMPONENT)

if(NOT ClanLib_FOUND AND ClanLib_FIND_REQUIRED)
  message(FATAL_ERROR
    "\n"
    "========================================================================\n"
    "ClanLib ${ClanLib_MAJOR_VERSION}.${ClanLib_MINOR_VERSION} was not found!\n\n"
    "AdaptiveShooter requires ClanLib ${ClanLib_MAJOR_VERSION}.${ClanLib_MINOR_VERSION}.\n"
    "Search attempted in:\n"
    "  - CLANLIB_ROOT_DIR / ClanLib_DIR: ${CLANLIB_ROOT_DIR}\n"
    "  - Submodule: ${CMAKE_SOURCE_DIR}/dependencies/clanlib\n"
    "  - System locations (/usr/local, /usr)\n\n"
    "If using git submodules, make sure it is initialized:\n"
    "    git submodule update --init --recursive\n\n"
    "And build ClanLib as documented in BUILDING.md.\n"
    "You can also specify the ClanLib location with:\n"
    "    cmake -B build -DCLANLIB_ROOT_DIR=<path-to-clanlib>\n"
    "========================================================================"
  )
endif()

mark_as_advanced(
  ClanLib_INCLUDE_DIRS
  ClanLib_App_LIBRARY
  ClanLib_Core_LIBRARY
  ClanLib_Display_LIBRARY
  ClanLib_GL_LIBRARY
  ClanLib_GUI_LIBRARY
  ClanLib_GUIStyleSilver_LIBRARY
  ClanLib_MikMod_LIBRARY
  ClanLib_Network_LIBRARY
  ClanLib_SDL_LIBRARY
  ClanLib_Signals_LIBRARY
  ClanLib_Sound_LIBRARY
  ClanLib_Vorbis_LIBRARY
)
