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
//SisCooRect3d3d.cc

#include "SisCooRect3d3d.h"
#include "../pos_vec/Pos3d.h"
#include "../pos_vec/Vector3d.h"

SisCooRect3d3d::SisCooRect3d3d(const VGlobal &v1,const VGlobal &v2)
  : SisCooXd3d(3,v1,v2) {}
SisCooRect3d3d::SisCooRect3d3d(const PGlobal &o,const PGlobal &p)
  : SisCooXd3d(3,o,p) {}
SisCooRect3d3d::SisCooRect3d3d(const PGlobal &p1,const PGlobal &p2, const PGlobal &p3)
  : SisCooXd3d(3,p1,p2,p3) {}
SisCooRect3d3d::SisCooRect3d3d(const VGlobal &v1,const VGlobal &v2,const VGlobal &v3)
  : SisCooXd3d(3,v1,v2,v3) {}
SisCooRect3d3d::VGlobal SisCooRect3d3d::GetI(void) const
//Return el vector unitario I en el sistema global.
  { return getAxisVDir(1); }
SisCooRect3d3d::VGlobal SisCooRect3d3d::GetJ(void) const
//Return el vector unitario J en el sistema global.
  { return getAxisVDir(2); }
SisCooRect3d3d::VGlobal SisCooRect3d3d::GetK(void) const
//Return el vector unitario K en el sistema global.
  { return getAxisVDir(3); }
SisCooRect3d3d::VGlobal SisCooRect3d3d::GetCooGlobales(const VLocal &v) const
//Return las componentes del vector v expresado en locales
//expresadas en coordenadas globales.
  { return SisCooXd3d::GetCooGlobales(v.getMatrix()); }
SisCooRect3d3d::VLocal SisCooRect3d3d::GetCooLocales(const VGlobal &v) const
//Return las componentes del vector v expresado en locales
//expresadas en coordenadas globales.
  {
    const FT_matrix tmp= SisCooXd3d::GetCooLocales(v);
    return VLocal(tmp(1),tmp(2),tmp(3));
  }

