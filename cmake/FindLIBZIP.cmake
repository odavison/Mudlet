# Locate LIBZIP library
# This module defines
#  LIBZIP_FOUND, if false, do not try to link to LIBZIP 
#  LIBZIP_LIBRARIES
#  LIBZIP_INCLUDE_DIR, where to find libzip/*.h 

find_package(ZLIB)

find_path(LIBZIP_INCLUDE_DIR_zch
	NAMES
	zipconf.h
	PATHS
	/lib/libzip/include
	)

FIND_PATH(LIBZIP_INCLUDE_DIR_zh zip.h
  HINTS
  ${LIBZIP_DIR} $ENV{LIBZIP_DIR}
  PATH_SUFFIXES include
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
  /opt
)

FIND_PATH(LIBZIP_INCLUDE_DIR_zch zipconf.h
  HINTS
  ${LIBZIP_DIR} $ENV{LIBZIP_DIR}
  PATH_SUFFIXES lib/libzip/include
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
  /opt
)

FIND_LIBRARY(LIBZIP_LIBRARY_RELEASE 
  NAMES zip libzip
  HINTS
  ${LIBZIP_DIR} $ENV{LIBZIP_DIR}
  PATH_SUFFIXES lib64 lib
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw
  /opt/local
  /opt/csw
  /opt
)

FIND_LIBRARY(LIBZIP_LIBRARY_DEBUG 
  NAMES zip zipd
  HINTS
  ${LIBZIP_DIR} $ENV{LIBZIP_DIR}
  PATH_SUFFIXES lib64 lib
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw
  /opt/local
  /opt/csw
  /opt
)

IF(LIBZIP_LIBRARY_DEBUG AND LIBZIP_LIBRARY_RELEASE)
  SET(LIBZIP_LIBRARY optimized ${LIBZIP_LIBRARY_RELEASE} debug ${LIBZIP_LIBRARY_DEBUG} )
ELSEIF(LIBZIP_LIBRARY_RELEASE)
  SET(LIBZIP_LIBRARY ${LIBZIP_LIBRARY_RELEASE} )
ELSEIF(LIBZIP_LIBRARY_DEBUG)
  SET(LIBZIP_LIBRARY ${LIBZIP_LIBRARY_DEBUG} )
ENDIF()

if (LIBZIP_INCLUDE_DIR_zh AND LIBZIP_INCLUDE_DIR_zch AND LIBZIP_LIBRARY)
	set(LIBZIP_INCLUDE_DIRS "${LIBZIP_INCLUDE_DIR_zh};${LIBZIP_INCLUDE_DIR_zch};${ZLIB_INCLUDE_DIRS}")
	set(LIBZIP_LIBRARIES ${LIBZIP_LIBRARY} ${ZLIB_LIBRARIES})
endif()

SET( LIBZIP_STATIC OFF CACHE BOOL "Use LIBZIP static libraries.")

IF(LIBZIP_STATIC)
  ADD_DEFINITIONS(-DLIBZIP_STATIC)
ENDIF(LIBZIP_STATIC)

SET( LIBZIP_LIBRARIES "${LIBZIP_LIBRARY}" CACHE STRING "LIBZIP Libraries")

INCLUDE(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBZIP_FOUND to TRUE if 
# all listed variables are TRUE
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LIBZIP  DEFAULT_MSG  LIBZIP_LIBRARIES LIBZIP_INCLUDE_DIRS)

MARK_AS_ADVANCED(LIBZIP_INCLUDE_DIR LIBZIP_LIBRARIES LIBZIP_LIBRARY LIBZIP_LIBRARY_RELEASE LIBZIP_LIBRARY_DEBUG)

