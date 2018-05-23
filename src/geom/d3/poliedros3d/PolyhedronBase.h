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
//POLYHEDRONBASE.h

#ifndef POLYHEDRONBASE_H
#define POLYHEDRONBASE_H

#include <iostream>
#include "../GeomObj3d.h"

class SemiEspacio3d;


//! @ingroup GEOM
//
//! @brief Tetraedro.
class PolyhedronBase: public GeomObj3d
  {
  public:
    inline virtual unsigned short int Dimension(void) const
      { return 3; }
    virtual GEOM_FT Longitud(void) const;
    virtual GEOM_FT Volumen(void) const;
    virtual GEOM_FT Ix(void) const;
    virtual GEOM_FT Iy(void) const;
    virtual GEOM_FT Iz(void) const;
    virtual Pos3d getCenterOfMass(void) const;
  };


#endif
