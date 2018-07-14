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
//Dir2d.h

#ifndef DIR2D_H
#define DIR2D_H

#include "../cgal_types.h"
#include <iostream>

class Vector2d;
class FT_matrix;


//! @ingroup GEOM
//
//! @brief Dirección en dos dimensiones.
class Dir2d
  {
    CGDirection_2 cgd;
  public:
    Dir2d(const CGDirection_2 d): cgd(d) {}
    Dir2d(const GEOM_FT &x,const GEOM_FT &y);
    Dir2d(const double &ang);
    Dir2d(const Vector2d &v);
    const CGDirection_2 &ToCGAL(void) const
      { return cgd; }
    void Neg(void)
      { cgd= -cgd; }
    inline GEOM_FT operator()(const size_t &i) const
      { return cgd.delta(i-1); }
    inline GEOM_FT dx(void) const
      { return cgd.dx(); }
    inline GEOM_FT dy(void) const
      { return cgd.dy(); }
    inline Dir2d Perpendicular(void) const
      //Return la dirección perpendicular en sentido antihorario.
      { return Dir2d(-dy(),dx()); }
    FT_matrix getMatrix(void) const;
    Vector2d GetVector(void) const;
    friend std::ostream &operator << (std::ostream &stream,const Dir2d &n);
    friend bool operator==(const Dir2d &v1,const Dir2d &v2);
    inline virtual ~Dir2d(void) {}
  };
inline Dir2d operator-(const Dir2d &d)
  {
    Dir2d retval(d);
    retval.Neg();
    return retval;
  }

inline bool operator==(const Dir2d &v1,const Dir2d &v2)
  { return (v1.cgd==v2.cgd); }  
inline bool paralelas(const Dir2d &v1,const Dir2d &v2)
  { return ((v1==v2) || (v1==-v2)); } 

#endif
