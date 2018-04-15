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
//GeomObj2d.cc

#include "GeomObj2d.h"
#include "xc_basic/src/util/inercia.h"
#include "xc_utils/src/geom/pos_vec/Dir2d.h"
#include "xc_utils/src/geom/d1/Recta2d.h"
#include "xc_utils/src/geom/sis_ref/Ref2d2d.h"
#include "xc_utils/src/geom/matriz_FT.h"
#include "BND2d.h"


#include "xc_utils/src/geom/trf/Translation2d.h"

Pos2d GeomObj2d::GetPMax(void) const
  {
    Pos2d p(GetXMax(),GetYMax());
    return p;
  }

Pos2d GeomObj2d::GetPMin(void) const
  {
    Pos2d p(GetXMin(),GetYMin());
    return p;
  }


//! @brief Return el rectángulo envolvente del objeto.
BND2d GeomObj2d::Bnd(void) const
  { return BND2d(GetPMin(),GetPMax()); }

//! @brief Return true if the point lies inside the object.
bool GeomObj2d::In(const Pos2d &p, const double &tol) const
  { 
    std::cerr << getClassName() << "::" << __FUNCTION__
	      << "; método In(p,tol) not implemented" << std::endl;
    return false;
  }

//! @brief Return true if the point lies outside the object.
bool GeomObj2d::Out(const Pos2d &p, const double &tol) const
  { return !In(p,tol); }


//! @brief Return el ángulo que define un eje principal de inercia.
double GeomObj2d::Theta_p(void) const
  { return theta_inercia(Ix(),Iy(),Pxy()); }

//! @brief Return the dirección de un eje principal de inercia (no sabemos si
//! el mayor o el menor).
Dir2d GeomObj2d::DirEjeI_a(void) const
  { return Dir2d(Theta_p()); }

//! @brief Return the dirección del otro eje principal de inercia (no sabemos si
//! el mayor o el menor).
Dir2d GeomObj2d::DirEjeI_b(void) const
  { return DirEjeI_a().Perpendicular(); }

//! @brief Return un eje principal de inercia (no sabemos si
//! el mayor o el menor
Recta2d GeomObj2d::EjeI_a(void) const
  { return Recta2d(Cdg(),DirEjeI_a()); }

//! @brief Return un eje principal de inercia (no sabemos si
//! el mayor o el menor
Recta2d GeomObj2d::EjeI_b(void) const
  { return Recta2d(Cdg(),DirEjeI_b()); }

//! @brief Return los ejes principales de inercia.
Ref2d2d GeomObj2d::PrincipalAxesOfInertia(void) const
  { return Ref2d2d(Cdg(),DirEjeI_a()); }

//! @brief Return el momento de inercia principal mayor.
GEOM_FT GeomObj2d::I1(void) const
  { return I1_inercia(Ix(),Iy(),Pxy()); }

//! @brief Return el momento de inercia principal menor.
GEOM_FT GeomObj2d::I2(void) const
  { return I2_inercia(Ix(),Iy(),Pxy()); }

//! @brief Return the componente i,j del tensor de inercia calculado respecto al CDG.
GEOM_FT GeomObj2d::I(const unsigned short int &i,const unsigned short int &j) const
  {
    unsigned short int k= i + (j-1)*2;
    GEOM_FT retval= 0.0;
    switch(k)
      {
        case 1: //(1,1)
          retval= Ix();
          break;
        case 2: //(2,1)
        case 3: //(1,2)
          retval= -Pxy();
          break;
	case 4:
          retval= Iy();
          break;
      }
    return retval;
  }

//! @brief Return the componente i,j del tensor de inercia calculado with respect to the point "o".
GEOM_FT GeomObj2d::I(const unsigned short int i,const unsigned short int j,const Pos2d &o) const
  {
    const GEOM_FT Iij= I(i,j);
    if(TieneCdg())
      {
        Ref2d2d ejes(Cdg()); //
        Pos2d pos_local= ejes.GetPosLocal(o);
        return Iij + IArea() * pos_local(i) * pos_local(j);
      }
    else
      {
	std::cerr << "El objeto no tiene centro de gravedad." << std::endl;
        return Iij;
      }
  }

//! @brief Return el tensor de inercia respecto al centro de gravedad del objeto.
matriz_FT GeomObj2d::I(void) const
  {
    matriz_FT i(2,2);
    i(1,1)= Ix();   i(1,2)= -Pxy();
    i(2,1)= i(1,2); i(2,2)= Iy();
    return i;
  }

//Return el tensor de inercia with respect to the point o.
matriz_FT GeomObj2d::I(const Pos2d &o) const
  {
    matriz_FT Ig= I();
    Vector2d og= Cdg() - o;
    GEOM_FT m= IArea();
    return Ig+m*(Abs2(og)*identidad(Ig)-(og & og));
  }
GEOM_FT GeomObj2d::I(const Recta2d &r) const
//Return el momento de inercia respecto a la recta que se pasa
//como parámetro.
  { return I(r.Point(),r.VDir()); }


//! @brief Return el momento de inercia respecto al eje que pasa por O
//! con dirección la de e.
GEOM_FT GeomObj2d::I(const Pos2d &O,const Vector2d &e) const
  {
    const matriz_FT Io= I(O);
    return dot(e,Io*e)/Abs2(e);
  }

//! @brief Return el momento polar de inercia with respect to the point o.
GEOM_FT GeomObj2d::IO(const Pos2d &o) const
  { return (I(1,1,o)+I(2,2,o)+I(3,3,o))/2; }

//! @brief Desplaza el objeto.
void GeomObj2d::Mueve(const Vector2d &v)
  {
    Translation2d m(v);
    Transforma(m);
  }
