# - Find TinyXML
# Find the native TinyXML includes and library
#
# TINYXML2_FOUND - True if TinyXML found.
# TINYXML2_INCLUDE_DIR - where to find tinyxml.h, etc.
# TINYXML2_LIBRARIES - List of libraries when using TinyXML.
#

IF( TINYXML2_INCLUDE_DIR )
# Already in cache, be silent
SET( TinyXML2_FIND_QUIETLY TRUE )
ENDIF( TINYXML2_INCLUDE_DIR )

FIND_PATH( TINYXML2_INCLUDE_DIR "tinyxml2.h"
HINTS "thirdparty/tinyxml2/"
PATH_SUFFIXES "tinyxml" "tinyxml2")

FIND_LIBRARY( TINYXML2_LIBRARIES
NAMES "tinyxml2"
PATH_SUFFIXES "tinyxml"
HINTS /usr/lib64 thirdparty/tinyxml2/lib)

# handle the QUIETLY and REQUIRED arguments and set TINYXML_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE( "FindPackageHandleStandardArgs" )
FIND_PACKAGE_HANDLE_STANDARD_ARGS( "TinyXML2" DEFAULT_MSG TINYXML2_INCLUDE_DIR TINYXML2_LIBRARIES )

MARK_AS_ADVANCED( TINYXML2_INCLUDE_DIR TINYXML2_LIBRARIES )
