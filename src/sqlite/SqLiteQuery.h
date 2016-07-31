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
//SqLiteQuery.h

#ifndef SQLITEQUERY_H
#define SQLITEQUERY_H

#include "SqLiteObject.h"
#include <sqlite3.h>
#include "xc_basic/src/sqlitepp/IError.h"
#include "xc_basic/src/sqlitepp/Database.h"
#include "xc_basic/src/sqlitepp/Query.h"

//! @ingroup SQLITE
//
//!  @brief Clase para consulta SQL
class SqLiteQuery: public SqLiteObject
  {
    Query q; //!< Consulta SqLite.

  public:
    SqLiteQuery(Database &db);
    SqLiteQuery(SqLiteDatabase &db);
    SqLiteQuery(Database &db,const std::string &sql);

    int GetErrno(void);
    std::string getError(void) const;
    bool execute(const std::string &sql);
    sqlite3_stmt *get_result(const std::string& sql);
    void free_result();
    bool fetch_row(void) const;
    long num_rows(void) const;
    bool insert_blob1(const std::string &sql,const void *blobData,const size_t &numBytes);

    const void *getBlob(const std::string &fieldName) const;
    std::string getStr(const std::string &fieldName) const;
    int getInt(const std::string &fieldName) const;
    size_t getSizeT(const std::string &fieldName) const;
    long int getLongInt(const std::string &fieldName) const;
    unsigned long int getULongInt(const std::string &fieldName) const;
    double getDouble(const std::string &fieldName) const;

    const void *getBlob(const int &index) const;
    std::string getStr(const int &index) const;
    int getInt(const int &index) const;
    size_t getSizeT(const int &index) const;
    long int getLongInt(const int &index) const;
    unsigned long int getULongInt(const int &index) const;
    double getDouble(const int &index) const;

    std::string getStr(void) const;
    int getInt(void) const;
    size_t getSizeT(void) const;
    long int getLongInt(void) const;
    unsigned long int getULongInt(void) const;
    double getDouble(void) const;

  };
#endif
