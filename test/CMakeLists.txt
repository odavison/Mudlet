CMAKE_MINIMUM_REQUIRED(VERSION 2.8.2)

INCLUDE(CTest)

####################
# Setup google test
####################
IF(CMAKE_VERSION VERSION_LESS 3.2)
    SET(UPDATE_DISCONNECTED_IF_AVAILABLE "")
ELSE()
    SET(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")
ENDIF()

INCLUDE(DownloadProject)
DOWNLOAD_PROJECT(PROJ                googletest
                 GIT_REPOSITORY      https://github.com/google/googletest.git
                 GIT_TAG             master
                 ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
SET(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

ADD_SUBDIRECTORY(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

# When using CMake 2.8.11 or later, header path dependencies
# are automatically added to the gtest and gmock targets.
# For earlier CMake versions, we have to explicitly add the
# required directories to the header search path ourselves.
IF (CMAKE_VERSION VERSION_LESS 2.8.11)
    INCLUDE_DIRECTORIES("${gtest_SOURCE_DIR}/include"
                        "${gmock_SOURCE_DIR}/include")
ENDIF()

INCLUDE(add_mudlet_test) # CMake module to simplify adding tests

# Add googletest tests
ADD_GTEST_TEST(TArea_test TArea_test.cpp)

# Add Qt5Test tests
SET(CMAKE_AUTOMOC ON)
FIND_PACKAGE(Qt5Test REQUIRED)

ADD_QT5_TEST(example_qttest example_qttest.cpp)
