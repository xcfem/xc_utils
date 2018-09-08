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
//Rect3d3dCooSys.h
//Sistema de coordenadas rectangular en 3 dimensiones en un espacio de tres
//dimensiones.

#ifndef RECT3D3D_COO_SYS_H
#define RECT3D3D_COO_SYS_H

#include "Xd3dCooSys.h"

//! @ingroup CooSys
//
//! @brief Sistema de coordenadas de tres dimensiones
//! definido en un espacio de tres dimensiones.
class Rect3d3dCooSys: public Xd3dCooSys
  {
  public:
    typedef Vector3d VLocal; //Dimensión del vector en locales.
    typedef Pos3d PLocal; //Dimensión del vector en locales.
  public:
    Rect3d3dCooSys(void): Xd3dCooSys(3) {}
    Rect3d3dCooSys(const Rect3d3dCooSys &other)
      : Xd3dCooSys(other) {}
    Rect3d3dCooSys(const PGlobal &o,const PGlobal &p);
    Rect3d3dCooSys(const PGlobal &p1,const PGlobal &p2, const PGlobal &p3);
    Rect3d3dCooSys(const VGlobal &v1,const VGlobal &v2,const VGlobal &v3);
    Rect3d3dCooSys(const VGlobal &v1,const VGlobal &v2);
    virtual CooSys *Copia(void) const
      { return new Rect3d3dCooSys(*this); }
    virtual Xd3dCooSys *CopiaXd3d(void) const
      { return new Rect3d3dCooSys(*this); }

    VGlobal GetI(void) const; //Return el vector unitario I en el sistema global.
    VGlobal GetJ(void) const; //Return el vector unitario J en el sistema global.
    VGlobal GetK(void) const; //Return el vector unitario K en el sistema global.

    VGlobal GetCooGlobales(const VLocal &v) const;
    VLocal GetCooLocales(const VGlobal &v) const;
    virtual ~Rect3d3dCooSys(void)
      {}
  };

#endif
