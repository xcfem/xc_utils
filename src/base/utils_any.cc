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
//utils_any.cc

#include "utils_any.h"
#include "any_const_ptr.h"
#include "utils_any_const_ptr.h"
#include <boost/any.hpp>
#include "xc_basic/src/funciones/algebra/ExprAlgebra.h"
#include "boost/lexical_cast.hpp"
#include "xc_basic/src/texto/StringFormatter.h"
#include "xc_basic/src/texto/tab_cod.h"

#include "xc_utils/src/nucleo/VarTypes.h"


#include <cctype>
#include <boost/algorithm/string/trim.hpp>
#include "../nucleo/aux_any.h"
#include <boost/math/special_functions/sign.hpp>

//! @brief Devuelve verdadero si está vacío.
bool boost_any_is_empty(const boost::any &operand)
  { return operand.empty(); }

//! @brief Devuelve verdadero si el objeto es un bool.
bool boost_any_is_bool(const boost::any &operand)
  { return operand.type() == typeid(bool); }

//! @brief Devuelve una referencia a bool.
const bool &boost_any_to_bool(const boost::any &operand)
  { return *(boost::any_cast<bool>(&operand)); }

//! @brief Devuelve verdadero si es un vector de caracteres.
bool boost_any_is_vector_char(const boost::any &operand)
  { return operand.type() == typeid(std::vector<char>); }

//! @brief Devuelve una referencia a vector<char>.
const std::vector<char> &boost_any_to_vector_char(const boost::any &operand)
  { return *(boost::any_cast<std::vector<char> >(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en vector<char>.
std::vector<char> convert_to_vector_char(const boost::any &operand)
  {
    std::vector<char> retval;
    if(boost_any_is_vector_char(operand))
      { retval= boost_any_to_vector_char(operand); }
    else if(boost_any_is_char(operand))
      {
        retval.resize(1);
        retval[0]= boost_any_to_char(operand);
      }
    else if(boost_any_is_number(operand))
      {
        retval.resize(1);
        retval[0]= convert_to_char(operand);
      }
    else if(boost_any_is_string(operand))
      {
	const std::string tmp= boost_any_to_string(operand);
        const size_t sz= tmp.size();
        retval.resize(sz);
        for(size_t i= 0;i<sz;i++)
          retval[i]= tmp[i];
      }
    else if(boost_any_is_vector_any(operand))
      {
	const std::vector<boost::any> &tmp= boost_any_to_vector_any(operand);
        const size_t sz= tmp.size();
        retval.resize(sz);
        for(size_t i= 0;i<sz;i++)
          retval[i]= convert_to_char(tmp[i]);
      }
    else if(!operand.empty())
      std::cerr << "convert_to_vector_char; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un vector de enteros." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es un int.
bool boost_any_is_int(const boost::any &operand)
  { return operand.type() == typeid(int); }
//! @brief Devuelve una referencia a int.
const int &boost_any_to_int(const boost::any &operand)
  { return *(boost::any_cast<int>(&operand)); }

//! @brief Devuelve verdadero si el objeto es un long int.
bool boost_any_is_long_int(const boost::any &operand)
  { return operand.type() == typeid(long int); }
//! @brief Devuelve una referencia a int.
const long int &boost_any_to_long_int(const boost::any &operand)
  { return *(boost::any_cast<long int>(&operand)); }

//! @brief Devuelve verdadero si es un vector de cadenas de caracteres.
bool boost_any_is_vector_string(const boost::any &operand)
  { return operand.type() == typeid(std::vector<std::string>); }

//! @brief Devuelve una referencia a vector<std::string>.
const std::vector<std::string> &boost_any_to_vector_string(const boost::any &operand)
  { return *(boost::any_cast<std::vector<std::string> >(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en vector<std::string>.
std::vector<std::string> convert_to_vector_string(const boost::any &operand)
  {
    std::vector<std::string> retval;
    if(boost_any_is_vector_string(operand))
      { retval= boost_any_to_vector_string(operand); }
    else if(boost_any_is_vector_any(operand))
      {
	const std::vector<boost::any> &tmp= boost_any_to_vector_any(operand);
        const int sz= tmp.size();
        retval.resize(sz);
        for(int i= 0;i<sz;i++)
          retval[i]= convert_to_string(tmp[i]);
      }
    else if(boost_any_is_any_const_ptr(operand))
      {
        const any_const_ptr &tmp= boost_any_to_any_const_ptr(operand);
        if(is_const_ptr_to_vector_string(tmp))
          retval= deref_to_vector_string(tmp); 
      }
    else if(!operand.empty())
      std::cerr << "convert_to_vector_string; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un vector de enteros." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si es un vector de enteros.
bool boost_any_is_vector_int(const boost::any &operand)
  { return operand.type() == typeid(std::vector<int>); }

//! @brief Devuelve una referencia a vector<int>.
const std::vector<int> &boost_any_to_vector_int(const boost::any &operand)
  { return *(boost::any_cast<std::vector<int> >(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en vector<int>.
std::vector<int> convert_to_vector_int(const boost::any &operand)
  {
    std::vector<int> retval;
    if(boost_any_is_vector_int(operand))
      { retval= boost_any_to_vector_int(operand); }
    else if(boost_any_is_number(operand))
      {
	const int &tmp= convert_to_int(operand);
        retval.resize(1);
        retval[0]= tmp;
      }
    else if(boost_any_is_vector_any(operand))
      {
	const std::vector<boost::any> &tmp= boost_any_to_vector_any(operand);
        const int sz= tmp.size();
        retval.resize(sz);
        for(int i= 0;i<sz;i++)
          retval[i]= convert_to_int(tmp[i]);
      }
    else if(boost_any_is_any_const_ptr(operand))
      {
        const any_const_ptr &tmp= boost_any_to_any_const_ptr(operand);
        if(is_const_ptr_to_vector_int(tmp))
          retval= deref_to_vector_int(tmp); 
      }
    else if(!operand.empty())
      std::cerr << "convert_to_vector_int; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un vector de enteros." << std::endl;
    return retval;
  }
bool boost_any_is_dq_int(const boost::any &operand)
  { return operand.type() == typeid(std::deque<int>); }

//! @brief Devuelve una referencia a deque<int>.
const std::deque<int> &boost_any_to_dq_int(const boost::any &operand)
  { return *(boost::any_cast<std::deque<int> >(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en deque<int>.
std::deque<int> convert_to_dq_int(const boost::any &operand)
  {
    std::deque<int> retval;
    if(boost_any_is_dq_int(operand))
      { retval= boost_any_to_dq_int(operand); }
    else if(boost_any_is_dq_any(operand))
      {
	const std::deque<boost::any> &tmp= boost_any_to_dq_any(operand);
        const int sz= tmp.size();
        retval.resize(sz);
        for(int i= 0;i<sz;i++)
          retval[i]= convert_to_int(tmp[i]);
      }
    else if(!operand.empty())
      std::cerr << "convert_to_dq_int; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un deque de enteros." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si es un vector de enteros largos.
bool boost_any_is_vector_long_int(const boost::any &operand)
  { return operand.type() == typeid(std::vector<long int>); }

//! @brief Devuelve una referencia a vector<long int>.
const std::vector<long int> &boost_any_to_vector_long_int(const boost::any &operand)
  { return *(boost::any_cast<std::vector<long int> >(&operand)); }


//! @brief Devuelve verdadero si el objeto es un size_t.
bool boost_any_is_size_t(const boost::any &operand)
  { return operand.type() == typeid(size_t); }
//! @brief Devuelve una referencia a size_t.
const size_t &boost_any_to_size_t(const boost::any &operand)
  { return *(boost::any_cast<size_t>(&operand)); }

//! @brief Devuelve verdadero si es un vector de size_t.
bool boost_any_is_vector_size_t(const boost::any &operand)
  { return operand.type() == typeid(std::vector<size_t>); }

//! @brief Intenta, por todos los medios, convertir el argumento en vector<size_t>.
std::vector<size_t> convert_to_vector_size_t(const boost::any &operand)
  {
    std::vector<size_t> retval;
    if(boost_any_is_vector_size_t(operand))
      { retval= boost_any_to_vector_size_t(operand); }
    else if(boost_any_is_number(operand))
      {
	const size_t &tmp= convert_to_size_t(operand);
        retval.resize(1);
        retval[0]= tmp;
      }
    else if(boost_any_is_vector_any(operand))
      {
	const std::vector<boost::any> &tmp= boost_any_to_vector_any(operand);
        const size_t sz= tmp.size();
        retval.resize(sz);
        for(size_t i= 0;i<sz;i++)
          retval[i]= convert_to_size_t(tmp[i]);
      }
//     else if(boost_any_is_any_const_ptr(operand))
//       {
//         const any_const_ptr &tmp= boost_any_to_any_const_ptr(operand);
//         if(is_const_ptr_to_vector_size_t(tmp))
//           retval= deref_to_vector_size_t(tmp); 
//       }
    else if(!operand.empty())
      std::cerr << "convert_to_vector_size_t; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un vector de enteros sin signo." << std::endl;
    return retval;
  }

//! @brief Devuelve una referencia a vector<size_t>.
const std::vector<size_t> &boost_any_to_vector_size_t(const boost::any &operand)
  { return *(boost::any_cast<std::vector<size_t> >(&operand)); }


//! @brief Devuelve verdadero si el objeto es un string.
//! XXX ¡Ojo! Devuelve falso si es (char *).
bool boost_any_is_string(const boost::any &operand)
  { return boost::any_cast<std::string>(&operand); }
//! @brief Devuelve una referencia a string.
const std::string &boost_any_to_string(const boost::any &operand)
  { return *(boost::any_cast<std::string>(&operand)); }

//! @brief Devuelve verdadero si el objeto es de tipo Path.
bool boost_any_is_path(const boost::any &operand)
  { return boost::any_cast<Path>(&operand); }

//! @brief Devuelve una referencia a Path.
const Path &boost_any_to_path(const boost::any &operand)
  { return *(boost::any_cast<Path>(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento
//! un objeto de tipo Path.
Path convert_to_path(const boost::any &operand)
  {
    Path retval;
    if(boost_any_is_path(operand))
      { retval= boost_any_to_path(operand); }
    else if(boost_any_is_string(operand))
      {
	std::string tmp= boost_any_to_string(operand);
        retval= Path(tmp);
      }
    else if(boost_any_is_any_const_ptr(operand))
      {
        const any_const_ptr &tmp= boost_any_to_any_const_ptr(operand);
        if(is_const_ptr_to_string(tmp))
          retval= deref_to_string(tmp); 
      }
    else if(!operand.empty())
      std::cerr << "convert_to_path; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un path." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es un char.
bool boost_any_is_char(const boost::any &operand)
  { return boost::any_cast<char>(&operand); }
//! @brief Devuelve una referencia a string.
const char &boost_any_to_char(const boost::any &operand)
  { return *(boost::any_cast<char>(&operand)); }

//! @brief Devuelve verdadero si el objeto es un float.
bool boost_any_is_float(const boost::any &operand)
  { return boost::any_cast<float>(&operand); }
//! @brief Devuelve una referencia a float.
const float &boost_any_to_float(const boost::any &operand)
  { return *(boost::any_cast<float>(&operand)); }

//! @brief Devuelve verdadero si el objeto es un double.
bool boost_any_is_double(const boost::any &operand)
  { return boost::any_cast<double>(&operand); }
//! @brief Devuelve una referencia a double.
const double &boost_any_to_double(const boost::any &operand)
  { return *(boost::any_cast<double>(&operand)); }

//! @brief Devuelve verdadero si es un vector de double.
bool boost_any_is_vector_double(const boost::any &operand)
  { return operand.type() == typeid(std::vector<double>); }

//! @brief Intenta, por todos los medios, convertir el argumento en vector<double>.
std::vector<double> convert_to_vector_double(const boost::any &operand)
  {
    std::vector<double> retval;
    if(boost_any_is_vector_double(operand))
      { retval= boost_any_to_vector_double(operand); }
    else if(boost_any_is_number(operand))
      {
        retval.resize(1);
	retval[0]= convert_to_double(operand);
      }
    else if(boost_any_is_expr_algebra(operand))
      {
        retval.resize(1);
	retval[0]= convert_to_double(operand);
      }
    else if(boost_any_is_vector_int(operand))
      {
	const std::vector<int> &tmp= boost_any_to_vector_int(operand);
        const size_t sz= tmp.size();
        retval.resize(sz);
        for(size_t i= 0;i<sz;i++)
          retval[i]= convert_to_double(tmp[i]);
      }
    else if(boost_any_is_vector_char(operand))
      {
	const std::vector<char> &tmp= boost_any_to_vector_char(operand);
        const size_t sz= tmp.size();
        retval.resize(sz);
        for(size_t i= 0;i<sz;i++)
          retval[i]= convert_to_double(tmp[i]);
      }
    else if(boost_any_is_vector_size_t(operand))
      {
	const std::vector<size_t> &tmp= boost_any_to_vector_size_t(operand);
        const size_t sz= tmp.size();
        retval.resize(sz);
        for(size_t i= 0;i<sz;i++)
          retval[i]= convert_to_double(tmp[i]);
      }
    else if(boost_any_is_vector_expr(operand))
      {
	const std::vector<ExprAlgebra> &tmp= boost_any_to_vector_expr(operand);
        const size_t sz= tmp.size();
        retval.resize(sz);
        for(size_t i= 0;i<sz;i++)
          retval[i]= convert_to_double(tmp[i]);
      }
    else if(boost_any_is_vector_any(operand))
      {
	const std::vector<boost::any> &tmp= boost_any_to_vector_any(operand);
        const size_t sz= tmp.size();
        retval.resize(sz);
        for(size_t i= 0;i<sz;i++)
          retval[i]= convert_to_double(tmp[i]);
      }
    else if(boost_any_is_dq_any(operand))
      {
	const std::deque<boost::any> &tmp= boost_any_to_dq_any(operand);
        const int sz= tmp.size();
        retval.resize(sz);
        for(int i= 0;i<sz;i++)
          retval[i]= convert_to_double(tmp[i]);
      }
    else if(boost_any_is_m_double(operand))
      {
	const m_double &tmp= boost_any_to_m_double(operand);
        const size_t sz= tmp.size();
        retval.resize(sz);
        size_t j=0;
	for(m_double::const_iterator i= tmp.begin();i!=tmp.end();i++,j++)
          retval[j]= *i;
      }
    else if(boost_any_is_m_string(operand))
      {
	const m_string &tmp= boost_any_to_m_string(operand);
        const size_t sz= tmp.size();
        retval.resize(sz);
        size_t j=0;
	for(m_string::const_iterator i= tmp.begin();i!=tmp.end();i++,j++)
          retval[j]= convert_to_double(*i);
      }
    else if(boost_any_is_m_int(operand))
      {
	const m_int &tmp= boost_any_to_m_int(operand);
        const size_t sz= tmp.size();
        retval.resize(sz);
        size_t j=0;
	for(m_int::const_iterator i= tmp.begin();i!=tmp.end();i++,j++)
          retval[j]= *i;
      }
    else if(boost_any_is_m_sizet(operand))
      {
	const m_sizet &tmp= boost_any_to_m_sizet(operand);
        const size_t sz= tmp.size();
        retval.resize(sz);
        size_t j=0;
	for(m_sizet::const_iterator i= tmp.begin();i!=tmp.end();i++,j++)
          retval[j]= *i;
      }
    else if(boost_any_is_vector3d(operand))
      {
	const Vector3d &tmp= boost_any_to_vector3d(operand);
        retval.resize(3);
        retval[0]= tmp.x();
        retval[1]= tmp.y();
        retval[2]= tmp.z();
      }
    else if(boost_any_is_vector2d(operand))
      {
	const Vector2d &tmp= boost_any_to_vector2d(operand);
        retval.resize(2);
        retval[0]= tmp.x();
        retval[1]= tmp.y();
      }
    else if(boost_any_is_pos3d(operand))
      {
	const Pos3d &tmp= boost_any_to_pos3d(operand);
        retval.resize(3);
        retval[0]= tmp.x();
        retval[1]= tmp.y();
        retval[2]= tmp.z();
      }
    else if(boost_any_is_pos2d(operand))
      {
	const Pos2d &tmp= boost_any_to_pos2d(operand);
        retval.resize(2);
        retval[0]= tmp.x();
        retval[1]= tmp.y();
      }
    else if(boost_any_is_any_const_ptr(operand))
      {
        const any_const_ptr &tmp= boost_any_to_any_const_ptr(operand);
        if(is_const_ptr_to_vector_double(tmp))
          retval= deref_to_vector_double(tmp);
        else if(is_const_ptr_to_m_double(tmp))
          {
            const m_double &mdbl= deref_to_m_double(tmp);
            const size_t sz= mdbl.size();
            retval.resize(sz);
            size_t j=0;
	    for(m_double::const_iterator i= mdbl.begin();i!=mdbl.end();i++,j++)
              retval[j]= *i;            
          }
        else if(is_const_ptr_to_vector_any(tmp))
          retval= convert_to_vector_double(deref_to_vector_any(tmp));
      }
    else if(!operand.empty())
      std::cerr << "convert_to_vector_double; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un vector de doubles." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es una m_int.
bool boost_any_is_m_int(const boost::any & operand)
  { return boost::any_cast<m_int>(&operand); }

//! @brief Devuelve una referencia a m_int.
const m_int &boost_any_to_m_int(const boost::any & operand)
  { return *(boost::any_cast<m_int>(&operand)); }

//! @brief Devuelve verdadero si el objeto es una m_sizet.
bool boost_any_is_m_sizet(const boost::any & operand)
  { return boost::any_cast<m_sizet>(&operand); }

//! @brief Devuelve una referencia a m_sizet.
const m_sizet &boost_any_to_m_sizet(const boost::any & operand)
  { return *(boost::any_cast<m_sizet>(&operand)); }

//! @brief Devuelve verdadero si el objeto es una m_double.
bool boost_any_is_m_double(const boost::any & operand)
  { return boost::any_cast<m_double>(&operand); }

//! @brief Devuelve una referencia a m_double.
const m_double &boost_any_to_m_double(const boost::any &operand)
  { return *(boost::any_cast<m_double>(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en vector<boost::any>.
m_double convert_to_m_double(const boost::any &operand)
  {
    m_double retval;
    if(boost_any_is_m_double(operand))
      { retval= boost_any_to_m_double(operand); }
    else if(boost_any_is_matriz_any(operand))
      {
        MatrizAny tmp= boost_any_to_matriz_any(operand);
        const size_t fls= tmp.getNumFilas();
        const size_t cls= tmp.getNumCols();
        retval= m_double(fls,cls);
        for(size_t i= 1;i<=fls;i++)
          for(size_t j= 1;j<=cls;j++)
            retval(i,j)= convert_to_double(tmp(i,j));
      }
    else if(boost_any_is_vector_any(operand))
      {
        const std::vector<boost::any> &tmp= boost_any_to_vector_any(operand);
        const size_t cls= tmp.size();
        retval= m_double(1,cls);
        for(size_t j= 0;j<cls;j++)
          retval(1,j+1)= convert_to_double(tmp[j]);
      }
    else if(boost_any_is_vector_double(operand))
      {
        const std::vector<double> tmp= boost_any_to_vector_double(operand);
        const size_t cls= tmp.size();
        retval= m_double(1,cls);
        for(size_t j= 0;j<cls;j++)
          retval(1,j+1)= tmp[j];
      }
    else if(boost_any_is_any_const_ptr(operand))
      {
        const any_const_ptr &tmp= boost_any_to_any_const_ptr(operand);
        if(is_const_ptr_to_m_double(tmp))
          retval= deref_to_m_double(tmp); 
      }
    else
      { retval= m_double(1,1,convert_to_double(operand)); }
    return retval;
  }
//! @brief Devuelve verdadero si el objeto es una m_string.
bool boost_any_is_m_string(const boost::any & operand)
  { return boost::any_cast<m_string>(&operand); }

//! @brief Devuelve una referencia a m_string.
const m_string &boost_any_to_m_string(const boost::any &operand)
  { return *(boost::any_cast<m_string>(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en vector<boost::any>.
m_string convert_to_m_string(const boost::any &operand)
  {
    m_string retval;
    if(boost_any_is_m_string(operand))
      { retval= boost_any_to_m_string(operand); }
    else if(boost_any_is_matriz_any(operand))
      {
        MatrizAny tmp= boost_any_to_matriz_any(operand);
        const size_t fls= tmp.getNumFilas();
        const size_t cls= tmp.getNumCols();
        retval= m_string(fls,cls);
        for(size_t i= 1;i<=fls;i++)
          for(size_t j= 1;j<=cls;j++)
            retval(i,j)= convert_to_string(tmp(i,j));
      }
    else if(boost_any_is_any_const_ptr(operand))
      {
        const any_const_ptr &tmp= boost_any_to_any_const_ptr(operand);
        if(is_const_ptr_to_m_string(tmp))
          retval= deref_to_m_string(tmp); 
      }
    else
      { retval= m_string(1,1,convert_to_string(operand)); }
    return retval;
  }

//! @brief Intenta, por todos los medios, convertir el argumento en vector<boost::any>.
m_int convert_to_m_int(const boost::any &operand)
  {
    m_int retval;
    if(boost_any_is_m_int(operand))
      { retval= boost_any_to_m_int(operand); }
    else if(boost_any_is_m_double(operand))
      {
        m_double tmp= boost_any_to_m_double(operand);
        const size_t fls= tmp.getNumFilas();
        const size_t cls= tmp.getNumCols();
        retval= m_int(fls,cls);
        for(size_t i= 1;i<=fls;i++)
          for(size_t j= 1;j<=cls;j++)
            retval(i,j)= boost::lexical_cast<int>(tmp(i,j));
      }
    else if(boost_any_is_matriz_any(operand))
      {
        MatrizAny tmp= boost_any_to_matriz_any(operand);
        const size_t fls= tmp.getNumFilas();
        const size_t cls= tmp.getNumCols();
        retval= m_int(fls,cls);
        for(size_t i= 1;i<=fls;i++)
          for(size_t j= 1;j<=cls;j++)
            retval(i,j)= convert_to_int(tmp(i,j));
      }
    else if(boost_any_is_any_const_ptr(operand))
      {
        const any_const_ptr &tmp= boost_any_to_any_const_ptr(operand);
        if(is_const_ptr_to_m_int(tmp))
          retval= deref_to_m_int(tmp); 
      }
    else
      { retval= m_int(1,1,convert_to_int(operand)); }
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es una matrizM.
bool boost_any_is_matrizM(const boost::any & operand)
  { return boost::any_cast<matrizM>(&operand); }

//! @brief Devuelve una referencia a matrizM.
const matrizM &boost_any_to_matrizM(const boost::any & operand)
  { return *(boost::any_cast<matrizM>(&operand)); }

//! @brief Devuelve verdadero si el objeto es una matrizMExpr.
bool boost_any_is_matrizMExpr(const boost::any & operand)
  { return boost::any_cast<matrizMExpr>(&operand); }

//! @brief Devuelve una referencia a matrizMExpr.
const matrizMExpr &boost_any_to_matrizMExpr(const boost::any & operand)
  { return *(boost::any_cast<matrizMExpr>(&operand)); }

//! @brief Devuelve una referencia a vector<double>.
const std::vector<double> &boost_any_to_vector_double(const boost::any &operand)
  { return *(boost::any_cast<std::vector<double> >(&operand)); }


//! @brief Devuelve verdadero si el objeto es un long double.
bool boost_any_is_long_double(const boost::any &operand)
  { return boost::any_cast<long double>(&operand); }
//! @brief Devuelve una referencia a long double.
const long double &boost_any_to_long_double(const boost::any &operand)
  { return *(boost::any_cast<long double>(&operand)); }


//! @brief Devuelve una referencia a ExprAlgebra.
const ExprAlgebra &boost_any_to_ExprAlgebra(const boost::any &operand)
  { return *(boost::any_cast<ExprAlgebra>(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en un ExprAlgebra.
ExprAlgebra convert_to_ExprAlgebra(const boost::any &operand)
  {
    ExprAlgebra retval;
    if(boost_any_is_expr_algebra(operand))
      { retval= boost_any_to_ExprAlgebra(operand); }
    else if(boost_any_is_number(operand))
      { retval= ExprAlgebra(boost_any_number_to_double(operand)); }
    else if(boost_any_is_string(operand))
      { retval= ExprAlgebra(boost_any_to_string(operand)); }
    else if(boost_any_is_any_const_ptr(operand))
      {
        const any_const_ptr &tmp= boost_any_to_any_const_ptr(operand);
        if(is_const_ptr_to_expr_algebra(tmp))
          retval= deref_to_ExprAlgebra(tmp); 
      }
    else if(!operand.empty())
      std::cerr << "convert_to_ExprAlgebra; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en una expresión algebraica." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si es un vector de caracteres.
bool boost_any_is_vector_expr(const boost::any &operand)
  { return operand.type() == typeid(std::vector<ExprAlgebra>); }

//! @brief Devuelve una referencia a vector<ExprAlgebra>.
const std::vector<ExprAlgebra> &boost_any_to_vector_expr(const boost::any &operand)
  { return *(boost::any_cast<std::vector<ExprAlgebra> >(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en vector<ExprAlgebra>.
std::vector<ExprAlgebra> convert_to_vector_expr(const boost::any &operand)
  {
    std::vector<ExprAlgebra> retval;
    if(boost_any_is_vector_expr(operand))
      { retval= boost_any_to_vector_expr(operand); }
    else if(boost_any_is_expr_algebra(operand))
      {
        retval.resize(1);
        retval[0]= boost_any_to_ExprAlgebra(operand);
      }
    else if(boost_any_is_number(operand))
      {
        retval.resize(1);
        retval[0]= convert_to_ExprAlgebra(operand);
      }
    else if(boost_any_is_vector_any(operand))
      {
	const std::vector<boost::any> &tmp= boost_any_to_vector_any(operand);
        const size_t sz= tmp.size();
        retval.resize(sz);
        for(size_t i= 0;i<sz;i++)
          retval[i]= convert_to_ExprAlgebra(tmp[i]);
      }
//     else if(boost_any_is_any_const_ptr(operand))
//       {
//         const any_const_ptr &tmp= boost_any_to_any_const_ptr(operand);
//         if(is_const_ptr_to_vector_expr(tmp))
//           retval= deref_to_vector_expr(tmp); 
//       }
    else if(!operand.empty())
      std::cerr << "convert_to_vector_expr; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un vector de enteros." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es una matrizExpr.
bool boost_any_is_matriz_expr(const boost::any & operand)
  { return boost::any_cast<matrizExpr>(&operand); }

//! @brief Devuelve una referencia a matrizExpr.
const matrizExpr &boost_any_to_matrizExpr(const boost::any & operand)
  { return *(boost::any_cast<matrizExpr>(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en un double.
double convert_to_double(const boost::any &operand)
  {
    double retval= NAN;
    if(boost_any_is_expr_algebra(operand))
      { retval= boost_any_to_ExprAlgebra(operand).ToNum(); }
    else if(boost_any_is_number(operand))
      { retval= boost_any_number_to_double(operand); }
    else if(boost_any_is_bool(operand))
      { retval= boost_any_to_bool(operand); }
    else if(boost_any_is_string(operand))
      {
        const std::string tmp= boost_any_to_string(operand);
        if(isNumber(tmp))
          retval= boost::lexical_cast<double>(tmp);
      }
    else if(boost_any_is_any_const_ptr(operand))
      {
        const any_const_ptr &tmp= boost_any_to_any_const_ptr(operand);
        if(is_const_ptr_to_double(tmp))
          retval= deref_to_double(tmp); 
      }
    else if(!operand.empty())
      std::cerr << "convert_to_double; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un double." << std::endl;
    return retval;
  }

//! @brief Intenta, por todos los medios, convertir el argumento en un long double.
long double convert_to_long_double(const boost::any &operand)
  {
    long double retval= NAN;
    if(boost_any_is_expr_algebra(operand))
      { retval= boost_any_to_ExprAlgebra(operand).ToNum(); }
    else if(boost_any_is_number(operand))
      { retval= boost_any_number_to_long_double(operand); }
    else if(boost_any_is_bool(operand))
      { retval= boost_any_to_bool(operand); }
    else if(boost_any_is_string(operand))
      {
        const std::string tmp= boost_any_to_string(operand);
        if(isNumber(tmp))
          retval= boost::lexical_cast<long double>(tmp);
      }
    else if(boost_any_is_any_const_ptr(operand))
      {
        const any_const_ptr &tmp= boost_any_to_any_const_ptr(operand);
        if(is_const_ptr_to_long_double(tmp))
          retval= deref_to_long_double(tmp); 
      }
    else if(!operand.empty())
      std::cerr << "convert_to_long_double; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un long double." << std::endl;
    return retval;
  }

//! @brief Intenta, por todos los medios, convertir el argumento en un bool.
bool convert_to_bool(const boost::any &operand)
  {
    bool retval= false;
    if(boost_any_is_bool(operand))
      { retval= boost_any_to_bool(operand); }
    else if(boost_any_is_expr_algebra(operand))
      {
        const ExprAlgebra expr= boost_any_to_ExprAlgebra(operand);
        if(expr.Evaluable())
          if(expr.ToNum()!=0.0)
            retval= true;
      }
    else if(boost_any_is_number(operand))
      { retval= (boost_any_number_to_double(operand) == 1.0); }
    else if(boost_any_is_string(operand))
      {
        const std::string tmp= q_blancos(boost_any_to_string(operand));
        if(isNumber(tmp))
          retval= boost::lexical_cast<bool>(tmp);
        else if(toupper(tmp)=="SI")
          retval= true;
      }
    else if(boost_any_is_any_const_ptr(operand))
      {
        const any_const_ptr &tmp= boost_any_to_any_const_ptr(operand);
        if(is_const_ptr_to_bool(tmp))
          retval= deref_to_bool(tmp); 
      }
    else if(!operand.empty())
      std::cerr << "convert_to_bool; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un booleano." << std::endl;
    return retval;
  }

//! @brief Intenta, por todos los medios, convertir el argumento en un int.
int convert_to_int(const boost::any &operand)
  {
    int retval= 0;
    if(boost_any_is_int(operand))
      { retval= boost_any_to_int(operand); }
    else if(boost_any_is_expr_algebra(operand))
      {
        const ExprAlgebra expr= boost_any_to_ExprAlgebra(operand);
        if(expr.Evaluable())
          retval= static_cast<int>(expr.ToNum());
      }
    else if(boost_any_is_number(operand))
      { retval= static_cast<int>(boost_any_number_to_double(operand)); }
    else if(boost_any_is_string(operand))
      {
        const std::string tmp= boost_any_to_string(operand);
        if(isNumber(tmp))
          retval= boost::lexical_cast<int>(tmp);
      }
    else if(boost_any_is_any_const_ptr(operand))
      {
        const any_const_ptr &tmp= boost_any_to_any_const_ptr(operand);
        if(is_const_ptr_to_int(tmp))
          retval= deref_to_int(tmp); 
      }
    else if(!operand.empty())
      std::cerr << "convert_to_int; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un entero." << std::endl;
    return retval;
  }

//! @brief Intenta, por todos los medios, convertir el argumento en un long int.
long int convert_to_long_int(const boost::any &operand)
  {
    long int retval= 0;
    if(boost_any_is_long_int(operand))
      { retval= boost_any_to_long_int(operand); }
    else if(boost_any_is_expr_algebra(operand))
      {
        const ExprAlgebra expr= boost_any_to_ExprAlgebra(operand);
        if(expr.Evaluable())
          retval= static_cast<long int>(expr.ToNum());
      }
    else if(boost_any_is_number(operand))
      { retval= static_cast<long int>(boost_any_number_to_double(operand)); }
    else if(boost_any_is_string(operand))
      {
        const std::string tmp= boost_any_to_string(operand);
        if(isNumber(tmp))
          retval= boost::lexical_cast<long int>(tmp);
      }
    else if(boost_any_is_any_const_ptr(operand))
      {
        const any_const_ptr &tmp= boost_any_to_any_const_ptr(operand);
        if(is_const_ptr_to_long_int(tmp))
          retval= deref_to_long_int(tmp); 
      }
    else if(!operand.empty())
      std::cerr << "convert_to_long_int; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un entero." << std::endl;
    return retval;
  }

//! @brief Intenta, por todos los medios, convertir el argumento en un size_t.
size_t convert_to_size_t(const boost::any &operand)
  {
    size_t retval= 0;
    if(boost_any_is_size_t(operand))
      { retval= boost_any_to_size_t(operand); }
    else if(boost_any_is_int(operand))
      {
        const int tmp= boost_any_to_int(operand);
        if(tmp<0)
	  std::cerr << "convert_to_size_t; se asignó un entero negativo." << std::endl;
        retval= static_cast<size_t>(tmp);
      }
    else if(boost_any_is_expr_algebra(operand))
      {
        const ExprAlgebra expr= boost_any_to_ExprAlgebra(operand);
        if(expr.Evaluable())
          {
            const double tmp= expr.ToNum();
            if(tmp<0)
              std::cerr << "convert_to_size_t; se asignó un número negativo." << std::endl;
            retval= static_cast<size_t>(tmp);
          }
      }
    else if(boost_any_is_number(operand))
      { retval= static_cast<size_t>(boost_any_number_to_double(operand)); }
    else if(boost_any_is_string(operand))
      {
        const std::string tmp= boost_any_to_string(operand);
        if(isNumber(tmp))
           retval= boost::lexical_cast<size_t>(tmp);
      }
    else if(boost_any_is_any_const_ptr(operand))
      {
        const any_const_ptr &tmp= boost_any_to_any_const_ptr(operand);
        if(is_const_ptr_to_size_t(tmp))
          retval= deref_to_size_t(tmp); 
      }
    else if(!operand.empty())
      std::cerr << "convert_to_size_t; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un entero sin signo." << std::endl;
    return retval;
  }

//! @brief Intenta, por todos los medios, convertir el argumento en un string.
std::string convert_to_string(const boost::any &operand)
  {
    std::string retval= "";
    if(!operand.empty())
      {
        if(boost_any_is_string(operand))
          { retval= boost_any_to_string(operand); }
        else if(boost_any_is_char_ptr(operand))
          retval= boost::lexical_cast<std::string>(*(boost::any_cast<const char *>(&operand)));
        else if(boost_any_is_path(operand))
          { retval= boost_any_to_path(operand).string(); }
        else if(boost_any_is_int(operand))
          retval= boost::lexical_cast<std::string>(boost_any_to_int(operand));
        else if(boost_any_is_long_int(operand))
          retval= boost::lexical_cast<std::string>(boost_any_to_long_int(operand));
        else if(boost_any_is_size_t(operand))
          retval= boost::lexical_cast<std::string>(boost_any_to_size_t(operand));
        else if(boost_any_is_float(operand))
          retval= boost::lexical_cast<std::string>(boost_any_to_float(operand));
        else if(boost_any_is_double(operand))
          retval= boost::lexical_cast<std::string>(boost_any_to_double(operand));
        else if(boost_any_is_long_double(operand))
          retval= boost::lexical_cast<std::string>(boost_any_to_long_double(operand));
        else if(boost_any_is_any_const_ptr(operand))
          {
            const any_const_ptr &tmp= boost_any_to_any_const_ptr(operand);
            if(is_const_ptr_to_string(tmp))
              retval= deref_to_string(tmp); 
          }
        else
          std::cerr << "convert_to_string; no se pudo convertir el objeto de tipo: '"
                    << boost_any_tipo_operando(operand) 
                    << "' en una cadena de caracteres." << std::endl;
      }
    return retval;
  }

//! @brief Intenta, por todos los medios, convertir el argumento en una cola de strings.
std::deque<std::string> convert_to_dq_string(const std::deque<boost::any> &l)
  {
    std::deque<std::string> retval;
    for(std::deque<boost::any>::const_iterator i= l.begin();i!=l.end();i++)
      retval.push_back(convert_to_string(*i));
    return retval;
  }


//! @brief Intenta, por todos los medios, convertir el argumento en un char.
char convert_to_char(const boost::any &operand)
  {
    char retval= 0;
    if(boost_any_is_char(operand))
      { retval= boost_any_to_char(operand); }
    else if(boost_any_is_string(operand))
      {
        const std::string &str= boost_any_to_string(operand);
        if(!str.empty())
          retval= str[0];
      }
    else if(!operand.empty())
      std::cerr << "convert_to_char; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un char." << std::endl;
    return retval;
  }

//! @brief Intenta, por todos los medios, convertir el argumento en vector<boost::any>.
std::vector<boost::any> convert_to_vector_any(const boost::any &operand)
  {
    std::vector<boost::any> retval;
    if(boost_any_is_vector_any(operand))
      { retval= boost_any_to_vector_any(operand); }
    else if(boost_any_is_m_double(operand))
      {
	const m_double &tmp= boost_any_to_m_double(operand);
        const size_t sz= tmp.size();
        retval.resize(sz);
        size_t j=0;
	for(m_double::const_iterator i= tmp.begin();i!=tmp.end();i++,j++)
          retval[j]= *i;
      }
    else if(boost_any_is_m_int(operand))
      {
	const m_int &tmp= boost_any_to_m_int(operand);
        const size_t sz= tmp.size();
        retval.resize(sz);
        size_t j=0;
	for(m_int::const_iterator i= tmp.begin();i!=tmp.end();i++,j++)
          retval[j]= *i;
      }
    else if(boost_any_is_m_sizet(operand))
      {
	const m_sizet &tmp= boost_any_to_m_sizet(operand);
        const size_t sz= tmp.size();
        retval.resize(sz);
        size_t j=0;
	for(m_sizet::const_iterator i= tmp.begin();i!=tmp.end();i++,j++)
          retval[j]= *i;
      }
    else if(boost_any_is_matriz_any(operand))
      {
	const MatrizAny &tmp= boost_any_to_matriz_any(operand);
        const size_t sz= tmp.size();
        retval.resize(sz);
        size_t j=0;
	for(MatrizAny::const_iterator i= tmp.begin();i!=tmp.end();i++,j++)
          retval[j]= *i;
      }
    else if(boost_any_is_lista(operand))
      {
	const Lista &tmp= boost_any_to_lista(operand);
        const size_t sz= tmp.size();
        retval.resize(sz);
        size_t j=0;
	for(Lista::const_iterator i= tmp.begin();i!=tmp.end();i++,j++)
          retval[j]= *i;
      }
    else if(boost_any_is_vector3d(operand))
      {
	const Vector3d &tmp= boost_any_to_vector3d(operand);
        retval.resize(3);
        retval[0]= tmp.x();
        retval[1]= tmp.y();
        retval[2]= tmp.z();
      }
    else if(boost_any_is_vector2d(operand))
      {
	const Vector2d &tmp= boost_any_to_vector2d(operand);
        retval.resize(2);
        retval[0]= tmp.x();
        retval[1]= tmp.y();
      }
    else if(boost_any_is_pos3d(operand))
      {
	const Pos3d &tmp= boost_any_to_pos3d(operand);
        retval.resize(3);
        retval[0]= tmp.x();
        retval[1]= tmp.y();
        retval[2]= tmp.z();
      }
    else if(boost_any_is_pos2d(operand))
      {
	const Pos2d &tmp= boost_any_to_pos2d(operand);
        retval.resize(2);
        retval[0]= tmp.x();
        retval[1]= tmp.y();
      }
//     else if(boost_any_is_any_const_ptr(operand))
//       {
//         const any_const_ptr &tmp= boost_any_to_any_const_ptr(operand);
//         if(is_const_ptr_to_vector_any(tmp))
//           retval= deref_to_vector_any(tmp); 
//       }
    else
      { retval= std::vector<boost::any>(1,operand); }
    return retval;
  }

//! @brief Intenta, por todos los medios, convertir el argumento en vector<boost::any>.
MatrizAny convert_to_matriz_any(const boost::any &operand)
  {
    MatrizAny retval;
    if(boost_any_is_matriz_any(operand))
      { retval= boost_any_to_matriz_any(operand); }
    else if(boost_any_is_m_double(operand))
      { retval= boost_any_to_m_double(operand); }
    else if(boost_any_is_vector_any(operand))
      { retval= MatrizAny(1,boost_any_to_vector_any(operand)); }
    else if(boost_any_is_vector_double(operand))
      { retval= MatrizAny(1,boost_any_to_vector_any(operand)); }
    else if(boost_any_is_vector3d(operand))
      {
	const Vector3d &tmp= boost_any_to_vector3d(operand);
        retval= MatrizAny(1,3);
        retval(1,1)= tmp.x();
        retval(1,2)= tmp.y();
        retval(1,3)= tmp.z();
      }
    else if(boost_any_is_vector2d(operand))
      {
	const Vector2d &tmp= boost_any_to_vector2d(operand);
        retval= MatrizAny(1,2);
        retval(1,1)= tmp.x();
        retval(1,2)= tmp.y();
      }
    else if(boost_any_is_pos3d(operand))
      {
	const Pos3d &tmp= boost_any_to_pos3d(operand);
        retval= MatrizAny(1,3);
        retval(1,1)= tmp.x();
        retval(1,2)= tmp.y();
        retval(1,3)= tmp.z();
      }
    else if(boost_any_is_pos2d(operand))
      {
	const Pos2d &tmp= boost_any_to_pos2d(operand);
        retval= MatrizAny(1,2);
        retval(1,1)= tmp.x();
        retval(1,2)= tmp.y();
      }
    else if(boost_any_is_any_const_ptr(operand))
      {
        const any_const_ptr &tmp= boost_any_to_any_const_ptr(operand);
        if(is_const_ptr_to_matriz_any(tmp))
          retval= deref_to_matriz_any(tmp);
        else if(is_const_ptr_to_m_double(tmp))
          {
            const m_double &mdbl= deref_to_m_double(tmp);
            const size_t nfilas= mdbl.getNumFilas();
            const size_t ncols= mdbl.getNumCols();
            retval= MatrizAny(nfilas,ncols);
            for(size_t i=1;i<=nfilas;i++)
              for(size_t j=1;j<=ncols;j++)
                retval(i,j)= mdbl(i,j);            
          }
        else if(is_const_ptr_to_vector_any(tmp))
          retval= convert_to_matriz_any(deref_to_vector_any(tmp));
      }
    else
      { retval= MatrizAny(1,1,operand); }
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es un char *.
bool boost_any_is_char_ptr(const boost::any &operand)
  {
    try
      {
        boost::any_cast<const char *>(operand);
        return true;
      }
    catch(const boost::bad_any_cast &)
      {
        return false;
      }
  }

//! @brief Devuelve una cadena de caracteres si el operando es un puntero a carácter.
const std::string char_ptr_to_string(const boost::any &operand)
  { return boost::lexical_cast<std::string>(boost::any_cast<const char *>(operand)); }

//! @brief Devuelve verdadero si el objeto es un ExprAlgebra.
bool boost_any_is_expr_algebra(const boost::any &operand)
  { return boost::any_cast<ExprAlgebra>(&operand); }


//! @brief Devuelve verdadero si el objeto es un número de cualquier tipo.
bool boost_any_is_number(const boost::any &operand)
  {
    bool retval= false;
    if(boost_any_is_bool(operand))
      retval= true;
    else if(boost_any_is_int(operand))
      retval= true;
    else if(boost_any_is_long_int(operand))
      retval= true;
    else if(boost_any_is_double(operand))
      retval= true;
    else if(boost_any_is_long_double(operand))
      retval= true;
    else if(boost_any_is_float(operand))
      retval= true;
    else if(boost_any_is_size_t(operand))
      retval= true;
    else if(boost_any_is_any_const_ptr(operand))
      {
        const any_const_ptr &tmp= boost_any_to_any_const_ptr(operand);
        if(is_const_ptr_to_bool(tmp))
          retval= true;
        else if(is_const_ptr_to_int(tmp))
          retval= true;
        else if(is_const_ptr_to_long_int(tmp))
          retval= true;
        else if(is_const_ptr_to_double(tmp))
          retval= true;
        else if(is_const_ptr_to_long_double(tmp))
          retval= true;
        else if(is_const_ptr_to_float(tmp))
          retval= true;
      }
    return retval;
  }

//! @brief Devuelve un double si el operando es un número de cualquier tipo (int,size_t,double,...)
double boost_any_number_to_double(const boost::any &operand)
  {
    double retval= 0.0;
    if(boost_any_is_number(operand))
      {
        if(boost_any_is_bool(operand))
          retval= static_cast<double>(boost_any_to_bool(operand));
        else if(boost_any_is_int(operand))
          retval= static_cast<double>(boost_any_to_int(operand));
        else if(boost_any_is_long_int(operand))
          retval= static_cast<double>(boost_any_to_long_int(operand));
        else if(boost_any_is_float(operand))
          retval= boost_any_to_float(operand);
        else if(boost_any_is_double(operand))
          retval= boost_any_to_double(operand);
        else if(boost_any_is_long_double(operand))
          retval= static_cast<double>(boost_any_to_long_double(operand));
        else if(boost_any_is_size_t(operand))
          retval= static_cast<double>(boost_any_to_size_t(operand));
        else if(boost_any_is_any_const_ptr(operand))
          {
            const any_const_ptr &tmp= boost_any_to_any_const_ptr(operand);
            if(is_const_ptr_to_bool(tmp))
              retval= deref_to_bool(tmp);
            else if(is_const_ptr_to_int(tmp))
               retval= deref_to_int(tmp);
            else if(is_const_ptr_to_long_int(tmp))
              retval= deref_to_long_int(tmp);
            else if(is_const_ptr_to_double(tmp))
              retval= deref_to_double(tmp);
            else if(is_const_ptr_to_long_double(tmp))
              retval= deref_to_long_double(tmp);
            else if(is_const_ptr_to_float(tmp))
              retval= deref_to_float(tmp);
          }
      }
    return retval;
  }

//! @brief Devuelve un long double si el operando es un número de cualquier tipo (int,size_t,double,...)
long double boost_any_number_to_long_double(const boost::any &operand)
  {
    long double retval= 0.0;
    if(boost_any_is_number(operand))
      {
        if(boost_any_is_bool(operand)) retval= static_cast<long double>(boost_any_to_bool(operand));
        if(boost_any_is_int(operand)) retval= static_cast<long double>(boost_any_to_int(operand));
        if(boost_any_is_long_int(operand)) retval= static_cast<long double>(boost_any_to_long_int(operand));
        if(boost_any_is_float(operand)) retval= boost_any_to_float(operand);
        if(boost_any_is_double(operand)) retval= boost_any_to_double(operand);
        if(boost_any_is_long_double(operand)) retval= boost_any_to_long_double(operand);
        if(boost_any_is_size_t(operand)) retval= static_cast<long double>(boost_any_to_size_t(operand));
      }
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es de tipo lista.
bool boost_any_is_lista(const boost::any &operand)
  { return boost::any_cast<Lista>(&operand); }

//! @brief Devuelve una referencia a Lista.
const Lista &boost_any_to_lista(const boost::any &operand)
  { return *(boost::any_cast<Lista>(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en una lista.
Lista convert_to_lista(const boost::any &operand)
  {
    Lista retval(NULL);
    if(boost_any_is_lista(operand))
      { retval= boost_any_to_lista(operand); }
    else if(boost_any_is_string(operand))
      {
        const std::string &str= boost_any_to_string(operand);
        if(!str.empty())
          retval.fromString(str);
      }
    else if(boost_any_is_double(operand))
      {
        const double &dbl= boost_any_to_double(operand);
        retval.Inserta(dbl);
      }
    else if(boost_any_is_int(operand))
      {
        const int &entero= boost_any_to_int(operand);
        retval.Inserta(entero);
      }
    else if(!operand.empty())
      std::cerr << "convert_to_lista; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en una lista." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es de tipo mapa.
bool boost_any_is_mapa(const boost::any &operand)
  { return boost::any_cast<Mapa>(&operand); }

//! @brief Devuelve una referencia a mapa.
const Mapa &boost_any_to_mapa(const boost::any &operand)
  { return *(boost::any_cast<Mapa>(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en un mapa.
Mapa convert_to_mapa(const boost::any &operand)
  {
    Mapa retval(NULL);
    if(boost_any_is_mapa(operand))
      { retval= boost_any_to_mapa(operand); }
    else if(!operand.empty())
      std::cerr << "convert_to_mapa; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un mapa." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es de tipo record.
bool boost_any_is_record(const boost::any &operand)
  { return boost::any_cast<Record>(&operand); }

//! @brief Devuelve una referencia a Record.
const Record &boost_any_to_record(const boost::any &operand)
  { return *(boost::any_cast<Record>(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en un record.
Record convert_to_record(const boost::any &operand)
  {
    Record retval(NULL);
    if(boost_any_is_record(operand))
      { retval= boost_any_to_record(operand); }
    else if(!operand.empty())
      std::cerr << "convert_to_record; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un record." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es de tipo CmdFuncPorPuntos.
bool boost_any_is_CmdFuncPorPuntos(const boost::any &operand)
  { return boost::any_cast<CmdFuncPorPuntos>(&operand); }

//! @brief Intenta, por todos los medios, convertir el argumento en una función por puntos.
CmdFuncPorPuntos convert_to_CmdFuncPorPuntos(const boost::any &operand)
  {
    CmdFuncPorPuntos retval(NULL);
    if(boost_any_is_CmdFuncPorPuntos(operand))
      { retval= boost_any_to_CmdFuncPorPuntos(operand); }
    else if(boost_any_is_string(operand))
      {
        const std::string &str= boost_any_to_string(operand);
        if(!str.empty())
          retval.fromString(str);
      }
    else if(!operand.empty())
      std::cerr << "convert_to_CmdFuncPorPuntos; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en una función por puntos." << std::endl;
    return retval;
  }


//! @brief Devuelve una referencia a CmdFuncPorPuntos.
const CmdFuncPorPuntos &boost_any_to_CmdFuncPorPuntos(const boost::any &operand)
  { return *(boost::any_cast<CmdFuncPorPuntos>(&operand)); }

//! @brief Devuelve verdadero si el objeto es de tipo EntCmd.
bool boost_any_is_ent_cmd(const boost::any &operand)
  { return boost::any_cast<EntCmd>(&operand); }
const EntCmd &boost_any_to_ent_cmd(const boost::any &operand)
  { return *(boost::any_cast<EntCmd>(&operand)); }

//! @brief Devuelve verdadero si el objeto es de tipo EntCmdPtr.
bool boost_any_is_ent_cmd_ptr(const boost::any &operand)
  { return boost::any_cast<EntCmdPtr>(&operand); }
const EntCmdPtr &boost_any_to_ent_cmd_ptr(const boost::any &operand)
  { return *(boost::any_cast<EntCmdPtr>(&operand)); }


//! @brief Devuelve verdadero si el objeto es de tipo std::vector<boost::any>.
bool boost_any_is_vector_any(const boost::any &operand)
  { return boost::any_cast<std::vector<boost::any> >(&operand); }

//! @brief Devuelve una referencia a std::vector<boost::any>.
const std::vector<boost::any> &boost_any_to_vector_any(const boost::any &operand)
  { return *(boost::any_cast<std::vector<boost::any> >(&operand)); }

//! @brief Devuelve verdadero si el objeto es de tipo std::deque<boost::any>.
bool boost_any_is_dq_any(const boost::any &operand)
  { return operand.type() == typeid(std::deque<boost::any>); }

//! @brief Devuelve una referencia a std::deque<boost::any>.
const std::deque<boost::any> &boost_any_to_dq_any(const boost::any &operand)
  { return *(boost::any_cast<std::deque<boost::any> >(&operand)); }

//! @brief Devuelve verdadero si el objeto es de tipo MatrizT<boost::any,std::vector<boost::any>>.
bool boost_any_is_matriz_any(const boost::any &operand)
  { return boost::any_cast<MatrizAny>(&operand); }

//! @brief Devuelve una referencia a MatrizT<boost::any,std::vector<boost::any>>.
const MatrizAny &boost_any_to_matriz_any(const boost::any &operand)
  { return *(boost::any_cast<MatrizAny>(&operand)); }

//! @brief Devuelve verdadero si el objeto es un Geom_FT.
bool boost_any_is_geom_FT(const boost::any & operand)
  { return operand.type() == typeid(GEOM_FT); }
//! @brief Devuelve una referencia a Geom_FT.
const GEOM_FT &boost_any_to_geom_FT(const boost::any & operand)
  { return *(boost::any_cast<GEOM_FT>(&operand)); }

//! @brief Devuelve verdadero si el objeto es una matriz_FT.
bool boost_any_is_matriz_FT(const boost::any & operand)
  { return boost::any_cast<matriz_FT>(&operand); }

//! @brief Devuelve una referencia a matriz_FT.
const matriz_FT &boost_any_to_matriz_FT(const boost::any & operand)
  { return *(boost::any_cast<matriz_FT>(&operand)); }

//! @brief Devuelve verdadero si el objeto es de tipo Poligono2d.
bool boost_any_is_poligono2d(const boost::any &operand)
  { return boost::any_cast<Poligono2d>(&operand); }

//! @brief Devuelve una referencia a Poligono2d.
const Poligono2d &boost_any_to_poligono2d(const boost::any &operand)
  { return *(boost::any_cast<Poligono2d>(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en Poligono2d.
Poligono2d convert_to_poligono2d(const boost::any &operand)
  {
    Poligono2d retval;
    if(boost_any_is_poligono2d(operand))
      { retval= boost_any_to_poligono2d(operand); }
    else if(boost_any_is_lista_pos2d(operand))
      { retval= Poligono2d(boost_any_to_lista_pos2d(operand).getPuntos()); }
    else if(!operand.empty())
      std::cerr << "convert_to_poligono2d; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un poligono2d." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es de tipo PoligonoConAgujeros2d.
bool boost_any_is_poligono_con_agujeros2d(const boost::any &operand)
  { return boost::any_cast<PoligonoConAgujeros2d>(&operand); }

//! @brief Devuelve una referencia a PoligonoConAgujeros2d.
const PoligonoConAgujeros2d &boost_any_to_poligono_con_agujeros2d(const boost::any &operand)
  { return *(boost::any_cast<PoligonoConAgujeros2d>(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en PoligonoConAgujeros2d.
PoligonoConAgujeros2d convert_to_poligono_con_agujeros2d(const boost::any &operand)
  {
    PoligonoConAgujeros2d retval;
    if(boost_any_is_poligono_con_agujeros2d(operand))
      { retval= boost_any_to_poligono_con_agujeros2d(operand); }
    else if(boost_any_is_poligono2d(operand))
      {
        Poligono2d tmp= boost_any_to_poligono2d(operand);
        retval= PoligonoConAgujeros2d(tmp);
      }
    else if(!operand.empty())
      std::cerr << "convert_to_poligono_con_agujeros2d; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un poligono_con_agujeros2d." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es de tipo ListaPos2d.
bool boost_any_is_lista_pos2d(const boost::any &operand)
  { return boost::any_cast<ListaPos2d>(&operand); }

//! @brief Devuelve una referencia a ListaPos2d.
const ListaPos2d &boost_any_to_lista_pos2d(const boost::any &operand)
  { return *(boost::any_cast<ListaPos2d>(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en ListaPos2d.
ListaPos2d convert_to_lista_pos2d(const boost::any &operand)
  {
    ListaPos2d retval;
    if(boost_any_is_lista_pos2d(operand))
      { retval= boost_any_to_lista_pos2d(operand); }
    else if(boost_any_is_poligono2d(operand))
      {
        Poligono2d tmp= boost_any_to_poligono2d(operand);
        retval= ListaPos2d(tmp.ListaVertices());
      }
    else if(!operand.empty())
      std::cerr << "convert_to_lista_pos2d; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en una ListaPos2d." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es de tipo Polilinea2d.
bool boost_any_is_polilinea2d(const boost::any &operand)
  { return boost::any_cast<Polilinea2d>(&operand); }

//! @brief Devuelve una referencia a Polilinea2d.
const Polilinea2d &boost_any_to_polilinea2d(const boost::any &operand)
  { return *(boost::any_cast<Polilinea2d>(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en Polilinea2d.
Polilinea2d convert_to_polilinea2d(const boost::any &operand)
  {
    Polilinea2d retval;
    if(boost_any_is_polilinea2d(operand))
      { retval= boost_any_to_polilinea2d(operand); }
    else if(boost_any_is_lista_pos2d(operand))
      { retval= Polilinea2d(boost_any_to_lista_pos2d(operand).getPuntos()); }
    else if(!operand.empty())
      std::cerr << "convert_to_polilinea2d; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un polilinea2d." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es de tipo ListaPos3d.
bool boost_any_is_lista_pos3d(const boost::any &operand)
  { return boost::any_cast<ListaPos3d>(&operand); }

//! @brief Devuelve una referencia a ListaPos3d.
const ListaPos3d &boost_any_to_lista_pos3d(const boost::any &operand)
  { return *(boost::any_cast<ListaPos3d>(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en ListaPos3d.
ListaPos3d convert_to_lista_pos3d(const boost::any &operand)
  {
    ListaPos3d retval;
    if(boost_any_is_lista_pos3d(operand))
      { retval= boost_any_to_lista_pos3d(operand); }
    else if(!operand.empty())
      std::cerr << "convert_to_lista_pos3d; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en una ListaPos3d." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es un Vector2d.
bool boost_any_is_vector2d(const boost::any &operand)
  { return operand.type() == typeid(Vector2d); }
//! @brief Devuelve una referencia a Vector2d.
const Vector2d &boost_any_to_vector2d(const boost::any & operand)
  { return *(boost::any_cast<Vector2d>(&operand)); }
//! @brief Intenta, por todos los medios, convertir el argumento en Vector2d.
Vector2d convert_to_vector2d(const boost::any &operand)
  {
    Vector2d retval;
    if(boost_any_is_vector2d(operand))
      { retval= boost_any_to_vector2d(operand); }
    else if(boost_any_is_vector_any(operand))
      {
	const std::vector<boost::any> &tmp= boost_any_to_vector_any(operand);
	std::vector<GEOM_FT> coo(2,0.0);
        const int sz= std::min(tmp.size(),coo.size());
        for(int i= 0;i<sz;i++)
          coo[i]= convert_to_double(tmp[i]);
        retval= Vector2d(coo[0],coo[1]);
      }
    else if(boost_any_is_m_double(operand))
      {
	const m_double &tmp= boost_any_to_m_double(operand);
        const size_t sz= tmp.size();
        if(sz>1)
          {
	    std::vector<double> v(2);
            size_t j=0;
	    for(m_double::const_iterator i= tmp.begin();i!=tmp.end();i++,j++)
              {
                v[j]= *i;
                if(j>1) break;
              }
            retval= Vector2d(v[0],v[1]);
          }
        else
	  std::cerr << "convert_to_vector2d; se necesitan dos coordendadas." << std::endl;
      }
    else if(!operand.empty())
      std::cerr << "convert_to_vector2d; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en una vector2d." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es un Segmento2d.
bool boost_any_is_segmento2d(const boost::any &operand)
  { return operand.type() == typeid(Segmento2d); }
//! @brief Devuelve una referencia a Segmento2d.
const Segmento2d &boost_any_to_segmento2d(const boost::any & operand)
  { return *(boost::any_cast<Segmento2d>(&operand)); }
//! @brief Intenta, por todos los medios, convertir el argumento en Segmento2d.
Segmento2d convert_to_segmento2d(const boost::any &operand)
  {
    Segmento2d retval;
    if(boost_any_is_segmento2d(operand))
      { retval= boost_any_to_segmento2d(operand); }
    else if(boost_any_is_vector_any(operand))
      {
	const std::vector<boost::any> &tmp= boost_any_to_vector_any(operand);
	std::vector<Pos2d> pts(2);
        const int sz= std::min(tmp.size(),pts.size());
        for(int i= 0;i<sz;i++)
          pts[i]= convert_to_pos2d(tmp[i]);
        retval= Segmento2d(pts[0],pts[1]);
      }
    else if(!operand.empty())
      std::cerr << "convert_to_segmento2d; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un segmento2d." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es un Pos2d.
bool boost_any_is_pos2d(const boost::any &operand)
  { return operand.type() == typeid(Pos2d); }
//! @brief Devuelve una referencia a Pos2d.
const Pos2d &boost_any_to_pos2d(const boost::any & operand)
  { return *(boost::any_cast<Pos2d>(&operand)); }
//! @brief Intenta, por todos los medios, convertir el argumento en Pos3d.
Pos2d convert_to_pos2d(const boost::any &operand)
  {
    Pos2d retval;
    if(boost_any_is_pos2d(operand))
      { retval= boost_any_to_pos2d(operand); }
    else if(boost_any_is_vector_any(operand))
      {
	const std::vector<boost::any> &tmp= boost_any_to_vector_any(operand);
	std::vector<GEOM_FT> coo(2,0.0);
        const int sz= std::min(tmp.size(),coo.size());
        for(int i= 0;i<sz;i++)
          coo[i]= convert_to_double(tmp[i]);
        retval= Pos2d(coo[0],coo[1]);
      }
    else if(boost_any_is_vector2d(operand))
      {
	const Vector2d &coo= boost_any_to_vector2d(operand);
        retval= Pos2d(coo.x(),coo.y());
      }
    else if(boost_any_is_m_double(operand))
      {
	const m_double &tmp= boost_any_to_m_double(operand);
        const size_t sz= tmp.size();
        if(sz>1)
          {
	    std::vector<double> v(2);
            size_t j=0;
	    for(m_double::const_iterator i= tmp.begin();i!=tmp.end();i++,j++)
              {
                v[j]= *i;
                if(j>1) break;
              }
            retval= Pos2d(v[0],v[1]);
          }
        else
	  std::cerr << "convert_to_pos2d; se necesitan dos coordendadas." << std::endl;
      }
    else if(!operand.empty())
      std::cerr << "convert_to_pos2d; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un pos2d." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es de tipo Recta2d.
bool boost_any_is_recta2d(const boost::any &operand)
  { return operand.type() == typeid(Recta2d); }

//! @brief Devuelve una referencia a Recta2d.
const Recta2d &boost_any_to_recta2d(const boost::any &operand)
  { return *(boost::any_cast<Recta2d>(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en Recta2d.
Recta2d convert_to_recta2d(const boost::any &operand)
  {
    Recta2d retval;
    if(boost_any_is_recta2d(operand))
      { retval= boost_any_to_recta2d(operand); }
    else if(!operand.empty())
      std::cerr << "convert_to_recta2d; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en una recta2d." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es de tipo Pos3d.
bool boost_any_is_pos3d(const boost::any &operand)
  { return operand.type() == typeid(Pos3d); }

//! @brief Devuelve una referencia a Pos3d.
const Pos3d &boost_any_to_pos3d(const boost::any &operand)
  { return *(boost::any_cast<Pos3d>(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en Pos3d.
Pos3d convert_to_pos3d(const boost::any &operand)
  {
    Pos3d retval;
    if(boost_any_is_pos3d(operand))
      { retval= boost_any_to_pos3d(operand); }
    else if(boost_any_is_vector_any(operand))
      {
	const std::vector<boost::any> &tmp= boost_any_to_vector_any(operand);
	std::vector<GEOM_FT> coo(3,0.0);
        const int sz= std::min(tmp.size(),coo.size());
        for(int i= 0;i<sz;i++)
          coo[i]= convert_to_double(tmp[i]);
        retval= Pos3d(coo[0],coo[1],coo[2]);
      }
    else if(boost_any_is_vector3d(operand))
      {
	const Vector3d &coo= boost_any_to_vector3d(operand);
        retval= Pos3d(coo.x(),coo.y(),coo.z());
      }
    else if(boost_any_is_m_double(operand))
      {
	const m_double &tmp= boost_any_to_m_double(operand);
        const size_t sz= tmp.size();
        if(sz>2)
          {
	    std::vector<double> v(3);
            size_t j=0;
	    for(m_double::const_iterator i= tmp.begin();i!=tmp.end();i++,j++)
              {
                v[j]= *i;
                if(j>2) break;
              }
            retval= Pos3d(v[0],v[1],v[2]);
          }
        else
	  std::cerr << "convert_to_pos3d; se necesitan tres coordendadas." << std::endl;
      }
    else if(!operand.empty())
      std::cerr << "convert_to_pos3d; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un pos3d." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es de tipo Vector3d.
bool boost_any_is_vector3d(const boost::any &operand)
  { return operand.type() == typeid(Vector3d); }

//! @brief Devuelve una referencia a Vector3d.
const Vector3d &boost_any_to_vector3d(const boost::any &operand)
  { return *(boost::any_cast<Vector3d>(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en Vector3d.
Vector3d convert_to_vector3d(const boost::any &operand)
  {
    Vector3d retval;
    if(boost_any_is_vector3d(operand))
      { retval= boost_any_to_vector3d(operand); }
    else if(boost_any_is_vdesliz3d(operand))
      { retval= boost_any_to_vdesliz3d(operand); }
    else if(boost_any_is_vector_any(operand))
      {
	const std::vector<boost::any> &tmp= boost_any_to_vector_any(operand);
	std::vector<GEOM_FT> coo(3,0.0);
        const int sz= std::min(tmp.size(),coo.size());
        for(int i= 0;i<sz;i++)
          coo[i]= convert_to_double(tmp[i]);
        retval= Vector3d(coo[0],coo[1],coo[2]);
      }
    else if(boost_any_is_m_double(operand))
      {
	const m_double &tmp= boost_any_to_m_double(operand);
        const size_t sz= tmp.size();
        if(sz>2)
          {
	    std::vector<double> v(3);
            size_t j=0;
	    for(m_double::const_iterator i= tmp.begin();i!=tmp.end();i++,j++)
              {
                v[j]= *i;
                if(j>2) break;
              }
            retval= Vector3d(v[0],v[1],v[2]);
          }
        else
	  std::cerr << "convert_to_vector3d; se necesitan tres coordendadas." << std::endl;
      }
    else if(!operand.empty())
      std::cerr << "convert_to_lista_vector3d; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un vector3d." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es un Segmento3d.
bool boost_any_is_segmento3d(const boost::any &operand)
  { return operand.type() == typeid(Segmento3d); }
//! @brief Devuelve una referencia a Segmento3d.
const Segmento3d &boost_any_to_segmento3d(const boost::any & operand)
  { return *(boost::any_cast<Segmento3d>(&operand)); }
//! @brief Intenta, por todos los medios, convertir el argumento en Segmento3d.
Segmento3d convert_to_segmento3d(const boost::any &operand)
  {
    Segmento3d retval;
    if(boost_any_is_segmento3d(operand))
      { retval= boost_any_to_segmento3d(operand); }
    else if(boost_any_is_vector_any(operand))
      {
	const std::vector<boost::any> &tmp= boost_any_to_vector_any(operand);
	std::vector<Pos3d> pts(2);
        const int sz= std::min(tmp.size(),pts.size());
        for(int i= 0;i<sz;i++)
          pts[i]= convert_to_pos3d(tmp[i]);
        retval= Segmento3d(pts[0],pts[1]);
      }
    else if(!operand.empty())
      std::cerr << "convert_to_segmento3d; no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en una segmento3d." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es de tipo VDesliz2d.
bool boost_any_is_vdesliz2d(const boost::any &operand)
  { return operand.type() == typeid(VDesliz2d); }

//! @brief Devuelve una referencia a VDesliz2d.
const VDesliz2d &boost_any_to_vdesliz2d(const boost::any &operand)
  { return *(boost::any_cast<VDesliz2d>(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en VDesliz2d.
VDesliz2d convert_to_vdesliz2d(const boost::any &operand)
  {
    VDesliz2d retval;
    if(boost_any_is_vdesliz2d(operand))
      { retval= boost_any_to_vdesliz2d(operand); }
    else if(!operand.empty())
      std::cerr << "convert_to_lista_vdesliz2d no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un vdesliz2d." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es de tipo VDesliz3d.
bool boost_any_is_vdesliz3d(const boost::any &operand)
  { return operand.type() == typeid(VDesliz3d); }

//! @brief Devuelve una referencia a VDesliz3d.
const VDesliz3d &boost_any_to_vdesliz3d(const boost::any &operand)
  { return *(boost::any_cast<VDesliz3d>(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en VDesliz3d.
VDesliz3d convert_to_vdesliz3d(const boost::any &operand)
  {
    VDesliz3d retval;
    if(boost_any_is_vdesliz3d(operand))
      { retval= boost_any_to_vdesliz3d(operand); }
    else if(!operand.empty())
      std::cerr << "convert_to_lista_vdesliz3d no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un vdesliz3d." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es de tipo VFijo2d.
bool boost_any_is_vfijo2d(const boost::any &operand)
  { return operand.type() == typeid(VFijo2d); }

//! @brief Devuelve una referencia a VFijo2d.
const VFijo2d &boost_any_to_vfijo2d(const boost::any &operand)
  { return *(boost::any_cast<VFijo2d>(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en VFijo2d.
VFijo2d convert_to_vfijo2d(const boost::any &operand)
  {
    VFijo2d retval;
    if(boost_any_is_vfijo2d(operand))
      { retval= boost_any_to_vfijo2d(operand); }
    else if(!operand.empty())
      std::cerr << "convert_to_lista_vfijo2d no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un vfijo2d." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es de tipo VFijo3d.
bool boost_any_is_vfijo3d(const boost::any &operand)
  { return operand.type() == typeid(VFijo3d); }

//! @brief Devuelve una referencia a VFijo3d.
const VFijo3d &boost_any_to_vfijo3d(const boost::any &operand)
  { return *(boost::any_cast<VFijo3d>(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en VFijo3d.
VFijo3d convert_to_vfijo3d(const boost::any &operand)
  {
    VFijo3d retval;
    if(boost_any_is_vfijo3d(operand))
      { retval= boost_any_to_vfijo3d(operand); }
    else if(!operand.empty())
      std::cerr << "convert_to_lista_vfijo3d no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un vfijo3d." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es de tipo SVD3d.
bool boost_any_is_svd3d(const boost::any &operand)
  { return boost::any_cast<SVD3d>(&operand); }

//! @brief Devuelve una referencia a SVD3d.
const SVD3d &boost_any_to_svd3d(const boost::any &operand)
  { return *(boost::any_cast<SVD3d>(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en SVD3d.
SVD3d convert_to_svd3d(const boost::any &operand)
  {
    SVD3d retval;
    if(boost_any_is_svd3d(operand))
      { retval= boost_any_to_svd3d(operand); }
    else if(boost_any_is_vdesliz3d(operand))
      { retval= SVD3d(boost_any_to_vdesliz3d(operand)); }
    else if(!operand.empty())
      std::cerr << "convert_to_lista_svd3d no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un svd3d." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es de tipo Circulo2d.
bool boost_any_is_circulo2d(const boost::any &operand)
  { return operand.type() == typeid(Circulo2d); }

//! @brief Devuelve una referencia a Circulo2d.
const Circulo2d &boost_any_to_circulo2d(const boost::any &operand)
  { return *(boost::any_cast<Circulo2d>(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en Circulo2d.
Circulo2d convert_to_circulo2d(const boost::any &operand)
  {
    Circulo2d retval;
    if(boost_any_is_circulo2d(operand))
      { retval= boost_any_to_circulo2d(operand); }
    else if(!operand.empty())
      std::cerr << "convert_to_lista_circulo2d no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un circulo2d." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es de tipo Recta3d.
bool boost_any_is_recta3d(const boost::any &operand)
  { return operand.type() == typeid(Recta3d); }

//! @brief Devuelve una referencia a Recta3d.
const Recta3d &boost_any_to_recta3d(const boost::any &operand)
  { return *(boost::any_cast<Recta3d>(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en Recta3d.
Recta3d convert_to_recta3d(const boost::any &operand)
  {
    Recta3d retval;
    if(boost_any_is_recta3d(operand))
      { retval= boost_any_to_recta3d(operand); }
    else if(!operand.empty())
      std::cerr << "convert_to_lista_recta3d no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en una recta3d." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es de tipo Plano3d.
bool boost_any_is_plano3d(const boost::any &operand)
  { return operand.type() == typeid(Plano3d); }

//! @brief Devuelve una referencia a Plano3d.
const Plano3d &boost_any_to_plano3d(const boost::any &operand)
  { return *(boost::any_cast<Plano3d>(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en Plano3d.
Plano3d convert_to_plano3d(const boost::any &operand)
  {
    Plano3d retval;
    if(boost_any_is_plano3d(operand))
      { retval= boost_any_to_plano3d(operand); }
    else if(!operand.empty())
      std::cerr << "convert_to_lista_plano3d no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un plano3d." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es de tipo SemiEspacio3d.
bool boost_any_is_se3d(const boost::any &operand)
  { return operand.type() == typeid(SemiEspacio3d); }

//! @brief Devuelve una referencia a SemiEspacio3d.
const SemiEspacio3d &boost_any_to_se3d(const boost::any &operand)
  { return *(boost::any_cast<SemiEspacio3d>(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en SemiEspacio3d.
SemiEspacio3d convert_to_se3d(const boost::any &operand)
  {
    SemiEspacio3d retval;
    if(boost_any_is_se3d(operand))
      { retval= boost_any_to_se3d(operand); }
    else if(boost_any_is_plano3d(operand))
      { retval= SemiEspacio3d(boost_any_to_plano3d(operand)); }
    else if(!operand.empty())
      std::cerr << "convert_to_lista_se3d no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un semiespacio3d." << std::endl;
    return retval;
  }


//! @brief Devuelve verdadero si el objeto es de tipo Poliedro3d.
bool boost_any_is_poliedro3d(const boost::any &operand)
  { return operand.type() == typeid(Poliedro3d); }

//! @brief Devuelve una referencia a Poliedro3d.
const Poliedro3d &boost_any_to_poliedro3d(const boost::any &operand)
  { return *(boost::any_cast<Poliedro3d>(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en Poliedro3d.
Poliedro3d convert_to_poliedro3d(const boost::any &operand)
  {
    Poliedro3d retval;
    if(boost_any_is_poliedro3d(operand))
      { retval= boost_any_to_poliedro3d(operand); }
    else if(!operand.empty())
      std::cerr << "convert_to_lista_poliedro3d no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un poliedro3d." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es de tipo Tetraedro3d.
bool boost_any_is_tetra3d(const boost::any &operand)
  { return operand.type() == typeid(Tetraedro3d); }

//! @brief Devuelve una referencia a Tetraedro3d.
const Tetraedro3d &boost_any_to_tetra3d(const boost::any &operand)
  { return *(boost::any_cast<Tetraedro3d>(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en Tetraedro3d.
Tetraedro3d convert_to_tetra3d(const boost::any &operand)
  {
    Tetraedro3d retval;
    if(boost_any_is_tetra3d(operand))
      { retval= boost_any_to_tetra3d(operand); }
    else if(!operand.empty())
      std::cerr << "convert_to_lista_tetra3d no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un tetraedro3d." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es de tipo BlockPyramid.
bool boost_any_is_blockPyramid(const boost::any &operand)
  { return operand.type() == typeid(BlockPyramid); }

//! @brief Devuelve una referencia a BlockPyramid.
const BlockPyramid &boost_any_to_blockPyramid(const boost::any &operand)
  { return *(boost::any_cast<BlockPyramid>(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en BlockPyramid.
BlockPyramid convert_to_blockPyramid(const boost::any &operand)
  {
    BlockPyramid retval;
    if(boost_any_is_blockPyramid(operand))
      { retval= boost_any_to_blockPyramid(operand); }
    else if(!operand.empty())
      std::cerr << "convert_to_lista_blockPyramid no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un blockPyramid." << std::endl;
    return retval;
  }


//! @brief Devuelve verdadero si el objeto es de tipo SisCooRect2d3d.
bool boost_any_is_sisCooRect2d3d(const boost::any &operand)
  { return operand.type() == typeid(SisCooRect2d3d); }

//! @brief Devuelve una referencia a SisCooRect2d3d.
const SisCooRect2d3d &boost_any_to_sisCooRect2d3d(const boost::any &operand)
  { return *(boost::any_cast<SisCooRect2d3d>(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en SisCooRect2d3d.
SisCooRect2d3d convert_to_sisCooRect2d3d(const boost::any &operand)
  {
    SisCooRect2d3d retval;
    if(boost_any_is_sisCooRect2d3d(operand))
      { retval= boost_any_to_sisCooRect2d3d(operand); }
    else if(!operand.empty())
      std::cerr << "convert_to_lista_sisCooRect2d3d no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en un sisCooRect2d3d." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el objeto es de tipo Ref2d3d.
bool boost_any_is_ref2d3d(const boost::any &operand)
  { return operand.type() == typeid(Ref2d3d); }

//! @brief Devuelve una referencia a Ref2d3d.
const Ref2d3d &boost_any_to_ref2d3d(const boost::any &operand)
  { return *(boost::any_cast<Ref2d3d>(&operand)); }

//! @brief Intenta, por todos los medios, convertir el argumento en Ref2d3d.
Ref2d3d convert_to_ref2d3d(const boost::any &operand)
  {
    Ref2d3d retval;
    if(boost_any_is_ref2d3d(operand))
      { retval= boost_any_to_ref2d3d(operand); }
    else if(!operand.empty())
      std::cerr << "convert_to_lista_ref2d3d no se pudo convertir el objeto de tipo: '"
                << boost_any_tipo_operando(operand) 
                << "' en una ref2d3d." << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si los objetos son del mismo tipo.
bool boost_any_same_type(const boost::any &a,const boost::any &b)
  { return (a.type() == b.type()); }



//! @brief Devuelve la cadena de caracteres que representa al objeto con el
//! formato que se pasa como parámetro.
std::string boost_any_format(const boost::any &operand,const std::string &fmt)
  {
    std::string retval("");
    if(boost_any_is_empty(operand))
      return retval;
    else if(boost_any_is_bool(operand))
      {
        retval= format(fmt,boost_any_to_bool(operand));
        return retval;
      }
    else if(boost_any_is_int(operand))
      {
        retval= format(fmt,boost_any_to_int(operand));
        return retval;
      }
    else if(boost_any_is_long_int(operand))
      {
        retval= format(fmt,boost_any_to_long_int(operand));
        return retval;
      }
    else if(boost_any_is_size_t(operand))
      {
        retval= format(fmt,boost_any_to_size_t(operand));
        return retval;
      }
    else if(boost_any_is_string(operand))
      {
        retval= format(fmt,boost_any_to_string(operand));
        return retval;
      }
    else if(boost_any_is_float(operand))
      {
        retval= format(fmt,boost_any_to_float(operand));
        return retval;
      }
    else if(boost_any_is_double(operand))
      {
        retval= format(fmt,boost_any_to_double(operand));
        return retval;
      }
    else if(boost_any_is_expr_algebra(operand))
      {
        retval= format(fmt,boost_any_to_ExprAlgebra(operand).ToNum());
        return retval;
      }
    else
      std::cerr << "format(boost_any): No se ha definido la operación format para el objeto de tipo: "
                << operand.type().name() << " que se pasa como parámetro." << std::endl;
    return retval;
  }

std::string boost_any_to_sql_value(const boost::any &operand)
  {
    std::string retval= "";
    if(boost_any_is_empty(operand))
      return retval;
    else if(boost_any_is_int(operand))
      retval= boost::lexical_cast<std::string>(boost_any_to_int(operand));
    else if(boost_any_is_long_int(operand))
      retval= boost::lexical_cast<std::string>(boost_any_to_long_int(operand));
    else if(boost_any_is_size_t(operand))
      retval= boost::lexical_cast<std::string>(boost_any_to_size_t(operand));
    else if(boost_any_is_char_ptr(operand))
      retval= "'" + boost::lexical_cast<std::string>(*(boost::any_cast<const char *>(&operand))) + "'";
    else if(boost_any_is_string(operand))
      retval= "'" + boost_any_to_string(operand) + "'";
    else if(boost_any_is_float(operand))
      retval= boost::lexical_cast<std::string>(boost_any_to_float(operand));
    else if(boost_any_is_double(operand))
      retval= boost::lexical_cast<std::string>(boost_any_to_double(operand));
    else if(boost_any_is_long_double(operand))
      retval= boost::lexical_cast<std::string>(boost_any_to_long_double(operand));
    else if(boost_any_is_lista(operand))
      retval= boost_any_to_lista(operand).sqlValues();
    else
      std::cerr << "boost_any_to_sql_value(boost_any): No se ha definido la operación para el objeto de tipo: "
                << operand.type().name() << " que se pasa como parámetro." << std::endl;
    return retval;    
  }



std::ostream &operator<<(std::ostream &os,const boost::any &operand)
  {
    boost_any_print(os,operand);
    return os;
  }

//! @brief Define un vector.
std::vector<boost::any> def_vector_any(const size_t &sz,const boost::any &a)
  {
    std::vector<boost::any> retval(sz);
    for(size_t i= 0;i<sz;i++)
      retval[i]= a;
    return retval;
  }

//! @brief Multiplica un escalar por el vector.
std::vector<boost::any> mult_vector_any(const boost::any &a,const std::vector<boost::any> &b)
  {
    const size_t sz= b.size();
    std::vector<boost::any> retval(sz);
    for(size_t i= 0;i<sz;i++)
      retval[i]= mult_boost_any(a,b[i]);
    return retval;
  }

//! @brief Calcula la suma de los vectores.
std::vector<boost::any> suma_vector_any(const std::vector<boost::any> &a,const std::vector<boost::any> &b)
  {
    const size_t sz= b.size();
    std::vector<boost::any> retval(sz);
    for(size_t i= 0;i<sz;i++)
      retval[i]= suma_boost_any(a[i],b[i]);
    return retval;
  }

//! @brief Calcula la resta de los vectores.
std::vector<boost::any> resta_vector_any(const std::vector<boost::any> &a,const std::vector<boost::any> &b)
  {
    const size_t sz= b.size();
    std::vector<boost::any> retval(sz);
    retval.resize(sz);
    for(size_t i= 0;i<sz;i++)
      retval[i]= resta_boost_any(a[i],b[i]);
    return retval;
  }

//! @brief Calcula el producto vectorial de los vectores.
std::vector<boost::any> cross_vector_any(const std::vector<boost::any> &a,const std::vector<boost::any> &b)
  {
    std::vector<boost::any> retval(3);
    retval[0]= resta_boost_any(mult_boost_any(a[1],b[2]),mult_boost_any(a[2],b[1]));
    retval[1]= resta_boost_any(mult_boost_any(a[2],b[0]),mult_boost_any(a[0],b[2]));
    retval[2]= resta_boost_any(mult_boost_any(a[0],b[1]),mult_boost_any(a[1],b[0]));
    return retval;
  }


//! @brief Calcula el producto escalar de los vectores.
boost::any dot_vector_any(const std::vector<boost::any> &a,const std::vector<boost::any> &b)
  {
    const size_t sz= b.size();
    boost::any retval(0.0);
    for(size_t i= 0;i<sz;i++)
      retval= suma_boost_any(retval,mult_boost_any(a[i],b[i]));
    return retval;
  }

//! @brief Calcula el producto escalar de los vectores.
boost::any abs_vector_any(const std::vector<boost::any> &a)
  { return sqrt_boost_any(dot_vector_any(a,a)); }


//! @brief Devuelve el vector normalizado (unitario).
std::vector<boost::any> normaliza_vector_any(const std::vector<boost::any> &a)
  { return mult_vector_any(inv_boost_any(abs_vector_any(a)),a); }

//! @brief Devuelve la proyección del primer vector sobre el segundo.
std::vector<boost::any> proj_vector_any(const std::vector<boost::any> &a,const std::vector<boost::any> &b)
  { return mult_vector_any(div_boost_any(dot_vector_any(a,b),dot_vector_any(b,b)),b); }

//! @brief Devuelve (si puede) la suma de los operandos.
boost::any suma_boost_any(const boost::any &a,const boost::any &b)
  {
    boost::any retval;
    if(boost_any_is_number(a) && boost_any_is_number(b)) //NUM + NUM
      retval= boost::any(boost_any_number_to_double(a)+boost_any_number_to_double(b));
    else if(boost_any_is_expr_algebra(a) && boost_any_is_number(b)) //EXPR + NUM
      retval= boost::any(boost_any_to_ExprAlgebra(a)+boost_any_number_to_double(b));
    else if(boost_any_is_number(a) && boost_any_is_expr_algebra(b))  //NUM + EXPR
      retval= boost::any(boost_any_number_to_double(a)+boost_any_to_ExprAlgebra(b));
    else if(boost_any_is_expr_algebra(a) && boost_any_is_expr_algebra(b))  //EXPR + EXPR
      retval= boost::any(boost_any_to_ExprAlgebra(a)+boost_any_to_ExprAlgebra(b));
    else if(boost_any_is_vector_any(a) && boost_any_is_vector_any(b))  //VECTOR + VECTOR
      retval= suma_vector_any(boost_any_to_vector_any(a),boost_any_to_vector_any(b));
    else if(boost_any_is_vector3d(a) && boost_any_is_vector3d(b))  //VECTOR3d + VECTOR3d
      retval= boost::any(boost_any_to_vector3d(a)+boost_any_to_vector3d(b));
    else if(boost_any_is_pos3d(a) && boost_any_is_vector3d(b)) //pos3d + vector3d
      retval= boost::any(boost_any_to_pos3d(a)+boost_any_to_vector3d(b));
    else if(boost_any_is_vdesliz3d(a) && boost_any_is_vdesliz3d(b))  //Vdesliz3d + Vdesliz3d
      retval= boost::any(boost_any_to_vdesliz3d(a)+boost_any_to_vdesliz3d(b));
    else if(boost_any_is_svd3d(a) && boost_any_is_svd3d(b))  //Svd3d + Svd3d
      retval= boost::any(boost_any_to_svd3d(a)+boost_any_to_svd3d(b));
    else if(boost_any_is_svd3d(a) && boost_any_is_vdesliz3d(b))  //Svd3d + VDesliz3d
      retval= boost::any(boost_any_to_svd3d(a)+boost_any_to_vdesliz3d(b));
    else if(boost_any_is_vdesliz3d(a) && boost_any_is_svd3d(b))  //vdesliz3d + Svd3d
      retval= boost::any(boost_any_to_vdesliz3d(a)+boost_any_to_svd3d(b));
    else if(boost_any_is_m_double(a) && boost_any_is_m_double(b))  //m_double + m_double
      retval= boost::any(boost_any_to_m_double(a)+boost_any_to_m_double(b));
    else if(boost_any_is_m_double(a) && boost_any_is_vector_any(b))  //m_double + VECTOR
      retval= suma_vector_any(convert_to_vector_any(a),boost_any_to_vector_any(b));
    else if(boost_any_is_vector_any(a) && boost_any_is_m_double(b))  //VECTOR + m_double
      retval= suma_vector_any(boost_any_to_vector_any(a),convert_to_vector_any(b));
    else if(boost_any_is_CmdFuncPorPuntos(a) && boost_any_is_CmdFuncPorPuntos(b))  //FPtos + FPtos
      retval= boost::any(boost_any_to_CmdFuncPorPuntos(a)+boost_any_to_CmdFuncPorPuntos(b));
    else if(boost_any_is_CmdFuncPorPuntos(a) && boost_any_is_number(b))  //FPtos + NUM
      retval= boost::any(boost_any_to_CmdFuncPorPuntos(a)+boost_any_to_double(b));
    else if(boost_any_is_double(a) && boost_any_is_CmdFuncPorPuntos(b))  //NUM + FPtos
      retval= boost::any(boost_any_to_double(a)+boost_any_to_CmdFuncPorPuntos(b));
    else if(boost_any_is_string(a))  //STR + ANY
      retval= boost::any(boost_any_to_string(a)+convert_to_string(b));
    else if(boost_any_is_vector2d(a) && boost_any_is_vector2d(b))  //VECTOR2d + VECTOR2d
      retval= boost::any(boost_any_to_vector2d(a)+boost_any_to_vector2d(b));
    else if(boost_any_is_pos2d(a) && boost_any_is_vector2d(b)) //pos2d + vector2d
      retval= boost::any(boost_any_to_pos2d(a)+boost_any_to_vector2d(b));
    else
      std::cerr << "No se pudieron sumar los operandos de tipo: "
                << boost_any_tipo_operando(a) << " y "
                << boost_any_tipo_operando(b) << std::endl;
    return retval;
  }

//! @brief Devuelve (si puede) la resta de los operandos.
boost::any resta_boost_any(const boost::any &a,const boost::any &b)
  {
    boost::any retval;
    if(boost_any_is_number(a) && boost_any_is_number(b))
      retval= boost::any(boost_any_number_to_double(a)-boost_any_number_to_double(b));
    else if(boost_any_is_expr_algebra(a) && boost_any_is_number(b))
      retval= boost::any(boost_any_to_ExprAlgebra(a)-boost_any_number_to_double(b));
    else if(boost_any_is_number(a) && boost_any_is_expr_algebra(b))
      retval= boost::any(boost_any_number_to_double(a)-boost_any_to_ExprAlgebra(b));
    else if(boost_any_is_expr_algebra(a) && boost_any_is_expr_algebra(b))  //EXPR - EXPR
      retval= boost::any(boost_any_to_ExprAlgebra(a)-boost_any_to_ExprAlgebra(b));
    else if(boost_any_is_vector_any(a) && boost_any_is_vector_any(b))  //VECTOR - VECTOR
      retval= resta_vector_any(boost_any_to_vector_any(a),boost_any_to_vector_any(b));
    else if(boost_any_is_vector3d(a) && boost_any_is_vector3d(b))  //VECTOR3d - VECTOR3d
      retval= boost::any(boost_any_to_vector3d(a)-boost_any_to_vector3d(b));
    else if(boost_any_is_pos3d(a) && boost_any_is_vector3d(b)) //pos3d - vector3d
      retval= boost::any(boost_any_to_pos3d(a)-boost_any_to_vector3d(b));
    else if(boost_any_is_pos3d(a) && boost_any_is_pos3d(b)) //pos3d - pos3d
      retval= boost::any(boost_any_to_pos3d(a)-boost_any_to_pos3d(b));
    else if(boost_any_is_m_double(a) && boost_any_is_m_double(b))  //m_double - m_double
      retval= boost::any(boost_any_to_m_double(a)-boost_any_to_m_double(b));
    else if(boost_any_is_m_double(a) && boost_any_is_vector_any(b))  //m_double - VECTOR
      retval= resta_vector_any(convert_to_vector_any(a),boost_any_to_vector_any(b));
    else if(boost_any_is_vector_any(a) && boost_any_is_m_double(b))  //VECTOR - m_double
      retval= resta_vector_any(boost_any_to_vector_any(a),convert_to_vector_any(b));
    else if(boost_any_is_CmdFuncPorPuntos(a) && boost_any_is_CmdFuncPorPuntos(b))  //FPtos - FPtos
      retval= boost::any(boost_any_to_CmdFuncPorPuntos(a)-boost_any_to_CmdFuncPorPuntos(b));
    else if(boost_any_is_CmdFuncPorPuntos(a) && boost_any_is_number(b))  //FPtos - NUM
      retval= boost::any(boost_any_to_CmdFuncPorPuntos(a)-boost_any_to_double(b));
    else if(boost_any_is_double(a) && boost_any_is_CmdFuncPorPuntos(b))  //NUM - FPtos
      retval= boost::any(boost_any_to_double(a)-boost_any_to_CmdFuncPorPuntos(b));
    else if(boost_any_is_vector2d(a) && boost_any_is_vector2d(b))  //VECTOR2d - VECTOR2d
      retval= boost::any(boost_any_to_vector2d(a)-boost_any_to_vector2d(b));
    else if(boost_any_is_pos2d(a) && boost_any_is_vector2d(b)) //pos2d - vector2d
      retval= boost::any(boost_any_to_pos2d(a)-boost_any_to_vector2d(b));
    else if(boost_any_is_pos2d(a) && boost_any_is_pos2d(b)) //pos2d - pos2d
      retval= boost::any(boost_any_to_pos2d(a)-boost_any_to_pos2d(b));
    else
      std::cerr << "No se pudieron restar los operandos de tipo: "
                << boost_any_tipo_operando(a) << " y "
                << boost_any_tipo_operando(b) << std::endl;
    return retval;
  }

//! @brief Devuelve (si puede) el producto de los operandos.
boost::any mult_boost_any(const boost::any &a,const boost::any &b)
  {
    boost::any retval;
    if(boost_any_is_number(a) && boost_any_is_number(b))  //NUM * NUM
      retval= boost::any(boost_any_number_to_double(a)*boost_any_number_to_double(b));
    else if(boost_any_is_expr_algebra(a) && boost_any_is_number(b)) //EXPR * NUM
      retval= boost::any(boost_any_to_ExprAlgebra(a)*ExprAlgebra(boost_any_number_to_double(b)));
    else if(boost_any_is_number(a) && boost_any_is_expr_algebra(b)) //NUM * EXPR
      retval= boost::any(ExprAlgebra(boost_any_number_to_double(a))*boost_any_to_ExprAlgebra(b));
    else if(boost_any_is_expr_algebra(a) && boost_any_is_expr_algebra(b))  //EXPR * EXPR
      retval= boost::any(boost_any_to_ExprAlgebra(a)*boost_any_to_ExprAlgebra(b));
    else if(boost_any_is_number(a) && boost_any_is_vector_any(b))  //NUM * VECTOR
      retval= mult_vector_any(a,boost_any_to_vector_any(b));
    else if(boost_any_is_vector_any(a) && boost_any_is_number(b))  //VECTOR * NUM
      retval= mult_vector_any(b,boost_any_to_vector_any(a));
    else if(boost_any_is_expr_algebra(a) && boost_any_is_vector_any(b))  //EXPR * VECTOR
      retval= mult_vector_any(a,boost_any_to_vector_any(b));
    else if(boost_any_is_vector_any(a) && boost_any_is_expr_algebra(b))  //VECTOR * EXPR
      retval= mult_vector_any(b,boost_any_to_vector_any(a));
    else if(boost_any_is_CmdFuncPorPuntos(a) && boost_any_is_CmdFuncPorPuntos(b))  //FPtos * FPtos
      retval= boost::any(boost_any_to_CmdFuncPorPuntos(a)*boost_any_to_CmdFuncPorPuntos(b));
    else if(boost_any_is_CmdFuncPorPuntos(a) && boost_any_is_number(b))  //FPtos * NUM
      retval= boost::any(boost_any_to_CmdFuncPorPuntos(a)*boost_any_to_double(b));
    else if(boost_any_is_double(a) && boost_any_is_CmdFuncPorPuntos(b))  //NUM * FPtos
      retval= boost::any(boost_any_to_double(a)*boost_any_to_CmdFuncPorPuntos(b));
    else if(boost_any_is_vector2d(a) && boost_any_is_number(b))  //Vector2d * NUM
      retval= boost::any(boost_any_to_vector3d(a)*boost_any_to_double(b));
    else if(boost_any_is_double(a) && boost_any_is_vector2d(b))  //NUM * Vector2d
      retval= boost::any(boost_any_to_double(a)*boost_any_to_vector2d(b));
    else if(boost_any_is_vector3d(a) && boost_any_is_number(b))  //Vector3d * NUM
      retval= boost::any(boost_any_to_vector3d(a)*boost_any_to_double(b));
    else if(boost_any_is_double(a) && boost_any_is_vector3d(b))  //NUM * Vector3d
      retval= boost::any(boost_any_to_double(a)*boost_any_to_vector3d(b));
    else if(boost_any_is_vdesliz3d(a) && boost_any_is_number(b))  //Vdesliz3d * NUM
      retval= boost::any(boost_any_to_vdesliz3d(a)*boost_any_to_double(b));
    else if(boost_any_is_double(a) && boost_any_is_vdesliz3d(b))  //NUM * Vdesliz3d
      retval= boost::any(boost_any_to_double(a)*boost_any_to_vdesliz3d(b));
    else if(boost_any_is_m_double(a) && boost_any_is_number(b))  //m_double * NUM
      retval= boost::any(boost_any_to_m_double(a)*boost_any_to_double(b));
    else if(boost_any_is_double(a) && boost_any_is_m_double(b))  //NUM * m_double
      retval= boost::any(boost_any_to_double(a)*boost_any_to_m_double(b));
    else if(boost_any_is_m_double(a) && boost_any_is_vector_any(b))  //m_double * VECTOR
      retval= boost::any(boost_any_to_m_double(a)*convert_to_m_double(b).GetTrn());
    else if(boost_any_is_vector_any(a) && boost_any_is_m_double(b))  //VECTOR * m_double
      retval= boost::any(convert_to_m_double(a)*boost_any_to_m_double(b));
    else if(boost_any_is_m_double(a) && boost_any_is_m_double(b))  //m_double * m_double
      { retval= boost::any(boost_any_to_m_double(a)*boost_any_to_m_double(b)); }
    else
      std::cerr << "No se pudieron multiplicar los operandos de tipo: "
                << boost_any_tipo_operando(a) << " y "
                << boost_any_tipo_operando(b) << std::endl;
    return retval;
  }

//! @brief Devuelve (si puede) el producto escalar de los operandos.
boost::any dot_boost_any(const boost::any &a,const boost::any &b)
  {
    boost::any retval;
    if(boost_any_is_vector_any(a) && boost_any_is_vector_any(b))  //VECTOR * VECTOR
      retval= dot_vector_any(boost_any_to_vector_any(a),boost_any_to_vector_any(b));
    else
      std::cerr << "No se pudo obtener el producto escalar de los operandos de tipo: "
                << boost_any_tipo_operando(a) << " y "
                << boost_any_tipo_operando(b) << std::endl;
    return retval;
  }

//! @brief Devuelve (si puede) el producto vectorial de los operandos.
boost::any cross_boost_any(const boost::any &a,const boost::any &b)
  {
    boost::any retval;
    if(boost_any_is_vector_any(a) && boost_any_is_vector_any(b))  //VECTOR ^ VECTOR
      retval= cross_vector_any(boost_any_to_vector_any(a),boost_any_to_vector_any(b));
    else if(boost_any_is_vector_any(a) && boost_any_is_vector3d(b))  //VECTOR ^ Vector3d
      retval= cross_vector_any(boost_any_to_vector_any(a),convert_to_vector_any(b));
    else if(boost_any_is_vector3d(a) && boost_any_is_vector_any(b))  //Vector3d ^ VECTOR
      retval= cross_vector_any(convert_to_vector_any(a),boost_any_to_vector_any(b));
    else if(boost_any_is_vector3d(a) && boost_any_is_vector3d(b))  //Vector3d ^ Vector3d
      retval= cross(boost_any_to_vector3d(a),boost_any_to_vector3d(b));
    else
      std::cerr << "No se pudo obtener el producto vectorial de los operandos de tipo: "
                << boost_any_tipo_operando(a) << " y "
                << boost_any_tipo_operando(b) << std::endl;
    return retval;
  }

//! @brief Devuelve (si puede) la proyección del primer vector sobre el segundo.
boost::any proj_boost_any(const boost::any &a,const boost::any &b)
  {
    boost::any retval;
    if(boost_any_is_vector_any(a) && boost_any_is_vector_any(b))  //VECTOR -| VECTOR
      retval= proj_vector_any(boost_any_to_vector_any(a),boost_any_to_vector_any(b));
    else
      std::cerr << "No se pudo proyectar el operando de tipo: "
                << boost_any_tipo_operando(a) << " y sobre el de tipo: "
                << boost_any_tipo_operando(b) << std::endl;
    return retval;
  }

//! @brief Devuelve (si puede) el vector normalizado.
boost::any normaliza_boost_any(const boost::any &a)
  {
    boost::any retval;
    if(boost_any_is_vector_any(a))  //VECTOR
      retval= normaliza_vector_any(boost_any_to_vector_any(a));
    else
      std::cerr << "No se pudo normalizar el operando de tipo: "
                << boost_any_tipo_operando(a) << std::endl;
    return retval;
  }

//! @brief Devuelve (si puede) el cociente de los operandos.
boost::any div_boost_any(const boost::any &a,const boost::any &b)
  {
    boost::any retval;
    if(boost_any_is_number(a) && boost_any_is_number(b))
      retval= boost::any(boost_any_number_to_double(a)/boost_any_number_to_double(b));
    else if(boost_any_is_expr_algebra(a) && boost_any_is_number(b))
      retval= boost::any(boost_any_to_ExprAlgebra(a)/boost_any_number_to_double(b));
    else if(boost_any_is_number(a) && boost_any_is_expr_algebra(b))
      retval= boost::any(boost_any_number_to_double(a)/boost_any_to_ExprAlgebra(b));
    else if(boost_any_is_expr_algebra(a) && boost_any_is_expr_algebra(b))
      retval= boost::any(boost_any_to_ExprAlgebra(a)/boost_any_to_ExprAlgebra(b));
    else if(boost_any_is_vector_any(a))  //VECTOR / NUM
      retval= mult_vector_any(inv_boost_any(b),boost_any_to_vector_any(a));
    else if(boost_any_is_m_double(a) && boost_any_is_number(b))  //MATRIZ / NUM
      retval= boost::any(boost_any_to_m_double(a)*(1.0/boost_any_number_to_double(b)));
    else if(boost_any_is_vector2d(a) && boost_any_is_number(b))  //Vector2d / NUM
      retval= boost::any(boost_any_to_vector2d(a)*(1.0/boost_any_number_to_double(b)));
    else if(boost_any_is_vector3d(a) && boost_any_is_number(b))  //Vector3d / NUM
      retval= boost::any(boost_any_to_vector3d(a)*(1.0/boost_any_number_to_double(b)));
    else if(boost_any_is_CmdFuncPorPuntos(a) && boost_any_is_CmdFuncPorPuntos(b))  //FPtos / FPtos
      retval= boost::any(boost_any_to_CmdFuncPorPuntos(a)/boost_any_to_CmdFuncPorPuntos(b));
    else if(boost_any_is_CmdFuncPorPuntos(a) && boost_any_is_number(b))  //FPtos / NUM
      retval= boost::any(boost_any_to_CmdFuncPorPuntos(a)/boost_any_to_double(b));
    else
      std::cerr << "No se pudieron dividir los operandos de tipo: "
                << boost_any_tipo_operando(a) << " y "
                << boost_any_tipo_operando(b) << std::endl;
    return retval;
  }

//! @brief Devuelve (si puede) el valor de a^b.
boost::any pow_boost_any(const boost::any &a,const boost::any &b)
  {
    boost::any retval;
    if(boost_any_is_number(a) && boost_any_is_number(b))
      retval= boost::any(pow(boost_any_number_to_double(a),boost_any_number_to_double(b)));
    else if(boost_any_is_expr_algebra(a) && boost_any_is_number(b))
      retval= boost::any(pow(boost_any_to_ExprAlgebra(a),boost_any_number_to_double(b)));
    else if(boost_any_is_number(a) && boost_any_is_expr_algebra(b))
      retval= boost::any(pow(boost_any_number_to_double(a),boost_any_to_ExprAlgebra(b)));
    else if(boost_any_is_expr_algebra(a) && boost_any_is_expr_algebra(b))
      retval= boost::any(pow(boost_any_to_ExprAlgebra(a),boost_any_to_ExprAlgebra(b)));
    else
      std::cerr << "No se pudo calcular a^b para los operandos de tipo: "
                << boost_any_tipo_operando(a) << " y "
                << boost_any_tipo_operando(b) << std::endl;
    return retval;
  }


//! @brief Devuelve (si puede) el operando cambiado de signo.
boost::any neg_boost_any(const boost::any &a)
  {
    boost::any retval;
    if(boost_any_is_number(a))
      retval= boost::any(-boost_any_number_to_double(a));
    else if(boost_any_is_expr_algebra(a))
      {
        ExprAlgebra tmp= boost_any_to_ExprAlgebra(a);
        retval= boost::any(-tmp);
      }
    else if(boost_any_is_m_double(a))
      {
        m_double tmp= boost_any_to_m_double(a);
        retval= boost::any(-tmp);
      }
    else if(boost_any_is_vector2d(a))
      {
        Vector2d tmp= boost_any_to_vector2d(a);
        retval= boost::any(-tmp);
      }
    else if(boost_any_is_vector3d(a))
      {
        Vector3d tmp= boost_any_to_vector3d(a);
        retval= boost::any(-tmp);
      }
    else if(boost_any_is_vector_any(a))
      retval= mult_boost_any(-1.0,a);
    else
      std::cerr << "No se pudo cambiar de signo al operando de tipo: "
                << boost_any_tipo_operando(a) << std::endl;
    return retval;
  }

//! @brief Devuelve (si puede) el signo del operando.
int sign_boost_any(const boost::any &a)
  {
    int retval= 0;
    if(boost_any_is_number(a))
      retval= boost::math::sign(boost_any_number_to_double(a));
    else if(boost_any_is_expr_algebra(a))
      {
        const double tmp= boost_any_to_ExprAlgebra(a).ToNum();
        retval= boost::math::sign(tmp);
      }
    else
      std::cerr << "No se pudo obtener el signo del operando de tipo: "
                << boost_any_tipo_operando(a) << std::endl;
    return retval;
  }

//! @brief Devuelve (si puede) el valor absoluto del operando.
boost::any abs_boost_any(const boost::any &a)
  {
    boost::any retval;
    if(boost_any_is_number(a))
      retval= boost::any(fabs(boost_any_number_to_double(a)));
    else if(boost_any_is_expr_algebra(a))
      {
        ExprAlgebra tmp= boost_any_to_ExprAlgebra(a);
        retval= boost::any(abs(tmp));
      }
    else if(boost_any_is_vector_any(a))
      retval= abs_vector_any(boost_any_to_vector_any(a));
    else if(boost_any_is_vector2d(a))
      retval= boost::any(Abs(boost_any_to_vector2d(a)));
    else if(boost_any_is_vector3d(a))
      retval= boost::any(Abs(boost_any_to_vector3d(a)));
    else if(boost_any_is_vdesliz3d(a))
      retval= boost::any(Abs(boost_any_to_vdesliz3d(a)));
    else if(boost_any_is_m_double(a))
      retval= boost::any(boost_any_to_m_double(a).Abs());
    else
      std::cerr << "No se pudo obtener el valor absoluto del operando de tipo: "
                << boost_any_tipo_operando(a) << std::endl;
    return retval;
  }

//! @brief Devuelve (si puede) la traza del operando.
boost::any traza_boost_any(const boost::any &a)
  {
    boost::any retval;
    if(boost_any_is_number(a))
      retval= boost::any(boost_any_number_to_double(a));
    else if(boost_any_is_expr_algebra(a))
      {
        ExprAlgebra tmp= boost_any_to_ExprAlgebra(a);
        retval= boost::any(tmp);
      }
    else if(boost_any_is_m_double(a))
      retval= boost::any(boost_any_to_m_double(a).Traza());
    else
      std::cerr << "No se pudo obtener la traza del operando de tipo: "
                << boost_any_tipo_operando(a) << std::endl;
    return retval;
  }

//! @brief Devuelve (si puede) la traspuesta del operando.
boost::any traspuesta_boost_any(const boost::any &a)
  {
    boost::any retval;
    if(boost_any_is_number(a))
      retval= a;
    else if(boost_any_is_expr_algebra(a))
      {
        ExprAlgebra tmp= boost_any_to_ExprAlgebra(a);
        retval= boost::any(tmp);
      }
    else if(boost_any_is_m_double(a))
      retval= boost::any(boost_any_to_m_double(a).GetTrn());
    else if(boost_any_is_matriz_any(a))
      {
        MatrizAny m= boost_any_to_matriz_any(a);
        retval= boost::any(m.Trn());
      }
    else if(boost_any_is_vector_double(a))
      {
        m_double m= convert_to_m_double(a);
        m.Trn();
        retval= boost::any(m);
      }
    else
      {
        MatrizAny m= convert_to_matriz_any(a);
        m.Trn();
        retval= boost::any(m);
      }

    if(retval.empty())
      std::cerr << "No se pudo obtener la traspuesta del operando de tipo: "
                << boost_any_tipo_operando(a) << std::endl;
    return retval;
  }


//! @brief Devuelve (si puede) el inverso del operando.
boost::any inv_boost_any(const boost::any &a)
  {
    boost::any retval;
    if(boost_any_is_number(a))
      retval= boost::any(1.0/boost_any_number_to_double(a));
    else if(boost_any_is_expr_algebra(a))
      {
        ExprAlgebra tmp= boost_any_to_ExprAlgebra(a);
        retval= boost::any(1.0/tmp);
      }
    else
      std::cerr << "No se pudo obtener el valor absoluto del operando de tipo: "
                << boost_any_tipo_operando(a) << std::endl;
    return retval;
  }

//! @brief Devuelve (si puede) la raíz cuadrada del operando.
boost::any sqrt_boost_any(const boost::any &a)
  {
    boost::any retval;
    if(boost_any_is_number(a))
      retval= boost::any(sqrt(boost_any_number_to_double(a)));
    else if(boost_any_is_expr_algebra(a))
      {
        ExprAlgebra tmp= sqrt(boost_any_to_ExprAlgebra(a));
        retval= boost::any(tmp);
      }
    else
      std::cerr << "No se pudo obtener la raíz cuadrada del operando de tipo: "
                << boost_any_tipo_operando(a) << std::endl;
    return retval;
  }

//! @brief Devuelve el máximo de ambos valores.
boost::any max_boost_any(const boost::any &a,const boost::any &b)
  {
    boost::any retval;
    if(boost_any_is_number(a) && boost_any_is_number(b)) //max(NUM,NUM)
      retval= boost::any(std::max(boost_any_number_to_double(a),boost_any_number_to_double(b)));
    else if(boost_any_is_expr_algebra(a) && boost_any_is_number(b)) //max(EXPR,NUM)
      retval= boost::any(std::max(boost_any_to_ExprAlgebra(a).ToNum(),boost_any_number_to_double(b)));
    else if(boost_any_is_number(a) && boost_any_is_expr_algebra(b)) //max(NUM,EXPR)
      retval= boost::any(std::max(boost_any_number_to_double(a),boost_any_to_ExprAlgebra(b).ToNum()));
    else if(boost_any_is_expr_algebra(a) && boost_any_is_expr_algebra(b)) //max(EXPR,EXPR)
      retval= boost::any(std::max(boost_any_to_ExprAlgebra(a).ToNum(),boost_any_to_ExprAlgebra(b).ToNum()));
    else if(boost_any_is_string(a) && boost_any_is_string(b))
      retval= boost::any(std::max(boost_any_to_string(a),boost_any_to_string(b)));
    else
      std::cerr << "No se pudo aplicar la función 'max' a los operandos de tipo: "
                << boost_any_tipo_operando(a) << " y "
                << boost_any_tipo_operando(b) << std::endl;
    return retval;
  }

//! @brief Devuelve el mínimo de ambos valores.
boost::any min_boost_any(const boost::any &a,const boost::any &b)
  {
    boost::any retval;
    if(boost_any_is_number(a) && boost_any_is_number(b))
      retval= boost::any(std::min(boost_any_number_to_double(a),boost_any_number_to_double(b)));
    else if(boost_any_is_expr_algebra(a) && boost_any_is_number(b))
      retval= boost::any(std::min(boost_any_to_ExprAlgebra(a).ToNum(),boost_any_number_to_double(b)));
    else if(boost_any_is_number(a) && boost_any_is_expr_algebra(b))
      retval= boost::any(std::min(boost_any_number_to_double(a),boost_any_to_ExprAlgebra(b).ToNum()));
    else if(boost_any_is_expr_algebra(a) && boost_any_is_expr_algebra(b)) //min(EXPR,EXPR)
      retval= boost::any(std::min(boost_any_to_ExprAlgebra(a).ToNum(),boost_any_to_ExprAlgebra(b).ToNum()));
    else if(boost_any_is_string(a) && boost_any_is_string(b))
      retval= boost::any(std::min(boost_any_to_string(a),boost_any_to_string(b)));
    else
      std::cerr << "No se pudo aplicar la función 'min' a los operandos de tipo: "
                << boost_any_tipo_operando(a) << " y "
                << boost_any_tipo_operando(b) << std::endl;
    return retval;
  }


//! @brief Devuelve verdadero si el primer operando es menor que el segundo.
boost::any menor_boost_any(const boost::any &a,const boost::any &b)
  {
    boost::any retval;
    if(boost_any_is_number(a) && boost_any_is_number(b)) //NUM < NUM
      retval= boost::any(boost_any_number_to_double(a)<boost_any_number_to_double(b));
    else if(boost_any_is_expr_algebra(a) && boost_any_is_number(b)) //EXPR < NUM
      retval= boost::any(boost_any_to_ExprAlgebra(a).ToNum() < boost_any_number_to_double(b));
    else if(boost_any_is_number(a) && boost_any_is_expr_algebra(b)) //NUM < EXPR
      retval= boost::any(boost_any_number_to_double(a) < boost_any_to_ExprAlgebra(b).ToNum());
    else if(boost_any_is_expr_algebra(a) && boost_any_is_expr_algebra(b)) //EXPR < EXPR
      retval= boost::any(boost_any_to_ExprAlgebra(a).ToNum() < boost_any_to_ExprAlgebra(b).ToNum());
    else if(boost_any_is_string(a) && boost_any_is_string(b)) //STR < STR
      retval= boost::any(boost_any_to_string(a)<boost_any_to_string(b));
    else
      std::cerr << "No se pudo aplicar el operador '<' a los operandos de tipo: "
                << boost_any_tipo_operando(a) << " y "
                << boost_any_tipo_operando(b) << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el primer operando es mayor que el segundo.
boost::any mayor_boost_any(const boost::any &a,const boost::any &b)
  {
    boost::any retval;
    if(boost_any_is_number(a) && boost_any_is_number(b)) //NUM < NUM
      retval= boost::any(boost_any_number_to_double(a)>boost_any_number_to_double(b));
    else if(boost_any_is_expr_algebra(a) && boost_any_is_number(b)) //EXPR > NUM
      retval= boost::any(boost_any_to_ExprAlgebra(a).ToNum() > boost_any_number_to_double(b));
    else if(boost_any_is_number(a) && boost_any_is_expr_algebra(b)) //NUM > EXPR
      retval= boost::any(boost_any_number_to_double(a) > boost_any_to_ExprAlgebra(b).ToNum());
    else if(boost_any_is_expr_algebra(a) && boost_any_is_expr_algebra(b)) //EXPR > EXPR
      retval= boost::any(boost_any_to_ExprAlgebra(a).ToNum() > boost_any_to_ExprAlgebra(b).ToNum());
    else if(boost_any_is_string(a) && boost_any_is_string(b)) //STR > STR
      retval= boost::any(boost_any_to_string(a)>boost_any_to_string(b));
    else
      std::cerr << "No se pudo aplicar el operador '>' a los operandos de tipo: "
                << boost_any_tipo_operando(a) << " y "
                << boost_any_tipo_operando(b) << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el primer operando es igual al segundo.
boost::any igual_boost_any(const boost::any &a,const boost::any &b)
  {
    boost::any retval;
    if(boost_any_is_number(a) && boost_any_is_number(b)) //NUM == NUM
      retval= boost::any(boost_any_number_to_double(a)==boost_any_number_to_double(b));
    else if(boost_any_is_expr_algebra(a) && boost_any_is_number(b)) //EXPR == NUM
      retval= boost::any(boost_any_to_ExprAlgebra(a).ToNum() == boost_any_number_to_double(b));
    else if(boost_any_is_number(a) && boost_any_is_expr_algebra(b)) //NUM == EXPR
      retval= boost::any(boost_any_number_to_double(a) == boost_any_to_ExprAlgebra(b).ToNum());
    else if(boost_any_is_expr_algebra(a) && boost_any_is_expr_algebra(b)) //EXPR == EXPR
      retval= boost::any(boost_any_to_ExprAlgebra(a).ToNum() == boost_any_to_ExprAlgebra(b).ToNum());
    else if(boost_any_is_string(a) && boost_any_is_string(b))
      retval= boost::any(boost_any_to_string(a)==boost_any_to_string(b));
    else if(boost_any_is_char(a) && boost_any_is_char(b))
      retval= boost::any(boost_any_to_char(a)==boost_any_to_char(b));
    else if(boost_any_is_char(a) && boost_any_is_string(b))
      retval= boost::any(boost_any_to_char(a)==boost_any_to_string(b)[0]);
    else if(boost_any_is_string(a) && boost_any_is_char(b))
      retval= boost::any(boost_any_to_string(a)[0]==boost_any_to_char(b));
    else
      std::cerr << "No se pudo aplicar el operador '==' a los operandos de tipo: "
                << boost_any_tipo_operando(a) << " y "
                << boost_any_tipo_operando(b) << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el primer operando es menor o igual que el segundo.
boost::any menor_o_igual_boost_any(const boost::any &a,const boost::any &b)
  {
    boost::any retval;
    if(boost_any_is_number(a) && boost_any_is_number(b)) //NUM <= NUM
      retval= boost::any(boost_any_number_to_double(a)<=boost_any_number_to_double(b));
    else if(boost_any_is_expr_algebra(a) && boost_any_is_number(b)) //EXPR <= NUM
      retval= boost::any(boost_any_to_ExprAlgebra(a).ToNum() <= boost_any_number_to_double(b));
    else if(boost_any_is_number(a) && boost_any_is_expr_algebra(b)) //NUM <= EXPR
      retval= boost::any(boost_any_number_to_double(a) <= boost_any_to_ExprAlgebra(b).ToNum());
    else if(boost_any_is_expr_algebra(a) && boost_any_is_expr_algebra(b)) //EXPR <= EXPR
      retval= boost::any(boost_any_to_ExprAlgebra(a).ToNum() <= boost_any_to_ExprAlgebra(b).ToNum());
    else if(boost_any_is_string(a) && boost_any_is_string(b)) //STR <= STR
      retval= boost::any(boost_any_to_string(a)<=boost_any_to_string(b));
    else
      std::cerr << "No se pudo aplicar el operador '<=' a los operandos de tipo: "
                << boost_any_tipo_operando(a) << " y "
                << boost_any_tipo_operando(b) << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el primer operando es mayor o igual que el segundo.
boost::any mayor_o_igual_boost_any(const boost::any &a,const boost::any &b)
  {
    boost::any retval;
    if(boost_any_is_number(a) && boost_any_is_number(b)) //NUM < NUM
      retval= boost::any(boost_any_number_to_double(a)>=boost_any_number_to_double(b));
    else if(boost_any_is_expr_algebra(a) && boost_any_is_number(b)) //EXPR >= NUM
      retval= boost::any(boost_any_to_ExprAlgebra(a).ToNum() >= boost_any_number_to_double(b));
    else if(boost_any_is_number(a) && boost_any_is_expr_algebra(b)) //NUM >= EXPR
      retval= boost::any(boost_any_number_to_double(a) >= boost_any_to_ExprAlgebra(b).ToNum());
    else if(boost_any_is_expr_algebra(a) && boost_any_is_expr_algebra(b)) //EXPR >= EXPR
      retval= boost::any(boost_any_to_ExprAlgebra(a).ToNum() >= boost_any_to_ExprAlgebra(b).ToNum());
    else if(boost_any_is_string(a) && boost_any_is_string(b)) //STR >= STR
      retval= boost::any(boost_any_to_string(a)>=boost_any_to_string(b));
    else
      std::cerr << "No se pudo aplicar el operador '>=' a los operandos de tipo: "
                << boost_any_tipo_operando(a) << " y "
                << boost_any_tipo_operando(b) << std::endl;
    return retval;
  }

//! @brief Devuelve verdadero si el primer operando es igual al segundo.
boost::any distinto_boost_any(const boost::any &a,const boost::any &b)
  {
    boost::any retval;
    if(boost_any_is_number(a) && boost_any_is_number(b))
      retval= boost::any(boost_any_number_to_double(a)!=boost_any_number_to_double(b));
    else if(boost_any_is_expr_algebra(a) && boost_any_is_number(b)) //EXPR != NUM
      retval= boost::any(boost_any_to_ExprAlgebra(a).ToNum() != boost_any_number_to_double(b));
    else if(boost_any_is_number(a) && boost_any_is_expr_algebra(b)) //NUM != EXPR
      retval= boost::any(boost_any_number_to_double(a) != boost_any_to_ExprAlgebra(b).ToNum());
    else if(boost_any_is_expr_algebra(a) && boost_any_is_expr_algebra(b)) //EXPR != EXPR
      retval= boost::any(boost_any_to_ExprAlgebra(a).ToNum() != boost_any_to_ExprAlgebra(b).ToNum());
    else if(boost_any_is_string(a) && boost_any_is_string(b))
      retval= boost::any(boost_any_to_string(a)!=boost_any_to_string(b));
    else
      std::cerr << "No se pudo aplicar el operador '!=' a los operandos de tipo: "
                << boost_any_tipo_operando(a) << " y "
                << boost_any_tipo_operando(b) << std::endl;
    return retval;
  }

boost::any and_boost_any(const boost::any &a,const boost::any &b)
  { return (convert_to_bool(a) && convert_to_bool(b)); }

boost::any or_boost_any(const boost::any &a,const boost::any &b)
  { return (convert_to_bool(a) || convert_to_bool(b)); }

boost::any not_boost_any(const boost::any &a)
  { return (!convert_to_bool(a)); }

const boost::any &ifte_boost_any(const boost::any &a,const boost::any &b,const boost::any &c)
  {
    const bool cumple= convert_to_bool(a);
    if(cumple)
      return b;
    else
      return c;
  }

//! @brief Devuelve (si puede) el objeto correspondiente a los índices b.
boost::any at_boost_any(const boost::any &a,const boost::any &b)
  {
    boost::any retval;
    if(boost_any_is_vector_any(b))
      {
        const std::vector<boost::any> &indices= boost_any_to_vector_any(b);
        const size_t szIndices= indices.size();
        const size_t i= convert_to_size_t(indices[0]);
        if(boost_any_is_string(a))  //STR[INT]
          retval= boost::any(boost_any_to_string(a)[i]);
        else if(boost_any_is_lista(a))  //LISTA[INT]
          retval= boost::any(boost_any_to_lista(a)[i]);
        else if(boost_any_is_lista_pos3d(a))  //LIST_POS3d[INT]
          retval= boost::any(boost_any_to_lista_pos3d(a)[i]);
        else if(boost_any_is_lista_pos2d(a))  //LIST_POS2d[INT]
          retval= boost::any(boost_any_to_lista_pos2d(a)[i]);
        else if(boost_any_is_vector3d(a))  //Vector3d[INT]
          retval= boost::any(boost_any_to_vector3d(a)(i+1));
        else if(boost_any_is_vector2d(a))  //Vector3d[INT]
          retval= boost::any(boost_any_to_vector2d(a)(i+1));
        else if(boost_any_is_m_double(a))  //M_DOUBLE[INT]
          {
            const m_double &m= boost_any_to_m_double(a);
            if(szIndices<2)
              retval= boost::any(m[i]);
            else
              {
                const size_t j= convert_to_size_t(indices[1]);
		retval= boost::any(m(i+1,j+1));
              }
          }
        else if(boost_any_is_vector_any(a))  //VECTOR_ANY[INT]
          retval= boost::any(boost_any_to_vector_any(a)[convert_to_size_t(indices[0])]);
        else
          {
	    std::cerr << "No se pudo aplicar el operador at al objeto de tipo: "
                      << boost_any_tipo_operando(a) << " para los índices de tipo "
                      << boost_any_tipo_operando(b) << std::endl;
          }
      }
    return retval;
  }

//! @brief Devuelve el tamaño del objeto.
size_t size_boost_any(const boost::any &a)
  {
    size_t retval= 0;
    if(boost_any_is_string(a)) //STR
      retval= boost_any_to_string(a).size();
    else if(boost_any_is_lista(a)) //LISTA
      retval= boost_any_to_lista(a).size();
    else if(boost_any_is_m_double(a)) //M_DOUBLE
      retval= boost_any_to_m_double(a).size();
    else if(boost_any_is_vector_any(a))  //VECTOR_ANY
      retval= boost_any_to_vector_any(a).size();
    else
      {
        std::cerr << "No se pudo aplicar el operador size al objeto de tipo: "
                  << boost_any_tipo_operando(a) << std::endl;
      }
    return retval;
  }

//! @brief Devuelve el número de filas del objeto.
size_t nfilas_boost_any(const boost::any &a)
  {
    size_t retval= 0;
    if(boost_any_is_m_double(a)) //M_DOUBLE
      retval= boost_any_to_m_double(a).getNumFilas();
    else if(boost_any_is_vector_any(a))  //VECTOR_ANY
      retval= 1;
    else
      {
        std::cerr << "No se pudo aplicar el operador nFilas al objeto de tipo: "
                  << boost_any_tipo_operando(a) << std::endl;
      }
    return retval;
  }

//! @brief Devuelve el número de columnas del objeto.
size_t ncols_boost_any(const boost::any &a)
  {
    size_t retval= 0;
    if(boost_any_is_m_double(a)) //M_DOUBLE
      retval= boost_any_to_m_double(a).getNumCols();
    else if(boost_any_is_vector_any(a))  //VECTOR_ANY
      retval= boost_any_to_vector_any(a).size();
    else
      {
        std::cerr << "No se pudo aplicar el operador nCols al objeto de tipo: "
                  << boost_any_tipo_operando(a) << std::endl;
      }
    return retval;
  }

//Geometría.
//! @brief Devuelve (si puede) la distancia entre dos objetos.
boost::any distancia_boost_any(const boost::any &a,const boost::any &b)
  {
    boost::any retval;
    if(boost_any_is_pos2d(a) && boost_any_is_pos2d(b))  //dist(Pos2d,Pos2d)
      retval= boost::any(dist(boost_any_to_pos2d(a),boost_any_to_pos2d(b)));
    else if(boost_any_is_pos3d(a) && boost_any_is_pos3d(b))  //dist(Pos3d,Pos3d)
      retval= boost::any(dist(boost_any_to_pos3d(a),boost_any_to_pos3d(b)));
    else
      {
        std::cerr << "No se pudo aplicar la funcion distancia  a los operandos de tipo: "
                  << boost_any_tipo_operando(a) << " y "
                  << boost_any_tipo_operando(b) << std::endl;
      }
    return retval;
  }

//Geometría.
//! @brief Devuelve (si puede) la angulo entre dos objetos.
boost::any angulo_boost_any(const boost::any &a,const boost::any &b)
  {
    boost::any retval;
    if(boost_any_is_vector2d(a) && boost_any_is_vector2d(b))  //angulo(Vector2d,Vector2d)
      retval= boost::any(angulo(boost_any_to_vector2d(a),boost_any_to_vector2d(b)));
    else if(boost_any_is_segmento2d(a) && boost_any_is_vector2d(b))  //angulo(Segmento2d,Vector2d)
      retval= boost::any(angulo(boost_any_to_segmento2d(a),boost_any_to_vector2d(b)));
    else if(boost_any_is_vector2d(a) && boost_any_is_segmento2d(b))  //angulo(Vector2d,Segmento2d)
      retval= boost::any(angulo(boost_any_to_vector2d(a),boost_any_to_segmento2d(b)));
    else if(boost_any_is_vector3d(a) && boost_any_is_vector3d(b))  //angulo(Vector3d,Vector3d)
      retval= boost::any(angulo(boost_any_to_vector3d(a),boost_any_to_vector3d(b)));
    else if(boost_any_is_plano3d(a) && boost_any_is_plano3d(b))  //angulo(Plano3d,Plano3d)
      retval= boost::any(angulo(boost_any_to_plano3d(a),boost_any_to_plano3d(b)));
    else if(boost_any_is_vector3d(a) && boost_any_is_plano3d(b))  //angulo(Vector3d,Plano3d)
      retval= boost::any(angulo(boost_any_to_vector3d(a),boost_any_to_plano3d(b)));
    else if(boost_any_is_plano3d(a) && boost_any_is_vector3d(b))  //angulo(Plano3d,Vector3d)
      retval= boost::any(angulo(boost_any_to_plano3d(a),boost_any_to_vector3d(b)));
    else if(boost_any_is_se3d(a) && boost_any_is_se3d(b))  //angulo(SemiEspacio3d,SemiEspacio3d)
      retval= boost::any(angulo(boost_any_to_se3d(a),boost_any_to_se3d(b)));
    else if(boost_any_is_vector3d(a) && boost_any_is_se3d(b))  //angulo(Vector3d,SemiEspacio3d)
      retval= boost::any(angulo(boost_any_to_vector3d(a),boost_any_to_se3d(b)));
    else if(boost_any_is_se3d(a) && boost_any_is_vector3d(b))  //angulo(SemiEspacio3d,Vector3d)
      retval= boost::any(angulo(boost_any_to_se3d(a),boost_any_to_vector3d(b)));
    else if(boost_any_is_recta2d(a) && boost_any_is_recta2d(b))  //angulo(Recta2d,Recta2d)
      retval= boost::any(angulo(boost_any_to_recta2d(a),boost_any_to_recta2d(b)));
    else
      {
        std::cerr << "No se pudo aplicar la funcion angulo a los operandos de tipo: "
                  << boost_any_tipo_operando(a) << " y "
                  << boost_any_tipo_operando(b) << std::endl;
      }
    return retval;
  }

//! @brief Devuelve (si puede) la interseccion de dos objetos.
boost::any interseccion_boost_any(const boost::any &a,const boost::any &b)
  {
    boost::any retval;
    if(boost_any_is_recta2d(a) && boost_any_is_recta2d(b))  //interseccion(Recta2d,Recta2d)
      retval= boost::any(interseccion(boost_any_to_recta2d(a),boost_any_to_recta2d(b)));
    else if(boost_any_is_plano3d(a) && boost_any_is_plano3d(b))  //interseccion(Plano3d,Plano3d)
      {
	Recta3d recta= recta_interseccion(boost_any_to_plano3d(a),boost_any_to_plano3d(b));
	if(recta.exists())
          retval= recta;
      }
    else
      {
        std::cerr << "No se pudo aplicar la funcion interseccion a los operandos de tipo: "
                  << boost_any_tipo_operando(a) << " y "
                  << boost_any_tipo_operando(b) << std::endl;
      }
    return retval;
  }

//! @brief Devuelve (si puede) la interseccion de dos objetos.
boost::any punto_interseccion_boost_any(const boost::any &a,const boost::any &b)
  {
    boost::any retval;
    if(boost_any_is_recta2d(a) && boost_any_is_recta2d(b))  //interseccion(Recta2d,Recta2d)
      {
	Pos2d p= punto_interseccion(boost_any_to_recta2d(a),boost_any_to_recta2d(b));
        if(p.exists())
          retval= p;
      }
    else
      {
        std::cerr << "No se pudo aplicar la funcion punto_interseccion a los operandos de tipo: "
                  << boost_any_tipo_operando(a) << " y "
                  << boost_any_tipo_operando(b) << std::endl;
      }
    return retval;
  }
