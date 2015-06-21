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
//MySqlRow.h
//Entidad para conexiones con MySql.

#ifndef MYSQLROW_H
#define MYSQLROW_H

#include "MySqlObject.h"

//! @ingroup MYSQL
//
//!  @brief Fila de una tabla MySql.
class MySqlRow: public MySqlObject
  {
    mysqlpp::Row f; //!< Fila de una tabla MySql.
  protected:
    template <class Num>
    void get_numeric_field_value(const std::string &nmb_campo,Num &retval) const;
    void get_string_field_value(const std::string &nmb_campo,std::string &retval) const;
    bool procesa_comando(CmdStatus &status);
  public:
    MySqlRow(MySqlConnection *ptr_conex);
    MySqlRow(const mysqlpp::Row &r,MySqlConnection *ptr_conex);
    virtual MySqlObject *getCopy(void) const;
    void SetRow(const mysqlpp::Row &r);
    any_const_ptr GetProp(const std::string &) const;
  };

template <class Num>
void MySqlRow::get_numeric_field_value(const std::string &nmb_campo,Num &retval) const
  {
    try
      { retval= f[nmb_campo.c_str()]; }

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

#endif
