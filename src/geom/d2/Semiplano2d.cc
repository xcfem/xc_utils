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
//Semiplano2d.cc

#include "Semiplano2d.h"
#include "GmGrupo2d.h"
#include "xc_utils/src/geom/d1/SemiRecta2d.h"
#include "xc_utils/src/geom/d1/Segmento2d.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "../pos_vec/Dir2d.h"
#include "../pos_vec/Vector2d.h"

Semiplano2d::Semiplano2d(void)
  : Superficie2d(), lim() {}

Semiplano2d::Semiplano2d(const Recta2d &r)
  : Superficie2d(), lim(r) {}

Semiplano2d::Semiplano2d(const Recta2d &r, const Pos2d &p)
  : Superficie2d(), lim(r)
  {
    if(!In(p))
      Swap();
  }

Semiplano2d::Semiplano2d(const Pos2d &p1,const Pos2d &p2)
  : Superficie2d(), lim(p1,p2) {}
Semiplano2d::Semiplano2d(const Semiplano2d &sp)
  : Superficie2d(sp),lim(sp.lim) {}
Semiplano2d &Semiplano2d::operator=(const Semiplano2d &sp)
  {
    Superficie2d::operator=(sp);
    lim= sp.lim;
    return *this;
  }

GeomObj *Semiplano2d::clon(void) const
  { return new Semiplano2d(*this); }
void Semiplano2d::Swap(void)
  { lim.Swap(); }

bool Semiplano2d::procesa_comando(CmdStatus &status)
  {
    Pos2d o,d;
    if(status.Cmd() == "recta")
      {
        lim.LeeCmd(status);
        (*this)= Semiplano2d(lim);
        return true;
      }
    else
      return Superficie2d::procesa_comando(status);
  }

bool Semiplano2d::Interseca(const SemiRecta2d &sr) const
  { return sr.Interseca(lim); }
bool Semiplano2d::Interseca(const Segmento2d &sg) const
  { return sg.Interseca(lim); }

Semiplano2d Semiplano2d::GetSwap(void) const
  {
    Semiplano2d retval(*this);
    retval.Swap();
    return retval;
  }

GmGrupo2d Semiplano2d::Interseccion(const Recta2d &r) const
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

GmGrupo2d Semiplano2d::Interseccion(const SemiRecta2d &sr) const
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

GmGrupo2d Semiplano2d::Interseccion(const Segmento2d &sg) const
  {
    GmGrupo2d retval;
    if(!Interseca(sg)) return retval;
    GeomObj::list_Pos2d lista= interseccion(lim,sg);
    const Pos2d pint= *lista.begin();
    const Pos2d p1= sg.Destino();
    const Pos2d p2= sg.Origen();
    if(In(p1))
      retval.push_back(Segmento2d(pint,p1));
    else
      retval.push_back(Segmento2d(pint,p2));
    return retval;
  }

GmGrupo2d interseccion(const Semiplano2d &sp,const Recta2d &r)
  { return sp.Interseccion(r); }
GmGrupo2d interseccion(const Semiplano2d &sp,const SemiRecta2d &sr)
  { return sp.Interseccion(sr); }
GmGrupo2d interseccion(const Semiplano2d &sp,const Segmento2d &sg)
  { return sp.Interseccion(sg); }
GmGrupo2d interseccion(const Recta2d &r,const Semiplano2d &sp)
  { return interseccion(sp,r); }
GmGrupo2d interseccion(const SemiRecta2d &sr,const Semiplano2d &sp)
  { return interseccion(sp,sr); }
GmGrupo2d interseccion(const Segmento2d &sg,const Semiplano2d &sp)
  { return interseccion(sp,sg); }

Semiplano2d Semiplano2d::getNormalizado(void) const
  { return Semiplano2d(lim.getNormalizada()); }

//! @brief Aplica al objeto la transformación que se
//! pasa como parámetro.
void Semiplano2d::Transforma(const Trf2d &trf2d)
  { lim.Transforma(trf2d); }
