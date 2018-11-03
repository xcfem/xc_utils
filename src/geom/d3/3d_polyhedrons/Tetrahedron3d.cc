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
//Tetrahedron3d.cc

#include "Tetrahedron3d.h"
#include "Polyhedron3d.h"
#include "xc_utils/src/geom/pos_vec/Pos3d.h"
#include "xc_utils/src/geom/d3/HalfSpace3d.h"



#include "xc_utils/src/matrices/m_double.h"
#include "xc_utils/src/geom/pos_vec/Pos3dList.h"

const Pos3d v1PorDefecto(1.0,0.0,0.0);
const Pos3d v2PorDefecto(0.0,1.0,0.0);
const Pos3d v3PorDefecto(0.0,0.0,1.0);
const Pos3d v4PorDefecto(0.0,0.0,0.0);

//! @brief Default constructor.
Tetrahedron3d::Tetrahedron3d(void)
  : cgtetrahedron(v1PorDefecto.ToCGAL(),v2PorDefecto.ToCGAL(),v3PorDefecto.ToCGAL(),v4PorDefecto.ToCGAL()) {}

//! @brief Constructor.
Tetrahedron3d::Tetrahedron3d(const Pos3d &p0, const Pos3d &p1,const Pos3d &p2, const Pos3d &p3)
  : cgtetrahedron(p0.ToCGAL(),p1.ToCGAL(),p2.ToCGAL(),p3.ToCGAL()){}

//! @brief Constructor.
Tetrahedron3d::Tetrahedron3d(const HalfSpace3d &se0, const HalfSpace3d &se1,const HalfSpace3d &se2, const HalfSpace3d &se3)
  : cgtetrahedron()
  {
    Polyhedron3d tmp(se0,se1,se2,se3);
    GeomObj::list_Pos3d vertices= tmp.getVertices();
    assert (vertices.size()==4);
    cgtetrahedron= CGTetrahedron_3(vertices[0].ToCGAL(),vertices[1].ToCGAL(),vertices[2].ToCGAL(),vertices[3].ToCGAL());
  }

Polyhedron3d Tetrahedron3d::getPolyhedron3d(void) const
  {
    return Polyhedron3d(Pos3d(cgtetrahedron.vertex(0)),Pos3d(cgtetrahedron.vertex(1)),Pos3d(cgtetrahedron.vertex(2)),Pos3d(cgtetrahedron.vertex(3)));
  }

GEOM_FT Tetrahedron3d::GetMax(unsigned short int i) const
  {
    CGPoint_3 vi= cgtetrahedron.vertex(0);
    GEOM_FT retval= vi.cartesian(i-1);
    for(int j=1;j<4;j++)
      {
        vi= cgtetrahedron.vertex(j);
        retval= std::max(retval,vi.cartesian(i-1));
      }
    return retval;
  }
GEOM_FT Tetrahedron3d::GetMin(unsigned short int i) const
  {
    CGPoint_3 vi= cgtetrahedron.vertex(0);
    GEOM_FT retval= vi.cartesian(i-1);
    for(int j=1;j<4;j++)
      {
        vi= cgtetrahedron.vertex(j);
        retval= std::min(retval,vi.cartesian(i-1));
      }
    return retval;
  }

//! @brief Return the object area.
GEOM_FT Tetrahedron3d::getArea(void) const
  { return getPolyhedron3d().getArea(); }

//! @brief Return the volume of the body with sign.
GEOM_FT Tetrahedron3d::getVolumeWithSign(void) const
  {
    return cgtetrahedron.volume();
  }

//! @brief Return the volume of the object.
GEOM_FT Tetrahedron3d::getVolume(void) const
  { return std::abs(getVolumeWithSign()); }

//! @brief Returns true if point inside tetrahedron.
bool Tetrahedron3d::In(const Pos3d &p,const double &tol) const
  {
    CGAL::Bounded_side side= cgtetrahedron.bounded_side(p.ToCGAL());
    return (side != CGAL::ON_UNBOUNDED_SIDE);
  }

//! @brief Prints object.
void Tetrahedron3d::Print(std::ostream &os) const
  {
    CGAL::set_ascii_mode(os);
    CGAL::set_pretty_mode(os);
    os << cgtetrahedron << std::endl;
  }

PolygonMap<CGPolyhedron_3> getPolygonMap(const Tetrahedron3d &t)
  { return t.getPolyhedron3d().GetPolygonMap(); }

