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
//HalfPlane2d.cc

#include "HalfPlane2d.h"
#include "GmGrupo2d.h"
#include "xc_utils/src/geom/d1/SemiRecta2d.h"
#include "xc_utils/src/geom/d1/Segment2d.h"

#include "../pos_vec/Dir2d.h"
#include "../pos_vec/Vector2d.h"

HalfPlane2d::HalfPlane2d(void)
  : Superficie2d(), lim() {}

HalfPlane2d::HalfPlane2d(const Recta2d &r)
  : Superficie2d(), lim(r) {}

HalfPlane2d::HalfPlane2d(const Recta2d &r, const Pos2d &p)
  : Superficie2d(), lim(r)
  {
    if(!In(p))
      Swap();
  }

HalfPlane2d::HalfPlane2d(const Pos2d &p1,const Pos2d &p2)
  : Superficie2d(), lim(p1,p2) {}
HalfPlane2d::HalfPlane2d(const HalfPlane2d &sp)
  : Superficie2d(sp),lim(sp.lim) {}
HalfPlane2d &HalfPlane2d::operator=(const HalfPlane2d &sp)
  {
    Superficie2d::operator=(sp);
    lim= sp.lim;
    return *this;
  }

GeomObj *HalfPlane2d::clon(void) const
  { return new HalfPlane2d(*this); }
void HalfPlane2d::Swap(void)
  { lim.Swap(); }

bool HalfPlane2d::Interseca(const SemiRecta2d &sr) const
  { return sr.Interseca(lim); }
bool HalfPlane2d::Interseca(const Segment2d &sg) const
  { return sg.Interseca(lim); }

HalfPlane2d HalfPlane2d::GetSwap(void) const
  {
    HalfPlane2d retval(*this);
    retval.Swap();
    return retval;
  }

GmGrupo2d HalfPlane2d::Interseccion(const Recta2d &r) const
  {
    GmGrupo2d retval;
    if(!Interseca(r)) return retval;
    GeomObj::list_Pos2d lista= interseccion(lim,r);
    const Pos2d pint= *lista.begin();
    const Vector2d vd= r.VDir();
    const Pos2d p1= pint+vd;
    if(In(p1))
      retval.push_back(SemiRecta2d(pint,vd));
    else
      retval.push_back(SemiRecta2d(pint,-vd));
    return retval;
  }

GmGrupo2d HalfPlane2d::Interseccion(const SemiRecta2d &sr) const
  {
    GmGrupo2d retval;
    if(!Interseca(sr)) return retval;
    GeomObj::list_Pos2d lista= interseccion(lim,sr);
    const Pos2d pint= *lista.begin();
    const Vector2d vd= sr.VDir();
    const Pos2d p1= pint+vd;
    if(In(p1))
      retval.push_back(SemiRecta2d(pint,vd));
    return retval;
  }

GmGrupo2d HalfPlane2d::Interseccion(const Segment2d &sg) const
  {
    GmGrupo2d retval;
    if(!Interseca(sg)) return retval;
    GeomObj::list_Pos2d lista= interseccion(lim,sg);
    const Pos2d pint= *lista.begin();
    const Pos2d p1= sg.Destino();
    const Pos2d p2= sg.Origen();
    if(In(p1))
      retval.push_back(Segment2d(pint,p1));
    else
      retval.push_back(Segment2d(pint,p2));
    return retval;
  }

GmGrupo2d interseccion(const HalfPlane2d &sp,const Recta2d &r)
  { return sp.Interseccion(r); }
GmGrupo2d interseccion(const HalfPlane2d &sp,const SemiRecta2d &sr)
  { return sp.Interseccion(sr); }
GmGrupo2d interseccion(const HalfPlane2d &sp,const Segment2d &sg)
  { return sp.Interseccion(sg); }
GmGrupo2d interseccion(const Recta2d &r,const HalfPlane2d &sp)
  { return interseccion(sp,r); }
GmGrupo2d interseccion(const SemiRecta2d &sr,const HalfPlane2d &sp)
  { return interseccion(sp,sr); }
GmGrupo2d interseccion(const Segment2d &sg,const HalfPlane2d &sp)
  { return interseccion(sp,sg); }

HalfPlane2d HalfPlane2d::getNormalizado(void) const
  { return HalfPlane2d(lim.getNormalizada()); }

//! @brief Aplica al objeto la transformación que se
//! pasa como parámetro.
void HalfPlane2d::Transforma(const Trf2d &trf2d)
  { lim.Transforma(trf2d); }
