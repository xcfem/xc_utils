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
//MySqlQuery.h
//Entidad para conexiones con MySql.

#ifndef MYSQLQUERY_H
#define MYSQLQUERY_H

#include "MySqlObject.h"

class MySqlConnection;

//! @ingroup MYSQL
//
//!  @brief Consulta MySql.
class MySqlQuery: public MySqlObject
  {
    //Hacemos la conexión mutable porque la clase Query no tiene
    //miembros constantes.
    mutable mysqlpp::Query q; //!< Consulta MySql.

  protected:
    bool procesa_comando(CmdStatus &status);
  public:
    MySqlQuery(const MySqlConnection &con,const bool &ue,MySqlConnection *ptr_conex);
    MySqlQuery(const mysqlpp::Query &q,MySqlConnection *ptr_conex);
    virtual MySqlObject *getCopy(void) const;
    any_const_ptr GetProp(const std::string &) const;
  };
#endif
