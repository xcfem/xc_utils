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
//MEFSisCoo1DRect.cc

#include "SisCooRect1d3d.h"
#include "../pos_vec/Vector3d.h"
#include "../pos_vec/Dir3d.h"
#include "../pos_vec/Pos3d.h"



SisCooRect1d3d::SisCooRect1d3d(const VGlobal &vX)
  : SisCooXd3d(1,vX)  //Eje 1 paralelo a Vx.
  {}
SisCooRect1d3d::SisCooRect1d3d(const PGlobal &o,const PGlobal &p)
  : SisCooXd3d(1,o,p) {}

SisCooRect1d3d::VGlobal SisCooRect1d3d::GetI(void) const
//Return el vector unitario I en el sistema global.
  { return GetVDirEje(1); }
SisCooRect1d3d::VGlobal SisCooRect1d3d::GetCooGlobales(const VLocal &v) const
{ return SisCooXd3d::GetCooGlobales(matriz_FT(1,1,v)); }
SisCooRect1d3d::VLocal SisCooRect1d3d::GetCooLocales(const SisCooRect1d3d::VGlobal &v) const
//Return las componentes del vector v expresado en locales
//expresadas en coordenadas globales.
  {
    const matriz_FT tmp= SisCooXd3d::GetCooLocales(v);
    return VLocal(tmp(1));
  }

