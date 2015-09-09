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
//SisCooRect1d2d.h
//Sistema de coordenadas de una dimensión en un espacio de 3 dimensiones.

#ifndef SISCOORECT1D2D_H
#define SISCOORECT1D2D_H

#include "SisCooXd2d.h"

//! @ingroup SisCoo
//
//! @brief Sistema de coordenadas de 1 dimensión
//! definido en un espacio de dos dimensiones.
class SisCooRect1d2d: public SisCooXd2d
  {
  protected:
    virtual bool procesa_comando(CmdStatus &status);
  public:
    typedef GEOM_FT VLocal; //Dimensión del vector en locales.
    typedef GEOM_FT PLocal; //Dimensión del vector en locales.

    SisCooRect1d2d(void): SisCooXd2d(1) {}
    SisCooRect1d2d(const PGlobal &o,const PGlobal &p);
    SisCooRect1d2d(const VGlobal &vX);
    virtual SisCoo *Copia(void) const
      { return new SisCooRect1d2d(*this); }

    VGlobal GetI(void) const; //Devuelve el vector unitario I en el sistema global.

    VGlobal GetCooGlobales(const VLocal &v) const;
    VLocal GetCooLocales(const VGlobal &v) const;
    virtual any_const_ptr GetProp(const std::string &cod) const;
    virtual ~SisCooRect1d2d(void)
      {}
  };

#endif
