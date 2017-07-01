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

GEOM_FT (Pos2d::*distRecta2d)(const Recta2d &) const= &Pos2d::dist;
GEOM_FT (Pos2d::*distSemiRecta2d)(const SemiRecta2d &) const= &Pos2d::dist;
GEOM_FT (Pos2d::*distSegmento2d)(const Segmento2d &) const= &Pos2d::dist;
GEOM_FT (Pos2d::*dist2Recta2d)(const Recta2d &) const= &Pos2d::dist2;
GEOM_FT (Pos2d::*dist2SemiRecta2d)(const SemiRecta2d &) const= &Pos2d::dist2;
GEOM_FT (Pos2d::*dist2Segmento2d)(const Segmento2d &) const= &Pos2d::dist2;
GEOM_FT (Pos2d::*distPos2d)(const Pos2d &) const= &Pos2d::dist;
GEOM_FT (Pos2d::*dist2Pos2d)(const Pos2d &) const= &Pos2d::dist2;
GEOM_FT (Pos2d::*getItemPos2d)(const size_t &) const= &Pos2d::at0;
class_<Pos2d, bases<ProtoGeom> >("Pos2d")
  .def(init<double, double>())
  .def(init<Pos2d>())
  .def("__getitem__",getItemPos2d)
  .add_property("x", &Pos2d::x, &Pos2d::SetX)
  .add_property("y", &Pos2d::y, &Pos2d::SetY)
  .def("getDimension", &Pos2d::dimension)
  .def("getPositionVector", &Pos2d::VectorPos)
  .def("distPos2d",distPos2d)
  .def("distRecta2d",distRecta2d)
  .def("distSemiRecta2d",distSemiRecta2d)
  .def("distSegmento2d",distSegmento2d)
  .def("dist2Pos2d",dist2Pos2d)
  .def("dist2Recta2d",dist2Recta2d)
  .def("dist2SemiRecta2d",dist2SemiRecta2d)
  .def("dist2Segmento2d",dist2Segmento2d)
  .def(self + Vector2d())
  .def(self - Vector2d())
  .def(self - Pos2d())
  .def(self_ns::str(self_ns::self))
  ;
typedef MatrizT<Pos2d,std::vector<Pos2d> > mt_pos2d;
class_<mt_pos2d, bases<ProtoMatriz> >("mt_pos2d")
   .def("size", &mt_pos2d::size)
 ;

typedef MatrizPos<Pos2d> m_pos2d;
class_<m_pos2d, bases<mt_pos2d> >("m_pos2d")
  ;

class_<MatrizPos2d, bases<m_pos2d> >("MatrixPos2d")
  .def("getNumQuads",&MatrizPos2d::GetNumQuads)
  .def("getNumPoints",&MatrizPos2d::size)
  .def("getMax",&MatrizPos2d::GetMax)
  .def("getMin",&MatrizPos2d::GetMin)
  .def("getIx",&MatrizPos2d::GetIx)
  .def("getIy",&MatrizPos2d::GetIy)
  .def("getPxy",&MatrizPos2d::GetPxy)
  .def("Ix",&MatrizPos2d::Ix)
  .def("Iy",&MatrizPos2d::Iy)
  .def("Pxy",&MatrizPos2d::Pxy)
  .def("getCentro",&MatrizPos2d::GetCentro)
  .def("getCdg",&MatrizPos2d::GetCdg)
  .def("getArea",&MatrizPos2d::GetArea)
  .def("getTriangulo1",&MatrizPos2d::GetTriangulo1)
  .def("getTriangulo2",&MatrizPos2d::GetTriangulo2)
  .def("getX",&MatrizPos2d::GetX)
  .def("getY",&MatrizPos2d::GetY)
  .def("getPunto",&MatrizPos2d::GetPunto)
  .def("getQuad",&MatrizPos2d::GetQuad)
  .def("getAreaQuad",&MatrizPos2d::GetAreaQuad)
  .def("getCentroideQuad",&MatrizPos2d::GetCentroideQuad)
  .def("In",&MatrizPos2d::In)
  .def("Transforma",&MatrizPos2d::Transforma)
  .def("Lagrange",&MatrizPos2d::Lagrange)
  .def(self_ns::str(self_ns::self))
  ;


GEOM_FT (Vector2d::*dotVector2d)(const Vector2d &) const= &Vector2d::GetDot;
class_<Vector2d, bases<ProtoGeom> >("Vector2d")
  .def(init<double, double>())
  .def(init<Vector2d>())
  .add_property("x", &Vector2d::x, &Vector2d::SetX)
  .add_property("y", &Vector2d::y, &Vector2d::SetY)
  .def("normalizado", &Vector2d::Normalizado, "Devuelve el versor (vector de módulo unidad) correspondiente a este vector.")
  .def("angulo", &Vector2d::Angulo, "Devuelve el ángulo que forma el vector con aquel que se pasa como parámetro (el orden de éstos importa)")
  .def("getAnguloEjeX", &Vector2d::AnguloEjeX)
  .def("getAnguloEjeY", &Vector2d::AnguloEjeY)
  .def("dot", dotVector2d,"Returns scalar product.")
  .def("getModulo", &Vector2d::GetModulus)
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
  .def("normalizado", &Vector3d::Normalizado, "Devuelve el versor (vector de módulo unidad) correspondiente a este vector.")
  .def("angulo", &Vector3d::Angulo, "Devuelve el ángulo que forma el vector con aquel que se pasa como parámetro (el orden de éstos importa)")
  .def("perpendicular", &Vector3d::Perpendicular)
  .def("cross", &Vector3d::getCross)
  .def("dot", dotVector3d,"Returns scalar product.")
  .def("getModulo", &Vector3d::GetModulus)
  .def(self + Vector3d())
  .def(self - Vector3d())
  .def(self * double())
  .def(double() * self)
  .def(self_ns::str(self_ns::self))
   ;

GEOM_FT (Pos3d::*distRecta3d)(const Recta3d &) const= &Pos3d::dist;
GEOM_FT (Pos3d::*distSemiRecta3d)(const SemiRecta3d &) const= &Pos3d::dist;
GEOM_FT (Pos3d::*distSegmento3d)(const Segmento3d &) const= &Pos3d::dist;
GEOM_FT (Pos3d::*dist2Recta3d)(const Recta3d &) const= &Pos3d::dist2;
GEOM_FT (Pos3d::*dist2SemiRecta3d)(const SemiRecta3d &) const= &Pos3d::dist2;
GEOM_FT (Pos3d::*dist2Segmento3d)(const Segmento3d &) const= &Pos3d::dist2;
GEOM_FT (Pos3d::*getItemPos3d)(const size_t &) const= &Pos3d::at0;
GEOM_FT (Pos3d::*distPos3d)(const Pos3d &) const= &Pos3d::dist;
GEOM_FT (Pos3d::*distPlano3d)(const Plano3d &) const= &Pos3d::dist;
GEOM_FT (Pos3d::*distSemiEspacio3d)(const SemiEspacio3d &) const= &Pos3d::dist;
//GEOM_FT (Pos3d::*distSolido3d)(const Pos3d &) const= &Pos3d::dist;
GEOM_FT (Pos3d::*dist2Pos3d)(const Pos3d &) const= &Pos3d::dist2;
GEOM_FT (Pos3d::*dist2Plano3d)(const Plano3d &) const= &Pos3d::dist2;
GEOM_FT (Pos3d::*dist2SemiEspacio3d)(const SemiEspacio3d &) const= &Pos3d::dist2;
class_<Pos3d, bases<ProtoGeom> >("Pos3d")
  .def(init<double, double, double>())
  .def(init<Pos3d>())
  .def("__getitem__",getItemPos3d)
  .add_property("x", &Pos3d::x, &Pos3d::SetX)
  .add_property("y", &Pos3d::y, &Pos3d::SetY)
  .add_property("z", &Pos3d::z, &Pos3d::SetZ)
  .def("getPositionVector", &Pos3d::VectorPos)
  .def("distPos3d",distPos3d)
  .def("distRecta3d",distRecta3d)
  .def("distSemiRecta3d",distSemiRecta3d)
  .def("distSegmento3d",distSegmento3d)
  .def("distPlano3d",distPlano3d)
  .def("distSemiEspacio3d",distSemiEspacio3d)
  //.def("distSolido3d",distSolido3d)
  .def("dist2Pos3d",dist2Pos3d)
  .def("dist2Recta3d",dist2Recta3d)
  .def("dist2SemiRecta3d",dist2SemiRecta3d)
  .def("dist2Segmento3d",dist2Segmento3d)
  .def("dist2Plano3d",dist2Plano3d)
  .def("dist2SemiEspacio3d",dist2SemiEspacio3d)
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

// VDesliz2d (VDesliz2d::*getMomentoPos2d)(const Pos2d &o) const= &VDesliz2d::getMomento;
// GEOM_FT (VDesliz2d::*getMomentoRecta2d)(const Recta2d &e) const= &VDesliz2d::getMomento;

class_<VDesliz2d, bases<Vector2d> >("VDesliz2d")
  .def(init<Pos2d,Vector2d>())
  .def(init<Pos2d,Pos2d>())
  .def(init<VDesliz2d>())
  .def("getOrg", &VDesliz2d::getOrg,return_internal_reference<>())
  // .def("getMomentoPos2d",getMomentoPos2d)
  // .def("getMomentoRecta2d",getMomentoRecta2d)
  .def(self_ns::str(self_ns::self))
  ;


GEOM_FT (SVD2d::*getMomento2D)(void) const= &SVD2d::getMomento;
Vector2d (SVD2d::*getResultante2D)(void) const= &SVD2d::getResultante;

class_<SVD2d, bases<VDesliz2d> >("SVD2d")
  .def(init<Pos2d,Vector2d,GEOM_FT>())
  // .def(init<VDesliz2d>())
  .def("getResultante",getResultante2D)
  .def("getMomento",getMomento2D)
  .def("reduceTo",&SVD2d::ReduceA,"Sets the reference point to express the moments with respect to.")
  // //.def("getMomentoPos2d",getMomentoPos2d)
  // //.def("getMomentoRecta2d",getMomentoRecta2d)
  .def(VDesliz2d()+self) //Sobrecarga de operadores
  .def(self+VDesliz2d())
  .def(VDesliz2d()-self)
  .def(self-VDesliz2d())
  .def(self+=VDesliz2d())
  .def(self-=VDesliz2d())
  .def(SVD2d()+self)
  .def(self+SVD2d())
  .def(SVD2d()-self)
  .def(self-SVD2d())
  .def(self+=SVD2d())
  .def(self-=SVD2d())
  .def(self_ns::str(self_ns::self))
  ;

VDesliz3d (VDesliz3d::*getMomentoPos3d)(const Pos3d &o) const= &VDesliz3d::getMomento;
GEOM_FT (VDesliz3d::*getMomentoRecta3d)(const Recta3d &e) const= &VDesliz3d::getMomento;

class_<VDesliz3d, bases<Vector3d> >("VDesliz3d")
  .def(init<Pos3d,Vector3d>())
  .def(init<Pos3d,Pos3d>())
  .def(init<VDesliz3d>())
  .def("getOrg", &VDesliz3d::getOrg,return_internal_reference<>())
  .def("getMomentoPos3d",getMomentoPos3d)
  .def("getMomentoRecta3d",getMomentoRecta3d)
  .def(self_ns::str(self_ns::self))
  ;


const Vector3d &(SVD3d::*getMomento3D)(void) const= &SVD3d::getMomento;
const Vector3d &(SVD3d::*getResultante3D)(void) const= &SVD3d::getResultante;

class_<SVD3d, bases<VDesliz3d> >("SVD3d")
  .def(init<Pos3d,Vector3d,Vector3d>())
  .def(init<VDesliz3d>())
  .def("getResultante",getResultante3D,return_internal_reference<>())
  .def("getMomento",getMomento3D,return_internal_reference<>())
  .def("zeroMomentLine",&SVD3d::RectaMomNulo,"Return zero moment line (if it exists).")
  //.def("getMomentoPos3d",getMomentoPos3d)
  //.def("getMomentoRecta3d",getMomentoRecta3d)
  .def("reduceTo",&SVD3d::ReduceA,"Sets the reference point to express the moments with respect to.")
  .def(VDesliz3d()+self) //Sobrecarga de operadores
  .def(self+VDesliz3d())
  .def(VDesliz3d()-self)
  .def(self-VDesliz3d())
  .def(self+=VDesliz3d())
  .def(self-=VDesliz3d())
  .def(SVD3d()+self)
  .def(self+SVD3d())
  .def(SVD3d()-self)
  .def(self-SVD3d())
  .def(self+=SVD3d())
  .def(self-=SVD3d())
  .def(self_ns::str(self_ns::self))
  ;


typedef MatrizT<Pos3d,v_pos3d > mt_pos3d;
class_<mt_pos3d, bases<ProtoMatriz, v_pos3d> >("mt_pos3d")
  ;

typedef MatrizPos<Pos3d> m_pos3d;
class_<m_pos3d, bases<mt_pos3d> >("m_pos3d")
  ;

class_<MatrizPos3d, bases<m_pos3d> >("MatrixPos3d")
  ;

typedef std::vector<m_pos3d > ttz_pos3d;
class_<ttz_pos3d >("ttz_pos3d")
  .def(vector_indexing_suite<ttz_pos3d>() )
  ;

typedef TritrizPos<Pos3d> t_pos3d;
class_<t_pos3d, bases<ttz_pos3d> >("t_pos3d")
  ;

class_<TritrizPos3d, bases<t_pos3d> >("TritrizPos3d")
  ;

class_<ListaPos2d, bases<GeomObj2d> >("ListPos2d")
  .def(init<>())
  .def(init<ListaPos2d>())
  .def("getArea", &ListaPos2d::Area,"returns enclosed area.")
  .def("getCdg", &ListaPos2d::Cdg,"returns center of gravity.")
  .def("agregaPunto", &ListaPos2d::AgregaPunto,return_internal_reference<>(),"appends a point to the end of the list." )
  .def("getNumberOfVertices", &ListaPos2d::GetNumPuntos,"returns the number of vertices.")
  .def(self_ns::str(self_ns::self))
  ;

class_<ListaPos3d, bases<GeomObj3d> >("ListPos3d")
  .def(init<>())
  .def(init<ListaPos3d>())
  .def("getCdg", &ListaPos3d::Cdg)
  .def("agregaPunto", &ListaPos3d::AgregaPunto,return_internal_reference<>() )
  .def(self_ns::str(self_ns::self))
  ;
