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
//SectorCircular3d.cc

#include "SectorCircular3d.h"
#include "../tipos_cgal.h"
#include "xc_utils/src/geom/d2/Plano3d.h"
#include "xc_basic/src/util/matem.h"
#include <plotter.h>

#include "xc_utils/src/geom/pos_vec/MatrizPos2d.h"
#include "xc_utils/src/geom/pos_vec/MatrizPos3d.h"
#include "xc_utils/src/geom/pos_vec/Vector3d.h"
#include "boost/progress.hpp"


//! @brief Constructor de copia
SectorCircular3d::SectorCircular3d(const SectorCircular3d &otro)
  : D2to3d(otro), sect_circ(otro.sect_circ) {}

//! @brief Operador asignación.
SectorCircular3d &SectorCircular3d::operator=(const SectorCircular3d &p)
  {
    D2to3d::operator=(p);
    sect_circ= p.sect_circ;
    return *this;
  }

//! @brief Constructor virtual.
D2to3d *SectorCircular3d::clon(void) const
  { return new SectorCircular3d(*this); }

//! @brief Constructor.
SectorCircular3d::SectorCircular3d(const Pos3d centro,const GEOM_FT &rad,const double &th1,const double &th2)
  : D2to3d(centro), sect_circ()
  { sect_circ= SectorCircular2d(Circulo2d(to_2d(centro),rad),th1,th2); }

//! @brief Constructor.
SectorCircular3d::SectorCircular3d(const GEOM_FT &rad2,const Pos3d &centro,const double &th1,const double &th2)
  : D2to3d(centro), sect_circ()
  { sect_circ= SectorCircular2d(Circulo2d(rad2,to_2d(centro)),th1,th2); }

SectorCircular3d::SectorCircular3d(const Pos3d &c,const double &r,const Vector3d &n,const Vector3d &ejeX,const double &th1,const double &th2)
  : D2to3d(c,n,ejeX), sect_circ()
  { sect_circ= SectorCircular2d(Circulo2d(to_2d(c),r),th1,th2); }

 
//! @brief Constructor; sector circular definido por tres puntos p1->p2->p3.
SectorCircular3d::SectorCircular3d(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3)
  : D2to3d(p1,p2,p3), sect_circ()
  {
    const Pos2d pA= to_2d(p1);
    const Pos2d pB= to_2d(p2);
    const Pos2d pC= to_2d(p3);
    const Circulo2d C(pA,pB,pC);
    const Pos2d po= C.Centro();
    //Ajustamos el centro y los ejes del sistema de coordenadas.
    TresPuntos(to_3d(po),p1,p3);
    const Pos2d pa= to_2d(p1);
    const Pos2d pb= to_2d(p2);
    const Pos2d pc= to_2d(p3);
    sect_circ= SectorCircular2dTresPuntos(pa,pb,pc);
  }

//! @brief Devuelve el centro del círculo.
Pos3d SectorCircular3d::Centro(void) const
  { return to_3d(sect_circ.Centro()); }

//! @brief Devuelve el punto inicial del arco.
Pos3d SectorCircular3d::PInic(void) const
  { return to_3d(sect_circ.PInic()); }

//! @brief Devuelve el punto final del arco.
Pos3d SectorCircular3d::PFin(void) const
  { return to_3d(sect_circ.PFin()); }

//! @brief Devuelve el punto medio del arco.
Pos3d SectorCircular3d::PMed(void) const
  { return to_3d(sect_circ.PMed()); }

Pos3d SectorCircular3d::Cdg(void) const
  { return Centro(); }

//! @brief Return the position of the arc centroid.
Pos3d SectorCircular3d::ArcCentroid(void) const
  { return to_3d(sect_circ.ArcCentroid()); }

GEOM_FT SectorCircular3d::Radio2(void) const
  { return sect_circ.Radio2(); }
GEOM_FT SectorCircular3d::Radio(void) const
  { return sect_circ.Radio(); }
GEOM_FT SectorCircular3d::Diametro(void) const
  { return sect_circ.Diametro(); }

double SectorCircular3d::Angulo(const Pos3d &p) const
  { return sect_circ.Angulo(to_2d(p)); }

//! @brief Returns the parameter of the point in the arc (distance to the arc's first point measured over the arc)
double SectorCircular3d::getLambda(const Pos3d &p) const
  { return sect_circ.getLambda(to_2d(p)); }

GEOM_FT SectorCircular3d::Ix(void) const
  { return sect_circ.Ix(); }
GEOM_FT SectorCircular3d::Iy(void) const
  { return sect_circ.Iy(); }
GEOM_FT SectorCircular3d::Pxy(void) const
  { return sect_circ.Pxy(); }
GEOM_FT SectorCircular3d::Iz(void) const
  { return sect_circ.Iz(); }

GEOM_FT SectorCircular3d::GetMax(unsigned short int i) const
  {
    std::cerr << "SectorCircular3d::GetMax(i), no implementada." << std::endl;
    return 1;
  }
GEOM_FT SectorCircular3d::GetMin(unsigned short int i) const
  {
    std::cerr << "SectorCircular3d::GetMin(i), no implementada." << std::endl;
    return -1;
  }
bool SectorCircular3d::In(const Pos3d &p, const double &tol) const
//Devuelve verdadero si el punto est'a sobre el Plano.
  {
    if(GetPlano().In(p,tol))
      return sect_circ.In(to_2d(p),tol);
    else
      return false;
  }

//! @brief Devuelve n puntos equiespaciados sobre el arco de círculo.
MatrizPos3d SectorCircular3d::PuntosArco(const size_t &n) const
  {
    MatrizPos3d retval= to_3d(sect_circ.PuntosArco(n));
    return retval;
  }

void SectorCircular3d::Print(std::ostream &os) const
  { os << sect_circ; }

bool operator ==(const SectorCircular3d &a,const SectorCircular3d &b)
  {
    if((const D2to3d &) a ==(const D2to3d &) b)  
      return ( a.sect_circ == b.sect_circ );
    else
      return false;
  }
