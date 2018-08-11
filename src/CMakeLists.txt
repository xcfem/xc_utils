cmake_minimum_required(VERSION 2.6)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
set(CMAKE_VERSION_STRING ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION})
IF (${CMAKE_VERSION_STRING} GREATER 2.8.4)
  cmake_policy(SET CMP0017 NEW) 
  MESSAGE ("CMake version is greater than 2.8.4")
ELSE (${CMAKE_VERSION_STRING} GREATER 2.8.4)
  MESSAGE ("CMake version is not greater than 2.8.4")
ENDIF (${CMAKE_VERSION_STRING} GREATER 2.8.4)

#Project name.
PROJECT(xc_utils)

SET(build_setup_dir $ENV{HOME}/.xc_build)

#xc_basic
SET(basica_setup_file ${build_setup_dir}/basica_dirs.cmake)
INCLUDE(${basica_setup_file})
SET(xc_basic_DIR ${basica_src_dir}/..)
message(STATUS "basica project dir: "${xc_basic_DIR})
SET(xc_basic_INC ${basica_inc_dir})
message(STATUS "basica include dir: "${xc_basic_INC})
INCLUDE_DIRECTORIES(${xc_basic_INC})
SET(xc_basic_LIB ${basica_lib_dir})
message(STATUS "basica lib dir: "${xc_basic_LIB})


SET(xc_utils_DIR ${CMAKE_SOURCE_DIR}/..)
message(STATUS "project dir: "${xc_utils_DIR})
string(REGEX REPLACE "/xc_utils/src.*" "" xc_utils_INC ${CMAKE_SOURCE_DIR})
message(STATUS "include dir: "${xc_utils_INC})
SET(xc_utils_LIB ${xc_utils_INC}/xc_utils/lib)
message(STATUS "lib dir: "${xc_utils_LIB})

SET(build_setup_file ${build_setup_dir}/lcmd_dirs.cmake)
file(MAKE_DIRECTORY ${build_setup_dir})
file(WRITE ${build_setup_file} "SET(lcmd_src_dir "${CMAKE_SOURCE_DIR}")\n")
file(APPEND ${build_setup_file} "SET(lcmd_inc_dir "${xc_utils_INC}")\n")
file(APPEND ${build_setup_file} "SET(lcmd_lib_dir "${xc_utils_LIB}")\n")

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${xc_basic_DIR}/CMake")
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${xc_utils_DIR}/CMake")

SET(LIBRARY_OUTPUT_PATH ${xc_utils_LIB})

INCLUDE_DIRECTORIES(${xc_utils_INC})

INCLUDE(${xc_utils_DIR}/CMake/find_packages.txt)
MESSAGE(STATUS "Boost_LIBRARIES: "${Boost_LIBRARIES})

#Biblioteca VTK
#vtk
IF(USE_VTK_FILE)
  INCLUDE(${USE_VTK_FILE})
  message(STATUS "vtk file: "${USE_VTK_FILE})
  SET(VTK_BIB vtkRendering vtkIO vtkHybrid)
  SET(VTK_FOUND 1)
ENDIF(USE_VTK_FILE)

#Biblioteca CGAL
IF(CGAL_USE_FILE)
  INCLUDE(${CGAL_USE_FILE})
  message(STATUS "cgal file: "${CGAL_USE_FILE})
ENDIF(CGAL_USE_FILE)

#Biblioteca GLIB (para gts)
INCLUDE_DIRECTORIES(${GLIB2_INCLUDE_DIRS})

#Biblioteca CGAL
INCLUDE_DIRECTORIES(${CGAL_INCL_DIR})
INCLUDE_DIRECTORIES(${CGAL_INCL_CONF_DIR})

#Biblioteca MySql++
INCLUDE_DIRECTORIES(${MYSQL_INCLUDE_DIRECTORIES})
INCLUDE_DIRECTORIES(${MYSQLPP_INCL_DIR})

#Biblioteca SqLiteWrapped
INCLUDE_DIRECTORIES(${SQLITEWP_INCL_DIR})

#Python
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_DIRS})

ADD_DEFINITIONS(-Wall -O3 -march=native -frounding-math -pedantic -fPIC)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
#SET(CMAKE_VERBOSE_MAKEFILE ON)


SET(SQLITE sqlite/SqLiteObject sqlite/SqLiteQuery sqlite/SqLiteDatabase)

SET(cuadGauss gauss_quadrature/GaussQuadrature2D gauss_quadrature/GaussQuadrature3D gauss_quadrature/gssleg gauss_quadrature/GaussPoints gauss_quadrature/GaussWeights1d gauss_quadrature/GaussWeights2d gauss_quadrature/GaussWeights3d)

SET(geomTrfs geom/trf/Trf geom/trf/Trf2d geom/trf/Rotation2d geom/trf/Trf3d geom/trf/Translation2d geom/trf/Scaling3d geom/trf/Scaling2d geom/trf/Identidad2d geom/trf/Identidad3d geom/trf/Translation3d geom/trf/Reflection2d geom/trf/Rotation3d geom/trf/Reflection3d geom/trf/Revolucion3d)

SET(geomSisCooRef geom/sis_coo/SisCoo geom/sis_coo/SisCooRect1d3d geom/sis_coo/SisCooRect2d3d geom/sis_coo/SisCooRect3d3d geom/sis_coo/SisCooRect1d2d geom/sis_coo/SisCooRect2d2d geom/sis_coo/SisCooXd3d geom/sis_coo/SisCooXd2d geom/ geom/sis_ref/Ref1d2d geom/sis_ref/Ref3d3d geom/sis_ref/Ref2d2d geom/sis_ref/Ref1d3d geom/sis_ref/Ref2d3d geom/sis_ref/PrincipalAxesOfInertia2D)

SET(geomD0 geom/d0/Point3d geom/d0/Point2d)

SET(geomD1 geom/d1/Line3d geom/d1/Line2d geom/d1/Ray3d geom/d1/Segment2d geom/d1/Ray2d geom/d1/Segment3d geom/d1/Polyline2d geom/d1/Polyline3d)

SET(geomD2 geom/d2/GeomGroup2d geom/d2/Surface2d geom/d2/Surface3d geom/d2/Plane geom/d2/BND2d geom/d2/Circle2d geom/d2/CircularSector2d geom/d2/CircularSector3d geom/d2/AnnulusSector2d geom/d2/GeomObj2d geom/d2/Polygon3d geom/d2/2d_polygons/Polygon2d geom/d2/2d_polygons/PolygonWithHoles2d geom/d2/2d_polygons/PolygonalSurface2d geom/d2/2d_polygons/Triangle2d geom/d2/2d_polygons/carsten_steger geom/d2/2d_polygons/polygon2d_bool_op geom/d2/2d_polygons/Cuadrilatero2d geom/d2/2d_polygons/Rectangle2d geom/d2/2d_polygons/Cuadrado2d geom/d2/HalfPlane2d geom/d2/Triangle3d geom/d2/Circle3d geom/d2/D2to3d geom/d2/Trihedron geom/d2/Triang3dMesh geom/d2/ConvexHull2d geom/d2/GeneralEquationOfPlane geom/d2/Grid2d)

SET(geomD3 geom/d3/BND3d geom/d3/GeomObj3d geom/d3/BspTree3d geom/d3/Cylinder geom/d3/GeomGroup3d geom/d3/3d_polyhedrons/VertexMap geom/d3/3d_polyhedrons/PolyhedronBase geom/d3/3d_polyhedrons/Poliedro3d geom/d3/3d_polyhedrons/PolygonMap geom/d3/3d_polyhedrons/modifier_quad_triangle geom/d3/3d_polyhedrons/enriched_polyhedron geom/d3/3d_polyhedrons/Tetraedro3d geom/d3/3d_polyhedrons/BlockPyramid geom/d3/3d_polyhedrons/bool_op_poliedro3d geom/d3/HalfSpace3d geom/d3/ConvexHull3d geom/d3/Solid3d geom/d3/3d_prisms/PrismaTriang3d)

SET(funcFromPoints geom/d1/function_from_points/FunctionFromPointsR_R geom/d1/function_from_points/FunctionFromPointsR2_R)

SET(geom geom/pos_vec/VDesliz3d geom/pos_vec/VFijo3d geom/pos_vec/Vector2d geom/pos_vec/Vector3d geom/pos_vec/Pos2d geom/pos_vec/Pos2dList geom/pos_vec/Pos3d geom/pos_vec/KDTreePos geom/pos_vec/Pos3dList geom/pos_vec/Dir3d geom/pos_vec/Dir2d geom/pos_vec/VDesliz2d geom/pos_vec/VFijo2d geom/pos_vec/SVD3d geom/pos_vec/SVD2d geom/pos_vec/Pos2dArray geom/pos_vec/BaseRefCajaArray3d geom/pos_vec/Array3dRange geom/pos_vec/Pos2dArray3d geom/pos_vec/Pos3dArray geom/pos_vec/Pos3dArray3d geom/lists/ThreePoints3d geom/lists/utils_list_pos2d geom/lists/utils_list_pos3d geom/Wm3/Wm3Math geom/Wm3/Wm3Distance geom/Wm3/Wm3DistVector3Triangle3 ${geomD0} ${geomD1} ${geomD2} ${geomD3} ${geomSisCooRef} ${geomTrfs} ${funcFromPoints} geom/cgal_types geom/GeomObj geom/FT_matrix geom/ProtoGeom)

SET(GnuGts gnu_gts/GTSSurface gnu_gts/GTSVertex gnu_gts/GTSEdge gnu_gts/GTSFace gnu_gts/GTSSplit gnu_gts/GTSSurfaceTraverse gnu_gts/GTSSurfaceIntersection gnu_gts/GTSBBoxTree gnu_gts/GTSGraph gnu_gts/TriangleMap)

SET(NUCLEO nucleo/EntProp nucleo/EntCmd nucleo/Signos nucleo/TokenList nucleo/EntConNmb nucleo/EntWOwner nucleo/ErrLogFiles nucleo/python_utils.cc)

#SET(VtkAux vtk_aux/vtkShStrArray vtk_aux/vtkLabeledShStrMapper vtk_aux/vtkTakePhotoDefs vtk_aux/vtkTakePhoto vtk_aux/vtkXOpenGLOffScreenRenderWindow vtk_aux/vtkDoubleHeadedArrowSource vtk_aux/vtkArcSource)

SET(ca_factors loadCombinations/factors/PartialSafetyFactors loadCombinations/factors/PartialSafetyFactorsMap loadCombinations/factors/CombinationFactors loadCombinations/factors/CombinationFactorsMap loadCombinations/factors/Factors)

SET(ca_acciones loadCombinations/actions/LeadingActionInfo loadCombinations/actions/Action loadCombinations/actions/ActionRelationships loadCombinations/actions/ActionRValue loadCombinations/actions/ActionRValueList loadCombinations/actions/ActionsFamily loadCombinations/actions/ActionContainer loadCombinations/actions/ActionsAndFactors)

SET(ca_combinations loadCombinations/comb_analysis/Variation loadCombinations/comb_analysis/Variations loadCombinations/comb_analysis/LoadCombinationVector loadCombinations/comb_analysis/LoadCombinations loadCombinations/comb_analysis/ActionWeightingMap loadCombinations/comb_analysis/LoadCombinationGenerator)

ADD_LIBRARY(xc_utils SHARED ${MYSQL} ${SQLITE} ${cuadGauss} ${geom} ${GnuGts} ${NUCLEO}  ${VtkAux} ${ca_factors} ${ca_acciones} ${ca_combinations})

#Interfaz Python
LINK_LIBRARIES(xc_utils xc_basic ${VTK_BIB} ${CGAL_LIBRARIES} ${Plot_LIBRARY} ${MPFR_LIBRARIES} ${GMP_LIBRARY} ${MySQLpp_LIBRARIES} ${SQLITE3_LIBRARY} ${GNUGTS_LIBRARIES} boost_python ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
LINK_DIRECTORIES("/usr/lib/python2.7") # Not needed?
ADD_DEFINITIONS(-fno-strict-aliasing)
ADD_LIBRARY(xc_base SHARED nucleo/python_interface.cc)
ADD_LIBRARY(loadCombinations SHARED loadCombinations/python_interface.cc)
ADD_LIBRARY(geom SHARED geom/d1/export_d1_entities.cc geom/d2/export_d2_entities.cc geom/d3/export_d3_entities.cc geom/export_sys_trf.cc geom/python_interface.cc)
ADD_LIBRARY(xcGnuGts SHARED gnu_gts/python_interface.cc)
#ADD_LIBRARY(vtk_aux SHARED vtk_aux/python_interface.cc)

INSTALL(TARGETS xc_utils loadCombinations geom DESTINATION lib)

SET(CPACK_GENERATOR "DEB")
INCLUDE(InstallRequiredSystemLibraries)

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "xc_utils")
SET(CPACK_DEBIAN_PACKAGE_NAME "xc_utils")
SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
INCLUDE(${xc_utils_DIR}/CMake/debian_package_params.txt)

SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libstdc++ (>=4.3), libgcc1 (>=1:4.3), libc6 (>=2.7), libvtk5 (>=5.0), libcgal2 (>=3.3), libplot2c2 (>=2.5), libmpfr1ldbl  (>=2.3), libgmp3c2 (>=4.2), libboost-regex1.34.1 (>=1.34), libmysql++3 (>=3.0), libsqlite3-0 (>=3.5), libxt6  (>=1.0), libsm6  (>=1.0), libxext6  (>=1.0), libice6  (>=1.0), libxft2  (>=2.1), xc_basic (>=0.9)")
SET(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Function library for XC and other programs.")

 
INCLUDE(CPack)
#execute fakeroot make package
