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
//MapAuxData.cxx

#include "MapAuxData.h"
#include <iostream>

//! @brief Constructor por defecto.
MapAuxData::MapAuxData(void)
  {}

//! @brief Lista los punteros a datos auxiliares.
void MapAuxData::ListaAuxData(std::ostream &os) const
  {
    for(const_iterator i= aux_data.begin();i!=aux_data.end();i++)
      os << (*i).first << ": "<< reinterpret_cast<size_t>((*i).second) << std::endl;
  }

//! @brief Borra los punteros a datos auxiliares.
void MapAuxData::BorraAuxData(void)
  { aux_data.clear(); }

//! @brief Borra el puntero a datos auxiliares cuyo identificador se pasa como parámetro.
void MapAuxData::BorraAuxData(const std::string &clave)
  { aux_data.erase(clave); }

//! @brief Inserta el puntero a datos auxiliares cuyo identificador se pasa como parámetro.
void *MapAuxData::inserta(const std::string &id,void *ptr)
  { 
    aux_data[id]= ptr;
    return ptr;
  }

void *MapAuxData::operator[](const std::string &clave)
  { return aux_data[clave]; }

const void *MapAuxData::operator[](const std::string &clave) const
  {
    const void *retval= NULL;
    const_iterator i= aux_data.find(clave);
    if(i!=aux_data.end())
      retval= (*i).second;
    return retval;
  }
