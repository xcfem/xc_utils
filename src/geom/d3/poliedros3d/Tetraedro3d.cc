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
//Tetraedro3c.cc

#include "Tetraedro3d.h"
#include "Poliedro3d.h"
#include "xc_utils/src/geom/pos_vec/Pos3d.h"
#include "xc_utils/src/geom/d3/SemiEspacio3d.h"



#include "xc_basic/src/matrices/m_double.h"
#include "xc_utils/src/geom/pos_vec/ListaPos3d.h"

const Pos3d v1PorDefecto(1.0,0.0,0.0);
const Pos3d v2PorDefecto(0.0,1.0,0.0);
const Pos3d v3PorDefecto(0.0,0.0,1.0);
const Pos3d v4PorDefecto(0.0,0.0,0.0);

//! @brief Default constructor.
Tetraedro3d::Tetraedro3d(void)
  : cgtetraedro(v1PorDefecto.ToCGAL(),v2PorDefecto.ToCGAL(),v3PorDefecto.ToCGAL(),v4PorDefecto.ToCGAL()) {}

//! @brief Constructor.
Tetraedro3d::Tetraedro3d(const Pos3d &p0, const Pos3d &p1,const Pos3d &p2, const Pos3d &p3)
  : cgtetraedro(p0.ToCGAL(),p1.ToCGAL(),p2.ToCGAL(),p3.ToCGAL()){}

//! @brief Constructor.
Tetraedro3d::Tetraedro3d(const SemiEspacio3d &se0, const SemiEspacio3d &se1,const SemiEspacio3d &se2, const SemiEspacio3d &se3)
  : cgtetraedro()
  {
    Poliedro3d tmp(se0,se1,se2,se3);
    GeomObj::list_Pos3d vertices= tmp.getVertices();
    assert (vertices.size()==4);
    cgtetraedro= CGTetrahedron_3(vertices[0].ToCGAL(),vertices[1].ToCGAL(),vertices[2].ToCGAL(),vertices[3].ToCGAL());
  }

Poliedro3d Tetraedro3d::getPoliedro3d(void) const
  {
    return Poliedro3d(Pos3d(cgtetraedro.vertex(0)),Pos3d(cgtetraedro.vertex(1)),Pos3d(cgtetraedro.vertex(2)),Pos3d(cgtetraedro.vertex(3)));
  }

GEOM_FT Tetraedro3d::GetMax(unsigned short int i) const
  {
    CGPoint_3 vi= cgtetraedro.vertex(0);
    GEOM_FT retval= vi.cartesian(i-1);
    for(int j=1;j<4;j++)
      {
        vi= cgtetraedro.vertex(j);
        retval= std::max(retval,vi.cartesian(i-1));
      }
    return retval;
  }
GEOM_FT Tetraedro3d::GetMin(unsigned short int i) const
  {
    CGPoint_3 vi= cgtetraedro.vertex(0);
    GEOM_FT retval= vi.cartesian(i-1);
    for(int j=1;j<4;j++)
      {
        vi= cgtetraedro.vertex(j);
        retval= std::min(retval,vi.cartesian(i-1));
      }
    return retval;
  }

//! @brief Return the object area.
GEOM_FT Tetraedro3d::getArea(void) const
  { return getPoliedro3d().getArea(); }

//! @brief Return the volume of the body with sign.
GEOM_FT Tetraedro3d::getVolumeWithSign(void) const
  {
    return cgtetraedro.volume();
  }

//! @brief Return the volume of the object.
GEOM_FT Tetraedro3d::getVolume(void) const
  { return std::abs(getVolumeWithSign()); }

//! @brief Returns true if point inside tetrahedron.
bool Tetraedro3d::In(const Pos3d &p,const double &tol) const
  {
    CGAL::Bounded_side side= cgtetraedro.bounded_side(p.ToCGAL());
    return (side != CGAL::ON_UNBOUNDED_SIDE);
  }

//! @brief Prints object.
void Tetraedro3d::Print(std::ostream &os) const
  {
    CGAL::set_ascii_mode(os);
    CGAL::set_pretty_mode(os);
    os << cgtetraedro << std::endl;
  }

MapPoligonos<CGPoliedro_3> getMapPoligonos(const Tetraedro3d &t)
  { return t.getPoliedro3d().GetMapPoligonos(); }

