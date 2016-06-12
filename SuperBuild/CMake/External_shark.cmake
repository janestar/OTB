if(NOT __EXTERNAL_SHARK__)
set(__EXTERNAL_SHARK__ 1)

if(USE_SYSTEM_SHARK)
  message(STATUS "  Using SHARK system version")
else()
  SETUP_SUPERBUILD(PROJECT SHARK)
  cmake_minimum_required(VERSION 3.1)
  message(STATUS "  Using SHARK SuperBuild version")

  # declare dependencies
  ADDTO_DEPENDENCIES_IF_NOT_SYSTEM(SHARK BOOST)

  ADD_SUPERBUILD_CMAKE_VAR(SHARK Boost_INCLUDE_DIR)
  ADD_SUPERBUILD_CMAKE_VAR(SHARK Boost_LIBRARY_DIR)

  ExternalProject_Add(SHARK
    PREFIX SHARK
    GIT_REPOSITORY "https://github.com/inglada/Shark.git"
    GIT_TAG "master"
    SOURCE_DIR ${SHARK_SB_SRC}
    BINARY_DIR ${SHARK_SB_BUILD_DIR}
    INSTALL_DIR ${SB_INSTALL_PREFIX}
    DOWNLOAD_DIR ${DOWNLOAD_LOCATION}
    CMAKE_CACHE_ARGS
      -DCMAKE_INSTALL_PREFIX:STRING=${SB_INSTALL_PREFIX}
      -DCMAKE_PREFIX_PATH:STRING=${SB_INSTALL_PREFIX};${CMAKE_PREFIX_PATH}
      -DCMAKE_BUILD_TYPE:STRING=Release
      -DBUILD_SHARED_LIBS:BOOL=ON
      -DBUILD_DOCS:BOOL=OFF
      -DBUILD_EXAMPLES:BOOL=OFF
      -DBUILD_TESTING:BOOL=OFF
      -DENABLE_HDF5:BOOL=OFF
      CMAKE_COMMAND ${SB_CMAKE_COMMAND}
    )
  SUPERBUILD_PATCH_SOURCE(SHARK "patch-for-at-rpath")
  set(_SB_SHARK_DIR ${SB_INSTALL_PREFIX}/share/SHARK)
endif()
endif()