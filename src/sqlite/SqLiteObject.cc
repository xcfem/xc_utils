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
//SqLiteObject

#include "SqLiteObject.h"
#include "SqLiteDatabase.h"
#include "SqLiteQuery.h"
#include "boost/algorithm/string/trim.hpp"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"
#include "xc_basic/src/sqlitepp/StderrLog.h"
#include "xc_utils/src/nucleo/InterpreteRPN.h"

SqLiteObject::map_sql_objs SqLiteObject::SqLiteObjs;

//! @brief Borra las consultas.
void SqLiteObject::borra_queries(void)
  {
    for(sql_objs_iterator i= SqLiteObjs.begin();i!=SqLiteObjs.end();i++)
      {
        SqLiteQuery *tmp= dynamic_cast<SqLiteQuery *>((*i).second);
        if(tmp)
          {
            delete (*i).second;
            (*i).second= NULL;
            SqLiteObjs.erase(i);            
          }
      }
  }

//! @brief Borra las bases de datos.
void SqLiteObject::borra_databases(void)
  {
    borra_queries(); //Primero consultas y luego bases de datos.
    for(sql_objs_iterator i= SqLiteObjs.begin();i!=SqLiteObjs.end();i++)
      {
        SqLiteDatabase *tmp= dynamic_cast<SqLiteDatabase *>((*i).second);
        if(tmp)
          {
            delete (*i).second;
            (*i).second= NULL;
            SqLiteObjs.erase(i);            
          }
      }
  }

//! @brief Borra todos los objetos.
void SqLiteObject::borra_objetos(void)
  {
    borra_databases(); //Borramos consultas y después bases de datos.
    for(sql_objs_iterator i= SqLiteObjs.begin();i!=SqLiteObjs.end();i++) //Borramos el resto de objetos.
      {
        delete (*i).second;
        (*i).second= NULL;
      }
    SqLiteObjs.clear();
  }

//! @brief Inserta el objeto cuyo puntero se pasa como parámetro en el contenedor
void SqLiteObject::inserta_objeto(const std::string &nmb,SqLiteObject *ptr)
  {
    assert(ptr);
    sql_objs_iterator i= SqLiteObjs.find(nmb);
    if(i!= SqLiteObjs.end()) //El objeto ya existe.
      {
        std::cerr << "No se pudo crear el objeto: '" 
                  << nmb << "' ya existe." << std::endl;
        delete ptr; //Liberamos la memoria.
      }
    else
      SqLiteObjs[nmb]= ptr;
  }

//! @brief Devuelve un puntero al objeto cuyo nombre se pasa como parámetro (si existe). 
SqLiteObject *SqLiteObject::busca_objeto(const std::string &nmb)
  {
    SqLiteObject *retval= NULL;
    sql_objs_iterator i= SqLiteObjs.find(nmb);
    if(i!= SqLiteObjs.end()) //El objeto existe.
      retval= (*i).second;
    return retval;
  }


//! @brief Constructor.
SqLiteObject::SqLiteObject(void)
  {}

bool SqLiteObject::procesa_comando_obj_sqlite(const std::string &cmd,CmdStatus &status)
  {
    SqLiteObject *tmp= busca_objeto(cmd);
    if(tmp) //Encuentra el objeto al que se refiere el comando.
      {
        tmp->set_owner(this);
        tmp->LeeCmd(status);
        return true;
      }
    else
      return false;
  }

//! @brief Lectura del objeto desde archivo.
bool SqLiteObject::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(SqLiteObject) Procesando comando: " << cmd << std::endl;

    if(cmd == "erase") //Borra un objeto.
      {
        BorraObjeto(interpretaString(status.GetBloque()));
        return true;
      }
    else if(cmd == "clearQueries") //Borra todas las consultas.
      {
        status.GetBloque(); //Ignora entrada.
        borra_queries();
        return true;
      }
    else if(cmd == "clearDatabases") //Borra todas las bases de datos.
      {
        status.GetBloque(); //Ignora entrada.
        borra_databases();
        return true;
      }
    else if(cmd == "clearAll") //Borra todos los objetos.
      {
        status.GetBloque(); //Ignora entrada.
        clearAll();
        return true;
      }
    else if(cmd == "openDB") //Abre una base de datos.
      {
        const std::string path= interpretaString(status.GetBloque());
        if(existe_archivo(path))
          NuevaDatabase(path);
        else
	  std::cerr << "(SqLiteObject) Procesando comando: " << cmd
                    << "; no existe el archivo " << path << std::endl;
        return true;
      }
    else if(cmd == "newDB") //Crea una base de datos.
      {
        NuevaDatabase(interpretaString(status.GetBloque()));
        return true;
      }
    else if(cmd == "newQuery") //Crea una consulta.
      {
        const CmdParser &parser= status.Parser();
        if(parser.TieneIndices())
          {
            interpreta(parser.GetIndices());
            if(InterpreteRPN::HayArgumentos(1,cmd))
              {
                const std::string tag_db= convert_to_string(InterpreteRPN::Pila().Pop()); //Tag de la base de datos.
                NuevaQuery(interpretaString(status.GetBloque()),tag_db);
              }
          }
        return true;
      }
    else if(procesa_comando_obj_sqlite(cmd,status))
      return true;
    else
      return EntCmd::procesa_comando(status);
  }

//! @brief Destructor.
SqLiteObject::~SqLiteObject(void)
  {}

void SqLiteObject::clearAll(void)
  { borra_objetos(); }

//! @brief Crea la base de datos con el nombre que se pasa como parametro.
void SqLiteObject::NuevaDatabase(const std::string &nmb)
  { 
    SqLiteObject *ptr= new SqLiteDatabase(nmb);
    if(ptr)
      inserta_objeto(nmb,ptr);
    else
      std::cerr << "SqLiteObject::NuevoObjetoSql; el puntero al objeto es nulo." << std::endl;
  }

//! @brief Crea la consulta el nombre que se pasa como parametro.
void SqLiteObject::NuevaQuery(const std::string &nmb,const std::string &nmb_db)
  { 
    SqLiteDatabase *ptr_db= getDatabase(nmb_db);
    if(ptr_db)
      ptr_db->NuevaQuery(nmb);
    else
      std::cerr << "No se encontró la base de datos: " << nmb_db << std::endl;

  }


//! @brief Preprocesa una cadena de caracteres que contiene una sentencia SQL.
std::string SqLiteObject::preprocesa_str_sql(const std::string &str) const
  {
    return boost::trim_copy_if(interpretaString(str),boost::is_any_of("\""));
  }


//! @brief Devuelve la base de datos cuyo nombre se pasa como parámetro. 
SqLiteDatabase *SqLiteObject::getDatabase(const std::string &nmb)
  {
    SqLiteDatabase *retval= NULL;
    sql_objs_iterator i= SqLiteObjs.find(nmb);
    if(i!= SqLiteObjs.end()) //El objeto existe.
      retval= dynamic_cast<SqLiteDatabase *>((*i).second);
    return retval;
  }

//! @brief Devuelve la consulta cuyo nombre se pasa como parámetro. 
SqLiteQuery *SqLiteObject::getQuery(const std::string &nmb)
  {
    SqLiteQuery *retval= NULL;
    sql_objs_iterator i= SqLiteObjs.find(nmb);
    if(i!= SqLiteObjs.end()) //El objeto existe.
      retval= dynamic_cast<SqLiteQuery *>((*i).second);
    return retval;
  }

//! @brief Borra del contenedor el objeto cuyo nombre se pasa como parámetro. 
void SqLiteObject::BorraObjeto(const std::string &nmb)
  {
    sql_objs_iterator i= SqLiteObjs.find(nmb);
    if(i!= SqLiteObjs.end()) //El objeto existe.
      {
        delete (*i).second;
        (*i).second= NULL;
        SqLiteObjs.erase(i);
      }
  }

//! Devuelve la propiedad del objeto cuyo código se pasa 
//! como parámetro. 
any_const_ptr SqLiteObject::GetProp(const std::string &cod) const 
  {
    if(verborrea>4)
      std::clog << "SqLiteObject::GetProp (" << nombre_clase() << "::GetProp) Buscando propiedad: " << cod << std::endl;
    return EntCmd::GetProp(cod);
  }

