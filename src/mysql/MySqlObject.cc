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
//MySqlObject

#include "MySqlObject.h"
#include "MySqlConnection.h"
#include "boost/algorithm/string/trim.hpp"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"
#include "xc_utils/src/base/utils_any_const_ptr.h"
#include "boost/lexical_cast.hpp"
#include <boost/algorithm/string.hpp>
#include "xc_utils/src/base/CmdStatus.h"

//! @brief Constructor.
MySqlObject::MySqlObject(MySqlConnection *ptr_conex)
  : conexion(ptr_conex) {}

//! @brief Lectura del objeto desde archivo.
bool MySqlObject::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(MySqlObject) Procesando comando: " << cmd << std::endl;

    if(cmd == "erase") //Borra un objeto.
      {
        BorraObjetoSql(interpretaString(status.GetBloque()));
        return true;
      }
    else
      return EntCmd::procesa_comando(status);
  }

//! @brief Almacena el nuevo objeto con el nombre que se pasa como parametro.
void MySqlObject::NuevoObjetoSql(const std::string &nmb,MySqlObject *ptr)
  {
    if(conexion)
      conexion->NuevoObjetoSql(nmb,ptr);
    else
      std::cerr << "MySqlObject::NuevoObjetoSql; el puntero a la conexión es nulo." << std::endl;
  }

//! @brief Almacena el nuevo objeto con el nombre que se pasa como parametro.
void MySqlObject::NuevoObjetoSql(const std::string &nmb,const MySqlObject &ref)
  {
    if(conexion)
      conexion->NuevoObjetoSql(nmb,ref);
    else
      std::cerr << "MySqlObject::NuevoObjetoSql; el puntero a la conexión es nulo." << std::endl;
  }

//! @brief Borra el objeto cuyo nombre se pasa como parametro.
void MySqlObject::BorraObjetoSql(const std::string &nmb)
  {
    if(conexion)
      conexion->BorraObjetoSql(nmb);
    else
      std::cerr << "MySqlObject::BorraObjetoSql; el puntero a la conexión es nulo." << std::endl;
  }

//! @brief Preprocesa una cadena de caracteres que contiene una sentencia SQL.
std::string MySqlObject::preprocesa_str_sql(const std::string &str) const
  {
    return boost::trim_copy_if(interpretaString(str),boost::is_any_of("\""));
  }

//! Devuelve la propiedad del objeto cuyo código se pasa 
//! como parámetro. 
any_const_ptr MySqlObject::GetProp(const std::string &cod) const 
  { return EntCmd::GetProp(cod); }
