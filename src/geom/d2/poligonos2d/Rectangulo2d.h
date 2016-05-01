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
//Rectangulo2d.h

#ifndef RECTANGULO2D_H
#define RECTANGULO2D_H

#include "Cuadrilatero2d.h"

//! @ingroup GEOM
//
//! @brief Rectángulo en dos dimensiones.
class Rectangulo2d: public Cuadrilatero2d
  {
  public:
    Rectangulo2d(const double &b=1.0,const double &h=1.0): Cuadrilatero2d()
      {
        push_back(Pos2d(0,0));
        push_back(Pos2d(b,0));
        push_back(Pos2d(b,h));
        push_back(Pos2d(0,h));
      }
    Rectangulo2d(const Pos2d &o,const double &b=1.0,const double &h=1.0): Cuadrilatero2d()
      {
        push_back(o+Vector2d(0,0));
        push_back(o+Vector2d(b,0));
        push_back(o+Vector2d(b,h));
        push_back(o+Vector2d(0,h));
      }
      //Rectangulo2d(const Ref2d &ref, const double &b=1.0,const double &h=1.0) : Cuadrilatero2d(ref,b),altura(h) {}
    Rectangulo2d(const Rectangulo2d &r): Cuadrilatero2d(r) {}
    Rectangulo2d &operator=(const Rectangulo2d &r)
      {
	Cuadrilatero2d::operator=(r);
        return *this;
      }
    virtual GeomObj *clon(void) const
      { return new Rectangulo2d(*this); }
/*     void Offset(const double &offset) */
/*       { */
/* 	Cuadrilatero2d::Offset(offset); */
/*         altura+=2.0*offset; */
/*       } */
/*     Rectangulo2d GetOffset(const double &offset) const */
/*       { */
/*         Rectangulo2d retval(*this); */
/*         retval.Offset(offset); */
/*         return retval; */
/*       } */
/*     inline const double &Base(void) const */
/*       { return lado; } */
/*     inline double &Base(void) */
/*       { return lado; } */
/*     inline const double &Altura(void) const */
/*       { return altura; } */
/*     inline double &Altura(void) */
/*       { return altura; } */
  };

#endif





