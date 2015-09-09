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
//MySqlObject.h
//Envoltorio para objetos de MySql++.

#ifndef MYSQLOBJECT_H
#define MYSQLOBJECT_H

#include "../nucleo/EntCmd.h"
#include <mysql++/mysql++.h>

class MySqlConnection;


//! @defgroup MYSQL Interfaz con la biblioteca MySql++.
//
//! @ingroup MYSQL
//
//!  @brief Clase base para objetos MySQL.
class MySqlObject: public EntCmd
  {
  protected:
    MySqlConnection *conexion;
    std::string preprocesa_str_sql(const std::string &str) const;
    bool procesa_comando(CmdStatus &status);
  public:
    MySqlObject(MySqlConnection *ptr_conex= NULL);
    virtual ~MySqlObject(void) {}
    virtual MySqlObject *getCopy(void) const= 0;
    virtual void NuevoObjetoSql(const std::string &nmb,MySqlObject *ptr);
    virtual void NuevoObjetoSql(const std::string &nmb,const MySqlObject &ref);
    virtual void BorraObjetoSql(const std::string &nmb);
    any_const_ptr GetProp(const std::string &) const;
  };
#endif
