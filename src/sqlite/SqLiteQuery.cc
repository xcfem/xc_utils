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
//SqLiteQuery

#include "SqLiteQuery.h"
#include "SqLiteDatabase.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"
#include "xc_basic/src/sqlitepp/Database.h"
#include "xc_utils/src/nucleo/InterpreteRPN.h"

//! @brief Constructor.
SqLiteQuery::SqLiteQuery(Database &db)
  : SqLiteObject(), q(db) {}

//! @brief Constructor.
SqLiteQuery::SqLiteQuery(SqLiteDatabase &db)
  : SqLiteObject(), q(db.getDB()) {}

//! @brief Constructor.
SqLiteQuery::SqLiteQuery(Database &db,const std::string &sql)
  : SqLiteObject(), q(db,sql) {}

//! @brief Lectura de la Timer desde archivo.
bool SqLiteQuery::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(SqLiteQuery (" << size_t(this) << ")) Procesando comando: " << cmd << std::endl;

    if(cmd == "execute_sql") //Ejecuta una sentencia SQL.
      {
        execute(preprocesa_str_sql(status.GetBloque()));
        return true;
      }
    else if(cmd == "get_result")
      {
        get_result(preprocesa_str_sql(status.GetBloque()));
        return true;
      }
    else if(cmd == "free_result")
      {
	status.GetBloque(); //Ignoramos entrada.
        free_result();
        return true;
      }
    else
      return SqLiteObject::procesa_comando(status);
  }

int SqLiteQuery::GetErrno(void)
  { return q.GetErrno(); }

std::string SqLiteQuery::GetError(void)
  { return q.GetError(); }

bool SqLiteQuery::execute(const std::string &sql)
  { return q.execute(sql); }

bool SqLiteQuery::insert_blob1(const std::string &sql,const void *blobData,const size_t &numBytes)
  { return q.insert_blob1(sql,blobData,numBytes); }


sqlite3_stmt *SqLiteQuery::get_result(const std::string &sql)
  { return q.get_result(sql); }

void SqLiteQuery::free_result(void)
  { q.free_result(); }

bool SqLiteQuery::fetch_row(void) const
  { return const_cast<Query *>(&q)->fetch_row(); }

long SqLiteQuery::num_rows(void) const
  { return const_cast<Query *>(&q)->num_rows(); }

//! @brief Devuelve el valor del campo denominado fieldName como BLOB.
const void *SqLiteQuery::getBlob(const std::string &fieldName) const
  { return const_cast<Query *>(&q)->getblob(fieldName); }

//! @brief Devuelve el valor del campo denominado fieldName como cadena de caracteres.
std::string SqLiteQuery::getStr(const std::string &fieldName) const
  { return std::string(const_cast<Query *>(&q)->getstr(fieldName)); }

//! @brief Devuelve el valor del campo denominado fieldName como entero.
int SqLiteQuery::getInt(const std::string &fieldName) const
  { return static_cast<int>(getLongInt(fieldName)); }

//! @brief Devuelve el valor del campo denominado fieldName como entero sin signo.
size_t SqLiteQuery::getSizeT(const std::string &fieldName) const
  { return static_cast<size_t>(getLongInt(fieldName)); }

//! @brief Devuelve el valor del campo denominado fieldName como entero largo.
long int SqLiteQuery::getLongInt(const std::string &fieldName) const
  { return const_cast<Query *>(&q)->getval(fieldName); }

//! @brief Devuelve el valor del campo denominado fieldName como entero largo sin signo.
unsigned long int SqLiteQuery::getULongInt(const std::string &fieldName) const
  { return const_cast<Query *>(&q)->getuval(fieldName); }

//! @brief Devuelve el valor del campo denominado fieldName como double.
double SqLiteQuery::getDouble(const std::string &fieldName) const
  { return const_cast<Query *>(&q)->getnum(fieldName); }


//! @brief Devuelve el valor del campo de índice 'index' como BLOB.
const void *SqLiteQuery::getBlob(const int &index) const
  { return const_cast<Query *>(&q)->getblob(index); }

//! @brief Devuelve el valor del campo de índice 'index' como cadena de caracteres.
std::string SqLiteQuery::getStr(const int &index) const
  { return std::string(const_cast<Query *>(&q)->getstr(index)); }

//! @brief Devuelve el valor del campo de índice 'index' como entero.
int SqLiteQuery::getInt(const int &index) const
  { return static_cast<int>(getLongInt(index)); }

//! @brief Devuelve el valor del campo de índice 'index' como entero sin signo.
size_t SqLiteQuery::getSizeT(const int &index) const
  { return static_cast<size_t>(getLongInt(index)); }

//! @brief Devuelve el valor del campo de índice 'index' como entero largo.
long int SqLiteQuery::getLongInt(const int &index) const
  { return const_cast<Query *>(&q)->getval(index); }

//! @brief Devuelve el valor del campo de índice 'index' como entero largo sin signo.
unsigned long int SqLiteQuery::getULongInt(const int &index) const
  { return const_cast<Query *>(&q)->getuval(index); }

//! @brief Devuelve el valor del campo de índice 'index' como double.
double SqLiteQuery::getDouble(const int &index) const
  { return const_cast<Query *>(&q)->getnum(index); }

//! @brief Devuelve el valor del siguiente campo como cadena de caracteres.
std::string SqLiteQuery::getStr(void) const
  { return std::string(const_cast<Query *>(&q)->getstr()); }

//! @brief Devuelve el valor del siguiente campo como entero.
int SqLiteQuery::getInt(void) const
  { return static_cast<int>(getLongInt()); }

//! @brief Devuelve el valor del siguiente campo como entero sin signo.
size_t SqLiteQuery::getSizeT(void) const
  { return static_cast<size_t>(getLongInt()); }

//! @brief Devuelve el valor del siguiente campo como entero largo.
long int SqLiteQuery::getLongInt(void) const
  { return const_cast<Query *>(&q)->getval(); }

//! @brief Devuelve el valor del siguiente campo como entero largo sin signo.
unsigned long int SqLiteQuery::getULongInt(void) const
  { return const_cast<Query *>(&q)->getuval(); }

//! @brief Devuelve el valor del siguiente campo como double.
double SqLiteQuery::getDouble(void) const
  { return const_cast<Query *>(&q)->getnum(); }


//! Devuelve la propiedad del objeto cuyo código se pasa 
//! como parámetro. 
any_const_ptr SqLiteQuery::GetProp(const std::string &cod) const 
  {
    if(verborrea>4)
      std::clog << "SqLiteQuery::GetProp (" << nombre_clase() << "::GetProp) Buscando propiedad: " << cod << std::endl;
    if(cod=="num_rows")
      {
        tmp_gp_lint= num_rows();
        return any_const_ptr(tmp_gp_lint);
      }
    else if(cod=="fetch_row")
      {
        tmp_gp_bool= fetch_row();
        return any_const_ptr(tmp_gp_bool);
      }
    else if(cod=="getStr")
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            const std::string fieldName= boost_any_to_string(InterpreteRPN::Pila().Pop());
            tmp_gp_str= getStr(fieldName);
            return any_const_ptr(tmp_gp_str);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetProp",cod);
            return any_const_ptr();
          }
      }
    else if(cod=="getInt")
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            const std::string fieldName= boost_any_to_string(InterpreteRPN::Pila().Pop());
            tmp_gp_int= getInt(fieldName);
            return any_const_ptr(tmp_gp_int);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetProp",cod);
            return any_const_ptr();
          }
      }
    else if(cod=="getSizeT")
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            const std::string fieldName= boost_any_to_string(InterpreteRPN::Pila().Pop());
            tmp_gp_szt= getSizeT(fieldName);
            return any_const_ptr(tmp_gp_szt);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetProp",cod);
            return any_const_ptr();
          }
      }
    else if(cod=="getLongInt")
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            const std::string fieldName= boost_any_to_string(InterpreteRPN::Pila().Pop());
            tmp_gp_lint= getLongInt(fieldName);
            return any_const_ptr(tmp_gp_lint);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetProp",cod);
            return any_const_ptr();
          }
      }
    else if(cod=="getDouble")
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            const std::string fieldName= boost_any_to_string(InterpreteRPN::Pila().Pop());
            tmp_gp_dbl= getDouble(fieldName);
            return any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetProp",cod);
            return any_const_ptr();
          }
      }
    else if(cod=="fieldIndex")
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            const std::string fieldName= boost_any_to_string(InterpreteRPN::Pila().Pop());
            tmp_gp_int= const_cast<Query *>(&q)->field_index(fieldName);
            return any_const_ptr(tmp_gp_int);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetProp",cod);
            return any_const_ptr();
          }
      }
    else if(cod=="errorCode")
      {
        tmp_gp_int= const_cast<Query *>(&q)->GetErrno();
        return any_const_ptr(tmp_gp_int);
      }
    else if(cod=="error")
      {
        tmp_gp_str= q.GetError();
        return any_const_ptr(tmp_gp_str);
      }
    else if(cod=="lastQuery")
      {
        tmp_gp_str= q.GetLastQuery();
        return any_const_ptr(tmp_gp_str);
      }
    else if(cod=="numColumns")
      {
        tmp_gp_szt= q.num_cols();
        return any_const_ptr(tmp_gp_szt);
      }
    else if(cod=="fieldNames")
      {
        tmp_gp_str= q.field_names();
        return any_const_ptr(tmp_gp_str);
      }
    return SqLiteObject::GetProp(cod);
  }
