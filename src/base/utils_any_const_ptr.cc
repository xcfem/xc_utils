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
//utils_any_const_ptr.cc

#include "utils_any_const_ptr.h"
#include "any_const_ptr.h"
#include "xc_basic/src/funciones/algebra/ExprAlgebra.h"
#include "boost/lexical_cast.hpp"
#include "xc_basic/src/texto/StringFormatter.h"

#include "xc_utils/src/nucleo/VarTypes.h"

#include <boost/any.hpp>
#include <boost/lexical_cast.hpp>
#include "utils_any.h"
#include "../nucleo/aux_any.h"

//! @brief Devuelve verdadero si el objeto está vacío.
bool const_ptr_is_empty(const any_const_ptr &operand)
  {
    if(operand.empty())
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_empty(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve verdadero si el objeto es un bool.
bool is_const_ptr_to_bool(const any_const_ptr &operand)
  {
    if(operand.empty()) return false;
    if(is_type<bool>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_bool(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a bool.
const bool &deref_to_bool(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_bool(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<bool>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un int.
bool is_const_ptr_to_int(const any_const_ptr &operand)
  {
    if(operand.empty()) return false;
    if(is_type<int>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_int(deref_to_boost_any(operand));
    else
      return false;
  }


//! @brief Devuelve una referencia a int.
const int &deref_to_int(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_int(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<int>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un long int.
bool is_const_ptr_to_long_int(const any_const_ptr &operand)
  {
    if(operand.empty()) return false;
    if(is_type<long int>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_long_int(deref_to_boost_any(operand));
    else
      return false;
  }


//! @brief Devuelve una referencia a long int.
const long int &deref_to_long_int(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_long_int(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<long int>(operand));
  }

//! @brief Devuelve verdadero si es un vector de cadenas de caracteres.
bool is_const_ptr_to_vector_string(const any_const_ptr &operand)
  {
    if(operand.empty()) return false;
    if(is_type<std::vector<std::string> >(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_vector_string(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a vector<std::string>.
const std::vector<std::string> &deref_to_vector_string(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_vector_string(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<std::vector<std::string> >(operand));
  }

//! @brief Devuelve verdadero si es un vector de enteros.
bool is_const_ptr_to_vector_int(const any_const_ptr &operand)
  {
    if(operand.empty()) return false;
    if(is_type<std::vector<int> >(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_vector_int(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a vector<int>.
const std::vector<int> &deref_to_vector_int(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_vector_int(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<std::vector<int> >(operand));
  }

//! @brief Devuelve verdadero si es un vector de doubles.
bool is_const_ptr_to_vector_double(const any_const_ptr &operand)
  {
    if(operand.empty()) return false;
    if(is_type<std::vector<double> >(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_vector_double(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a vector<double>.
const std::vector<double> &deref_to_vector_double(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_vector_double(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<std::vector<double> >(operand));
  }

//! @brief Devuelve verdadero si es un vector de enteros largos.
bool is_const_ptr_to_vector_long_int(const any_const_ptr &operand)
  {
    if(operand.empty()) return false;
    if(is_type<std::vector<long int> >(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_vector_long_int(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a vector<long int>.
const std::vector<long int> &deref_to_vector_long_int(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_vector_long_int(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<std::vector<long int> >(operand));
  }

//! @brief Devuelve verdadero si es un vector de boost::any.
bool is_const_ptr_to_vector_any(const any_const_ptr &operand)
  {
    if(operand.empty()) return false;
    if(is_type<std::vector<boost::any> >(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_vector_any(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a vector<boost::any>.
const std::vector<boost::any> &deref_to_vector_any(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_vector_any(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<std::vector<boost::any> >(operand));
  }

//! @brief Devuelve verdadero si el objeto es un size_t.
bool is_const_ptr_to_size_t(const any_const_ptr &operand)
  {
    if(operand.empty()) return false;
    if(is_type<size_t>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_size_t(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a size_t.
const size_t &deref_to_size_t(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_size_t(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<size_t>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un string.
//! XXX ¡Ojo! Devuelve falso si es (char *).
bool is_const_ptr_to_string(const any_const_ptr &operand)
  {
    if(operand.empty()) return false;
    if(is_type<std::string>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_string(deref_to_boost_any(operand));
    else
      return false;
  }
//! @brief Devuelve una referencia a string.
const std::string &deref_to_string(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_string(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<std::string>(operand));
  }
//! @brief Devuelve verdadero si el objeto es un Path.
bool is_const_ptr_to_path(const any_const_ptr &operand)
  {
    if(is_type<Path>(operand))
      return true;
    else if(is_const_ptr_to_path(operand))
      return boost_any_is_path(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a Path.
const Path &deref_to_path(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_path(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<Path>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un float.
bool is_const_ptr_to_float(const any_const_ptr &operand)
  {
    if(operand.empty()) return false;
    if(is_type<float>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_float(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a float.
const float &deref_to_float(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_float(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<float>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un double.
bool is_const_ptr_to_double(const any_const_ptr &operand)
  {
    if(operand.empty()) return false;
    if(is_type<double>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_double(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a double.
const double &deref_to_double(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_double(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<double>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un long double.
bool is_const_ptr_to_long_double(const any_const_ptr &operand)
  {
    if(operand.empty()) return false;
    if(is_type<long double>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_long_double(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a long double.
const long double &deref_to_long_double(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_long_double(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<long double>(operand));
  }

//! @brief Devuelve verdadero si el objeto es una m_int.
bool is_const_ptr_to_m_int(const any_const_ptr &operand)
  {
    if(is_type<m_int>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_m_int(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a m_int.
const m_int &deref_to_m_int(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_m_int(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<m_int>(operand));
  }

//! @brief Devuelve verdadero si el objeto es una m_sizet.
bool is_const_ptr_to_m_sizet(const any_const_ptr & operand)
  {
    if(is_type<m_sizet>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_m_sizet(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a m_sizet.
const m_sizet &deref_to_m_sizet(const any_const_ptr & operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_m_sizet(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<m_sizet>(operand));
  }

//! @brief Devuelve verdadero si el objeto es una m_double.
bool is_const_ptr_to_m_double(const any_const_ptr & operand)
  {
    if(is_type<m_double>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_m_double(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a m_double.
const m_double &deref_to_m_double(const any_const_ptr & operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_m_double(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<m_double>(operand));
  }

//! @brief Devuelve verdadero si el objeto es una m_string.
bool is_const_ptr_to_m_string(const any_const_ptr & operand)
  {
    if(is_type<m_string>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_m_string(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a m_string.
const m_string &deref_to_m_string(const any_const_ptr & operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_m_string(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<m_string>(operand));
  }

//! @brief Devuelve verdadero si el objeto es una matrizM.
bool is_const_ptr_to_matrizM(const any_const_ptr &operand)
  {
    if(is_type<matrizM>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_matrizM(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a matrizM.
const matrizM &deref_to_matrizM(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_matrizM(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<matrizM>(operand));
  }

//! @brief Devuelve verdadero si el objeto es una matrizMExpr.
bool is_const_ptr_to_matrizMExpr(const any_const_ptr &operand)
  {
    if(is_type<matrizMExpr>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_matrizMExpr(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a matrizMExpr.
const matrizMExpr &deref_to_matrizMExpr(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_matrizMExpr(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<matrizMExpr>(operand));
  }

//! @brief Devuelve verdadero si el objeto es una MatrizAny.
bool is_const_ptr_to_matriz_any(const any_const_ptr &operand)
  {
    if(is_type<MatrizAny>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_matriz_any(deref_to_boost_any(operand));
    else
      return false;
  }

const MatrizAny &deref_to_matriz_any(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_matriz_any(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<MatrizAny>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un ExprAlgebra.
bool is_const_ptr_to_expr_algebra(const any_const_ptr &operand)
  {
    if(operand.empty()) return false;
    if(is_type<ExprAlgebra>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_expr_algebra(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a ExprAlgebra.
const ExprAlgebra &deref_to_ExprAlgebra(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_ExprAlgebra(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<ExprAlgebra>(operand));
  }

//! @brief Devuelve verdadero si el objeto es una matrizExpr.
bool is_const_ptr_to_matriz_expr(const any_const_ptr & operand)
  {
    if(is_type<matrizExpr>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_matriz_expr(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a matrizExpr.
const matrizExpr &deref_to_matrizExpr(const any_const_ptr & operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_matrizExpr(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<matrizExpr>(operand));
  }

bool is_const_ptr_to_any_const_ptr(const any_const_ptr &operand)
  {
    if(operand.empty())
      return false;
    else
      return is_type<any_const_ptr>(operand);
  }

//! @brief Devuelve verdadero si el objeto es un número de cualquier tipo.
bool is_const_ptr_to_number(const any_const_ptr &operand)
  {
    if(operand.empty()) return false;
    if(is_const_ptr_to_int(operand)) return true;
    if(is_const_ptr_to_double(operand)) return true;
    if(is_const_ptr_to_float(operand)) return true;
    if(is_const_ptr_to_size_t(operand)) return true;
    return false;
  }
//! @brief Devuelve un double si el operando es un número de cualquier tipo (int,size_t,double,...)
double deref_number_to_double(const any_const_ptr &operand)
  {
    double retval= 0.0;
    if(is_const_ptr_to_number(operand))
      {
        if(is_const_ptr_to_int(operand)) retval= boost::lexical_cast<double>(deref_to_int(operand));
        if(is_const_ptr_to_float(operand)) retval= deref_to_float(operand);
        if(is_const_ptr_to_double(operand)) retval= deref_to_double(operand);
        if(is_const_ptr_to_size_t(operand)) retval= boost::lexical_cast<double>(deref_to_size_t(operand));
      }
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es de tipo lista.
bool is_const_ptr_to_lista(const any_const_ptr &operand)
  {
    if(operand.empty())
      return false;
    else if(is_type<Lista>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_lista(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a Lista.
const Lista &deref_to_lista(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_lista(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<Lista>(operand));
  }

//! @brief Devuelve verdadero si el objeto es de tipo mapa.
bool is_const_ptr_to_mapa(const any_const_ptr &operand)
  {
    if(operand.empty())
      return false;
    else if(is_type<Mapa>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_mapa(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a Mapa.
const Mapa &deref_to_mapa(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_mapa(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<Mapa>(operand));
  }

//! @brief Devuelve verdadero si el objeto es de tipo funcion por puntos.
bool is_const_ptr_to_CmdFuncPorPuntos(const any_const_ptr &operand)
  {
    if(operand.empty())
      return false;
    else if(is_type<CmdFuncPorPuntos>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_CmdFuncPorPuntos(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a CmdFuncPorPuntos.
const CmdFuncPorPuntos &deref_to_CmdFuncPorPuntos(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_CmdFuncPorPuntos(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<CmdFuncPorPuntos>(operand));
  }

//! @brief Devuelve verdadero si el objeto es de tipo EntCmd.
bool is_const_ptr_to_ent_cmd(const any_const_ptr &operand)
  {
    if(operand.empty())
      return false;
    else if(operand.isEntCmd())
      return true;
    else if(is_type<EntCmd>(operand))
      return true;
//     else if(is_const_ptr_to_boost_any(operand))
//       return boost_any_is_lista(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve verdadero si el objeto es un Geom_FT.
bool is_const_ptr_to_geom_FT(const any_const_ptr &operand)
  {
    if(is_type<GEOM_FT>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_geom_FT(deref_to_boost_any(operand));
    else
      return false;
  }
//! @brief Devuelve una referencia a Geom_FT.
const GEOM_FT &deref_to_geom_FT(const any_const_ptr & operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_geom_FT(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<GEOM_FT>(operand));
  }

//! @brief Devuelve verdadero si el objeto es una matriz_FT.
bool is_const_ptr_to_matriz_FT(const any_const_ptr & operand)
  {
    if(is_type<matriz_FT>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_matriz_FT(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a matriz_FT.
const matriz_FT &deref_to_matriz_FT(const any_const_ptr & operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_matriz_FT(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<matriz_FT>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un Vector2d.
bool is_const_ptr_to_vector2d(const any_const_ptr &operand)
  {
    if(is_type<Vector2d>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_vector2d(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a Vector2d.
const Vector2d &deref_to_vector2d(const any_const_ptr & operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_vector2d(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<Vector2d>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un Segmento2d.
bool is_const_ptr_to_segmento2d(const any_const_ptr &operand)
  {
    if(is_type<Segmento2d>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_segmento2d(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a Segmento2d.
const Segmento2d &deref_to_segmento2d(const any_const_ptr & operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_segmento2d(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<Segmento2d>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un Vector3d.
bool is_const_ptr_to_vector3d(const any_const_ptr &operand)
  {
    if(is_type<Vector3d>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_vector3d(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a Vector3d.
const Vector3d &deref_to_vector3d(const any_const_ptr & operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_vector3d(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<Vector3d>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un Recta2d.
bool is_const_ptr_to_recta2d(const any_const_ptr &operand)
  {
    if(is_type<Recta2d>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_recta2d(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a Recta2d.
const Recta2d &deref_to_recta2d(const any_const_ptr & operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_recta2d(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<Recta2d>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un Poligono2d.
bool is_const_ptr_to_poligono2d(const any_const_ptr &operand)
  {
    if(is_type<Poligono2d>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_poligono2d(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a Poligono2d.
const Poligono2d &deref_to_poligono2d(const any_const_ptr & operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_poligono2d(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<Poligono2d>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un PoligonoConAgujeros2d.
bool is_const_ptr_to_poligono_con_agujeros2d(const any_const_ptr &operand)
  {
    if(is_type<PoligonoConAgujeros2d>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_poligono_con_agujeros2d(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a PoligonoConAgujeros2d.
const PoligonoConAgujeros2d &deref_to_poligono_con_agujeros2d(const any_const_ptr & operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_poligono_con_agujeros2d(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<PoligonoConAgujeros2d>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un Circulo2d.
bool is_const_ptr_to_circulo2d(const any_const_ptr &operand)
  {
    if(is_type<Circulo2d>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_circulo2d(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a Circulo2d.
const Circulo2d &deref_to_circulo2d(const any_const_ptr & operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_circulo2d(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<Circulo2d>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un Recta3d.
bool is_const_ptr_to_recta3d(const any_const_ptr &operand)
  {
    if(is_type<Recta3d>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_recta3d(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a Recta3d.
const Recta3d &deref_to_recta3d(const any_const_ptr & operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_recta3d(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<Recta3d>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un Segmento3d.
bool is_const_ptr_to_segmento3d(const any_const_ptr &operand)
  {
    if(is_type<Segmento3d>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_segmento3d(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a Segmento3d.
const Segmento3d &deref_to_segmento3d(const any_const_ptr & operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_segmento3d(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<Segmento3d>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un VDesliz2d.
bool is_const_ptr_to_vdesliz2d(const any_const_ptr &operand)
  {
    if(is_type<VDesliz2d>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_vdesliz2d(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a VDesliz2d.
const VDesliz2d &deref_to_vdesliz2d(const any_const_ptr & operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_vdesliz2d(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<VDesliz2d>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un VDesliz3d.
bool is_const_ptr_to_vdesliz3d(const any_const_ptr &operand)
  {
    if(is_type<VDesliz3d>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_vdesliz3d(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a VDesliz3d.
const VDesliz3d &deref_to_vdesliz3d(const any_const_ptr & operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_vdesliz3d(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<VDesliz3d>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un VFijo2d.
bool is_const_ptr_to_vfijo2d(const any_const_ptr &operand)
  {
    if(is_type<VFijo2d>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_vfijo2d(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a VFijo2d.
const VFijo2d &deref_to_vfijo2d(const any_const_ptr & operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_vfijo2d(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<VFijo2d>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un VFijo3d.
bool is_const_ptr_to_vfijo3d(const any_const_ptr &operand)
  {
    if(is_type<VFijo3d>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_vfijo3d(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a VFijo3d.
const VFijo3d &deref_to_vfijo3d(const any_const_ptr & operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_vfijo3d(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<VFijo3d>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un SVD3d.
bool is_const_ptr_to_svd3d(const any_const_ptr &operand)
  {
    if(is_type<SVD3d>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_svd3d(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a SVD3d.
const SVD3d &deref_to_svd3d(const any_const_ptr & operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_svd3d(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<SVD3d>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un Plano3d.
bool is_const_ptr_to_plano3d(const any_const_ptr &operand)
  {
    if(is_type<Plano3d>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_plano3d(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a Plano3d.
const Plano3d &deref_to_plano3d(const any_const_ptr & operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_plano3d(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<Plano3d>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un Pos2d.
bool is_const_ptr_to_pos2d(const any_const_ptr &operand)
  {
    if(is_type<Pos2d>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_pos2d(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a Pos2d.
const Pos2d &deref_to_pos2d(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_pos2d(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<Pos2d>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un ListaPos2d.
bool is_const_ptr_to_lista_pos2d(const any_const_ptr &operand)
  {
    if(is_type<ListaPos2d>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_lista_pos2d(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a ListaPos2d.
const ListaPos2d &deref_to_lista_pos2d(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_lista_pos2d(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<ListaPos2d>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un Polilinea2d.
bool is_const_ptr_to_polilinea2d(const any_const_ptr &operand)
  {
    if(is_type<Polilinea2d>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_polilinea2d(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a Polilinea2d.
const Polilinea2d &deref_to_polilinea2d(const any_const_ptr & operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_polilinea2d(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<Polilinea2d>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un Pos3d.
bool is_const_ptr_to_pos3d(const any_const_ptr & operand)
  {
    if(is_type<Pos3d>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_pos3d(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a Pos3d.
const Pos3d &deref_to_pos3d(const any_const_ptr & operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_pos3d(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<Pos3d>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un ListaPos3d.
bool is_const_ptr_to_lista_pos3d(const any_const_ptr &operand)
  {
    if(is_type<ListaPos3d>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_lista_pos3d(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a ListaPos3d.
const ListaPos3d &deref_to_lista_pos3d(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_lista_pos3d(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<ListaPos3d>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un SemiEspacio3d.
bool is_const_ptr_to_semiEspacio3d(const any_const_ptr &operand)
  {
    if(is_type<SemiEspacio3d>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_se3d(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a SemiEspacio3d.
const SemiEspacio3d &deref_to_semiEspacio3d(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_se3d(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<SemiEspacio3d>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un Poliedro3d.
bool is_const_ptr_to_poliedro3d(const any_const_ptr &operand)
  {
    if(is_type<Poliedro3d>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_poliedro3d(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a Poliedro3d.
const Poliedro3d &deref_to_poliedro3d(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_poliedro3d(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<Poliedro3d>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un Tetraedro3d.
bool is_const_ptr_to_tetraedro3d(const any_const_ptr &operand)
  {
    if(is_type<Tetraedro3d>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_tetra3d(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a Tetraedro3d.
const Tetraedro3d &deref_to_tetraedro3d(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_tetra3d(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<Tetraedro3d>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un BlockPyramid.
bool is_const_ptr_to_blockPyramid(const any_const_ptr &operand)
  {
    if(is_type<BlockPyramid>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_blockPyramid(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a BlockPyramid.
const BlockPyramid &deref_to_blockPyramid(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_blockPyramid(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<BlockPyramid>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un SisCooRect2d3d.
bool is_const_ptr_to_sisCooRect2d3d(const any_const_ptr & operand)
  {
    if(is_type<SisCooRect2d3d>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_sisCooRect2d3d(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a SisCooRect2d3d.
const SisCooRect2d3d &deref_to_sisCooRect2d3d(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_sisCooRect2d3d(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<SisCooRect2d3d>(operand));
  }

//! @brief Devuelve verdadero si el objeto es un Ref2d3d.
bool is_const_ptr_to_ref2d3d(const any_const_ptr & operand)
  {
    if(is_type<Ref2d3d>(operand))
      return true;
    else if(is_const_ptr_to_boost_any(operand))
      return boost_any_is_ref2d3d(deref_to_boost_any(operand));
    else
      return false;
  }

//! @brief Devuelve una referencia a Ref2d3d.
const Ref2d3d &deref_to_ref2d3d(const any_const_ptr &operand)
  {
    if(is_const_ptr_to_boost_any(operand))
      return boost_any_to_ref2d3d(deref_to_boost_any(operand));
    else
      return *(any_const_ptr_cast<Ref2d3d>(operand));
  }

//! @brief Devuelve una referencia a EntCmd.
const EntCmd &deref_to_ent_cmd(const any_const_ptr &operand)
  { return *(operand.getEntCmdPtr()); }

//! @brief Devuelve la cadena de caracteres que representa al objeto con el
//! formato que se pasa como parámetro.
std::string const_ptr_format(const any_const_ptr &operand,const std::string &fmt)
  {
    std::string retval("");
    if(const_ptr_is_empty(operand))
      return retval;
    else if(is_const_ptr_to_any_const_ptr(operand))
      {
	std::cerr << "objeto any_const_ptr anidado." << std::endl;
        return retval;
      }
    else if(is_const_ptr_to_bool(operand))
      {
        retval= format(fmt,deref_to_bool(operand));
        return retval;
      }
    else if(is_const_ptr_to_int(operand))
      {
        retval= format(fmt,deref_to_int(operand));
        return retval;
      }
    else if(is_const_ptr_to_long_int(operand))
      {
        retval= format(fmt,deref_to_long_int(operand));
        return retval;
      }
    else if(is_const_ptr_to_size_t(operand))
      {
        retval= format(fmt,deref_to_size_t(operand));
        return retval;
      }
    else if(is_const_ptr_to_string(operand))
      {
        retval= format(fmt,deref_to_string(operand));
        return retval;
      }
    else if(is_const_ptr_to_float(operand))
      {
        retval= format(fmt,deref_to_float(operand));
        return retval;
      }
    else if(is_const_ptr_to_double(operand))
      {
        retval= format(fmt,deref_to_double(operand));
        return retval;
      }
    else if(is_const_ptr_to_expr_algebra(operand))
      {
        retval= format(fmt,deref_to_ExprAlgebra(operand).ToNum());
        return retval;
      }
    else if(is_const_ptr_to_boost_any(operand))
      {
        retval= boost_any_format(deref_to_boost_any(operand),fmt);
        return retval;
      }
    std::cerr << "print(any_const_ptr): No se ha definido la operación print para el objeto de tipo: "
              << operand.type().name() << " que se pasa como parámetro." << std::endl;
    return retval;
  }



std::ostream &operator<<(std::ostream &os,const any_const_ptr &operand)
  {
    const_ptr_print(os,operand);
    return os;
  }

