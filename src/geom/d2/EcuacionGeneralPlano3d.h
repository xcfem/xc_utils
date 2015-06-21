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
//EcuacionGeneralPlano3d.h

#ifndef ECUACIONGENERALPLANO3D_H
#define ECUACIONGENERALPLANO3D_H

#include <vector>
#include "../tipos_cgal.h"

class Pos3d;
class Pos2d;

//! @ingroup GEOM
//
//! @brief Ecuación general del plano ax + by + cz + d = 0
//! siendo v[0]= d, v[1]= a, v[2]= b, v[3]= c.
class EcuacionGeneralPlano3d: private std::vector<GEOM_FT>
  {
    std::vector<GEOM_RT> v; //!< siendo v[0]= d, v[1]= a, v[2]= b, v[3]= c.
  public:
/*     EcuacionGeneralPlano3d(const GEOM_RT &a,const GEOM_RT &b,const GEOM_RT &c,const GEOM_RT &d); */
    EcuacionGeneralPlano3d(const GEOM_FT &fa,const GEOM_FT &fb,const GEOM_FT &fc,const GEOM_FT &fd);
    inline const GEOM_RT &a(void) const
      { return v[1]; }
    inline const GEOM_RT &b(void) const
      { return v[2]; }
    inline const GEOM_RT &c(void) const
      { return v[3]; }
    inline const GEOM_RT &d(void) const
      { return v[0]; }
    GEOM_FT Eval(const Pos3d &p) const;

    GEOM_FT x(const GEOM_FT &y,const GEOM_FT &z) const;
    GEOM_FT x(const Pos2d &p) const;
    GEOM_FT y(const GEOM_FT &x,const GEOM_FT &z) const;
    GEOM_FT y(const Pos2d &p) const;
    GEOM_FT z(const GEOM_FT &x,const GEOM_FT &y) const;
    GEOM_FT z(const Pos2d &p) const;
  };

#endif
