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
//Dir3d.h

#ifndef DIR3D_H
#define DIR3D_H

#include "../tipos_cgal.h"

class Vector3d;
class matriz_FT;


//! @ingroup GEOM
//
//! @brief Dirección en el espacio de tres dimensiones.
class Dir3d
  {
    CGDirection_3 cgd;
  public:
    Dir3d(const CGDirection_3 &d)
      : cgd(d) {}
    Dir3d(GEOM_FT x,GEOM_FT y,GEOM_FT z);
    Dir3d(const Vector3d &v);
    const CGDirection_3 &ToCGAL(void) const
      { return cgd; }
    void Neg(void)
      { cgd=-cgd; }
    inline GEOM_FT operator()(const size_t &i) const
      { return cgd.delta(i-1); }
    inline GEOM_FT dx(void) const
      { return cgd.dx(); }
    inline GEOM_FT dy(void) const
      { return cgd.dy(); }
    inline GEOM_FT dz(void) const
      { return cgd.dz(); }
    matriz_FT GetMatriz(void) const;
    Vector3d GetVector(void) const;
    inline friend bool operator==(const Dir3d &v1,const Dir3d &v2)
      { return (v1.cgd==v2.cgd); }
    friend std::ostream &operator << (std::ostream &stream,const Dir3d &n);
    inline virtual ~Dir3d(void) {}
  };

inline bool paralelas(const Dir3d &v1,const Dir3d &v2)
  { return (v1==v2); } 

#endif
