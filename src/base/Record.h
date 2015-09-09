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
//Record.h

#ifndef RECORD_H
#define RECORD_H

#include "xc_utils/src/base/EntWOwner.h"

//MEJORAR. Debería tener un puntero a la definición del registro.

//! @ingroup BASE
//
//! @brief Objeto que se usa como propiedad que contiene propiedades.
class Record: public EntWOwner
  {
  protected:
    virtual bool procesa_comando(CmdStatus &status);
  public:
    Record(EntCmd *owr= NULL, const std::string &b= "");
    MapParam::param_iterator crea_user_prop(const std::string &,const boost::any &);
    std::string sqlNames(void) const;
    std::string sqlValues(void) const;
    virtual any_const_ptr GetProp(const std::string &cod) const;
    friend std::ostream &operator<<(std::ostream &,const Record &);
  };

std::ostream &operator<<(std::ostream &,const Record &);

#endif
