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

enable_language(Fortran) #umfpack, itpack,

INCLUDE(${xc_utils_DIR}/CMake/find_packages.txt)
if(GTK2_FOUND)
  include_directories(${GTK2_INCLUDE_DIRS})
endif()
INCLUDE_DIRECTORIES(${GTK_INCLUDE_DIR})

if(MPI_FOUND)
  include_directories(${MPI_INCLUDE_PATH})
endif()

#Biblioteca VTK
#vtk
IF(USE_VTK_FILE)
  INCLUDE(${USE_VTK_FILE})
  message(STATUS "vtk file: ${USE_VTK_FILE}")
  SET(VTK_BIB vtkRendering vtkIO vtkHybrid)
  SET(VTK_FOUND 1)
ENDIF(USE_VTK_FILE)
#Workaround to allow CGAL to set the Boost_LIBRARIES variables
#without removing the boost libraries that we also need to use.
#LCPT 3/09/2018
SET(XC_UTILS_BOOST_LIBRARIES ${Boost_LIBRARIES})
MESSAGE(STATUS ${Boost_LIBRARIES})
#Biblioteca CGAL
IF(CGAL_USE_FILE)
  INCLUDE(${CGAL_USE_FILE})
  message(STATUS "cgal file: ${CGAL_USE_FILE}")
ENDIF(CGAL_USE_FILE)
ADD_TO_LIST(XC_UTILS_BOOST_LIBRARIES ${Boost_LIBRARIES})
LIST(REMOVE_DUPLICATES XC_UTILS_BOOST_LIBRARIES)
MESSAGE(STATUS ${XC_UTILS_BOOST_LIBRARIES})
#End of the Workaround.

#Biblioteca GLIB (para gts)
INCLUDE_DIRECTORIES(${GLIB2_INCLUDE_DIRS})

#Biblioteca CGAL
INCLUDE_DIRECTORIES(${CGAL_INCL_DIR})
INCLUDE_DIRECTORIES(${CGAL_INCL_CONF_DIR})

#Biblioteca SqLiteWrapped
INCLUDE_DIRECTORIES(${SQLITEWP_INCL_DIR})

#Python
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_DIRS})

ADD_DEFINITIONS(-Wall -O3 -march=native -frounding-math -pedantic -fPIC)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
#SET(CMAKE_VERBOSE_MAKEFILE ON)

SET(text_utils utils/text/text_string utils/text/LabelContainer utils/text/en_letra utils/text/StrTok utils/text/tab_cod utils/text/latex utils/text/StringFormatter utils/text/FixedWidthReader)
SET(stream_utils utils/streams/imanip utils/streams/prep)
SET(misc_utils utils/misc_utils/cmd_args utils/misc_utils/memoria utils/misc_utils/inertia utils/misc_utils/print_trace)

SET(SQLITE sqlite/SqLiteObject sqlite/SqLiteQuery sqlite/SqLiteDatabase)

SET(sqlitepp_utils utils/sqlitepp/Database utils/sqlitepp/Query utils/sqlitepp/StderrLog utils/sqlitepp/SysLog)

SET(matrices matrices/MMatrix matrices/vcolM matrices/RangoIndice matrices/MatrixRange matrices/BoxConstRef matrices/ExpressionMatrix matrices/MExpressionMatrix matrices/PolynomialMatrix matrices/m_double matrices/m_bool matrices/m_double matrices/m_int matrices/m_sizet matrices/m_string matrices/giros matrices/op_tensor matrices/solvers/solver matrices/IndicesMatrix)

SET(three_d_arrays matrices/3d_arrays/Array3dBase matrices/3d_arrays/Array3dBoxRefBase matrices/3d_arrays/Array3dRange matrices/3d_arrays/BoolArray3d matrices/3d_arrays/Indices3dArray)

SET(skypack skypack/skypri.f skypack/skypds.f skypack/skyscf.f skypack/skyssb.f skypack/mtrxys.f skypack/skyssf.f skypack/skypsb.f skypack/skypdc.f skypack/skypf1.f skypack/skysdc.f skypack/skypsp.f skypack/skypcf.f skypack/skymef.f skypack/skyssd.f skypack/skyss.f skypack/skysf1.f skypack/skypf2.f skypack/mtrxy.f skypack/mtrxyd.f skypack/skysf2.f skypack/skypci.f)

SET(itpack itpack/dsrc2c.f itpack/jcg.f itpack/jsi.f itpack/rscg.f itpack/rssi.f itpack/sor.f itpack/ssorcg.f itpack/ssorsi.f)

SET(umfpack umfpack/umd2fb.f umfpack/umd2co.f umfpack/umd2fa.f umfpack/umd2f0.f umfpack/umd2f1.f umfpack/umd2f2.f umfpack/umd2fg.f umfpack/umd2in.f umfpack/umd2of.f umfpack/umd2s2.f umfpack/umd2sl.f umfpack/umd2so.f umfpack/umd2su.f umfpack/umd2er.f umfpack/umd2p1.f umfpack/umd2p2.f umfpack/umd2lt.f umfpack/umd2ut.f umfpack/umd2rf.f umfpack/umd2ra.f umfpack/umd2r0.f umfpack/umd2r2.f umfpack/umd2rg.f umfpack/umd21i.f umfpack/mc21b.f umfpack/mc13e.f)

SET(algebra functions/algebra/TablaLiterales functions/algebra/ArbolExpr functions/algebra/ExprAlgebra functions/algebra/Expresion functions/algebra/ExprInfija functions/algebra/ExprPostfija functions/algebra/LexAlgebra functions/algebra/Lexico functions/algebra/Literal functions/algebra/OpBinario functions/algebra/OpComparacion functions/algebra/OpBooleano functions/algebra/Macaulay functions/algebra/Operando functions/algebra/OpUnario functions/algebra/ProtoExpr functions/algebra/Rama functions/algebra/Variable functions/algebra/Operador functions/algebra/Segnal functions/algebra/ExprFunctor functions/algebra/OpndoConNombre functions/algebra/OpTrigonometricas functions/algebra/ConjVariables functions/algebra/MapValores functions/algebra/num_integration)

SET(functions_misc functions/estadisticas/statlib functions/estadisticas/Muestra functions/estadisticas/combinatoria functions/extremos/extremo functions/macaulay/Macaulay functions/polinomios/Polinomio functions/polinomios/IndPol functions/polinomios/NmbVars functions/raices/NewtonRaphson functions/raices/root functions/funcs_forma/FForma functions/funcs_forma/IntegrationPoints)

SET(functions ${algebra} ${functions_misc})

SET(cuadGauss gauss_quadrature/GaussQuadrature2D gauss_quadrature/GaussQuadrature3D gauss_quadrature/gssleg gauss_quadrature/GaussPoints gauss_quadrature/GaussWeights1d gauss_quadrature/GaussWeights2d gauss_quadrature/GaussWeights3d)

SET(geomTrfs geom/trf/Trf geom/trf/Trf2d geom/trf/Rotation2d geom/trf/Trf3d geom/trf/Translation2d geom/trf/Scaling3d geom/trf/Scaling2d geom/trf/Identity2d geom/trf/Identity3d geom/trf/Translation3d geom/trf/Reflection2d geom/trf/Rotation3d geom/trf/Reflection3d geom/trf/Revolution3d)

SET(geomRefCooSys geom/coo_sys/CooSys geom/coo_sys/Rect1d3dCooSys geom/coo_sys/Rect2d3dCooSys geom/coo_sys/Rect3d3dCooSys geom/coo_sys/Rect1d2dCooSys geom/coo_sys/Rect2d2dCooSys geom/coo_sys/Xd3dCooSys geom/coo_sys/Xd2dCooSys geom/ geom/sis_ref/Ref1d2d geom/sis_ref/Ref3d3d geom/sis_ref/Ref2d2d geom/sis_ref/Ref1d3d geom/sis_ref/Ref2d3d geom/sis_ref/PrincipalAxesOfInertia2D)

SET(geomD0 geom/d0/Point3d geom/d0/Point2d)

SET(geomD1 geom/d1/Line3d geom/d1/Line2d geom/d1/Ray3d geom/d1/Segment2d geom/d1/Ray2d geom/d1/Segment3d geom/d1/Polyline2d geom/d1/Polyline3d)

SET(geomD2 geom/d2/GeomGroup2d geom/d2/Surface2d geom/d2/Surface3d geom/d2/Plane geom/d2/BND2d geom/d2/Circle2d geom/d2/CircularSector2d geom/d2/CircularSector3d geom/d2/AnnulusSector2d geom/d2/GeomObj2d geom/d2/Polygon3d geom/d2/2d_polygons/Polygon2d geom/d2/2d_polygons/PolygonWithHoles2d geom/d2/2d_polygons/PolygonalSurface2d geom/d2/2d_polygons/Triangle2d geom/d2/2d_polygons/carsten_steger geom/d2/2d_polygons/polygon2d_bool_op geom/d2/2d_polygons/Quadrilateral2d geom/d2/2d_polygons/Rectangle2d geom/d2/2d_polygons/Square2d geom/d2/HalfPlane2d geom/d2/Triangle3d geom/d2/Circle3d geom/d2/D2to3d geom/d2/Trihedron geom/d2/Triang3dMesh geom/d2/ConvexHull2d geom/d2/GeneralEquationOfPlane geom/d2/Grid2d)

SET(geomD3 geom/d3/BND3d geom/d3/GeomObj3d geom/d3/BspTree3d geom/d3/Cylinder geom/d3/GeomGroup3d geom/d3/3d_polyhedrons/VertexMap geom/d3/3d_polyhedrons/PolyhedronBase geom/d3/3d_polyhedrons/Polyhedron3d geom/d3/3d_polyhedrons/PolygonMap geom/d3/3d_polyhedrons/modifier_quad_triangle geom/d3/3d_polyhedrons/enriched_polyhedron geom/d3/3d_polyhedrons/Tetrahedron3d geom/d3/3d_polyhedrons/BlockPyramid geom/d3/3d_polyhedrons/polyhedron3d_bool_op geom/d3/HalfSpace3d geom/d3/ConvexHull3d geom/d3/Solid3d geom/d3/3d_prisms/TriangularPrism3d)

SET(funcFromPoints geom/d1/function_from_points/FunctionFromPointsR_R geom/d1/function_from_points/FunctionFromPointsR2_R)

SET(geom geom/pos_vec/SlidingVector3d geom/pos_vec/FixedVector3d geom/pos_vec/Vector2d geom/pos_vec/Vector3d geom/pos_vec/Pos2d geom/pos_vec/Pos2dList geom/pos_vec/Pos3d geom/pos_vec/KDTreePos geom/pos_vec/Pos3dList geom/pos_vec/Dir3d geom/pos_vec/Dir2d geom/pos_vec/SlidingVector2d geom/pos_vec/FixedVector2d geom/pos_vec/SlidingVectorsSystem3d geom/pos_vec/SlidingVectorsSystem2d geom/pos_vec/Pos2dArray geom/pos_vec/Pos2dArray3d geom/pos_vec/Pos3dArray geom/pos_vec/Pos3dArray3d geom/lists/ThreePoints3d geom/lists/utils_list_pos2d geom/lists/utils_list_pos3d geom/Wm3/Wm3Math geom/Wm3/Wm3Distance geom/Wm3/Wm3DistVector3Triangle3 ${geomD0} ${geomD1} ${geomD2} ${geomD3} ${geomRefCooSys} ${geomTrfs} ${funcFromPoints} geom/cgal_types geom/GeomObj geom/FT_matrix geom/ProtoGeom)

SET(GnuGts gnu_gts/GTSSurface gnu_gts/GTSVertex gnu_gts/GTSEdge gnu_gts/GTSFace gnu_gts/GTSSplit gnu_gts/GTSSurfaceTraverse gnu_gts/GTSSurfaceIntersection gnu_gts/GTSBBoxTree gnu_gts/GTSGraph gnu_gts/TriangleMap)

SET(KERNEL kernel/EntityWithProperties kernel/CommandEntity kernel/NamedEntity kernel/EntityWithOwner kernel/ErrLogFiles kernel/python_utils.cc)

#SET(VtkAux vtk_aux/vtkShStrArray vtk_aux/vtkLabeledShStrMapper vtk_aux/vtkTakePhotoDefs vtk_aux/vtkTakePhoto vtk_aux/vtkXOpenGLOffScreenRenderWindow vtk_aux/vtkDoubleHeadedArrowSource vtk_aux/vtkArcSource)

SET(ca_factors loadCombinations/factors/PartialSafetyFactors loadCombinations/factors/PartialSafetyFactorsMap loadCombinations/factors/CombinationFactors loadCombinations/factors/CombinationFactorsMap loadCombinations/factors/Factors)

SET(ca_acciones loadCombinations/actions/LeadingActionInfo loadCombinations/actions/Action loadCombinations/actions/ActionRelationships loadCombinations/actions/ActionRValue loadCombinations/actions/ActionRValueList loadCombinations/actions/ActionsFamily loadCombinations/actions/ActionContainer loadCombinations/actions/ActionsAndFactors)

SET(ca_combinations loadCombinations/comb_analysis/Variation loadCombinations/comb_analysis/Variations loadCombinations/comb_analysis/LoadCombinationVector loadCombinations/comb_analysis/LoadCombinations loadCombinations/comb_analysis/ActionWeightingMap loadCombinations/comb_analysis/LoadCombinationGenerator)

ADD_LIBRARY(xc_basic_utils ${text_utils} ${stream_utils} ${misc_utils} ${sqlitepp_utils} ${matrices} ${three_d_arrays} ${skypack} ${itpack} ${umfpack} ${functions})
INSTALL(TARGETS xc_basic_utils DESTINATION lib)

ADD_LIBRARY(xc_utils SHARED ${SQLITE} ${cuadGauss} ${geom} ${GnuGts} ${KERNEL}  ${VtkAux} ${ca_factors} ${ca_acciones} ${ca_combinations})

#Interfaz Python
LINK_LIBRARIES(xc_utils xc_basic_utils ${VTK_BIB} ${CGAL_LIBRARIES} ${Plot_LIBRARY} ${MPFR_LIBRARIES} ${GMP_LIBRARY} ${SQLITE3_LIBRARY} ${GNUGTS_LIBRARIES} boost_python ${XC_UTILS_BOOST_LIBRARIES} ${PYTHON_LIBRARIES})
LINK_DIRECTORIES("/usr/lib/python2.7") # Not needed?
ADD_DEFINITIONS(-fno-strict-aliasing)
ADD_LIBRARY(xc_base SHARED kernel/python_interface.cc)
ADD_LIBRARY(loadCombinations SHARED loadCombinations/python_interface.cc)
ADD_LIBRARY(geom SHARED geom/d1/export_d1_entities.cc geom/d2/export_d2_entities.cc geom/d3/export_d3_entities.cc geom/export_sys_trf.cc geom/python_interface.cc)
ADD_LIBRARY(xcGnuGts SHARED gnu_gts/python_interface.cc)
#ADD_LIBRARY(vtk_aux SHARED vtk_aux/python_interface.cc)

INSTALL(TARGETS xc_basic_utils xc_utils loadCombinations geom DESTINATION lib)

