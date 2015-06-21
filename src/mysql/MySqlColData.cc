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
//MySqlColData

#include "MySqlColData.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include <boost/lexical_cast.hpp>

//! @brief Constructor.
MySqlColData::MySqlColData(MySqlConnection *ptr_conex)
  : MySqlObject(ptr_conex), dat() {}

//! @brief Constructor.
MySqlColData::MySqlColData(const mysqlpp::String &cd,MySqlConnection *ptr_conex)
  : MySqlObject(ptr_conex), dat(cd) {}

//! @brief Constructor virtual.
MySqlObject *MySqlColData::getCopy(void) const
  { return new MySqlColData(*this); }

//! @brief Lectura de la Timer desde archivo.
bool MySqlColData::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(MySqlColData) Procesando comando: " << cmd << std::endl;

    return MySqlObject::procesa_comando(status);
  }

//! Devuelve la propiedad del objeto cuyo código se pasa 
//! como parámetro. 
any_const_ptr MySqlColData::GetProp(const std::string &cod) const 
  {
    if(cod=="is_null") //Devuelve el número de campos de la fila.
      {
        tmp_gp_bool= dat.is_null();
        return any_const_ptr(tmp_gp_bool);
      }
    else if(cod=="get_string")
      {
        tmp_gp_str= std::string(dat.c_str());
        return any_const_ptr(tmp_gp_str);
      }
    else if(cod=="get_double")
      {
        tmp_gp_dbl= boost::lexical_cast<double>(dat);
        return any_const_ptr(tmp_gp_dbl);
      }
    else if(cod=="get_int")
      {
        tmp_gp_int= boost::lexical_cast<int>(dat);
        return any_const_ptr(tmp_gp_int);
      }
    else
      return MySqlObject::GetProp(cod);
  }
