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
//EntPropSorter.h

#ifndef ENTPROPSORTER_H
#define ENTPROPSORTER_H

#include <string>

class EntProp;

//! @ingroup NUCLEO
//
//! @brief Clase para ordenar objetos EntProp
//! por el valor de una propiedad.
class EntPropSorter
  {
    std::string cod;
    friend class EntProp;
  protected:
    EntPropSorter(const std::string &c= "");
    void set_cod(const std::string &c= "")
      { cod= c; }
    bool menor(const EntProp &a,const EntProp &b) const;
    bool menor(const EntProp *a,const EntProp *b) const;
    bool mayor(const EntProp &a,const EntProp &b) const;
    bool mayor(const EntProp *a,const EntProp *b) const;
  };

#endif
