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
//python_interface.cxx

class_<Linea2d, bases<GeomObj2d>, boost::noncopyable  >("Linea2d", no_init);
class_<SemiRecta2d, bases<Linea2d> >("SemiRecta2d")
  .def(init<SemiRecta2d>());


Recta2d (Recta2d::*OffsetVector)(const Vector2d &v) const= &Recta2d::Offset;
Recta2d (Recta2d::*OffsetDouble)(const GEOM_FT &) const= &Recta2d::Offset;
GeomObj::list_Pos2d (Recta2d::*intersectionWithR2D)(const Recta2d &) const= &Recta2d::Interseccion;
class_<Recta2d, bases<Linea2d> >("Recta2d")
  .def(init<Pos2d, Pos2d>())
  .def(init<Recta2d>())
  .def("OffsetVector",OffsetVector,"returns a parallel line obtained by adding the vector to the points that define this line.")
  .def("OffsetDouble",OffsetDouble,"returns a parallel line.")
  .def("getParamA",&Recta2d::GetParamA,"returns line slope; 'a' parameter from equation (y= a*x+b).")
  .def("getParamB",&Recta2d::GetParamB,"returns line y-intercept; 'b' parameter from equation (y= a*x+b).")
  .def("getIntersectionWithLine", intersectionWithR2D)
  ;

class_<Linea3d, bases<GeomObj3d>, boost::noncopyable  >("Linea3d", no_init);

class_<SemiRecta3d, bases<Linea3d> >("Ray3d")
  .def(init<SemiRecta3d>());

GEOM_FT (Segmento3d::*AnguloVector3D)(const Vector3d &v) const= &Segmento3d::Angulo;
GEOM_FT (Segmento3d::*AnguloSegmento3D)(const Segmento3d &v) const= &Segmento3d::Angulo;
class_<Segmento3d, bases<Linea3d> >("LineSegment3d")
  .def(init<>())
  .def(init<Pos3d,Pos3d>())
  .def("getOrigen", &Segmento3d::Origen)
  .def("getDestino", &Segmento3d::Destino)
  .def("getPendiente", &Segmento3d::GetPendiente)
  .def("distPto", &Segmento3d::dist)
  .def("getLongitud", &Segmento3d::Longitud)
  .def("getCdg", &Segmento3d::Cdg)
  .def("getPoint",&Segmento3d::PtoParametricas)
  .def("getAngleWithVector",AnguloVector3D,"Returns the angle between the line segment and the vector.")
  .def("getAngleWithLineSegment",AnguloSegmento3D,"Returns the angle between both line segments.")
  ;

Pos3d (Recta3d::*ProyPos3d)(const Pos3d &) const= &Recta3d::Proyeccion;
Vector3d (Recta3d::*ProyVector3d)(const Vector3d &) const= &Recta3d::Proyeccion;

class_<Recta3d, bases<Linea3d> >("Recta3d")
  .def(init<Pos3d, Pos3d>())
  .def(init<Pos3d, Dir3d>())
  .def(init<Recta3d>())
  .def("getProyPos3d",ProyPos3d)
  .def("getProyVector3d",ProyVector3d)
  .def("getVDir",&Recta3d::VDir)
  .def("getPoint",&Recta3d::PtoParametricas)
 ;

GeomObj::list_Pos2d (Polilinea2d::*intersectionWithLine)(const Recta2d &) const= &Polilinea2d::Interseccion;
GeomObj::list_Pos2d (Polilinea2d::*intersectionWithRay)(const SemiRecta2d &) const= &Polilinea2d::Interseccion;
GeomObj::list_Pos2d (Polilinea2d::*intersectionWithSegment)(const Segmento2d &) const= &Polilinea2d::Interseccion;
class_<Polilinea2d, bases<Linea2d, poliPos2d> >("Polilinea2d")
  .def(init<>())
  .def(init<ListaPos2d>())
  .def(init<Polilinea2d>())
  .def("agregaVertice", &Polilinea2d::AgregaVertice,return_internal_reference<>() )
  .def("getNumVertices", &Polilinea2d::GetNumVertices)
  .def("getNumSegmentos", &Polilinea2d::GetNumSegmentos)
  .def("getIx", &Polilinea2d::Ix)
  .def("getIy", &Polilinea2d::Iy)
  .def("getIz", &Polilinea2d::Iz)
  .def("getPxy", &Polilinea2d::Pxy)
  .def("getLongitud", &Polilinea2d::Longitud)
  .def("offset", &Polilinea2d::Offset)
  .def("getIntersectionWithLine", intersectionWithLine)
  .def("getIntersectionWithRay", intersectionWithRay)
  .def("getIntersectionWithSegment", intersectionWithSegment)
  ;


GEOM_FT (Segmento2d::*AnguloVector)(const Vector2d &v) const= &Segmento2d::Angulo;
GEOM_FT (Segmento2d::*AnguloSegmento)(const Segmento2d &v) const= &Segmento2d::Angulo;

Segmento2d (Segmento2d::*OffsetSegmentoVector)(const Vector2d &v) const= &Segmento2d::Offset;
Segmento2d (Segmento2d::*OffsetSegmentoDouble)(const GEOM_FT &d) const= &Segmento2d::Offset;

class_<Segmento2d, bases<Linea2d> >("Segmento2d")
  .def(init<>())
  .def(init<Pos2d,Pos2d>())
  .def(init<Segmento2d>())
  .def("getOrigen", &Segmento2d::Origen)
  .def("getDestino", &Segmento2d::Destino)
  .def("getPendiente", &Segmento2d::GetPendiente)
  .def("distPto", &Segmento2d::dist)
  .def("getLongitud", &Segmento2d::Longitud)
  .def("getCdg", &Segmento2d::Cdg)
  .def("anguloVector",AnguloVector)
  .def("anguloSegmento",AnguloSegmento)
  .def("offsetVector",OffsetSegmentoVector)
  .def("offsetDouble",OffsetSegmentoDouble);
  
class_<Polilinea3d, bases<Linea3d, poliPos3d> >("Polilinea3d")
  .def(init<>())
//.def(init<ListaPos3d>())
  .def(init<Polilinea3d>())
  .def("agregaVertice", &Polilinea3d::AgregaVertice,return_internal_reference<>() )
  .def("getNumVertices", &Polilinea3d::GetNumVertices)
  .def("getNumSegmentos", &Polilinea3d::GetNumSegmentos)
  .def("getLongitud", &Polilinea3d::Longitud)
  .def("getIntersection", &Polilinea3d::getIntersection)
  ;

typedef std::deque<Polilinea3d> dq_polyline3D;

class_<dq_polyline3D>("dq_polyline3D")
  .def(vector_indexing_suite<dq_polyline3D>() )
  ;

#include "func_por_puntos/python_interface.tcc"
