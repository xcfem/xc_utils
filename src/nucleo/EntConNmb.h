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
    std::string nmb; //!< @brief Nombre del objeto.
  public:
    //! @brief Constructor.
  EntConNmb(const std::string &Nombre="",EntCmd *owr= nullptr)
      : EntCmd(owr), nmb(Nombre) {}
    //! @brief Devuelve el nombre del objeto.
    const std::string &GetNombre(void) const
      { return nmb; }
    //! @brief Asigna el nombre del objeto.
    void SetNombre(const std::string &s)
      { nmb= s; }
    //! @brief Devuelve una referencia al nombre del objeto.
    std::string &Nombre(void)
      { return nmb; }
    //! @brief Compara el nombre del elemento con un nombre dado.
    int operator==(const EntConNmb &otro) const
      { return (nmb==otro.nmb); }
    //! @brief Operador menor.
    int operator<(const EntConNmb &otro) const
      { return (nmb<otro.nmb); }
  };

#endif
