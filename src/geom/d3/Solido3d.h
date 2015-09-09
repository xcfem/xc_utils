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
//Solido3d.h

#ifndef SOLIDO3D_H
#define SOLIDO3D_H

#include "GeomObj3d.h"

//! @ingroup GEOM
//
//! @brief Clase base para los sólidos en tres dimensiones.
class Solido3d : public GeomObj3d
  {
  public:
    Solido3d(void);
    virtual GEOM_FT dist(const Pos3d &p) const;
    virtual inline GEOM_FT IArea(void) const
      { return Volumen(); }
    virtual unsigned short int Dimension(void) const
      { return 3; }
    virtual void Print(std::ostream &os) const;
  };
#endif
