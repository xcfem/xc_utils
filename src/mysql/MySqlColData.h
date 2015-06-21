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
//MySqlColData.h
//Entidad para conexiones con MySql.

#ifndef MYSQLCOLDATA_H
#define MYSQLCOLDATA_H

#include "MySqlObject.h"

//! @ingroup MYSQL
//
//!  @brief Dato de una fila de una tabla MySql.
class MySqlColData: public MySqlObject
  {
    mysqlpp::String dat; //!< Dato de una fila de una tabla MySql.
  protected:
    bool procesa_comando(CmdStatus &status);
  public:
    MySqlColData(MySqlConnection *ptr_conex);
    MySqlColData(const mysqlpp::String &cd,MySqlConnection *ptr_conex);
    MySqlObject *getCopy(void) const;
    any_const_ptr GetProp(const std::string &) const;
  };
#endif
