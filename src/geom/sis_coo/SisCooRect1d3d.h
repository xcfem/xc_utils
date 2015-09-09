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
//SisCooRect1d3d.h
//Sistema de coordenadas de una dimensión en un espacio de 3 dimensiones.

#ifndef SISCOORECT1D3D_H
#define SISCOORECT1D3D_H

#include "SisCooXd3d.h"

//! @ingroup SisCoo
//
//! @brief Sistema de coordenadas de 1 dimensión
//! definido en un espacio de tres dimensiones.
class SisCooRect1d3d: public SisCooXd3d
  {
  public:
    typedef GEOM_FT VLocal; //Dimensión del vector en locales.
    typedef GEOM_FT PLocal; //Dimensión del punto en locales.

  protected:
    virtual bool procesa_comando(CmdStatus &status);
  public:
    SisCooRect1d3d(void): SisCooXd3d(1) {}
    SisCooRect1d3d(const PGlobal &o,const PGlobal &p);
    SisCooRect1d3d(const VGlobal &vX);
    virtual SisCoo *Copia(void) const
      { return new SisCooRect1d3d(*this); }
    virtual SisCooXd3d *CopiaXd3d(void) const
      { return new SisCooRect1d3d(*this); }
    void VectorEjeX(const VGlobal &vX);
    VGlobal GetI(void) const; //Devuelve el vector unitario I en el sistema global.
    VGlobal GetCooGlobales(const VLocal &v) const;
    VLocal GetCooLocales(const VGlobal &v) const;
    any_const_ptr GetProp(const std::string &cod) const;
    virtual ~SisCooRect1d3d(void)
      {}
  };

#endif
