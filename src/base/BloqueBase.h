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
//BloqueBase.h
//Entidad con nombre.

#ifndef BLOQUEBASE_H
#define BLOQUEBASE_H

#include "EntWOwner.h"

//! @ingroup BASE
//
//!  @brief Bloque de instrucciones para Peell.
class BloqueBase: public EntWOwner
  {
    friend class EntCmd;
    friend boost::any interpreta_string_to_boost_any(EntCmd &,const std::string &,const std::string &,const std::string &,const std::string &);
  protected:
    std::string nombre; //!< Nombre del bloque de instrucciones.
    std::string bloque; //!< Bloque de instrucciones a ejecutar.
    virtual bool procesa_comando(CmdStatus &status);
    //! @brief Constructor.
    BloqueBase(EntCmd *owr, const std::string &nmb, const std::string &b= "");
    
    const std::string &getNombre(void) const;
    const std::string &Bloque(void) const;
    any_const_ptr GetProp(const std::string &cod) const;
  };

#endif
