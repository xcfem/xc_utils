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
//Linear2d.h

#ifndef LINEAR2D_H
#define LINEAR2D_H

#include <stdlib.h>
#include "../d2/GeomObj2d.h"


//! @ingroup GEOM
//
//! @brief Base class for the objects involving a single dimension
//! in a two-dimensional space.
class Linear2d : public GeomObj2d
  {
  public:
    Linear2d(void): GeomObj2d(){}
    Linear2d(const Linear2d &l): GeomObj2d(l){}
    ~Linear2d(void) {}
    Linear2d &operator=(const Linear2d &l)
      {
	GeomObj2d::operator=(l);
        return *this;
      }
    virtual GeomObj *clon(void) const= 0;
    inline virtual unsigned short int Dimension(void) const
      { return 1; }
    //! @brief Return the area of the object.
    virtual GEOM_FT getArea(void) const
      { return 0.0; }
    //! @brief Return the volume of the object.
    virtual GEOM_FT getVolume(void) const
      { return 0.0; }
    //@brief Return true if the points is on sobre la Linea.
    virtual bool In(const Pos2d &p, const double &tol= 0.0) const= 0;
  };
#endif



