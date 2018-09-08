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
//Rect2d3dCooSys.h
//Sistema de coordenadas rectangular de 2 dimensiones
//en un espacio de tres dimensiones.

#ifndef RECT2D_COO_SYS_H
#define RECT2D_COO_SYS_H

#include "Xd3dCooSys.h"

class Vector2d;
class Pos2d;

//! @ingroup CooSys
//
//! @brief Sistema de coordenadas de dos dimensiones
//! definido en un espacio de tres dimensiones.
class Rect2d3dCooSys: public Xd3dCooSys
  {
  public:
    typedef Vector2d VLocal; //Vector dimension in local coordinates.
    typedef Pos2d PLocal; //Point dimension in local coordinates.

    Rect2d3dCooSys(void)
      : Xd3dCooSys(2) {}
    Rect2d3dCooSys(const VGlobal &v);
    Rect2d3dCooSys(const VGlobal &v1,const VGlobal &v2);
    Rect2d3dCooSys(const PGlobal &p1,const PGlobal &p2, const PGlobal &p3);
    Rect2d3dCooSys(const Rect2d3dCooSys &other)
      : Xd3dCooSys(other) {}
    Rect2d3dCooSys &operator=(const Rect2d3dCooSys &other)
      {
	Xd3dCooSys::operator=(other);
        return *this;
      }
    virtual CooSys *Copia(void) const
      { return new Rect2d3dCooSys(*this); }
    virtual Xd3dCooSys *CopiaXd3d(void) const
      { return new Rect2d3dCooSys(*this); }

    //Acceso a miembros.
    VGlobal GetI(void) const;
    VGlobal GetJ(void) const;

    VGlobal GetCooGlobales(const VLocal &v) const;
    VLocal GetCooLocales(const VGlobal &v) const;

    virtual ~Rect2d3dCooSys(void)
      {}
  };

#endif
