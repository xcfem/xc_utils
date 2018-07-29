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

class_<Linear2d, bases<GeomObj2d>, boost::noncopyable  >("Linear2d", no_init);
class_<Ray2d, bases<Linear2d> >("Ray2d")
  .def(init<Ray2d>());


Line2d (Line2d::*OffsetVector)(const Vector2d &v) const= &Line2d::Offset;
Line2d (Line2d::*OffsetDouble)(const GEOM_FT &) const= &Line2d::Offset;
GeomObj::list_Pos2d (Line2d::*intersectionWithR2D)(const Line2d &) const= &Line2d::getIntersection;
Pos2d (Line2d::*Pos2dProj)(const Pos2d &) const= &Line2d::Projection;
Vector2d (Line2d::*Vector2dProj)(const Vector2d &) const= &Line2d::Projection;
class_<Line2d, bases<Linear2d> >("Line2d")
  .def(init<Pos2d, Pos2d>())
  .def(init<Line2d>())
  .def("OffsetVector",OffsetVector,"returns a parallel line obtained by adding the vector to the points that define this line.")
  .def("OffsetDouble",OffsetDouble,"returns a parallel line.")
  .def("getParamA",&Line2d::GetParamA,"returns line slope; 'a' parameter from equation (y= a*x+b).")
  .def("getParamB",&Line2d::GetParamB,"returns line y-intercept; 'b' parameter from equation (y= a*x+b).")
  .def("getIntersectionWithLine", intersectionWithR2D)
  .def("getPos2dProj",Pos2dProj,"return the projection of a point onto the line.")
  .def("getVector2dProj",Vector2dProj,"return the projection of a vector onto the line.")
  .def("getPoint",&Line2d::PtoParametricas,"return a point on the line.")
  .def("getVDir",&Line2d::VDir,"return the line direction vector.")
  .def("getSlope", &Line2d::getSlope)
  .def("distPto", &Line2d::dist,"return the distance to the point.")
  ;

class_<Linear3d, bases<GeomObj3d>, boost::noncopyable  >("Linear3d", no_init);

class_<Ray3d, bases<Linear3d> >("Ray3d")
  .def(init<Ray3d>());

GEOM_FT (Segment3d::*AngleVector3D)(const Vector3d &v) const= &Segment3d::getAngle;
GEOM_FT (Segment3d::*AngleSegment3D)(const Segment3d &v) const= &Segment3d::getAngle;
class_<Segment3d, bases<Linear3d> >("LineSegment3d")
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

Pos3d (Line3d::*Pos3dProj)(const Pos3d &) const= &Line3d::Projection;
Vector3d (Line3d::*Vector3dProj)(const Vector3d &) const= &Line3d::Projection;

class_<Line3d, bases<Linear3d> >("Line3d")
  .def(init<Pos3d, Pos3d>())
  .def(init<Pos3d, Dir3d>())
  .def(init<Line3d>())
  .def("getPos3dProj",Pos3dProj,"return the projection of a point onto the line.")
  .def("getVector3dProj",Vector3dProj,"return the projection of a vector onto the line.")
  .def("getVDir",&Line3d::VDir,"return the line direction vector.")
  .def("getPoint",&Line3d::PtoParametricas)
  .def("getXY2DProjection",&Line3d::XY2DProjection,"Return the projection of the line onto the XY plane as a 2D line.")
  .def("getXZ2DProjection",&Line3d::XZ2DProjection,"Return the projection of the line onto the XZ plane as a 2D line.")
  .def("getYZ2DProjection",&Line3d::YZ2DProjection,"Return the projection of the line onto the YZ plane as a 2D line.")
  .def("getXY3DProjection",&Line3d::XY3DProjection,"Return the projection of the line onto the XY plane as a 3D line.")
  .def("getXZ3DProjection",&Line3d::XZ3DProjection,"Return the projection of the line onto the XZ plane as a 3D line.")
  .def("getYZ3DProjection",&Line3d::YZ3DProjection,"Return the projection of the line onto the YZ plane as a 3D line.")
  .def("distPto", &Line3d::dist,"return the distance to the point.")
 ;

GeomObj::list_Pos2d (Polyline2d::*intersectionWithLine)(const Line2d &) const= &Polyline2d::getIntersection;
GeomObj::list_Pos2d (Polyline2d::*intersectionWithRay)(const Ray2d &) const= &Polyline2d::getIntersection;
GeomObj::list_Pos2d (Polyline2d::*intersectionWithSegment)(const Segment2d &) const= &Polyline2d::getIntersection;
void (Polyline2d::*simplify2DPoly)(GEOM_FT epsilon)= &Polyline2d::simplify;
Segment2d (Polyline2d::*get2DSegment)(const size_t &) const= &Polyline2d::getSegment;
class_<Polyline2d, bases<Linear2d, poliPos2d> >("Polyline2d")
  .def(init<>())
  .def(init<ListaPos2d>())
  .def(init<Polyline2d>())
  .def("agregaVertice", &Polyline2d::AgregaVertice,return_internal_reference<>() )
  .def("getNumVertices", &Polyline2d::GetNumVertices)
  .def("getNumSegments", &Polyline2d::getNumSegments)
  .def("getIx", &Polyline2d::Ix)
  .def("getIy", &Polyline2d::Iy)
  .def("getIz", &Polyline2d::Iz)
  .def("getPxy", &Polyline2d::Pxy)
  .def("getLength", &Polyline2d::getLength,"Return the length of the polyline.")
  .def("offset", &Polyline2d::Offset)
  .def("getIntersectionWithLine", intersectionWithLine)
  .def("getIntersectionWithRay", intersectionWithRay)
  .def("getIntersectionWithSegment", intersectionWithSegment)
  .def("isClosed",&Polyline2d::isClosed,"returns true if the last vertex is coincident with the first one -dist(first,last)<tol*length-.")
  .def("simplify", simplify2DPoly,"simplification of the polyline (Douglas-Peucker algorithm).")
  .def("getSegment", get2DSegment, "return the i-th segment.")  
  ;


GEOM_FT (Segment2d::*AngleVector)(const Vector2d &v) const= &Segment2d::getAngle;
GEOM_FT (Segment2d::*AngleSegment)(const Segment2d &v) const= &Segment2d::getAngle;

Segment2d (Segment2d::*OffsetSegmentVector)(const Vector2d &v) const= &Segment2d::Offset;
Segment2d (Segment2d::*OffsetSegmentDouble)(const GEOM_FT &d) const= &Segment2d::Offset;

class_<Segment2d, bases<Linear2d> >("Segment2d")
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

void (Polyline3d::*simplify3DPoly)(GEOM_FT epsilon)= &Polyline3d::simplify;
Segment3d (Polyline3d::*get3DSegment)(const size_t &) const= &Polyline3d::getSegment;
class_<Polyline3d, bases<Linear3d, poliPos3d> >("Polyline3d")
  .def(init<>())
//.def(init<ListaPos3d>())
  .def(init<Polyline3d>())
  .def("agregaVertice", &Polyline3d::AgregaVertice,return_internal_reference<>() )
  .def("getNumVertices", &Polyline3d::GetNumVertices)
  .def("getNumSegments", &Polyline3d::getNumSegments)
  .def("getLength", &Polyline3d::getLength,"Return the length of the polyline.")
  .def("getIntersection", &Polyline3d::getIntersection)
  .def("isClosed",&Polyline3d::isClosed,"returns true if the last vertex is coincident with the first one -dist(first,last)<tol*length-.")
  .def("simplify", simplify3DPoly,"simplification of the polyline (Douglas-Peucker algorithm).")
  .def("getCenterOfMass", &Polyline3d::getCenterOfMass)
  .def("getSegment", get3DSegment, "return the i-th segment.")
  ;

typedef std::deque<Polyline3d> dq_polyline3D;

class_<dq_polyline3D>("dq_polyline3D")
  .def(vector_indexing_suite<dq_polyline3D>() )
  ;

#include "function_from_points/python_interface.tcc"
