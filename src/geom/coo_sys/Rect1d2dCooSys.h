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
//Rect1d2dCooSys.h
//One dimensional coordinate system defined in a three-dimensional space.

#ifndef SISCOORECT1D2D_H
#define SISCOORECT1D2D_H

#include "Xd2dCooSys.h"

//! @ingroup CooSys
//
//! @brief One dimensional coordinate system defined in a three-dimensional
//! space.
class Rect1d2dCooSys: public Xd2dCooSys
  {
  public:
    typedef GEOM_FT VLocal; //Vector type in local system.
    typedef GEOM_FT PLocal; //Point type in local system.

    Rect1d2dCooSys(void): Xd2dCooSys(1) {}
    Rect1d2dCooSys(const PGlobal &o,const PGlobal &p);
    Rect1d2dCooSys(const VGlobal &vX);
    virtual CooSys *Copia(void) const
      { return new Rect1d2dCooSys(*this); }

    VGlobal GetI(void) const; //Return global coordinates of unit vector I.

    VGlobal GetCooGlobales(const VLocal &v) const;
    VLocal GetCooLocales(const VGlobal &v) const;
    virtual ~Rect1d2dCooSys(void)
      {}
  };

#endif
