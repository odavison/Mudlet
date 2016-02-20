cmake_minimum_required(VERSION 2.8.2)

include(CTest)

##############
# GTest
##############
if (CMAKE_VERSION VERSION_LESS 3.2)
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "")
else()
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
message(${CMAKE_MODULE_PATH})

include(DownloadProject)
download_project(PROJ                googletest
                 GIT_REPOSITORY      https://github.com/google/googletest.git
                 GIT_TAG             master
                 ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

# When using CMake 2.8.11 or later, header path dependencies
# are automatically added to the gtest and gmock targets.
# For earlier CMake versions, we have to explicitly add the
# required directories to the header search path ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
                        "${gmock_SOURCE_DIR}/include")
endif()

# Trivial example using gtest and gmock
add_executable(example_gtest example_gtest.cpp)
target_link_libraries(example_gtest gtest gmock_main)
add_test(NAME example_gtest COMMAND example_gtest)

add_executable(TArea_test TArea_test.cpp)
target_link_libraries(TArea_test
  gtest
  gmock_main
  mudletLib
  ${Qt5Core_LIBRARIES}
  ${Qt5Widgets_LIBRARIES}
  ${Qt5Network_LIBRARIES}
  ${Qt5Multimedia_LIBRARIES}
  ${Qt5OpenGL_LIBRARIES}
  ${Qt5UiTools_LIBRARIES}
  ${Boost_LIBRARIES}
  ${HUNSPELL_LIBRARIES}
  ${LUA_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${PCRE_LIBRARIES}
  ${YAJL_LIBRARIES}
  ${ZLIB_LIBRARIES}
  irccqt
)

add_test(NAME TArea_test COMMAND TArea_test)

############
# Qt5Test
############
# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)

find_package(Qt5Test REQUIRED)

add_executable(example_qttest example_qttest.cpp)
add_test(example_qttest example_qttest)

target_link_libraries(example_qttest Qt5::Test)
