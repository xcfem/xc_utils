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
//SisCooRect1d2d.cc

#include "SisCooRect1d2d.h"
#include "xc_utils/src/geom/pos_vec/Pos2d.h"
#include "xc_utils/src/geom/pos_vec/Vector2d.h"
#include "xc_utils/src/geom/pos_vec/Dir2d.h"

#include "xc_basic/src/text/text_string.h"
#include "xc_basic/src/funciones/algebra/ExprAlgebra.h"


SisCooRect1d2d::SisCooRect1d2d(const VGlobal &vX)
  : SisCooXd2d(1,vX) {} //Eje 1 paralelo a Vx.
SisCooRect1d2d::SisCooRect1d2d(const PGlobal &p1,const PGlobal &p2)
  : SisCooXd2d(1,p1,p2) {} //Eje 1 desde p1 a p2.

SisCooRect1d2d::VGlobal SisCooRect1d2d::GetI(void) const
//Return el vector unitario I en el sistema global.
  { return GetVDirEje(1); }
SisCooRect1d2d::VGlobal SisCooRect1d2d::GetCooGlobales(const VLocal &v) const
//Return las componentes del vector v 
//que se pasa como parámetro expresado en locales
//expresadas en coordenadas globales.
  { return SisCooXd2d::GetCooGlobales(matriz_FT(1,1,v)); }
SisCooRect1d2d::VLocal SisCooRect1d2d::GetCooLocales(const SisCooRect1d2d::VGlobal &v) const
//Return las componentes del vector v expresado en locales
//expresadas en coordenadas globales.
  {
    const matriz_FT tmp= SisCooXd2d::GetCooLocales(v);
    return tmp(1,1);
  }

