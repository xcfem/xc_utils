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
//SisCooRect2d3d.h
//Sistema de coordenadas rectangular de 2 dimensiones
//en un espacio de tres dimensiones.

#ifndef _SIS_COO_2DRECT_H
#define _SIS_COO_2DRECT_H

#include "SisCooXd3d.h"

class Vector2d;
class Pos2d;

//! @ingroup SisCoo
//
//! @brief Sistema de coordenadas de dos dimensiones
//! definido en un espacio de tres dimensiones.
class SisCooRect2d3d: public SisCooXd3d
  {
  public:
    typedef Vector2d VLocal; //Dimensión del vector en locales.
    typedef Pos2d PLocal; //Dimensión del punto en locales.

    SisCooRect2d3d(void)
      : SisCooXd3d(2) {}
    SisCooRect2d3d(const VGlobal &v);
    SisCooRect2d3d(const VGlobal &v1,const VGlobal &v2);
    SisCooRect2d3d(const PGlobal &p1,const PGlobal &p2, const PGlobal &p3);
    SisCooRect2d3d(const SisCooRect2d3d &otro)
      : SisCooXd3d(otro) {}
    SisCooRect2d3d &operator=(const SisCooRect2d3d &otro)
      {
	SisCooXd3d::operator=(otro);
        return *this;
      }
    virtual SisCoo *Copia(void) const
      { return new SisCooRect2d3d(*this); }
    virtual SisCooXd3d *CopiaXd3d(void) const
      { return new SisCooRect2d3d(*this); }

    //Acceso a miembros.
    VGlobal GetI(void) const;
    VGlobal GetJ(void) const;

    VGlobal GetCooGlobales(const VLocal &v) const;
    VLocal GetCooLocales(const VGlobal &v) const;

    virtual ~SisCooRect2d3d(void)
      {}
  };

#endif
