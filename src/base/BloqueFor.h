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
//BloqueFor.h
//Entidad con nombre.

#ifndef BLOQUEFOR_H
#define BLOQUEFOR_H

#include "BloqueWhile.h"

//! @ingroup BASE
//
//!  @brief Bloque For para Peell.
class BloqueFor: public BloqueWhile
  {
    friend class EntCmd;
  private:
    std::string inicio; //!< Valor de partida.
    std::string incremento; //!< Incremento.
  protected:
    bool continua(void) const;
    virtual bool procesa_comando(CmdStatus &status);
    BloqueFor(EntCmd *owner);
    BloqueFor(EntCmd *owner,const std::string &ini,const std::string &cont,const std::string &incr);
    const std::string &Inicio(void) const;
    const std::string &Cond(void) const;
    const std::string &Incremento(void) const;
  };

#endif
