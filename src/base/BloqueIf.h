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
//BloqueIf.h
//Entidad con nombre.

#ifndef BLOQUEIF_H
#define BLOQUEIF_H

#include "BloqueCond.h"

//! @ingroup BASE
//
//!  @brief Bloque If para Peell.
class BloqueIf: public BloqueCond
  {
    friend class EntCmd;
  protected:
    std::string bloque_else; //!< Bloque de instrucciones a ejecutar si la condición resulta verdadera.

    virtual bool procesa_comando(CmdStatus &status);
    //! @brief Constructor.
    BloqueIf(EntCmd *owner);
    BloqueIf(EntCmd *owner,const std::string &,const std::string &thn="",const std::string &els="");
    const std::string &BloqueThen(void) const;
    const std::string &BloqueElse(void) const;
  };

#endif
