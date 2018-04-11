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
Database::Mutex SqLiteDatabase::mutex;
StderrLog SqLiteDatabase::log;
sqlite3_stmt *SqLiteDatabase::tmpRes= nullptr;

//! @brief Constructor.
SqLiteDatabase::SqLiteDatabase(const std::string &nmb)
  : SqLiteObject(), db(mutex,nmb,&log), defaultQuery(nullptr) 
  { defaultQuery= NuevaQuery("defaultQuery"); }

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
          insert_object(nmb,retval);
        else
          std::cerr << "SqLiteObject::NuevaQuery; el puntero al objeto es nulo." << std::endl;
      }
    else
      if(verbosity>1)
        std::clog << "SqLiteObject::NuevaQuery; no se pudo crear la consulta de nombre: '"
                  << nmb << "' ya existe un objeto con ese nombre." << std::endl;
    return retval;
  }

