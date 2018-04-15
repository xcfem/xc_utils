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
//SisCooRect3d3d.h
//Sistema de coordenadas rectangular en 3 dimensiones en un espacio de tres
//dimensiones.

#ifndef SIS_COO_RECT3D3D_H
#define SIS_COO_RECT3D3D_H

#include "SisCooXd3d.h"

//! @ingroup SisCoo
//
//! @brief Sistema de coordenadas de tres dimensiones
//! definido en un espacio de tres dimensiones.
class SisCooRect3d3d: public SisCooXd3d
  {
  public:
    typedef Vector3d VLocal; //Dimensión del vector en locales.
    typedef Pos3d PLocal; //Dimensión del vector en locales.
  public:
    SisCooRect3d3d(void): SisCooXd3d(3) {}
    SisCooRect3d3d(const SisCooRect3d3d &otro)
      : SisCooXd3d(otro) {}
    SisCooRect3d3d(const PGlobal &o,const PGlobal &p);
    SisCooRect3d3d(const PGlobal &p1,const PGlobal &p2, const PGlobal &p3);
    SisCooRect3d3d(const VGlobal &v1,const VGlobal &v2,const VGlobal &v3);
    SisCooRect3d3d(const VGlobal &v1,const VGlobal &v2);
    virtual SisCoo *Copia(void) const
      { return new SisCooRect3d3d(*this); }
    virtual SisCooXd3d *CopiaXd3d(void) const
      { return new SisCooRect3d3d(*this); }

    VGlobal GetI(void) const; //Return el vector unitario I en el sistema global.
    VGlobal GetJ(void) const; //Return el vector unitario J en el sistema global.
    VGlobal GetK(void) const; //Return el vector unitario K en el sistema global.

    VGlobal GetCooGlobales(const VLocal &v) const;
    VLocal GetCooLocales(const VGlobal &v) const;
    virtual ~SisCooRect3d3d(void)
      {}
  };

#endif
