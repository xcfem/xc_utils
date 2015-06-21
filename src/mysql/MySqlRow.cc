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
//MySqlRow

#include "MySqlRow.h"
#include "MySqlColData.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"

//! @brief Constructor.
MySqlRow::MySqlRow(MySqlConnection *ptr_conex)
  : MySqlObject(ptr_conex), f() {}

//! @brief Constructor.
MySqlRow::MySqlRow(const mysqlpp::Row &r,MySqlConnection *ptr_conex)
  : MySqlObject(ptr_conex), f(r) {}

//! @brief Constructor virtual.
MySqlObject *MySqlRow::getCopy(void) const
  { return new MySqlRow(*this); }

//! @brief Lectura del objeto desde archivo.
bool MySqlRow::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(MySqlRow) Procesando comando: " << cmd << std::endl;
    if(cmd=="at")
      {
        const CmdParser &parser= status.Parser();
        if(parser.TieneIndices())
          {
	    std::deque<boost::any> indices= parser.SeparaIndices(this);
            const size_t i= convert_to_size_t(indices[0]);
            MySqlColData tmp(f.at(i),conexion);
            tmp.LeeCmd(status);
          }
        else
	  std::cerr << "MySqlRow::comando:" << cmd
                   << "; es necesario especificar el índice del campo." << std::endl;
        return true;
      }
    else
      return MySqlObject::procesa_comando(status);
  }

//! @brief Asigna el valor de la fila.
void MySqlRow::SetRow(const mysqlpp::Row &r)
  { f= r; }

void MySqlRow::get_string_field_value(const std::string &nmb_campo,std::string &retval) const
  {
    try
      { retval= std::string(f[nmb_campo.c_str()]); }

    catch (const mysqlpp::BadQuery& er)
      {// Handle any query errors
        std::cerr << "Query error: " << er.what() << std::endl;
        return;
      }
    catch(const mysqlpp::BadConversion& er)
      {// Handle bad conversions
        std::cerr << "Conversion error: " << er.what() << std::endl
                  << "\tretrieved data size: " << er.retrieved
                  << ", actual size: " << er.actual_size << std::endl;
        return;
      }
    catch(const mysqlpp::Exception& er)
      {
        // Catch-all for any other MySQL++ exceptions
        std::cerr << "Error: " << er.what() << std::endl;
        return;
      }
  }

//! Devuelve la propiedad del objeto cuyo código se pasa 
//! como parámetro. 
any_const_ptr MySqlRow::GetProp(const std::string &cod) const 
  {
    if(cod=="size") //Devuelve el número de campos de la fila.
      {
        tmp_gp_int= f.size();
        return any_const_ptr(tmp_gp_int);
      }
//     else if(cod=="raw_data")
//       {
//         size_t i= popInt(cod);
//         tmp_gp_str= f.raw_data(i);
//         return any_const_ptr(tmp_gp_str);
//       }
    else if(cod=="get_str_field") //Devuelve la cadena de caracteres contenida
      {                           //por el campo cuyo nombre se pasa como parámetro.
	std::string nmb_campo= popString(cod);
        get_string_field_value(nmb_campo,tmp_gp_str);
        return any_const_ptr(tmp_gp_str);
      }
    else if(cod=="get_int_field") //Devuelve el integer contenido
      {                           //por el campo cuyo nombre se pasa como parámetro.
	std::string nmb_campo= popString(cod);
        get_numeric_field_value(nmb_campo,tmp_gp_int);
        return any_const_ptr(tmp_gp_int);
      }
    else if(cod=="get_dbl_field") //Devuelve el double contenido
      {                           //por el campo cuyo nombre se pasa como parámetro.
	std::string nmb_campo= popString(cod);
        get_numeric_field_value(nmb_campo,tmp_gp_dbl);
        return any_const_ptr(tmp_gp_dbl);
      }
    else
      return MySqlObject::GetProp(cod);
  }
