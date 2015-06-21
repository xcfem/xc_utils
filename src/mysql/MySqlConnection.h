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
//MySqlConnection.h
//Entidad para conexiones con MySql.

#ifndef MYSQLCONNECTION_H
#define MYSQLCONNECTION_H

#include "MySqlObject.h"

//! @ingroup MYSQL
//
//!  @brief Clase para conexión de MySql.
class MySqlConnection: public MySqlObject
  {
  public:
    typedef std::map<std::string,MySqlObject *> map_sql_objs;//!< Contenedor de objetos de base de datos.
    typedef map_sql_objs::iterator sql_objs_iterator;//!< Iterador a objetos de base de datos.
    typedef map_sql_objs::const_iterator sql_objs_const_iterator;//!< Iterador a objetos de base de datos.
  private:
    //Hacemos la conexión mutable porque la clase Connection no tiene
    //miembros constantes.
    friend class MySqlQuery;
    mutable mysqlpp::Connection con; //!< Conexión con MySql.
    map_sql_objs mySqlObjs;//!< Contenedor de objetos de MySql++.

    void copia_objetos(const map_sql_objs &otro);
    void borra_objetos(void);
    bool conecta(const std::vector<std::string> &params);

    bool procesa_comando_obj_mysql(const std::string &cmd,CmdStatus &status);

    void InsertaObjeto(const std::string &,MySqlObject *ptr);
    void BorraObjeto(const std::string &nmb);
  protected:
    bool procesa_comando(CmdStatus &status);
  public:
    MySqlConnection(const bool &ue= true);
    MySqlConnection(const MySqlConnection &);
    MySqlConnection &operator=(const MySqlConnection &);
    virtual MySqlObject *getCopy(void) const;
    virtual void NuevoObjetoSql(const std::string &nmb,MySqlObject *ptr);
    virtual void NuevoObjetoSql(const std::string &nmb,const MySqlObject &ref);
    virtual void BorraObjetoSql(const std::string &nmb);
    any_const_ptr GetProp(const std::string &) const;
    virtual ~MySqlConnection(void);
  };
#endif
