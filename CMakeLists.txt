############################################################################
#    Copyright (C) 2014 by Ahmed Charles - acharles@outlook.com            #
#    Copyright (C) 2015 by Stephen Lyons - slysven@virginmedia.com         #
#                                                                          #
#    This program is free software; you can redistribute it and/or modify  #
#    it under the terms of the GNU General Public License as published by  #
#    the Free Software Foundation; either version 2 of the License, or     #
#    (at your option) any later version.                                   #
#                                                                          #
#    This program is distributed in the hope that it will be useful,       #
#    but WITHOUT ANY WARRANTY; without even the implied warranty of        #
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
#    GNU General Public License for more details.                          #
#                                                                          #
#    You should have received a copy of the GNU General Public License     #
#    along with this program; if not, write to the                         #
#    Free Software Foundation, Inc.,                                       #
#    59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             #
############################################################################

PROJECT(mudlet)

# FIXME: We need a check (for Qt 5.2 or greater) it is needed (at least) because
# of: using QComboBox::currentData() introduced in 5.2, in dlgProfilePreferences
# class

# Windows builds need 2.8.11, but for other platforms 2.8.9 should be enough
IF(MSVC)
  CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)
ELSE()
  CMAKE_MINIMUM_REQUIRED(VERSION 2.8.9)
ENDIF()

IF(CMAKE_CONFIGURATION_TYPES)
  ADD_CUSTOM_TARGET(check COMMAND ${CMAKE_CTEST_COMMAND}
                    --force-new-ctest-process --output-on-failure
                    --build-config "$<CONFIGURATION>")
ELSE()
  ADD_CUSTOM_TARGET(check COMMAND ${CMAKE_CTEST_COMMAND}
                    --force-new-ctest-process --output-on-failure)
ENDIF()

ENABLE_TESTING()

IF(POLICY CMP0020)
  CMAKE_POLICY(SET CMP0020 NEW)
ENDIF()

IF(WIN32)
    SET(APP_TARGET mudlet.exe)
ELSEIF(APPLE)
    SET(APP_TARGET Mudlet)
ELSE()
    SET(APP_TARGET mudlet)
ENDIF()

SET(APP_VERSION 3.0.1)
SET(APP_BUILD "-dev")
# APP_BUILD should only be empty/null in official "release" builds,
# developers may like to set it to their user and branch names to make it easier
# to tell different builds apart!
#
# Changing the above pair of values affects: ctelnet.cpp, main.cpp, mudlet.cpp
# dlgAboutDialog.cpp and TLuaInterpreter.cpp.  It will not necessarily cause
# those files to be automatically rebuilt so you may need to 'touch' those files if
# the variables are changed and you are not doing a full, clean, rebuild!
# Use APP_VERSION, APP_BUILD and APP_TARGET defines in the source code if needed.
# IMPORTANT:
# To insure consistency please ensure the SAME of the first two values are also
# assigned to the "VERSION" and "BUILD" variables in the native qmake project file,
# i.e. ./src/src.pro

#######################################
# Previously from src/CmakeLists.txt
#######################################
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

IF(MSVC)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -MP") # parallel builds
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Zc:inline") # improve link times
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Zc:rvalueCast") # improve conformance
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -wd4305") # '=' : truncation from 'double' to 'float'
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -wd4309") # 'initializing' : truncation of constant value
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -wd4996") # deprecation
ELSE()
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
  IF(APPLE)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
  ENDIF()
ENDIF()

SET(PCRE_DIR "${PROJECT_SOURCE_DIR}" CACHE PATH "PCRE install directory.")

SET(YAJL_DIR "${PROJECT_SOURCE_DIR}" CACHE PATH "YAJL install directory.")

SET(HUNSPELL_DIR "${PROJECT_SOURCE_DIR}" CACHE PATH "HUNSPELL install directory.")

SET(ZIP_DIR "${PROJECT_SOURCE_DIR}" CACHE PATH "ZIP install directory.")

IF(EXISTS "${PROJECT_SOURCE_DIR}/include/lua.h")
  SET(LUA_INCLUDE_DIR_TEMP "${PROJECT_SOURCE_DIR}/include")
  GET_FILENAME_COMPONENT(LUA_INCLUDE_DIR ${LUA_INCLUDE_DIR_TEMP} ABSOLUTE CACHE)
  IF(EXISTS "${PROJECT_SOURCE_DIR}/lib/lualib.lib")
    SET(LUA_LIBRARY_RELEASE_TEMP "${PROJECT_SOURCE_DIR}/lib/lualib.lib")
    GET_FILENAME_COMPONENT(LUA_LIBRARY_RELEASE ${LUA_LIBRARY_RELEASE_TEMP} ABSOLUTE CACHE)
  ENDIF()
  IF(EXISTS "${PROJECT_SOURCE_DIR}/lib/lualibd.lib")
    SET(LUA_LIBRARY_DEBUG_TEMP "${PROJECT_SOURCE_DIR}/lib/lualibd.lib")
    GET_FILENAME_COMPONENT(LUA_LIBRARY_DEBUG ${LUA_LIBRARY_DEBUG_TEMP} ABSOLUTE CACHE)
  ENDIF()
  IF(LUA_LIBRARY_DEBUG AND LUA_LIBRARY_RELEASE)
    SET(LUA_LIBRARY optimized ${LUA_LIBRARY_RELEASE} debug ${LUA_LIBRARY_DEBUG} )
  ELSEIF(LUA_LIBRARY_RELEASE)
    SET(LUA_LIBRARY ${LUA_LIBRARY_RELEASE} )
  ELSEIF(LUA_LIBRARY_DEBUG)
    SET(LUA_LIBRARY ${LUA_LIBRARY_DEBUG} )
  ENDIF()
ENDIF()

IF(WIN32)
  IF(EXISTS "${PROJECT_SOURCE_DIR}/include/zlib.h")
    SET(ZLIB_INCLUDE_DIR_TEMP "${PROJECT_SOURCE_DIR}/include")
    GET_FILENAME_COMPONENT(ZLIB_INCLUDE_DIR ${ZLIB_INCLUDE_DIR_TEMP} ABSOLUTE CACHE)
    SET(ZLIB_ROOT "${PROJECT_SOURCE_DIR}")
    IF(EXISTS "${PROJECT_SOURCE_DIR}/lib/zlibstat.lib")
      SET(ZLIB_LIBRARY_RELEASE_TEMP "${PROJECT_SOURCE_DIR}/lib/zlibstat.lib")
      GET_FILENAME_COMPONENT(ZLIB_LIBRARY_RELEASE ${ZLIB_LIBRARY_RELEASE_TEMP} ABSOLUTE CACHE)
    ENDIF()
    IF(EXISTS "${PROJECT_SOURCE_DIR}/lib/zlibstatd.lib")
      SET(ZLIB_LIBRARY_DEBUG_TEMP "${PROJECT_SOURCE_DIR}/lib/zlibstatd.lib")
      GET_FILENAME_COMPONENT(ZLIB_LIBRARY_DEBUG ${ZLIB_LIBRARY_DEBUG_TEMP} ABSOLUTE CACHE)
    ENDIF()
    IF(ZLIB_LIBRARY_DEBUG AND ZLIB_LIBRARY_RELEASE)
      SET(ZLIB_LIBRARY optimized ${ZLIB_LIBRARY_RELEASE} debug ${ZLIB_LIBRARY_DEBUG} )
    ELSEIF(ZLIB_LIBRARY_RELEASE)
      SET(ZLIB_LIBRARY ${ZLIB_LIBRARY_RELEASE} )
    ELSEIF(ZLIB_LIBRARY_DEBUG)
      SET(ZLIB_LIBRARY ${ZLIB_LIBRARY_DEBUG} )
    ENDIF()
  ENDIF()
ENDIF()

# Break each step into a separate command so any status message is output straigh away
IF(APPLE)
  # The include directory setup for Zip is unusual in that as well as e.g. /usr/include/zip.h
  # we need the path to an interal header zipconf.g that it calls for using '<''>'s
  # i.e. SYSTEM #include delimiters which are typically located at e.g. /usr/lib/libzip/include/zipconf.h
  # and using pkg-config is the recommended way to get the details.
  # Spotted recommendation to use pkg-config here https://github.com/Homebrew/homebrew/issues/13390
  FIND_PACKAGE(PkgConfig)
  IF(NOT(PKG_CONFIG_FOUND))
    MESSAGE(WARNING "Unable to use pkg_config - will possibly fail to find/use Zip library...")
  ENDIF()
ENDIF()

IF((APPLE) AND (PKG_CONFIG_FOUND))
  PKG_SEARCH_MODULE(PC_ZIP zip libzip)
  # Use a PC_ prefix to distinguish between what pkg-config finds and a direct use of FIND_PACKAGE(ZIP)
  # Package "zip" is called "libzip" at least on MY Linux box so look for BOTH
  IF(PC_ZIP_FOUND)
    IF(PC_ZIP_zip_FOUND)
      MESSAGE(STATUS "Using pkg_config, found \"zip\" version: ${PC_ZIP_zip_VERSION} with:")
    ELSEIF(PC_ZIP_libzip_FOUND)
      MESSAGE(STATUS "Using pkg_config, found \"libzip\" version: ${PC_ZIP_libzip_VERSION} with:")
    ELSE()
      MESSAGE(STATUS "Using pkg_config, found Zip version: ${PC_ZIP_VERSION} with:")
    ENDIF()
    MESSAGE(STATUS "  include directory(ies), ZIP_INCLUDE_DIRS: ${PC_ZIP_INCLUDE_DIRS} .")
    MESSAGE(STATUS "  library(ies): ZIP_LIBRARY_DIRS: ${PC_ZIP_LIBRARY_DIRS}; ZIP_LIBDIR: ${PC_ZIP_LIBDIR}. ")
  ELSE()
    MESSAGE(WARNING "Using pkg_config, failed to find any version of Zip library!")
  ENDIF()
ENDIF()

IF((APPLE) AND (PKG_CONFIG_FOUND))
  # Examining Homebrew (for MacOs) for libzzip:
  # https://bintray.com/homebrew/bottles/libzzip found that they use pkg-config
  # So use that to try and find what we want
  PKG_SEARCH_MODULE(PC_ZZIPLIB zziplib libzzip zzip)
  IF(PC_ZZIPLIB_FOUND)
    IF(PC_ZZIPLIB_zziplib_FOUND)
      MESSAGE(STATUS "Using pkg_config, found \"zziplib\" version: ${PC_ZZIPLIB_zziplib_VERSION} with:")
    ELSEIF(PC_ZZIPLIB_libzzip_FOUND)
      MESSAGE(STATUS "Using pkg_config, found \"libzzip\" version: ${PC_ZZIPLIB_libzzip_VERSION} with:")
    ELSEIF(PC_ZZIPLIB_zzip_FOUND)
      MESSAGE(STATUS "Using pkg_config, found \"zzip\" version: ${PC_ZZIPLIB_zzip_VERSION} with:")
    ELSE()
      MESSAGE(STATUS "Using pkg_config, found Zzip version: ${PC_ZZIPLIB_VERSION} with:")
    ENDIF()
    MESSAGE(STATUS "  include directory(ies), ZZIPLIB_INCLUDE_DIRS: ${PC_ZZIPLIB_INCLUDE_DIRS} .")
    MESSAGE(STATUS "  library(ies): ZZIPLIB_LIBRARY_DIRS: ${PC_ZZIPLIB_LIBRARY_DIRS}; ZZIPLIB_LIBDIR: ${PC_ZZIPLIB_LIBDIR}. ")
  ELSEIF()
    MESSAGE(WARNING "Using pkg_config, failed to find any version of Zziplib library!")
  ENDIF()
ENDIF()

FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Multimedia REQUIRED)
FIND_PACKAGE(Qt5Network REQUIRED)
FIND_PACKAGE(Qt5OpenGL REQUIRED)
FIND_PACKAGE(Qt5UiTools REQUIRED)
FIND_PACKAGE(Qt5Widgets REQUIRED)

IF(NOT(PC_ZIP_FOUND))
  FIND_PACKAGE(ZIP REQUIRED)
ENDIF()
FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(Lua51 REQUIRED)
# Needed (just) on MacOs as an #include in luazip.h:
IF(APPLE)
  IF(NOT(PC_ZZIPLIB_FOUND))
    FIND_PACKAGE(ZZIPLIB)
  ENDIF()
  IF(NOT((ZZIPLIB_FOUND) OR (PC_ZZIPLIB_FOUND) OR (PC_ZZIPLIB_zziplib_FOUND) OR (PC_ZZIPLIB_libzzip_FOUND) OR (PC_ZZIPLIB_zzip_FOUND)))
    MESSAGE(WARNING "Failed to find any trace of zziplib (or zzip or libzzip)\n- so will not be able to build the (internal version for Mac builds) of the lua zip module that Mudlet needs.")
  ENDIF()
ENDIF()
FIND_PACKAGE(ZLIB REQUIRED)
FIND_PACKAGE(PCRE REQUIRED)
FIND_PACKAGE(YAJL REQUIRED)
FIND_PACKAGE(HUNSPELL REQUIRED)

SET(Boost_USE_STATIC_LIBS ON)
FIND_PACKAGE(Boost 1.44 COMPONENTS graph)

ADD_DEFINITIONS(-DAPP_VERSION="${APP_VERSION}" -DAPP_BUILD="${APP_BUILD}" -DAPP_TARGET="${APP_TARGET}")

IF(UNIX)
    SET(DATAROOTDIR "${CMAKE_INSTALL_PREFIX}/share" CACHE STRING "The platform-specific directory in which read-only data is generally installed")
    SET(DATADIR "${DATAROOTDIR}/mudlet" CACHE STRING "Directory in which mudlet installs its read-only data")
    SET(LUA_DEFAULT_DIR "${DATADIR}/lua" CACHE STRING "Directory in which mudlet installs its read-only lua scripts")
ENDIF(UNIX)

# Define a preprocessor symbol with the default fallback location from which
# to load installed mudlet lua files. Set LUA_DEFAULT_DIR to a
# platform-specific value. If LUA_DEFAULT_DIR is unset, the root directory
# will be used.
ADD_DEFINITIONS(-DLUA_DEFAULT_PATH="${LUA_DEFAULT_DIR}")

# Enable leak detection for MSVC debug builds.
if(MSVC)
  SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -FItestdbg.h")
endif()

SET(CMAKE_INCLUDE_CURRENT_DIR ON)
INCLUDE_DIRECTORIES(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Network_INCLUDE_DIRS}
    ${Qt5OpenGL_INCLUDE_DIRS}
    ${Qt5Multimedia_INCLUDE_DIRS}
    ${Qt5UiTools_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/irc/include
    ${HUNSPELL_INCLUDE_DIR}
    ${LUA_INCLUDE_DIR}
    ${PCRE_INCLUDE_DIR}
    ${YAJL_INCLUDE_DIR}
)

# Need to use the plural variables as there can be more than ONE directory to specify:
IF(PC_ZIP_FOUND)
    INCLUDE_DIRECTORIES( ${PC_ZIP_INCLUDE_DIRS} )
ELSE()
    INCLUDE_DIRECTORIES( ${ZIP_INCLUDE_DIRS} )
ENDIF()

IF(APPLE)
  IF(PC_ZZIPLIB_FOUND)
    INCLUDE_DIRECTORIES( ${PC_ZZIPLIB_INCLUDE_DIRS} )
  ELSE()
    INCLUDE_DIRECTORIES( ${ZZIPLIB_INCLUDE_DIRS} )
  ENDIF()
ENDIF()

INCLUDE_DIRECTORIES( ${ZLIB_INCLUDE_DIR} )

ADD_SUBDIRECTORY(src)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/src)
ADD_SUBDIRECTORY(test)
