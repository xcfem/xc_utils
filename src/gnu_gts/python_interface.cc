//----------------------------------------------------------------------------
//  biblioteca xc_utils; bilioteca de comandos para el intérprete del lenguaje
//  de entrada de datos.
//
//  Copyright (C)  Luis Claudio Pérez Tato
//
//  Este software es libre: usted puede redistribuirlo y/o modificarlo 
//  bajo los términos de la Licencia Pública General GNU publicada 
//  por la Fundación para el Software Libre, ya sea la versión 3 
//  de la Licencia, o (a su elección) cualquier versión posterior.
//
//  Este software se distribuye con la esperanza de que sea útil, pero 
//  SIN GARANTÍA ALGUNA; ni siquiera la garantía implícita 
//  MERCANTIL o de APTITUD PARA UN PROPÓSITO DETERMINADO. 
//  Consulte los detalles de la Licencia Pública General GNU para obtener 
//  una información más detallada. 
//
// Debería haber recibido una copia de la Licencia Pública General GNU 
// junto a este programa. 
// En caso contrario, consulte <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------------
//python_interface.cc

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/class.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
#include <boost/python/docstring_options.hpp>
#include "GTSBBoxTree.h"
#include "GTSGraph.h"
#include "GTSSurfaceIntersection.h"
#include "TriangleMap.h"
#include "GTSEdge.h"
#include "GTSSplit.h"
#include "GTSSurfaceTraverse.h"
#include "GTSFace.h"
#include "GTSSurface.h"
#include "GTSVertex.h"
#include "xc_utils/src/geom/pos_vec/Pos3d.h"
#include "xc_utils/src/geom/pos_vec/Vector3d.h"


BOOST_PYTHON_MODULE(xcGnuGts)
  {
    using namespace boost::python;
    docstring_options doc_options;

    class_<GTSVertex>("GTSVertex")
      .def(init<double, double, double>())
      .def(init<Pos3d>())
      .add_property("getPos3d", &GTSVertex::Posicion)
      .def("getGaussianCurvature",&GTSVertex::GaussianCurvature)
      .def("getMeanCurvatureNormal",&GTSVertex::MeanCurvatureNormal)
      ;

    class_<GTSEdge>("GTSEdge", init<GTSVertex &,GTSVertex &>())
       .def("getV1",&GTSEdge::V1)
       .def("getV2",&GTSEdge::V2)
       .def("CollapseIsValid",&GTSEdge::CollapseIsValid)
     ;

    class_<GTSFace>("GTSFace", init<GTSEdge &,GTSEdge &,GTSEdge &>())
       .def("isNull",&GTSFace::Null)
     ;

    class_<GTSSurfaceTraverse>("GTSSurfaceTraverse", init<GTSSurface &,GTSFace &>())
      .def("next",&GTSSurfaceTraverse::Next)
     ;

    class_<GTSSurfaceIntersection>("GTSSurfaceIntersection")
      ;

    class_<GTSSurface>("GTSSurface")
      .def("appendFace",&GTSSurface::appendFace)
      .def("removeFace",&GTSSurface::removeFace);
     ;

    class_<GTSBBoxTree>("GTSBBoxTree")
      ;

    class_<GTSGraph>("GTSGraph", init<const GTSSurface &>())
      ;

    class_<GTSSplit>("GTSSplit", init<const GTSVertex &,const GTSVertex &,const GTSVertex &>())
      ;

    class_<VerticesKDTree>("VerticesKDTree")
      .def("getNearest",&VerticesKDTree::getNearest)
      .def("getNearest",&VerticesKDTree::getNearestBallPoint)
      ;

    typedef std::map<size_t,Pos3d> map_szt_pos3d;
    class_<map_szt_pos3d>("map_szt_pos3d")
      .def(map_indexing_suite<map_szt_pos3d >())
      ;

    class_<VerticesMap, bases<map_szt_pos3d> >("VerticesMap")
      ;

    const size_t &(TriangleVerticesIndexes::*v1)(void) const= &TriangleVerticesIndexes::V1;
    const size_t &(TriangleVerticesIndexes::*v2)(void) const= &TriangleVerticesIndexes::V2;
    const size_t &(TriangleVerticesIndexes::*v3)(void) const= &TriangleVerticesIndexes::V3;
    class_<TriangleVerticesIndexes>("TriangleVerticesIndexes", init<const size_t &,const size_t &,const size_t &>())
      .def("getV1",make_function(v1,return_value_policy<copy_const_reference>()),"Returns first vertex index.")
      .def("getV2",make_function(v2,return_value_policy<copy_const_reference>()),"Returns second vertex index.")
      .def("getV3",make_function(v3,return_value_policy<copy_const_reference>()),"Returns third vertex index.")
      ;

    typedef std::deque<TriangleVerticesIndexes> deque_triang;
    class_<deque_triang>("deque_triang")
      .def(vector_indexing_suite<deque_triang, false >())
      ;
    
    class_<TriangleFaces, bases<deque_triang> >("TriangleFaces")
      ;

    const VerticesMap &(TriangleMap::*GetVertices)(void) const= &TriangleMap::getVertices;
    const TriangleFaces &(TriangleMap::*GetFaces)(void) const= &TriangleMap::getFaces;
    class_<TriangleMap>("TriangleMap")
      .def("getVertices",make_function(GetVertices,return_internal_reference<>()),"Returns the vertices container.")
      .def("getFaces",make_function(GetFaces,return_internal_reference<>()),"Returns the faces container.")
      ;

  }
