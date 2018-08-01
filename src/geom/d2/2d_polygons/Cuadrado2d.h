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
//Cuadrado2d.h

#ifndef CUADRADO_H
#define CUADRADO_H

#include "Cuadrilatero2d.h"


//! @ingroup GEOM
//
//! @brief Cuadrado en dos dimensiones.
class Cuadrado2d : public Cuadrilatero2d
  {
  public:
    Cuadrado2d(const GEOM_FT &l= 1.0)
      : Cuadrilatero2d(Pos2d(0,0),Pos2d(l,0),Pos2d(l,l),Pos2d(0,l)) {}
    Cuadrado2d(const Pos2d &o,const GEOM_FT &l= 1.0);
    //Cuadrado2d(const Ref2d &ref,const GEOM_FT &l= 1.0): PolygonalSurface(ref), lado(l) {}
    Cuadrado2d(const Cuadrado2d &c): Cuadrilatero2d(c) {}
    ~Cuadrado2d(void) {}
    Cuadrado2d &operator=(const Cuadrado2d &c)
      {
	Cuadrilatero2d::operator=(c);
        return *this;
      }
    virtual GeomObj *clon(void) const
      { return new Cuadrado2d(*this); }
/*     void Offset(const GEOM_FT &offset) */
/*       { lado+=2*offset; } */
/*     Cuadrado2d GetOffset(const GEOM_FT &offset) const */
/*       { */
/*         Cuadrado2d retval(*this); */
/*         retval.Offset(offset); */
/*         return retval; */
/*       } */
    

  };

#endif






