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
//python_utils.h

#ifndef PYTHON_UTILS_H
#define PYTHON_UTILS_H

#include <vector>
#include <set>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/class.hpp>
#include <boost/python/list.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>



std::vector<int> vector_int_from_py_list(const boost::python::list &);
std::vector<double> vector_double_from_py_list(const boost::python::list &);

std::vector<std::string> vector_string_from_py_list(const boost::python::list &);

std::set<int> set_int_from_py_list(const boost::python::list &);

boost::python::list vector_int_to_py_list(const std::vector<int> &l);
boost::python::list vector_double_to_py_list(const std::vector<double> &l);

float mseImages(const std::string &fNameA, const std::string &fNameB);
float psnrImagenes(const std::string &fNameA, const std::string &fNameB);
float compare_images(const std::string &fNameA, const std::string &fNameB);


boost::python::object EntCmd_eval(boost::python::object self, const std::string &str);

boost::python::object EntCmd_exec(boost::python::object self, const std::string &block);

boost::python::object EntCmd_exec_file(boost::python::object self, const std::string &fileName);

//Helper class to expose container like std::list
inline void IndexError(void)
  { PyErr_SetString(PyExc_IndexError, "Index out of range"); }

template<class T>
struct std_item
{
    typedef typename T::value_type V;
    static V& get(T const& x, int i)
      {
        if( i<0 ) i+=x.size();
        if( i>=0 && i<x.size() ) return x[i];
        IndexError();
      }
    static void set(T const& x, int i, V const& v)
      {
        if( i<0 ) i+=x.size();
        if( i>=0 && i<x.size() ) x[i]=v;
        else IndexError();
      }
    static void del(T const& x, int i)
      {
        if( i<0 ) i+=x.size();
        if( i>=0 && i<x.size() ) x.erase(i);
        else IndexError();
      }
    static void add(T const& x, V const& v)
      {
        x.push_back(v);
      }
  };
#endif
