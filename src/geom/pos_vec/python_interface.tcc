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

GEOM_FT (Pos2d::*distLine2d)(const Line2d &) const= &Pos2d::dist;
GEOM_FT (Pos2d::*distRay2d)(const Ray2d &) const= &Pos2d::dist;
GEOM_FT (Pos2d::*distSegment2d)(const Segment2d &) const= &Pos2d::dist;
GEOM_FT (Pos2d::*dist2Line2d)(const Line2d &) const= &Pos2d::dist2;
GEOM_FT (Pos2d::*dist2Ray2d)(const Ray2d &) const= &Pos2d::dist2;
GEOM_FT (Pos2d::*dist2Segment2d)(const Segment2d &) const= &Pos2d::dist2;
GEOM_FT (Pos2d::*distPos2d)(const Pos2d &) const= &Pos2d::dist;
GEOM_FT (Pos2d::*dist2Pos2d)(const Pos2d &) const= &Pos2d::dist2;
GEOM_FT (Pos2d::*getItemPos2d)(const size_t &) const= &Pos2d::at0;
class_<Pos2d, bases<ProtoGeom> >("Pos2d")
  .def(init<double, double>())
  .def(init<Pos2d>())
  .def("__getitem__",getItemPos2d)
  .add_property("x", &Pos2d::x, &Pos2d::SetX)
  .add_property("y", &Pos2d::y, &Pos2d::SetY)
  .def("getDimension", &Pos2d::dimension,"return the dimension of the object.")
  .def("getPositionVector", &Pos2d::VectorPos,"return position vector of the point.")
  .def("distPos2d",distPos2d,"distance to a point.")
  .def("distLine2d",distLine2d,"distance to a straight line.")
  .def("distRay2d",distRay2d,"distance to a ray.")
  .def("distSegment2d",distSegment2d,"distance to a segment.")
  .def("dist2Pos2d",dist2Pos2d,"squared distance to a point.")
  .def("dist2Line2d",dist2Line2d,"squared distance to a straight line.")
  .def("dist2Ray2d",dist2Ray2d,"squared distance to a ray.")
  .def("dist2Segment2d",dist2Segment2d,"squared distance to a segment.")
  .def(self + Vector2d())
  .def(self - Vector2d())
  .def(self - Pos2d())
  .def(self_ns::str(self_ns::self))
  ;
typedef TMatrix<Pos2d,std::vector<Pos2d> > mt_pos2d;
class_<mt_pos2d, bases<ProtoMatrix> >("mt_pos2d")
   .def("size", &mt_pos2d::size)
 ;

typedef PosArray<Pos2d> m_pos2d;
class_<m_pos2d, bases<mt_pos2d> >("m_pos2d")
  ;

class_<Pos2dArray, bases<m_pos2d> >("MatrixPos2d")
  .def("getNumQuads",&Pos2dArray::GetNumQuads)
  .def("getNumPoints",&Pos2dArray::size)
  .def("getMax",&Pos2dArray::GetMax)
  .def("getMin",&Pos2dArray::GetMin)
  .def("getIx",&Pos2dArray::GetIx)
  .def("getIy",&Pos2dArray::GetIy)
  .def("getPxy",&Pos2dArray::GetPxy)
  .def("Ix",&Pos2dArray::Ix)
  .def("Iy",&Pos2dArray::Iy)
  .def("Pxy",&Pos2dArray::Pxy)
  .def("getCentro",&Pos2dArray::GetCentro)
  .def("getCenterOfMass",&Pos2dArray::getCenterOfMass)
  .def("getArea",&Pos2dArray::GetArea,"Return the total area.")
  .def("getTriangle1",&Pos2dArray::getTriangle1)
  .def("getTriangle2",&Pos2dArray::getTriangle2)
  .def("getX",&Pos2dArray::GetX)
  .def("getY",&Pos2dArray::GetY)
  .def("getPoint",&Pos2dArray::getPoint)
  .def("getQuad",&Pos2dArray::GetQuad,"Return the area of the (i,j) quad.")
  .def("getAreaQuad",&Pos2dArray::GetAreaQuad)
  .def("getCentroideQuad",&Pos2dArray::GetCentroideQuad)
  .def("In",&Pos2dArray::In)
  .def("Transforma",&Pos2dArray::Transforma)
  .def("Lagrange",&Pos2dArray::Lagrange)
  .def(self_ns::str(self_ns::self))
  ;


GEOM_FT (Vector2d::*dotVector2d)(const Vector2d &) const= &Vector2d::GetDot;
class_<Vector2d, bases<ProtoGeom> >("Vector2d")
  .def(init<double, double>())
  .def(init<Vector2d>())
  .add_property("x", &Vector2d::x, &Vector2d::SetX)
  .add_property("y", &Vector2d::y, &Vector2d::SetY)
  .def("normalizado", &Vector2d::Normalizado, "Return the normalized vector (vector with norm 1).")
  .def("getAngle", &Vector2d::getAngle, "Return the angle with the vector argumnet (order is important)")
  .def("getXAxisAngle", &Vector2d::XAxisAngle)
  .def("getYAxisAngle", &Vector2d::YAxisAngle)
  .def("dot", dotVector2d,"Returns scalar product.")
  .def("getModulo", &Vector2d::GetModulus)
  .def(-self) // __neg__ (unary minus)
  .def(self + self)          // __add__
  .def(self - self)           // __sub__
  .def(self * double())
  .def(double() * self)
  .def(self_ns::str(self_ns::self))
   ;


class_<Dir3d, boost::noncopyable>("Dir3d", no_init)
  .def(init<Dir3d>())
  .def(init<double, double, double>())
  .def(self_ns::str(self_ns::self))
  ;

GEOM_FT (Vector3d::*dotVector3d)(const Vector3d &) const= &Vector3d::GetDot;
class_<Vector3d, bases<ProtoGeom> >("Vector3d")
  .def(init<double, double, double>())
  .def(init<Vector3d>())
  .add_property("x", &Vector3d::x, &Vector3d::SetX)
  .add_property("y", &Vector3d::y, &Vector3d::SetY)
  .add_property("z", &Vector3d::z, &Vector3d::SetZ)
  // .def("normaliza", &Vector3d::Normaliza)
  .def("normalizado", &Vector3d::Normalizado, "Return the normalized vector (vector with norm 1).")
  .def("getAngle", &Vector3d::getAngle, "Return the angle with the vector argument (order is important)")
  .def("perpendicular", &Vector3d::Perpendicular)
  .def("cross", &Vector3d::getCross)
  .def("dot", dotVector3d,"Returns scalar product.")
  .def("getModulo", &Vector3d::GetModulus)
  .def(-self) // __neg__ (unary minus)
  .def(self + Vector3d())
  .def(self - Vector3d())
  .def(self * double())
  .def(double() * self)
  .def(self_ns::str(self_ns::self))
   ;

GEOM_FT (Pos3d::*distLine3d)(const Line3d &) const= &Pos3d::dist;
GEOM_FT (Pos3d::*distRay3d)(const Ray3d &) const= &Pos3d::dist;
GEOM_FT (Pos3d::*distSegment3d)(const Segment3d &) const= &Pos3d::dist;
GEOM_FT (Pos3d::*dist2Line3d)(const Line3d &) const= &Pos3d::dist2;
GEOM_FT (Pos3d::*dist2Ray3d)(const Ray3d &) const= &Pos3d::dist2;
GEOM_FT (Pos3d::*dist2Segment3d)(const Segment3d &) const= &Pos3d::dist2;
GEOM_FT (Pos3d::*getItemPos3d)(const size_t &) const= &Pos3d::at0;
GEOM_FT (Pos3d::*distPos3d)(const Pos3d &) const= &Pos3d::dist;
GEOM_FT (Pos3d::*distPlane)(const Plane &) const= &Pos3d::dist;
GEOM_FT (Pos3d::*distHalfSpace3d)(const HalfSpace3d &) const= &Pos3d::dist;
//GEOM_FT (Pos3d::*distSolid3d)(const Pos3d &) const= &Pos3d::dist;
GEOM_FT (Pos3d::*dist2Pos3d)(const Pos3d &) const= &Pos3d::dist2;
GEOM_FT (Pos3d::*dist2Plane)(const Plane &) const= &Pos3d::dist2;
GEOM_FT (Pos3d::*dist2HalfSpace3d)(const HalfSpace3d &) const= &Pos3d::dist2;
class_<Pos3d, bases<ProtoGeom> >("Pos3d")
  .def(init<double, double, double>())
  .def(init<Pos3d>())
  .def("__getitem__",getItemPos3d)
  .add_property("x", &Pos3d::x, &Pos3d::SetX)
  .add_property("y", &Pos3d::y, &Pos3d::SetY)
  .add_property("z", &Pos3d::z, &Pos3d::SetZ)
  .def("getPositionVector", &Pos3d::VectorPos)
  .def("distPos3d",distPos3d)
  .def("distLine3d",distLine3d)
  .def("distRay3d",distRay3d)
  .def("distSegment3d",distSegment3d)
  .def("distPlane",distPlane)
  .def("distHalfSpace3d",distHalfSpace3d)
  //.def("distSolid3d",distSolid3d)
  .def("dist2Pos3d",dist2Pos3d)
  .def("dist2Line3d",dist2Line3d)
  .def("dist2Ray3d",dist2Ray3d)
  .def("dist2Segment3d",dist2Segment3d)
  .def("dist2Plane",dist2Plane)
  .def("dist2HalfSpace3d",dist2HalfSpace3d)
  .def("getDimension", &Pos3d::dimension)
  .def(self + Vector3d())
  .def(self - Vector3d())
  .def(self - Pos3d())
  .def(self_ns::str(self_ns::self))
  ;

typedef std::vector<Pos3d> v_pos3d;
class_<v_pos3d>("v_pos3d")
  .def(vector_indexing_suite<v_pos3d>() )
 ;

// VDesliz2d (VDesliz2d::*getMomentPos2d)(const Pos2d &o) const= &VDesliz2d::getMoment;
// GEOM_FT (VDesliz2d::*getMomentLine2d)(const Line2d &e) const= &VDesliz2d::getMoment;

class_<VDesliz2d, bases<Vector2d> >("VDesliz2d")
  .def(init<Pos2d,Vector2d>())
  .def(init<Pos2d,Pos2d>())
  .def(init<VDesliz2d>())
  .def("getOrg", &VDesliz2d::getOrg,return_internal_reference<>())
  // .def("getMomentPos2d",getMomentPos2d)
  // .def("getMomentLine2d",getMomentLine2d)
  .def(self + self)          // __add__
  .def(self - self)           // __sub__
  .def(self * double())
  .def(double() * self)
  .def(self_ns::str(self_ns::self))
  ;


GEOM_FT (SlidingVectorsSystem2d::*getMoment2D)(void) const= &SlidingVectorsSystem2d::getMoment;
Vector2d (SlidingVectorsSystem2d::*getResultant2D)(void) const= &SlidingVectorsSystem2d::getResultant;

class_<SlidingVectorsSystem2d, bases<VDesliz2d> >("SlidingVectorsSystem2d")
  .def(init<Pos2d,Vector2d,GEOM_FT>())
  .def(init<VDesliz2d>())
  .def("getResultant",getResultant2D,"Return the resultant of the SVS.")
  .def("getMoment",getMoment2D)
  .def("reduceTo",&SlidingVectorsSystem2d::ReduceA,"Sets the reference point to express the moments with respect to.")
  .def("zeroMomentLine",&SlidingVectorsSystem2d::getZeroMomentLine,"Return zero moment line (if it exists).")
  // //.def("getMomentPos2d",getMomentPos2d)
  // //.def("getMomentLine2d",getMomentLine2d)
  .def(VDesliz2d()+self) //Sobrecarga de operadores
  .def(self+VDesliz2d())
  .def(VDesliz2d()-self)
  .def(self-VDesliz2d())
  .def(self+=VDesliz2d())
  .def(self-=VDesliz2d())
  .def(SlidingVectorsSystem2d()+self)
  .def(self+SlidingVectorsSystem2d())
  .def(SlidingVectorsSystem2d()-self)
  .def(self-SlidingVectorsSystem2d())
  .def(self+=SlidingVectorsSystem2d())
  .def(self-=SlidingVectorsSystem2d())
  .def(self * double())
  .def(double() * self)
  .def(self_ns::str(self_ns::self))
  ;

VDesliz3d (VDesliz3d::*getMomentPos3d)(const Pos3d &o) const= &VDesliz3d::getMoment;
GEOM_FT (VDesliz3d::*getMomentLine3d)(const Line3d &e) const= &VDesliz3d::getMoment;

class_<VDesliz3d, bases<Vector3d> >("VDesliz3d")
  .def(init<Pos3d,Vector3d>())
  .def(init<Pos3d,Pos3d>())
  .def(init<VDesliz3d>())
  .def("getOrg", &VDesliz3d::getOrg,return_internal_reference<>())
  .def("getMomentPos3d",getMomentPos3d)
  .def("getMomentLine3d",getMomentLine3d)
  .def(self + self)          // __add__
  .def(self - self)           // __sub__
  .def(self * double())
  .def(double() * self)
  .def(self_ns::str(self_ns::self))
  ;


const Vector3d &(SlidingVectorsSystem3d::*getMoment3D)(void) const= &SlidingVectorsSystem3d::getMoment;
const Vector3d &(SlidingVectorsSystem3d::*getResultant3D)(void) const= &SlidingVectorsSystem3d::getResultant;

class_<SlidingVectorsSystem3d, bases<VDesliz3d> >("SlidingVectorsSystem3d")
  .def(init<Pos3d,Vector3d,Vector3d>())
  .def(init<VDesliz3d>())
  .def("getResultant",getResultant3D,return_internal_reference<>(),"Return the resultant of the SVS.")
  .def("getMoment",getMoment3D,return_internal_reference<>())
  .def("zeroMomentLine",&SlidingVectorsSystem3d::getZeroMomentLine,"Return zero moment line (if it exists).")
  //.def("getMomentPos3d",getMomentPos3d)
  //.def("getMomentLine3d",getMomentLine3d)
  .def("reduceTo",&SlidingVectorsSystem3d::ReduceA,"Sets the reference point to express the moments with respect to.")
  .def(VDesliz3d()+self) //Sobrecarga de operadores
  .def(self+VDesliz3d())
  .def(VDesliz3d()-self)
  .def(self-VDesliz3d())
  .def(self+=VDesliz3d())
  .def(self-=VDesliz3d())
  .def(SlidingVectorsSystem3d()+self)
  .def(self+SlidingVectorsSystem3d())
  .def(SlidingVectorsSystem3d()-self)
  .def(self-SlidingVectorsSystem3d())
  .def(self+=SlidingVectorsSystem3d())
  .def(self-=SlidingVectorsSystem3d())
  .def(self * double())
  .def(double() * self)
  .def(self_ns::str(self_ns::self))
  ;


typedef TMatrix<Pos3d,v_pos3d > mt_pos3d;
class_<mt_pos3d, bases<ProtoMatrix, v_pos3d> >("mt_pos3d")
  ;

typedef PosArray<Pos3d> m_pos3d;
class_<m_pos3d, bases<mt_pos3d> >("m_pos3d")
  ;

class_<Pos3dArray, bases<m_pos3d> >("Pos3dArray")
  ;

typedef std::vector<m_pos3d > ttz_pos3d;
class_<ttz_pos3d >("ttz_pos3d")
  .def(vector_indexing_suite<ttz_pos3d>() )
  ;

typedef PosArray3d<Pos3d> t_pos3d;
class_<t_pos3d, bases<ttz_pos3d> >("t_pos3d")
  ;

class_<Pos3dArray3d, bases<t_pos3d> >("Pos3dArray3d")
  ;

class_<Pos2dList, bases<GeomObj2d> >("ListPos2d")
  .def(init<>())
  .def(init<Pos2dList>())
  .def("getArea", &Pos2dList::getArea,"returns enclosed area.")
  .def("getCenterOfMass", &Pos2dList::getCenterOfMass,"returns center of gravity.")
  .def("appendPoint", &Pos2dList::appendPoint,return_internal_reference<>(),"appends a point to the end of the list." )
  .def("getNumberOfVertices", &Pos2dList::getNumberOfPoints,"returns the number of vertices.")
  .def(self_ns::str(self_ns::self))
  ;

class_<Pos3dList, bases<GeomObj3d> >("ListPos3d")
  .def(init<>())
  .def(init<Pos3dList>())
  .def("getCenterOfMass", &Pos3dList::getCenterOfMass)
  .def("appendPoint", &Pos3dList::appendPoint,return_internal_reference<>() )
  .def(self_ns::str(self_ns::self))
  ;
