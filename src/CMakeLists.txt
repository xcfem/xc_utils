cmake_minimum_required(VERSION 2.6.3)
set(CMAKE_BUILD_TYPE to "Release")
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
set(CMAKE_VERSION_STRING ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION})
IF (${CMAKE_VERSION_STRING} GREATER 2.8.4)
  cmake_policy(SET CMP0017 NEW) 
  MESSAGE ("CMake version is greater than 2.8.4")
ELSE (${CMAKE_VERSION_STRING} GREATER 2.8.4)
  MESSAGE ("CMake version is not greater than 2.8.4")
ENDIF (${CMAKE_VERSION_STRING} GREATER 2.8.4)
set(OpenGL_GL_PREFERENCE "GLVND")
# Project name.
PROJECT(xc_utils)
SET(build_setup_dir $ENV{HOME}/.xc_build)

SET(xc_utils_DIR ${CMAKE_SOURCE_DIR}/..)
message(STATUS "project dir: ${xc_utils_DIR}")
string(REGEX REPLACE "/xc_utils/src.*" "" xc_utils_INC ${CMAKE_SOURCE_DIR})
message(STATUS "include dir: ${xc_utils_INC}")
SET(xc_utils_LIB ${xc_utils_INC}/xc_utils/lib)
message(STATUS "lib dir: ${xc_utils_LIB}")

SET(build_setup_file ${build_setup_dir}/lcmd_dirs.cmake)
file(MAKE_DIRECTORY ${build_setup_dir})
file(WRITE ${build_setup_file} "SET(lcmd_src_dir ${CMAKE_SOURCE_DIR})\n")
file(APPEND ${build_setup_file} "SET(lcmd_inc_dir ${xc_utils_INC})\n")
file(APPEND ${build_setup_file} "SET(lcmd_lib_dir ${xc_utils_LIB})\n")

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${xc_utils_DIR}/CMake")

SET(LIBRARY_OUTPUT_PATH ${xc_utils_LIB})

INCLUDE_DIRECTORIES(${xc_utils_INC})

enable_language(Fortran) # umfpack, itpack,

INCLUDE(${xc_utils_DIR}/CMake/find_packages.cmake)
if(GTK2_FOUND)
  include_directories(${GTK2_INCLUDE_DIRS})
endif()
INCLUDE_DIRECTORIES(${GTK_INCLUDE_DIR})

if(MPI_FOUND)
  include_directories(${MPI_INCLUDE_PATH})
endif()

# Python libraries
SET(XC_UTILS_BOOST_LIBRARIES ${Boost_LIBRARIES})
list(APPEND XC_UTILS_BOOST_LIBRARIES ${XC_UTILS_BOOST_PYTHON_LIBRARIES})
list(REMOVE_DUPLICATES XC_UTILS_BOOST_LIBRARIES)
#MESSAGE(STATUS "Boost_LIBRARIES = ${XC_UTILS_BOOST_LIBRARIES}")
MESSAGE(STATUS "Python version major: ${PYTHON_VERSION_MAJOR}")
if(PYTHON_VERSION_MAJOR EQUAL 3)
  set(PYTHON_FLAG "-D PYTHON3")
else()
  set(PYTHON_FLAG "-D PYTHON2")
endif()
  

# VTK library
IF(USE_VTK_FILE)
  INCLUDE(${USE_VTK_FILE})
  message(STATUS "vtk file: ${USE_VTK_FILE}")
  SET(VTK_BIB vtkRendering vtkIO vtkHybrid)
  SET(VTK_FOUND 1)
ENDIF(USE_VTK_FILE)

# Biblioteca GLIB (para gts)
INCLUDE_DIRECTORIES(${GLIB2_INCLUDE_DIRS})

# CGAL library
INCLUDE_DIRECTORIES(${CGAL_INCL_DIR})
INCLUDE_DIRECTORIES(${CGAL_INCL_CONF_DIR})

# SqLiteWrapped library
INCLUDE_DIRECTORIES(${SQLITEWP_INCL_DIR})

# Python
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17 ${CMAKE_CXX_FLAGS_RELEASE} -Wall -march=native -pedantic -fPIC ${PYTHON_FLAG}")
set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -fPIC")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
MESSAGE(STATUS "**** compiler fortran flags ${CMAKE_Fortran_FLAGS}")
MESSAGE(STATUS "**** compiler c flags ${CMAKE_C_FLAGS}")
MESSAGE(STATUS "**** compiler cxx flags ${CMAKE_CXX_FLAGS}")
MESSAGE(STATUS "**** linker flags ${CMAKE_EXE_LINKER_FLAGS}")
#set(CMAKE_VERBOSE_MAKEFILE ON)



# Python interface


