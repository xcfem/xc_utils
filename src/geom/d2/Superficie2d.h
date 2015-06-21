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
//Superficie2d.h

#ifndef SUPERFICIE2D_H
#define SUPERFICIE2D_H

#include "../d2/GeomObj2d.h"

class Pos2d;

//! @ingroup GEOM
//
//! @brief Clase base para las superficies en dos dimensiones.
class Superficie2d : public GeomObj2d
  {
  public:
    Superficie2d(void): GeomObj2d(){}
    inline virtual unsigned short int Dimension(void) const
    //Devuelve la dimensión del objeto 0, 1, 2 ó 3.
      { return 2; }
    virtual GEOM_FT Longitud(void) const
      { return 0.0; }
    GEOM_FT Perimetro(void) const
      { return Longitud(); }
    virtual GEOM_FT Area(void) const;
    virtual GEOM_FT Volumen(void) const
      { return 0.0; }
    virtual inline GEOM_FT IArea(void) const
      { return Area(); }
    //Devuelve verdadero si el punto esta sobre la Superficie.
    virtual bool In(const Pos2d &p, const double &tol= 0.0) const= 0;
    virtual any_const_ptr GetProp(const std::string &cod) const;
  };
#endif



