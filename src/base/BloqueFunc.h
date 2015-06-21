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
//BloqueFunc.h
//Función.

#ifndef BLOQUEFUNC_H
#define BLOQUEFUNC_H

#include "BloqueSub.h"
#include <boost/any.hpp>

//! @ingroup BASE
//
//!  @brief Bloque de instrucciones para Peell.
class BloqueFunc: public BloqueSub
  {
    friend boost::any interpreta_string_to_boost_any(EntCmd &,const std::string &,const std::string &,const std::string &,const std::string &);
  private:
    std::string tipo_retval; //!< Tipo del valor devuelto.
  protected:
    virtual bool procesa_comando(CmdStatus &status);

    //! @brief Constructor.
    BloqueFunc(EntCmd *owner, const std::string &nmb);
    BloqueFunc(EntCmd *owner, const std::string &nmb,const std::string &b,const std::string &def_args);
  public:
    BloqueFunc(const BloqueFunc &otro);
    BloqueFunc &operator=(const BloqueFunc &otro);
  };

#endif
