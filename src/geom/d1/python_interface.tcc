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
Pos2d (Recta2d::*Pos2dProj)(const Pos2d &) const= &Recta2d::Projection;
Vector2d (Recta2d::*Vector2dProj)(const Vector2d &) const= &Recta2d::Projection;
class_<Recta2d, bases<Linea2d> >("Recta2d")
  .def(init<Pos2d, Pos2d>())
  .def(init<Recta2d>())
  .def("OffsetVector",OffsetVector,"returns a parallel line obtained by adding the vector to the points that define this line.")
  .def("OffsetDouble",OffsetDouble,"returns a parallel line.")
  .def("getParamA",&Recta2d::GetParamA,"returns line slope; 'a' parameter from equation (y= a*x+b).")
  .def("getParamB",&Recta2d::GetParamB,"returns line y-intercept; 'b' parameter from equation (y= a*x+b).")
  .def("getIntersectionWithLine", intersectionWithR2D)
  .def("getPos2dProj",Pos2dProj,"return the projection of a point onto the line.")
  .def("getVector2dProj",Vector2dProj,"return the projection of a vector onto the line.")
  .def("getVDir",&Recta2d::VDir,"return the line direction vector.")
  .def("getSlope", &Recta2d::getSlope)
  .def("distPto", &Recta2d::dist,"return the distance to the point.")
  ;

class_<Linea3d, bases<GeomObj3d>, boost::noncopyable  >("Linea3d", no_init);

class_<SemiRecta3d, bases<Linea3d> >("Ray3d")
  .def(init<SemiRecta3d>());

GEOM_FT (Segment3d::*AngleVector3D)(const Vector3d &v) const= &Segment3d::Angulo;
GEOM_FT (Segment3d::*AngleSegment3D)(const Segment3d &v) const= &Segment3d::Angulo;
class_<Segment3d, bases<Linea3d> >("LineSegment3d")
  .def(init<>())
  .def(init<Pos3d,Pos3d>())
  .def("getOrigen", &Segment3d::Origen)
  .def("getDestino", &Segment3d::Destino)
  .def("getSlope", &Segment3d::getSlope)
  .def("distPto", &Segment3d::dist,"return the distance to the point.")
  .def("getLength", &Segment3d::getLength,"Return the length of the segment.")
  .def("getCenterOfMass", &Segment3d::getCenterOfMass)
  .def("getPoint",&Segment3d::PtoParametricas)
  .def("getAngleWithVector",AngleVector3D,"Returns the angle between the line segment and the vector.")
  .def("getAngleWithLineSegment",AngleSegment3D,"Returns the angle between both line segments.")
  .def("getVDir",&Segment3d::VDir,"return the direction vector of the segment.")
  ;

Pos3d (Recta3d::*Pos3dProj)(const Pos3d &) const= &Recta3d::Projection;
Vector3d (Recta3d::*Vector3dProj)(const Vector3d &) const= &Recta3d::Projection;

class_<Recta3d, bases<Linea3d> >("Recta3d")
  .def(init<Pos3d, Pos3d>())
  .def(init<Pos3d, Dir3d>())
  .def(init<Recta3d>())
  .def("getPos3dProj",Pos3dProj,"return the projection of a point onto the line.")
  .def("getVector3dProj",Vector3dProj,"return the projection of a vector onto the line.")
  .def("getVDir",&Recta3d::VDir,"return the line direction vector.")
  .def("getPoint",&Recta3d::PtoParametricas)
  .def("getXY2DProjection",&Recta3d::XY2DProjection,"Return the projection of the line onto the XY plane as a 2D line.")
  .def("getXZ2DProjection",&Recta3d::XZ2DProjection,"Return the projection of the line onto the XZ plane as a 2D line.")
  .def("getYZ2DProjection",&Recta3d::YZ2DProjection,"Return the projection of the line onto the YZ plane as a 2D line.")
  .def("getXY3DProjection",&Recta3d::XY3DProjection,"Return the projection of the line onto the XY plane as a 3D line.")
  .def("getXZ3DProjection",&Recta3d::XZ3DProjection,"Return the projection of the line onto the XZ plane as a 3D line.")
  .def("getYZ3DProjection",&Recta3d::YZ3DProjection,"Return the projection of the line onto the YZ plane as a 3D line.")
  .def("distPto", &Recta3d::dist,"return the distance to the point.")
 ;

GeomObj::list_Pos2d (Polilinea2d::*intersectionWithLine)(const Recta2d &) const= &Polilinea2d::Interseccion;
GeomObj::list_Pos2d (Polilinea2d::*intersectionWithRay)(const SemiRecta2d &) const= &Polilinea2d::Interseccion;
GeomObj::list_Pos2d (Polilinea2d::*intersectionWithSegment)(const Segment2d &) const= &Polilinea2d::Interseccion;
void (Polilinea2d::*simplify2DPoly)(GEOM_FT epsilon)= &Polilinea2d::simplify;
Segment2d (Polilinea2d::*get2DSegment)(const size_t &) const= &Polilinea2d::getSegment;
class_<Polilinea2d, bases<Linea2d, poliPos2d> >("Polilinea2d")
  .def(init<>())
  .def(init<ListaPos2d>())
  .def(init<Polilinea2d>())
  .def("agregaVertice", &Polilinea2d::AgregaVertice,return_internal_reference<>() )
  .def("getNumVertices", &Polilinea2d::GetNumVertices)
  .def("getNumSegments", &Polilinea2d::getNumSegments)
  .def("getIx", &Polilinea2d::Ix)
  .def("getIy", &Polilinea2d::Iy)
  .def("getIz", &Polilinea2d::Iz)
  .def("getPxy", &Polilinea2d::Pxy)
  .def("getLength", &Polilinea2d::getLength,"Return the length of the polyline.")
  .def("offset", &Polilinea2d::Offset)
  .def("getIntersectionWithLine", intersectionWithLine)
  .def("getIntersectionWithRay", intersectionWithRay)
  .def("getIntersectionWithSegment", intersectionWithSegment)
  .def("isClosed",&Polilinea2d::isClosed,"returns true if the last vertex is coincident with the first one -dist(first,last)<tol*length-.")
  .def("simplify", simplify2DPoly,"simplification of the polyline (Douglas-Peucker algorithm).")
  .def("getSegment", get2DSegment, "return the i-th segment.")  
  ;


GEOM_FT (Segment2d::*AngleVector)(const Vector2d &v) const= &Segment2d::Angulo;
GEOM_FT (Segment2d::*AngleSegment)(const Segment2d &v) const= &Segment2d::Angulo;

Segment2d (Segment2d::*OffsetSegmentVector)(const Vector2d &v) const= &Segment2d::Offset;
Segment2d (Segment2d::*OffsetSegmentDouble)(const GEOM_FT &d) const= &Segment2d::Offset;

class_<Segment2d, bases<Linea2d> >("Segment2d")
  .def(init<>())
  .def(init<Pos2d,Pos2d>())
  .def(init<Segment2d>())
  .def("getOrigen", &Segment2d::Origen)
  .def("getDestino", &Segment2d::Destino)
  .def("getSlope", &Segment2d::getSlope)
  .def("distPto", &Segment2d::dist,"return the distance to the point.")
  .def("getLength", &Segment2d::getLength,"Return the length of the segment.")
  .def("getCenterOfMass", &Segment2d::getCenterOfMass)
  .def("angleVector",AngleVector)
  .def("angleSegment",AngleSegment)
  .def("offsetVector",OffsetSegmentVector)
  .def("offsetDouble",OffsetSegmentDouble);

void (Polilinea3d::*simplify3DPoly)(GEOM_FT epsilon)= &Polilinea3d::simplify;
Segment3d (Polilinea3d::*get3DSegment)(const size_t &) const= &Polilinea3d::getSegment;
class_<Polilinea3d, bases<Linea3d, poliPos3d> >("Polilinea3d")
  .def(init<>())
//.def(init<ListaPos3d>())
  .def(init<Polilinea3d>())
  .def("agregaVertice", &Polilinea3d::AgregaVertice,return_internal_reference<>() )
  .def("getNumVertices", &Polilinea3d::GetNumVertices)
  .def("getNumSegments", &Polilinea3d::getNumSegments)
  .def("getLength", &Polilinea3d::getLength,"Return the length of the polyline.")
  .def("getIntersection", &Polilinea3d::getIntersection)
  .def("isClosed",&Polilinea3d::isClosed,"returns true if the last vertex is coincident with the first one -dist(first,last)<tol*length-.")
  .def("simplify", simplify3DPoly,"simplification of the polyline (Douglas-Peucker algorithm).")
  .def("getCenterOfMass", &Polilinea3d::getCenterOfMass)
  .def("getSegment", get3DSegment, "return the i-th segment.")
  ;

typedef std::deque<Polilinea3d> dq_polyline3D;

class_<dq_polyline3D>("dq_polyline3D")
  .def(vector_indexing_suite<dq_polyline3D>() )
  ;

#include "function_from_points/python_interface.tcc"
