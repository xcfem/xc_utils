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
//MySqlQuery

#include "MySqlQuery.h"
#include "MySqlConnection.h"
#include "MySqlResult.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/any_const_ptr.h"

//! @brief Constructor.
MySqlQuery::MySqlQuery(const MySqlConnection &c,const bool &ue,MySqlConnection *ptr_conex)
  : MySqlObject(ptr_conex), q(&c.con) {}

//! @brief Lectura de la Timer desde archivo.
bool MySqlQuery::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(MySqlQuery) Procesando comando: " << cmd << std::endl;

    if(cmd == "execute_sql") //Ejecuta una sentencia SQL.
      {
        try
          { q.execute(preprocesa_str_sql(status.GetBloque())); }
	catch (const mysqlpp::BadQuery& er)
          {// Handle any query errors
	    std::cerr << "Query error: " << er.what() << std::endl;
	    return true;
	  }
	catch(const mysqlpp::BadConversion& er)
          {
	    // Handle bad conversions
	    std::cerr << "Conversion error: " << er.what() << std::endl
                 << "\tretrieved data size: " << er.retrieved
                 << ", actual size: " << er.actual_size << std::endl;
            return true;
	  }
	catch(const mysqlpp::Exception& er)
          {
	    // Catch-all for any other MySQL++ exceptions
	    std::cerr << "Error: " << er.what() << std::endl;
	    return true;
	  }  
        return true;
      }
    else if(cmd == "execute") //Ejecuta la sentencia ya almacenada.
      {
        status.GetBloque(); //Ignoramos entrada.
        try
          { q.execute(); }
	catch (const mysqlpp::BadQuery& er)
          {// Handle any query errors
	    std::cerr << "Query error: " << er.what() << std::endl;
	    return true;
	  }
	catch(const mysqlpp::BadConversion& er)
          {
	    // Handle bad conversions
	    std::cerr << "Conversion error: " << er.what() << std::endl
                 << "\tretrieved data size: " << er.retrieved
                 << ", actual size: " << er.actual_size << std::endl;
            return true;
	  }
	catch(const mysqlpp::Exception& er)
          {
	    // Catch-all for any other MySQL++ exceptions
	    std::cerr << "Error: " << er.what() << std::endl;
	    return true;
	  }   
        return true;
      }
    else if(cmd == "sql_cmd") //Define el comando sql a ejecutar.
      {
        q << preprocesa_str_sql(status.GetBloque());
        return true;
      }
    else if(cmd == "parse") //The parse() call tells the query object that this is a template and		
      {                     // not a literal query string.
        status.GetBloque(); //Ignoramos entrada.
        q.parse();
        return true;
      }
    else if(cmd == "store") //Ejecuta la consulta y almacena el resultado.
      {
        const std::string nmb= interpretaString(status.GetBloque());
        try
          {
            mysqlpp::StoreQueryResult r(q.store());
            MySqlResult result(r,conexion);
            NuevoObjetoSql(nmb,result);
          }
	catch (const mysqlpp::BadQuery& er)
          {// Handle any query errors
	    std::cerr << "Query error: " << er.what() << std::endl;
	    return true;
	  }
	catch(const mysqlpp::BadConversion& er)
          {
	    // Handle bad conversions
	    std::cerr << "Conversion error: " << er.what() << std::endl
                 << "\tretrieved data size: " << er.retrieved
                 << ", actual size: " << er.actual_size << std::endl;
	    return true;
	  }
	catch(const mysqlpp::Exception& er)
          {
	    // Catch-all for any other MySQL++ exceptions
	    std::cerr << "Error: " << er.what() << std::endl;
	    return true;
	  }
        return true;
      }
    else
      return MySqlObject::procesa_comando(status);
  }
//! @brief Constructor.
MySqlQuery::MySqlQuery(const mysqlpp::Query &qu,MySqlConnection *ptr_conex)
  : MySqlObject(ptr_conex), q(qu) {}

//! @brief Constructor virtual.
MySqlObject *MySqlQuery::getCopy(void) const
  { return new MySqlQuery(*this); }

//! Devuelve la propiedad del objeto cuyo código se pasa 
//! como parámetro. 
any_const_ptr MySqlQuery::GetProp(const std::string &cod) const 
  {
    if(cod=="error")
      {
        tmp_gp_str= q.error();
        return any_const_ptr(tmp_gp_str);
      }
//     else if(cod=="success")
//       {
//         tmp_gp_bool= static_cast<bool>(q);
//         return any_const_ptr(tmp_gp_bool);
//       }
    else if(cod=="preview")
      {
        tmp_gp_str= q.str();
        return any_const_ptr(tmp_gp_str);
      }
    else
      return MySqlObject::GetProp(cod);
  }
