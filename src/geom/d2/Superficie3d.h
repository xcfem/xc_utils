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
//Superficie3d.h

#ifndef SUPERFICIE3D_H
#define SUPERFICIE3D_H

#include "../d3/GeomObj3d.h"


class Pos3d;


//! @ingroup GEOM
//
//! @brief Clase base para las superficies en 3D.
class Superficie3d : public GeomObj3d
  {
  public:
    Superficie3d(void): GeomObj3d(){}

    inline virtual unsigned short int Dimension(void) const
    //Return the dimension of the object 0, 1, 2 or 3.
      { return 2; }
    //! @brief Return the length of the object.
    virtual GEOM_FT getLength(void) const
      { return 0.0; }
    GEOM_FT Perimetro(void) const
      { return getLength(); }
    virtual GEOM_FT Area(void) const;
    virtual GEOM_FT Volumen(void) const
      { return 0.0; }
    virtual inline GEOM_FT IArea(void) const
      { return Area(); }
  };
#endif



