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
//MySqlConnection

#include "MySqlConnection.h"
#include "MySqlQuery.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include <vector>

//! @brief Copia los objetos de base de datos.
void MySqlConnection::copia_objetos(const map_sql_objs &otro)
  {
    borra_objetos();
    for(sql_objs_const_iterator i= otro.begin();i!=otro.end();i++)
      InsertaObjeto((*i).first,(*i).second);
  }

//! @brief Borra los objetos de base de datos.
void MySqlConnection::borra_objetos(void)
  {
    for(sql_objs_iterator i= mySqlObjs.begin();i!=mySqlObjs.end();i++)
      {
        if((*i).second)
          {
            delete (*i).second;
            (*i).second= NULL;
          }
        else
          std::cerr << "Se encontró un puntero nulo: '" << (*i).first << std::endl;
      }
    mySqlObjs.clear();
  }


//! @brief Constructor.
MySqlConnection::MySqlConnection(const bool &ue)
  : MySqlObject(NULL), con(ue) {}

//! @brief Constructor de copia.
MySqlConnection::MySqlConnection(const MySqlConnection &otro)
  : MySqlObject(otro), mySqlObjs()
  {
    // NO COPIAMOS LA CONEXIÓN, SE CREA UNA DISTINTA.
    if(!otro.mySqlObjs.empty())
      copia_objetos(otro.mySqlObjs);
  }

//! @brief Operador asignación.
MySqlConnection &MySqlConnection::operator=(const MySqlConnection &otro)
  {
    MySqlObject::operator=(otro);
    //con= otro.con; NO COPIAMOS LA CONEXIÓN, SE CREA UNA DISTINTA.
    if(!otro.mySqlObjs.empty())
      copia_objetos(otro.mySqlObjs);
    return *this;
  }


//! @brief Constructor virtual.
MySqlObject *MySqlConnection::getCopy(void) const
  { return new MySqlConnection(*this); }

//! @brief Conexión con MySql.
bool MySqlConnection::conecta(const std::vector<std::string> &params)
  {
    try
      {
        const size_t argc= params.size();
        if(argc == 1)
          return con.connect(params[0].c_str());
        else if(argc == 2)
          return con.connect(params[0].c_str(),params[1].c_str());
        else if(argc == 3)
          return con.connect(params[0].c_str(),params[1].c_str(),params[2].c_str());
        else if(argc == 4)
          return con.connect(params[0].c_str(),params[1].c_str(),params[2].c_str(),params[3].c_str());
        else
          {
	    std::cerr << "MySqlConnection::conecta; número incorrecto de parámetros, "
                      << "se esperaban 1,2,3 ó 4, se obtuvieron: " << argc << std::endl;
            return false;
          }
      }
    catch(const mysqlpp::BadQuery& er)
      {
	// Handle any query errors
	std::cerr << "Query error: " << er.what() << std::endl;
	return 1;
      }
    catch(const mysqlpp::BadConversion& er)
      {
	// Handle bad conversions
	std::cerr << "Conversion error: " << er.what() << std::endl
                  << "\tretrieved data size: " << er.retrieved
                  << ", actual size: " << er.actual_size << std::endl;
	return 1;
      }
    catch(const mysqlpp::Exception& er)
      {
	// Catch-all for any other MySQL++ exceptions
	std::cerr << "Error: " << er.what() << std::endl;
        return 1;
      }
  }

//! @brief Procesa un comando que se refiere a un objeto de mySqlObjs
bool MySqlConnection::procesa_comando_obj_mysql(const std::string &cmd,CmdStatus &status)
  {
    const sql_objs_iterator i= mySqlObjs.find(cmd);
    if(i!= mySqlObjs.end()) //Encuentra el objeto al que se refiere el comando.
      {
        (*i).second->LeeCmd(status);
        return true;
      }
    else
      return false;
  }

//! @brief Lectura del objeto desde archivo.
bool MySqlConnection::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(MySqlConnection) Procesando comando: " << cmd << std::endl;
    if(cmd == "connect") //Conecta con base de datos.
      {
        conecta(crea_vector_string(status.GetBloque()));
        return true;
      }
    else if(cmd == "disconnect") //Cierra la conexión con la base de datos.
      {
        con.disconnect();
        return true;
      }
    else if(cmd == "create_db") //Crea una base de datos.
      {
        con.create_db(interpretaString(status.GetBloque()));
        return true;
      }
    else if(cmd == "drop_db") //Borra una base de datos.
      {
        con.drop_db(interpretaString(status.GetBloque()));
        return true;
      }
    else if(cmd == "select_db") //Selecciona una base de datos.
      {
        con.select_db(interpretaString(status.GetBloque()));
        return true;
      }
    else if(cmd == "create_query") //Crea una consulta.
      {
        const std::string nmb= interpretaString(status.GetBloque()); //Nombre de la consulta.
        NuevoObjetoSql(nmb,MySqlQuery(con.query(),this));
        return true;
      }
    else if(procesa_comando_obj_mysql(cmd,status))
      return true;
    else
      return MySqlObject::procesa_comando(status);
  }

//! @brief Devuelve la propiedad del objeto cuyo código se pasa 
//! como parámetro. 
any_const_ptr MySqlConnection::GetProp(const std::string &cod) const 
  {
    if(cod=="connected")
      {
        tmp_gp_bool= con.connected();
        return any_const_ptr(tmp_gp_bool);
      }
    else if(cod=="info")
      {
        tmp_gp_str= con.ipc_info();
        return any_const_ptr(tmp_gp_str);
      }
//     else if(cod=="success")
//       {
//         tmp_gp_bool= con.success();
//         return any_const_ptr(tmp_gp_bool);
//       }
    else if(cod=="errnum")
      {
        tmp_gp_int= con.errnum();
        return any_const_ptr(tmp_gp_int);
      }
    else
      return MySqlObject::GetProp(cod);
  }

//! @brief Almacena el nuevo objeto con el nombre que se pasa como parametro.
void MySqlConnection::NuevoObjetoSql(const std::string &nmb,MySqlObject *ptr)
  { InsertaObjeto(nmb,ptr->getCopy()); }

//! @brief Almacena el nuevo objeto con el nombre que se pasa como parametro.
void MySqlConnection::NuevoObjetoSql(const std::string &nmb,const MySqlObject &ref)
  { InsertaObjeto(nmb,ref.getCopy()); }

//! @brief Borra el objeto con el nombre que se pasa como parametro.
void MySqlConnection::BorraObjetoSql(const std::string &nmb)
  { BorraObjeto(nmb); }

//! @brief Inserta el objeto cuyo puntero se pasa como parámetro en el contenedor- 
void MySqlConnection::InsertaObjeto(const std::string &nmb,MySqlObject *ptr)
  {
    assert(ptr);
    sql_objs_iterator i= mySqlObjs.find(nmb);
    if(i!= mySqlObjs.end()) //El objeto ya existe.
      {
        std::cerr << "No se pudo crear la consulta: '" 
                  << nmb << "' el objeto ya existe." << std::endl;
        delete ptr; //Liberamos la memoria.
      }
    else
      mySqlObjs[nmb]= ptr;
  }

//! @brief Borra del contenedor el objeto cuyo nombre se pasa como parámetro. 
void MySqlConnection::BorraObjeto(const std::string &nmb)
  {
    sql_objs_iterator i= mySqlObjs.find(nmb);
    if(i!= mySqlObjs.end()) //El objeto existe.
      {
        delete (*i).second;
        (*i).second= NULL;
        mySqlObjs.erase(i);
      }
  }

MySqlConnection::~MySqlConnection(void)
  {
    if(!mySqlObjs.empty())
      borra_objetos();
  }
