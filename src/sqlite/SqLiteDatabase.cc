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
//SqLiteDatabase

#include "SqLiteDatabase.h"
#include "SqLiteQuery.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"

Database::Mutex SqLiteDatabase::mutex;
StderrLog SqLiteDatabase::log;
sqlite3_stmt *SqLiteDatabase::tmpRes= NULL;

//! @brief Constructor.
SqLiteDatabase::SqLiteDatabase(const std::string &nmb)
  : SqLiteObject(), db(mutex,nmb,&log), defaultQuery(NULL) 
  { defaultQuery= NuevaQuery("defaultQuery"); }

//! @brief Lectura desde archivo.
bool SqLiteDatabase::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(SqLiteDatabase) Procesando comando: " << cmd << std::endl;

    if(cmd == "newQuery") //Crea una consulta.
      {
        NuevaQuery(interpretaString(status.GetBloque()));
        return true;
      }
    else if(cmd == "execute_sql") //Ejecuta una sentencia SQL.
      {
        if(!defaultQuery)
          defaultQuery= NuevaQuery("defaultQuery");
        defaultQuery->execute(preprocesa_str_sql(status.GetBloque()));
        return true;
      }
    else if(cmd == "borraTabla")
      {
        borraTabla(interpretaString(status.GetBloque()));
        return true;
      }
    else
      return SqLiteObject::procesa_comando(status);
  }

//! @brief Devuelve verdadero si existe la tabla cuyo nombre se pasa como parámetro.
bool SqLiteDatabase::existeTabla(const std::string &nmbTabla) const
  {
    SqLiteQuery tmp(const_cast<Database &>(db));
    tmpRes= tmp.get_result("select count(*) from sqlite_master where type='table' and name= '" + nmbTabla + "';");
    long int sz= 0;
    if(tmp.fetch_row())
      sz= tmp.getLongInt();
    tmp.free_result();
    return (sz>0);
  }

//! @brief Borra la tabla si existe.
bool SqLiteDatabase::borraTabla(const std::string &nmbTabla)
  { 
    if(!defaultQuery)
      defaultQuery= NuevaQuery("defaultQuery");
    return defaultQuery->execute("drop table if exists '" + nmbTabla + "';");
  }

//! @brief Devuelve la consulta por defecto.
SqLiteQuery *SqLiteDatabase::getDefaultQuery(void)
  { return defaultQuery; }

//! @brief Crea la consulta con el nombre que se pasa como parametro.
SqLiteQuery *SqLiteDatabase::NuevaQuery(const std::string &nmb)
  {
    SqLiteObject *ptr= busca_objeto(nmb);
    SqLiteQuery *retval= dynamic_cast<SqLiteQuery *>(ptr);
    if(!retval) //No existe
      {
        retval= new SqLiteQuery(db);
        if(retval)
          inserta_objeto(nmb,retval);
        else
          std::cerr << "SqLiteObject::NuevaQuery; el puntero al objeto es nulo." << std::endl;
      }
    else
      if(verborrea>1)
        std::clog << "SqLiteObject::NuevaQuery; no se pudo crear la consulta de nombre: '"
                  << nmb << "' ya existe un objeto con ese nombre." << std::endl;
    return retval;
  }

//! Devuelve la propiedad del objeto cuyo código se pasa 
//! como parámetro. 
any_const_ptr SqLiteDatabase::GetProp(const std::string &cod) const 
  {
    if(verborrea>4)
      std::clog << "SqLiteDatabase::GetProp (" << nombre_clase() << "::GetProp) Buscando propiedad: " << cod << std::endl;
    if(cod == "getNombre")
      {
        tmp_gp_str= db.getNombre();
        return any_const_ptr(tmp_gp_str);
      }
    else if(cod == "existeTabla")
      {
        tmp_gp_bool= existeTabla(popString(cod));
        return any_const_ptr(tmp_gp_bool);
      }
    else
      return SqLiteObject::GetProp(cod);
  }
