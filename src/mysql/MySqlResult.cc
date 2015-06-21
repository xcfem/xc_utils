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
//MySqlResult

#include "MySqlResult.h"
#include "MySqlConnection.h"
#include "MySqlRow.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/any_const_ptr.h"

//! @brief Constructor.
MySqlResult::MySqlResult(MySqlConnection *ptr_conex)
  : MySqlObject(ptr_conex), r()  {}

//! @brief Constructor.
MySqlResult::MySqlResult(const mysqlpp::StoreQueryResult &rs,MySqlConnection *ptr_conex)
  : MySqlObject(ptr_conex), r(rs) {}

//! @brief Constructor virtual.
MySqlObject *MySqlResult::getCopy(void) const
  { return new MySqlResult(*this); }

//! @brief Lectura del objeto desde archivo.
bool MySqlResult::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(MySqlResult) Procesando comando: " << cmd << std::endl;
//     if(cmd == "data_seek")
//       {
//         r.data_seek(interpretaInt(status.GetBloque()));
//         return true;
//       }
    if(cmd == "for_each_row") //Ejecuta un bloque de comandos para cada fila.
      {
        const std::string bloque= status.GetBloque();
        MySqlRow row(conexion);
        for(mysqlpp::StoreQueryResult::iterator i= r.begin();i!=r.end();i++)
          {
            row.SetRow(*i);
            row.EjecutaBloque(status,bloque,"MySqlResult:for_each_row");
          }
        return true;
      }
    else
      return MySqlObject::procesa_comando(status);
  }

//! Devuelve la propiedad del objeto cuyo código se pasa 
//! como parámetro. 
any_const_ptr MySqlResult::GetProp(const std::string &cod) const 
  {
    if(cod=="size")
      {
        tmp_gp_int= r.size();
        return any_const_ptr(tmp_gp_int);
      }
    else
      return MySqlObject::GetProp(cod);
  }
