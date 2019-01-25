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
//NamedEntity.h
//Entidad con nombre.

#ifndef ENTCONNMB_H
#define ENTCONNMB_H

#include <string>
#include "CommandEntity.h"

//! @ingroup CMDINTRP
//
//! @defgroup BASE Auxiliary classes.
//
//! @ingroup BASE
//
//!  @brief Objeto identificado por un nombre.
class NamedEntity: public CommandEntity
  {
  private:
    std::string name; //!< @brief Object name.
  public:
    //! @brief Constructor.
  NamedEntity(const std::string &Nombre="",CommandEntity *owr= nullptr)
      : CommandEntity(owr), name(Nombre) {}
    //! @brief Return the object name.
    const std::string &getName(void) const
      { return name; }
    //! @brief Set the  object name.
    virtual void setName(const std::string &s)
      { name= s; }
    //! @brief Return a reference to the object name.
    virtual std::string &Name(void)
      { return name; }
    //! @brief Compara el nombre del elemento con un nombre dado.
    int operator==(const NamedEntity &other) const
      { return (name==other.name); }
    //! @brief Operador menor.
    int operator<(const NamedEntity &other) const
      { return (name<other.name); }
    NamedEntity &operator+=(const NamedEntity &);
    NamedEntity &operator-=(const NamedEntity &);
    NamedEntity &operator*=(const NamedEntity &);
  };

NamedEntity operator+(const NamedEntity &,const NamedEntity &);
NamedEntity operator-(const NamedEntity &,const NamedEntity &);
NamedEntity operator*(const NamedEntity &,const NamedEntity &);

#endif
