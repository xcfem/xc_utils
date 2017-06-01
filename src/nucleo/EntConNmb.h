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
//EntConNmb.h
//Entidad con nombre.

#ifndef ENTCONNMB_H
#define ENTCONNMB_H

#include <string>
#include "EntCmd.h"

//! @ingroup CMDINTRP
//
//! @defgroup BASE Clases auxiliares del intérprete de comandos.
//
//! @ingroup BASE
//
//!  @brief Objeto identificado por un nombre.
class EntConNmb: public EntCmd
  {
  private:
    std::string name; //!< @brief Object name.
  public:
    //! @brief Constructor.
  EntConNmb(const std::string &Nombre="",EntCmd *owr= nullptr)
      : EntCmd(owr), name(Nombre) {}
    //! @brief Return the object name.
    const std::string &getName(void) const
      { return name; }
    //! @brief Set the  object name.
    void setName(const std::string &s)
      { name= s; }
    //! @brief Devuelve una referencia al nombre del objeto.
    std::string &Nombre(void)
      { return name; }
    //! @brief Compara el nombre del elemento con un nombre dado.
    int operator==(const EntConNmb &otro) const
      { return (name==otro.name); }
    //! @brief Operador menor.
    int operator<(const EntConNmb &otro) const
      { return (name<otro.name); }
  };

#endif
