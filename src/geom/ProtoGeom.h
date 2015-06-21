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
//ProtoGeom.h

#ifndef PROTOGEOM_H
#define PROTOGEOM_H

#include "xc_utils/src/nucleo/EntCmd.h"

//! @defgroup GEOM Entidades geométricas.
//
//! @ingroup GEOM
//
//! @brief Clase base para redefinir el método printprop
class ProtoGeom: public EntCmd
  {
  private:
    bool exts; //! False when solution is not possible: intersection of parallel planes.
  protected:
    virtual void printprop(std::ostream *out_file,const any_const_ptr &nmb_prop) const;
  public:
    ProtoGeom(void);
    virtual void Print(std::ostream &os) const;
    virtual ~ProtoGeom(void) {}
    inline void setExists(bool e)
      { exts= e; }
    bool exists(void) const
      { return exts; }
  };

#endif
