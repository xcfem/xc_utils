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
//SqLiteObject.h
//Envoltorio para objetos de SqLite++.

#ifndef SQLITEOBJECT_H
#define SQLITEOBJECT_H

#include "../kernel/CommandEntity.h"

class SqLiteDatabase;
class SqLiteQuery;

//! @defgroup SQLITE Interfaz con la biblioteca SqLite.
//
//! @ingroup SQLITE
//
//!  @brief Clase base de los objetos de base de datos.
class SqLiteObject: public CommandEntity
  {
  public:
    typedef std::map<std::string,SqLiteObject *> map_sql_objs;//!< Contenedor de objetos de base de datos.
    typedef map_sql_objs::iterator sql_objs_iterator;//!< Iterador a objetos de base de datos.
    typedef map_sql_objs::const_iterator sql_objs_const_iterator;//!< Iterador a objetos de base de datos.
  protected:
    static map_sql_objs SqLiteObjs;//!< Contenedor de objetos de SqLite.

    static void borra_queries(void);
    static void borra_databases(void);
    static void borra_objetos(void);
    static void insert_object(const std::string &nmb,SqLiteObject *ptr);
    static SqLiteObject *busca_objeto(const std::string &nmb);

    std::string preprocesa_str_sql(const std::string &str) const;
  public:
    SqLiteObject(void);
    virtual ~SqLiteObject(void);

    static void NuevaDatabase(const std::string &nmb);
    static void NuevaQuery(const std::string &nmb,const std::string &nmb_db);

    static void BorraObjeto(const std::string &nmb);
    static void clearAll(void);

    static SqLiteDatabase *getDatabase(const std::string &nmb);
    static SqLiteQuery *getQuery(const std::string &nmb);
  };
#endif
