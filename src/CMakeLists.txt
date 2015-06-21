cmake_minimum_required(VERSION 2.6)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
set(CMAKE_VERSION_STRING ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION})
IF (${CMAKE_VERSION_STRING} GREATER 2.8.4)
  cmake_policy(SET CMP0017 NEW) 
  MESSAGE ("CMake version is greater than 2.8.4")
ELSE (${CMAKE_VERSION_STRING} GREATER 2.8.4)
  MESSAGE ("CMake version is not greater than 2.8.4")
ENDIF (${CMAKE_VERSION_STRING} GREATER 2.8.4)

#Nombre del proyecto.
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

SET(BASE base/EntradaComandos base/Path base/ArchivosSalida base/ArchivosEntrada base/MapAuxData base/CmdStatus base/PilaLlamadas base/Buscadores base/EntWOwner base/BloqueBase base/BloqueCond base/BloqueIf base/BloqueSwitchStr base/BloqueWhile base/BloqueFor base/BloqueSub base/BloqueFunc base/EntConNmb base/CmdMatriz base/CmdVectorBase base/CmdVectorDenso base/utils_any base/utils_any_const_ptr base/ErrLogFiles base/Record base/Lista base/Mapa base/Locale base/CmdTimer base/CmdFuncPorPuntos base/CmdFixedWidthReader)

SET(MYSQL mysql/MySqlObject mysql/MySqlConnection mysql/MySqlQuery mysql/MySqlResult mysql/MySqlRow mysql/MySqlColData)

SET(SQLITE sqlite/SqLiteObject sqlite/SqLiteQuery sqlite/SqLiteDatabase)

SET(CMDLIBPLOT libplot/CmdPlotter)

SET(cuadGauss CuadGauss/Cuadratura2D CuadGauss/Cuadratura3D CuadGauss/gssleg CuadGauss/PuntosGauss CuadGauss/PsoGss1d CuadGauss/PsoGss2d CuadGauss/PsoGss3d)

SET(geomTrfs geom/trf/Trf geom/trf/Trf2d geom/trf/Rotacion2d geom/trf/Trf3d geom/trf/Traslacion2d geom/trf/Escalado3d geom/trf/Escalado2d geom/trf/Identidad2d geom/trf/Identidad3d geom/trf/Traslacion3d geom/trf/Reflexion2d geom/trf/Rotacion3d geom/trf/Reflexion3d geom/trf/Revolucion3d)

SET(geomSisCooRef geom/sis_coo/SisCoo geom/sis_coo/SisCooRect1d3d geom/sis_coo/SisCooRect2d3d geom/sis_coo/SisCooRect3d3d geom/sis_coo/SisCooRect1d2d geom/sis_coo/SisCooRect2d2d geom/sis_coo/SisCooXd3d geom/sis_coo/SisCooXd2d geom/ geom/sis_ref/Ref1d2d geom/sis_ref/Ref3d3d geom/sis_ref/Ref2d2d geom/sis_ref/Ref1d3d geom/sis_ref/Ref2d3d geom/sis_ref/EjesPrincInercia2d)

SET(geomD0 geom/d0/Punto3d geom/d0/Punto2d)

SET(geomD1 geom/d1/Recta3d geom/d1/Recta2d geom/d1/SemiRecta3d geom/d1/Segmento2d geom/d1/SemiRecta2d geom/d1/Segmento3d geom/d1/Polilinea2d geom/d1/Polilinea3d)

SET(geomD2 geom/d2/GmGrupo2d geom/d2/Superficie2d geom/d2/Superficie3d geom/d2/Plano3d geom/d2/BND2d geom/d2/Circulo2d geom/d2/SectorCircular2d geom/d2/SectorCircular3d geom/d2/SectorAnilloCircular2d geom/d2/GeomObj2d geom/d2/Poligono3d geom/d2/poligonos2d/Poligono2d geom/d2/poligonos2d/PoligonoConAgujeros2d geom/d2/poligonos2d/SupPoligonal2d geom/d2/poligonos2d/Triangulo2d geom/d2/poligonos2d/carsten_steger geom/d2/poligonos2d/bool_op_poligono2d geom/d2/poligonos2d/Cuadrilatero2d geom/d2/poligonos2d/Rectangulo2d geom/d2/poligonos2d/Cuadrado2d geom/d2/Semiplano2d geom/d2/Triangulo3d geom/d2/Circulo3d geom/d2/D2to3d geom/d2/Triedro3d geom/d2/MallaTriang3d geom/d2/EcuacionGeneralPlano3d geom/d2/Rejilla2d)

SET(geomD3 geom/d3/BND3d geom/d3/GeomObj3d geom/d3/BspTree3d geom/d3/Cilindro geom/d3/GmGrupo3d geom/d3/poliedros3d/VertexMap geom/d3/poliedros3d/Poliedro3d geom/d3/poliedros3d/MapPoligonos geom/d3/poliedros3d/modifier_quad_triangle geom/d3/poliedros3d/enriched_polyhedron geom/d3/poliedros3d/Tetraedro3d geom/d3/poliedros3d/BlockPyramid geom/d3/poliedros3d/bool_op_poliedro3d geom/d3/SemiEspacio3d geom/d3/ConvexHull3d geom/d3/Solido3d geom/d3/prismas3d/PrismaTriang3d)

SET(funcPorPuntos geom/d1/func_por_puntos/FuncPorPuntosR_R geom/d1/func_por_puntos/FuncPorPuntosR2_R)

SET(geom geom/pos_vec/VDesliz3d geom/pos_vec/VFijo3d geom/pos_vec/Vector2d geom/pos_vec/Vector3d geom/pos_vec/Pos2d geom/pos_vec/ListaPos2d geom/pos_vec/Pos3d geom/pos_vec/ListaPos3d geom/pos_vec/Dir3d geom/pos_vec/Dir2d geom/pos_vec/VDesliz2d geom/pos_vec/VFijo2d geom/pos_vec/SVD3d geom/pos_vec/SVD2d geom/pos_vec/MatrizPos2d geom/pos_vec/BaseRefCajaTritriz geom/pos_vec/RangoTritriz geom/pos_vec/TritrizPos2d geom/pos_vec/MatrizPos3d geom/pos_vec/TritrizPos3d geom/listas/TresPuntos3d geom/listas/utils_list_pos2d geom/listas/utils_list_pos3d geom/Wm3/Wm3Math geom/Wm3/Wm3Distance geom/Wm3/Wm3DistVector3Triangle3 ${geomD0} ${geomD1} ${geomD2} ${geomD3} ${geomSisCooRef} ${geomTrfs} ${funcPorPuntos} geom/tipos_cgal geom/GeomObj geom/matriz_FT geom/ProtoGeom)

SET(GnuGts gnu_gts/GTSSurface gnu_gts/GTSVertex gnu_gts/GTSEdge gnu_gts/GTSFace gnu_gts/GTSSplit gnu_gts/GTSSurfaceTraverse gnu_gts/GTSSurfaceIntersection gnu_gts/GTSBBoxTree gnu_gts/GTSGraph gnu_gts/MapTriangulos)

SET(NUCLEO nucleo/aux_any nucleo/EntBase nucleo/MapParam nucleo/MapPropVar nucleo/EntProp nucleo/EntPropSorter nucleo/EntCmd nucleo/Signos nucleo/TokenList nucleo/BoostAnyStack nucleo/AnalisisLexico nucleo/AnalisisSintactico nucleo/InterpreteRPN nucleo/MatrizAny nucleo/CmdParser nucleo/PropParser nucleo/python_utils.cc)

SET(ca_coefs loadCombinations/coefs/GammaF loadCombinations/coefs/CoefsPsi loadCombinations/coefs/MapCoefsPsi)

SET(ca_acciones loadCombinations/acciones/Accion loadCombinations/acciones/RelAcciones loadCombinations/acciones/VRAccion loadCombinations/acciones/ListaVRAccion loadCombinations/acciones/FamiliaAcciones loadCombinations/acciones/MapFamiliasAcc loadCombinations/acciones/AccionesClasificadas)

SET(ca_combinaciones loadCombinations/combinaciones/Variacion loadCombinations/combinaciones/Variaciones loadCombinations/combinaciones/VectorCombinaciones loadCombinations/combinaciones/Combinaciones loadCombinations/combinaciones/MapPondAcciones loadCombinations/combinaciones/GeneradorCombinaciones)

ADD_LIBRARY(xc_utils SHARED ${BASE} ${MYSQL} ${SQLITE} ${CMDLIBPLOT} ${cuadGauss} ${geom} ${GnuGts} ${NUCLEO} ${ca_coefs} ${ca_acciones} ${ca_combinaciones})

#Interfaz Python
LINK_LIBRARIES(xc_utils xc_basic ${VTK_BIB} ${CGAL_LIBRARIES} ${Plot_LIBRARY} ${MPFR_LIBRARIES} ${GMP_LIBRARY} ${MySQLpp_LIBRARIES} ${SQLITE3_LIBRARY} ${GNUGTS_LIBRARIES} boost_python ${Boost_LIBRARIES})
LINK_DIRECTORIES("/usr/lib/python2.6") # Not needed?
ADD_DEFINITIONS(-fno-strict-aliasing)
ADD_LIBRARY(xc_base SHARED nucleo/python_interface.cc)
ADD_LIBRARY(loadCombinations SHARED loadCombinations/python_interface.cc)
ADD_LIBRARY(geom SHARED geom/python_interface.cc)

INSTALL(TARGETS xc_utils loadCombinations geom DESTINATION lib)

SET(CPACK_GENERATOR "DEB")
INCLUDE(InstallRequiredSystemLibraries)

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "xc_utils")
SET(CPACK_DEBIAN_PACKAGE_NAME "xc_utils")
SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
INCLUDE(${xc_utils_DIR}/CMake/debian_package_params.txt)

SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libstdc++ (>=4.3), libgcc1 (>=1:4.3), libc6 (>=2.7), libvtk5 (>=5.0), libcgal2 (>=3.3), libplot2c2 (>=2.5), libmpfr1ldbl  (>=2.3), libgmp3c2 (>=4.2), libboost-regex1.34.1 (>=1.34), libmysql++3 (>=3.0), libsqlite3-0 (>=3.5), libxt6  (>=1.0), libsm6  (>=1.0), libxext6  (>=1.0), libice6  (>=1.0), libxft2  (>=2.1), xc_basic (>=0.9)")
SET(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Biblioteca de funciones para el intérprete de comandos de XC y otros programas.")

 
INCLUDE(CPack)
#ejecutar fakeroot make package
