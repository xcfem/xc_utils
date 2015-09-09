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
//BloqueSwitchStr.h
//Entidad con nombre.

#ifndef BLOQUESWITCHSTR_H
#define BLOQUESWITCHSTR_H

#include "BloqueCond.h"

//! @ingroup BASE
//
//!  @brief Bloque If para Peell.
class BloqueSwitchStr: public BloqueCond
  {
    friend class EntCmd;
  protected:
    std::map<std::string,std::string> bloques; //!< Bloques de instrucciones.

    virtual bool procesa_comando(CmdStatus &status);
    //! @brief Constructor.
    BloqueSwitchStr(EntCmd *owner);
    BloqueSwitchStr(EntCmd *owner,const std::string &,const std::string &def="");
    bool hasCase(const std::string &idx) const;
    const std::string &Bloque(const std::string &idx) const;
  };

#endif
