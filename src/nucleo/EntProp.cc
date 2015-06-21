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
//EntProp.cc

#include "EntProp.h"
#include "InterpreteRPN.h"
#include "MatrizAny.h"
#include <boost/any.hpp>
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"
#include "xc_utils/src/base/utils_any_const_ptr.h"
#include "xc_utils/src/nucleo/aux_any.h"
#include <fstream>
#include "xc_basic/src/texto/en_letra.h"
#include "xc_basic/src/texto/latex.h"
#include "xc_basic/src/funciones/algebra/LexAlgebra.h"
#include "xc_basic/src/funciones/algebra/integ_num.h"
#include "xc_basic/src/matrices/matrizExpr.h"
#include "xc_basic/src/util/memoria.h"
//#include "xc_basic/src/util/units.h"
#include "boost/lexical_cast.hpp"
#include "boost/algorithm/string/trim.hpp"
#include "boost/algorithm/string.hpp"
#include "boost/math/special_functions/acosh.hpp"
#include "boost/math/special_functions/asinh.hpp"
#include "boost/math/special_functions/atanh.hpp"
#include "boost/math/common_factor.hpp"
#include <cxxabi.h>
#include <sys/stat.h>
#include "boost/regex.hpp"

#include "VarTypes.h"

#include <cctype>
#include "CImg.h"

//Variables estáticas de EntProp.
int EntProp::verborrea= 0;

std::set<const EntProp *> EntProp::visitados;
EntPropSorter EntProp::ent_prop_sorter;

//! @brief Constructor por defecto.
EntProp::EntProp(EntProp *owr)
  : owner(owr), params(), sub(NULL)
  {
    if(this == owner)
      std::cerr << "EntProp constructor por defecto; ¡ojo!, objeto de clase: '" 
                << nombre_clase() << "', propietario de sí mismo." << std::endl;
  }

//! @brief Constructor de copia.
EntProp::EntProp(const EntProp &otro)
  : owner(otro.owner), params(otro.params), sub(NULL)
  {
    if(this == owner)
      std::cerr << "EntProp constructor de copia; ¡ojo!, objeto de clase: '"
                << nombre_clase() << "', propietario de sí mismo." << std::endl;
    params.SetOwner(this);
  }

//! @brief Operador asignación.
EntProp &EntProp::operator=(const EntProp &otro)
  {
    owner= otro.owner;
    sub= NULL;
    if(this == owner)
      {
        std::cerr << "EntProp operador asignación; ¡ojo!, objeto de clase: '" << nombre_clase() 
                  << "', propietario de sí mismo." << std::endl;
        owner= NULL;
      }
    params= otro.params;
    params.SetOwner(this);
    return *this;
  }

//! @brief Devuelve el nombre de la clase.
std::string EntProp::nombre_clase(void) const
  {
    std::string tmp= typeid(*this).name();
    std::bad_exception  e;
    int status;
    char *realname= abi::__cxa_demangle(tmp.c_str(), 0, 0, &status);
    if(realname)
      tmp= std::string(realname);
    free(realname);
    return tmp;
  }

//! @brief Devuelve el nivel de verborrea.
const int &EntProp::GetNivelVerborrea(void)
  { return verborrea; }

//! @brief Devuelve el nombre de la propiedad quitandole el carácter arroba.
std::string EntProp::nombre_propiedad(const std::string &str)
  { return boost::trim_copy_if(str,boost::is_any_of(" @")); }

//! @brief Devuelve el nombre de la variable quitandole el carácter dólar.
std::string EntProp::nombre_variable(const std::string &str)
  { return boost::trim_copy_if(str,boost::is_any_of(" $")); }

//! @brief Asigna el propietario del objeto.
void EntProp::set_owner(EntProp *owr)
  { owner= owr; }

//! @brief Asigna puntero a la rutina solicita la ejecución de un bloque de código.
void EntProp::set_sub(const BloqueSub *s) const
  { sub= s; }

//! @brief Imprime un mensaje de error advirtiendo que faltan argumentos para una función.
void EntProp::err_num_argumentos(std::ostream &os,const size_t &narg,const std::string &nmb_func,const std::string &nmb_prop) const
  {
    os << nombre_clase() 
       << "::" << nmb_func << " se esperaba(n) " << narg << " argumento(s) para "
       << nmb_prop << std::endl;
  }

//! @brief Imprime un mensaje de error advirtiendo que no se esperaba el tipo devuelto.
void EntProp::err_tipo_devuelto(std::ostream &os,const std::string &nmb_func,const std::string &nmb_prop,const std::string &tipos_esperados,const std::string &tipo_obtenido) const
  {
    os << nombre_clase() 
       << "::" << nmb_func << " el valor devuelto por " << nmb_prop << " es de tipo "
       << tipo_obtenido << ", se esperaba que fuera " << tipos_esperados << std::endl;
  }

//! @brief Imprime un mensaje de error advirtiendo que el tipo de un argumento para una función es incorrecto.
void EntProp::err_tipo_argumento(std::ostream &os,const size_t &narg,const std::string &nmb_func,const std::string &nmb_prop,const std::string &tipo_esperado,const std::string &tipo_obtenido) const
  {
    os << nombre_clase() 
       << "::" << nmb_func << " se esperaba que el argumento " << narg 
       << " para " << nmb_prop << " fuera de tipo " << tipo_esperado
       << ", pero se obtuvo uno de tipo: " << tipo_obtenido << std::endl;
  }

//! @brief Devuelve verdadero si el contenido de los archivos es el mismo. Copiado
//! de la página de Rebecca Hasti en la universidad de Wisconsin.
bool archivos_iguales(std::istream &in1, std::istream &in2)
  {
    char ch1, ch2;
    while(in1.get(ch1))
      {
        if(!in2.get(ch2) || (ch1 != ch2))
	  return false;
      }
    // here when no more characters in in1
    // input files are the same iff there are also no more characters in in2
    if(!in2.get(ch2))
      return true;
    else
      return false;
  }

bool archivos_iguales(const std::string &fname1,const std::string fname2)
  {
    if(fname1==fname2)
      return true;
    if(!EntProp::existe_archivo(fname1))
      return false;
    if(!EntProp::existe_archivo(fname2))
      return false;
    std::ifstream inFile1,inFile2;
    inFile1.open(fname1.c_str());
    if(inFile1.fail())
      {
	std::cerr << "No se pudo abrir el archivo:" << fname1 << std::endl;
        return false;
      }
    inFile2.open(fname2.c_str());
    if(inFile2.fail())
      {
	std::cerr << "No se pudo abrir el archivo:" << fname2 << std::endl;
        return false;
      }
    return archivos_iguales(inFile1,inFile2);
  }

bool EntProp::existe_archivo(const std::string &FileName)
  {
    struct stat my_stat;
    return (stat(FileName.c_str(), &my_stat) == 0);
  }

bool EntProp::es_directorio(const std::string &FileName)
  {
    struct stat my_stat;
    if(stat(FileName.c_str(), &my_stat) != 0)
      return false;
    else
      return ((my_stat.st_mode & S_IFDIR) != 0);
  }

//! @brief Devuelve verdadero si se cumple la condición
//! definida en cond.
bool EntProp::verdadero(const std::string &cond) const
  { return interpretaBool(cond); }

//! @brief Asigna el valor que se pasa como parámetro a la variable temporal adecuada
//! @param val: Valor a asignar.
//! @param cod: Sólo se pasa para el mensaje de error.
any_const_ptr EntProp::set_temp_var(const boost::any &val, const std::string &cod) const
  {
    if(boost_any_is_number(val))
      {
        tmp_gp_dbl= boost_any_number_to_double(val);
        return any_const_ptr(tmp_gp_dbl);
      }
    else if(boost_any_is_expr_algebra(val))
      {
        tmp_gp_expr= boost_any_to_ExprAlgebra(val);
        return any_const_ptr(tmp_gp_expr);
      }
    else if(boost_any_is_string(val))
      {
        tmp_gp_str= boost_any_to_string(val);
        return any_const_ptr(tmp_gp_str);
      }
    else if(boost_any_is_pos2d(val))
      {
        tmp_gp_pos2d= boost_any_to_pos2d(val);
        return any_const_ptr(tmp_gp_pos2d);
      }
    else if(boost_any_is_matriz_any(val))
      {
        tmp_gp_many= boost_any_to_matriz_any(val);
        return any_const_ptr(tmp_gp_many);
      }
    else
      {
        err_tipo_devuelto(std::cerr,"set_temp_var",cod,"double,ExprAlgebra o string",boost_any_tipo_operando(val));
        return any_const_ptr();
      }
  }

//! @brief Funciones matemáticas básicas.
any_const_ptr EntProp::BasicMathFunc(const std::string &cod) const
  {
    if(verborrea>4)
      std::clog << "EntProp::BasicMathFunc (" << nombre_clase() << "::BasicMathFunc) Buscando propiedad: " << cod << std::endl;
    any_const_ptr retval;
    if(cod == "evalExpr") //Evalúa la expresión que debe estar en la pila.
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const std::string args= convert_to_string(InterpreteRPN::Pila().Pop());
            tmp_gp_expr= convert_to_ExprAlgebra(InterpreteRPN::Pila().Pop()).Eval(args);
            retval= any_const_ptr(tmp_gp_expr);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "getNombresVariables") //Obtiene los nombres de las variables de la expresión que debe estar en la pila.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            const std::vector<std::string> vars= convert_to_ExprAlgebra(InterpreteRPN::Pila().Pop()).getNombresVariables();
            tmp_gp_lista.clearAll();
            tmp_gp_lista.Inserta(vars.begin(),vars.end());
            retval= any_const_ptr(tmp_gp_lista);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "tonum") //Evalúa la expresión que debe estar en la pila.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_dbl= convert_to_ExprAlgebra(InterpreteRPN::Pila().Pop()).ToNum();
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    // else if(cod == "factorConversion") //Factor de conversión entre unidades.
    //   {
    //     if(InterpreteRPN::Pila().size()>1)
    //       {
    //         const std::string unitB= convert_to_string(InterpreteRPN::Pila().Pop());
    //         const std::string unitA= convert_to_string(InterpreteRPN::Pila().Pop());
    //         tmp_gp_dbl=factor_conversion(unitA,unitB);
    //         retval= any_const_ptr(tmp_gp_dbl);
    //       }
    //     else
    //       {
    //         err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
    //       }
    //   }
    // else if(cod == "convierte") //Convierte entre unidades.
    //   {
    //     if(InterpreteRPN::Pila().size()>1)
    //       {
    //         const std::string unitB= convert_to_string(InterpreteRPN::Pila().Pop());
    //         const std::string unitA= convert_to_string(InterpreteRPN::Pila().Pop());
    //         const double v= convert_to_double(InterpreteRPN::Pila().Pop());
    //         tmp_gp_dbl=convierte(v,unitA,unitB);
    //         retval= any_const_ptr(tmp_gp_dbl);
    //       }
    //     else
    //       {
    //         err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
    //       }
    //   }
    else if(cod == "deg2rad") //Convierte grados a radianes.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_dbl= DegToRad(convert_to_double(InterpreteRPN::Pila().Pop()));
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "rad2deg") //Convierte radianes a grados.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_dbl=RadToDeg(convert_to_double(InterpreteRPN::Pila().Pop()));
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "PI") //Número Pi.
      {
        tmp_gp_dbl= M_PI;
        retval= any_const_ptr(tmp_gp_dbl);
      }
    else if(cod == "cos") //Coseno de un ángulo.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_dbl= cos(convert_to_double(InterpreteRPN::Pila().Pop()));
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "sec") //Secante de un ángulo.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_dbl= sec(convert_to_double(InterpreteRPN::Pila().Pop()));
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "sin") //Seno de un ángulo.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_dbl= sin(convert_to_double(InterpreteRPN::Pila().Pop()));
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "cosec") //Cosecante de un ángulo.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_dbl= 1.0/sin(convert_to_double(InterpreteRPN::Pila().Pop()));
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "tan") //Tangente de un ángulo.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_dbl= tan(convert_to_double(InterpreteRPN::Pila().Pop()));
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "cotg") //Cotangente de un ángulo.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_dbl= 1.0/tan(convert_to_double(InterpreteRPN::Pila().Pop()));
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "atan") //Arcotangente de un ángulo.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_dbl= atan(convert_to_double(InterpreteRPN::Pila().Pop()));
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "atan2") //Devuelve el arco tangente de y/x, en el intervalo [-PI, +PI] radianes.
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const double &x= convert_to_double(InterpreteRPN::Pila().Pop());
            const double &y= convert_to_double(InterpreteRPN::Pila().Pop());
            tmp_gp_dbl= atan2(y,x);
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "asin") //Arcoseno de un ángulo.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_dbl= asin(convert_to_double(InterpreteRPN::Pila().Pop()));
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "acos") //Arcocoseno de un ángulo.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_dbl= acos(convert_to_double(InterpreteRPN::Pila().Pop()));
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "round") //Redondea al entero más próximo.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_dbl= round(convert_to_double(InterpreteRPN::Pila().Pop()));
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "ceil") //Devuelve el entero más pequeño no menor que el argumento.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_dbl= ceil(convert_to_double(InterpreteRPN::Pila().Pop()));
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "floor") //Devuelve el entero más grande no mayor que el argumento.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_dbl= floor(convert_to_double(InterpreteRPN::Pila().Pop()));
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "even") //Devuelve verdadero si el número es par.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_bool= ((convert_to_long_int(InterpreteRPN::Pila().Pop())%2)==0);
            retval= any_const_ptr(tmp_gp_bool);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "odd") //Devuelve verdadero si el número es par.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_bool= ((convert_to_long_int(InterpreteRPN::Pila().Pop())%2)!=0);
            retval= any_const_ptr(tmp_gp_bool);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "sqr") //Devuelve el cuadrado del argumento.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_dbl= sqr(convert_to_double(InterpreteRPN::Pila().Pop()));
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "sqrt") //Devuelve la raíz cuadrada del argumento.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_dbl= sqrt(convert_to_double(InterpreteRPN::Pila().Pop()));
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "cosh") //Devuelve el coseno hiperbólico del argumento.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_dbl= cosh(convert_to_double(InterpreteRPN::Pila().Pop()));
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "sinh") //Devuelve el seno hiperbólico del argumento.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_dbl= sinh(convert_to_double(InterpreteRPN::Pila().Pop()));
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "tanh") //Devuelve la tangente hiperbólica del argumento.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_dbl= tanh(convert_to_double(InterpreteRPN::Pila().Pop()));
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "acosh") //Devuelve el argumento del coseno hiperbólico.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_dbl= boost::math::acosh(convert_to_double(InterpreteRPN::Pila().Pop()));
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "asinh") //Devuelve el argumento del seno hiperbólico.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_dbl= boost::math::asinh(convert_to_double(InterpreteRPN::Pila().Pop()));
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "atanh") //Devuelve el argumento de la tangente hiperbólica.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_dbl= boost::math::atanh(convert_to_double(InterpreteRPN::Pila().Pop()));
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "pow")
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const double b= convert_to_double(InterpreteRPN::Pila().Pop());
            const double a= convert_to_double(InterpreteRPN::Pila().Pop());
            tmp_gp_dbl= pow(a,b);
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "exp") //Devuelve la función exponencial del argumento.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_dbl= exp(convert_to_double(InterpreteRPN::Pila().Pop()));
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "log") //Devuelve el logaritmo natural (o neperiano) del argumento.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_dbl= log(convert_to_double(InterpreteRPN::Pila().Pop()));
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "log10") //Devuelve el logaritmo decimal del argumento.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_dbl= log10(convert_to_double(InterpreteRPN::Pila().Pop()));
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "expand") //Expande la expresión que se pasa como argumento.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_expr= expand(convert_to_ExprAlgebra(InterpreteRPN::Pila().Pop()));
            retval= any_const_ptr(tmp_gp_expr);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "colct") //Colct la expresión que se pasa como argumento.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_expr= colct(convert_to_ExprAlgebra(InterpreteRPN::Pila().Pop()));
            retval= any_const_ptr(tmp_gp_expr);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "integSimpson") //Devuelve la integral de la función por el método de simpson.
      {
        if(InterpreteRPN::Pila().size()>4)
          {
            const int n= convert_to_int(InterpreteRPN::Pila().Pop()); //Número de intervalos a adoptar.
            const ExprAlgebra b= convert_to_ExprAlgebra(InterpreteRPN::Pila().Pop()); //Límite de integración superior.
            const ExprAlgebra a= convert_to_ExprAlgebra(InterpreteRPN::Pila().Pop()); //Límite de integración inferior.
            const std::string var= convert_to_string(InterpreteRPN::Pila().Pop()); //Variable respecto a la que se integra.
            const ExprAlgebra e= convert_to_ExprAlgebra(InterpreteRPN::Pila().Pop()); //Expresión a integrar.
            tmp_gp_expr= e.IntegSimpson(Intervalo1D(var,a,b,n));
            retval= any_const_ptr(tmp_gp_expr);
          }
        else
          {
            err_num_argumentos(std::cerr,5,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "genListaEnteros") //Genera una lista de enteros.
      {
        if(InterpreteRPN::Pila().size()>2)
          {
            const int step= convert_to_int(InterpreteRPN::Pila().Pop()); //Incremento.
            const int ultimo= convert_to_int(InterpreteRPN::Pila().Pop());
            const int primero= convert_to_int(InterpreteRPN::Pila().Pop());

            tmp_gp_lista.clearAll();
            tmp_gp_lista.GenListaEnteros(primero,ultimo,step);
            retval= any_const_ptr(tmp_gp_lista);
          }
        else
          {
            err_num_argumentos(std::cerr,3,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "int") //Convierte en entero el argumento que está en la pila.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_int= convert_to_int(InterpreteRPN::Pila().Pop());
            retval= any_const_ptr(tmp_gp_int);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "vector") //Devuelve un vector del tamaño que se especifica.
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const boost::any seed= InterpreteRPN::Pila().Pop();
            const size_t sz= convert_to_size_t(InterpreteRPN::Pila().Pop());
            static boost::any tmp_vector;
            tmp_gp_vany= std::vector<boost::any>(sz,seed);
            tmp_vector= tmp_gp_vany;
            retval= any_const_ptr(tmp_vector);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "dot")
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const boost::any a= InterpreteRPN::Pila().Pop();
            const boost::any b= InterpreteRPN::Pila().Pop();
            const boost::any dot= dot_boost_any(a,b);
            retval= set_temp_var(dot,cod);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "cross")
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const boost::any b= InterpreteRPN::Pila().Pop();
            const boost::any a= InterpreteRPN::Pila().Pop();
            static boost::any tmp_vector;
            tmp_vector= cross_boost_any(a,b);
            retval= any_const_ptr(tmp_vector);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "anguloVectores")
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const boost::any b= InterpreteRPN::Pila().Pop();
            const boost::any a= InterpreteRPN::Pila().Pop();
            const boost::any prod_mod= mult_boost_any(abs_boost_any(a),abs_boost_any(b));
            const double coseno= convert_to_double(div_boost_any(dot_boost_any(a,b),prod_mod));
            tmp_gp_dbl= acos(coseno);
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "proj")
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const boost::any b= InterpreteRPN::Pila().Pop();
            const boost::any a= InterpreteRPN::Pila().Pop();
            static boost::any tmp_vector;
            tmp_vector= proj_boost_any(a,b);
            retval= any_const_ptr(tmp_vector);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "normaliza")
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            const boost::any a= InterpreteRPN::Pila().Pop();
            static boost::any tmp_vector;
            tmp_vector= normaliza_boost_any(a);
            retval= any_const_ptr(tmp_vector);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "abs")
      {
        if(InterpreteRPN::Pila().size()>0)
          retval= set_temp_var(abs_boost_any(InterpreteRPN::Pila().Pop()),cod);
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "traza")
      {
        if(InterpreteRPN::Pila().size()>0)
          retval= set_temp_var(traza_boost_any(InterpreteRPN::Pila().Pop()),cod);
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "trn")
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_many= convert_to_matriz_any(traspuesta_boost_any(InterpreteRPN::Pila().Pop()));
            retval= any_const_ptr(tmp_gp_many);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "getNumFilas")
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_many= convert_to_matriz_any(InterpreteRPN::Pila().Pop());
            retval= set_temp_var(tmp_gp_many.getNumFilas(),cod);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "getNumCols")
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_many= convert_to_matriz_any(InterpreteRPN::Pila().Pop());
            retval= set_temp_var(tmp_gp_many.getNumCols(),cod);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "getFila")
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const int f= convert_to_size_t(InterpreteRPN::Pila().Pop());
            tmp_gp_many= convert_to_matriz_any(InterpreteRPN::Pila().Pop());
            retval= set_temp_var(tmp_gp_many.GetFila(f),cod);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "getCaja")
      {
        if(InterpreteRPN::Pila().size()>4)
          {
            const int c2= convert_to_size_t(InterpreteRPN::Pila().Pop());
            const int f2= convert_to_size_t(InterpreteRPN::Pila().Pop());
            const int c1= convert_to_size_t(InterpreteRPN::Pila().Pop());
            const int f1= convert_to_size_t(InterpreteRPN::Pila().Pop());
            tmp_gp_many= convert_to_matriz_any(InterpreteRPN::Pila().Pop());
            retval= set_temp_var(tmp_gp_many.GetCaja(f1,c1,f2,c2),cod);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "getCol")
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const int c= convert_to_size_t(InterpreteRPN::Pila().Pop());
            tmp_gp_many= convert_to_matriz_any(InterpreteRPN::Pila().Pop());
            retval= set_temp_var(tmp_gp_many.GetCol(c),cod);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "sign")
      {
        if(InterpreteRPN::Pila().size()>0)
          retval= set_temp_var(sign_boost_any(InterpreteRPN::Pila().Pop()),cod);
        else
          {
            err_num_argumentos(std::cerr,1,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "max")
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const boost::any a= InterpreteRPN::Pila().Pop();
            const boost::any b= InterpreteRPN::Pila().Pop();
            const boost::any vmax= max_boost_any(a,b);
            retval= set_temp_var(vmax,cod);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "min")
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const boost::any a= InterpreteRPN::Pila().Pop();
            const boost::any b= InterpreteRPN::Pila().Pop();
            const boost::any vmin= min_boost_any(a,b);
            retval= set_temp_var(vmin,cod);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "gcd") //Devuelve el máximo común divisor de dos enteros positivos.
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const size_t &b= convert_to_size_t(InterpreteRPN::Pila().Pop());
            const size_t &a= convert_to_size_t(InterpreteRPN::Pila().Pop());
            tmp_gp_szt= boost::math::gcd(a,b);
            retval= any_const_ptr(tmp_gp_szt);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "lcm") //Devuelve el mínimo común múltiplo de dos enteros positivos.
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const size_t &b= convert_to_size_t(InterpreteRPN::Pila().Pop());
            const size_t &a= convert_to_size_t(InterpreteRPN::Pila().Pop());
            tmp_gp_szt= boost::math::lcm(a,b);
            retval= any_const_ptr(tmp_gp_szt);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"EntProp::BasicMathFunc",cod);
          }
      }
    else if(cod == "mod") //Devuelve el resto de la división
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const int b= convert_to_int(InterpreteRPN::Pila().Pop());
            const int a= convert_to_int(InterpreteRPN::Pila().Pop());
            tmp_gp_dbl= a % b;
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"EntProp::BasicMathFunc",cod);
          }
      }
    return retval;
  }

//! @brief Solicita al usuario una clave.
std::string EntProp::getPass(const std::string &msg) const
  {
    std::string retval=getpass(msg.c_str());
    return retval;
  }

//! @brief Funciones básicas para cadenas de caracteres.
any_const_ptr EntProp::BasicStrFunc(const std::string &cod) const
  {
    if(verborrea>4)
      std::clog << "EntProp::BasicStrFunc (" << nombre_clase() << "::GetPropLocal) Buscando propiedad: " << cod << std::endl;
    any_const_ptr retval;
    if(cod == "sqlValue")
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_str= boost_any_to_sql_value(InterpreteRPN::Pila().Pop());
            retval= any_const_ptr(tmp_gp_str);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetProp",cod);
          }
      }
    else if(cod == "boolToStr")
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            const bool b= convert_to_bool(InterpreteRPN::Pila().Pop());
            if(b)
              tmp_gp_str= "si";
            else
              tmp_gp_str= "no";
            retval= any_const_ptr(tmp_gp_str);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetProp",cod);
          }
      }
    else if(cod == "str_cmp") //Compara dos cadenas de caracteres.
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const std::string str1= convert_to_string(InterpreteRPN::Pila().Pop());
            const std::string str2= convert_to_string(InterpreteRPN::Pila().Pop());
            if(str1 == str2)
              tmp_gp_dbl= 1.0; //Verdadero.
            else
              tmp_gp_dbl= 0.0; //Falso.
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"GetProp",cod);
          }
      }
    else if(cod == "toupper") //Convierte la cadena de caracteres a mayúsculas.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
	    boost::any tmp= InterpreteRPN::Pila().Pop();
            if(boost_any_is_string(tmp))
              {
                tmp_gp_str= toupper(boost_any_to_string(tmp));
                retval= any_const_ptr(tmp_gp_str);
              }
            else
              {
                err_tipo_argumento(std::cerr,1,"GetProp",cod,"string",boost_any_tipo_operando(tmp));
              }
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetProp",cod);
          }
      }
    else if(cod == "tolower") //Convierte la cadena de caracteres a minúsculas.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
	    boost::any tmp= InterpreteRPN::Pila().Pop();
            if(boost_any_is_string(tmp))
              {
                tmp_gp_str= tolower(boost_any_to_string(tmp));
                retval= any_const_ptr(tmp_gp_str);
              }
            else
              {
                err_tipo_argumento(std::cerr,1,"GetProp",cod,"string",boost_any_tipo_operando(tmp));
              }
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetProp",cod);
          }
      }
    else if(cod == "toLaTex") //Coloca los caracteres de escape cuando es necesario.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
	    boost::any tmp= InterpreteRPN::Pila().Pop();
            if(boost_any_is_string(tmp))
              {
                tmp_gp_str= ascii2latex(boost_any_to_string(tmp));
                retval= any_const_ptr(tmp_gp_str);
              }
            else
              {
                err_tipo_argumento(std::cerr,1,"GetProp",cod,"string",boost_any_tipo_operando(tmp));
              }
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetProp",cod);
          }
      }
    else if(cod == "char") //Devuelve un carácter.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            const int ascii_code= convert_to_int(InterpreteRPN::Pila().Pop());
            tmp_gp_str= "A";
            tmp_gp_str[0]= char(ascii_code);
            retval= any_const_ptr(tmp_gp_str);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetProp",cod);
          }
      }
    else if(cod == "str2int") //Convierte la cadena de caracteres a entero.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
	    boost::any tmp= InterpreteRPN::Pila().Pop();
            if(boost_any_is_string(tmp))
              {
                tmp_gp_int= boost::lexical_cast<int>(boost_any_to_string(tmp));
                retval= any_const_ptr(tmp_gp_int);
              }
            else
              {
                err_tipo_argumento(std::cerr,1,"GetProp",cod,"string",boost_any_tipo_operando(tmp));
              }
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetProp",cod);
          }
      }
    else if(cod == "strlen") //Devuelve la longitud de la cadena de caracteres.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
	    boost::any tmp= InterpreteRPN::Pila().Pop();
            tmp_gp_str= convert_to_string(tmp);
            tmp_gp_szt= tmp_gp_str.size();
            retval= any_const_ptr(tmp_gp_szt);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetProp",cod);
          }
      }
    else if(cod == "strsub") //Devuelve una subcadena de caracteres.
      {
        if(InterpreteRPN::Pila().size()>2)
          {
            const size_t len= convert_to_size_t(InterpreteRPN::Pila().Pop());
            const size_t ini= convert_to_size_t(InterpreteRPN::Pila().Pop());
            const std::string str= convert_to_string(InterpreteRPN::Pila().Pop());
            tmp_gp_str= str.substr(ini,len);
            retval= any_const_ptr(tmp_gp_str);
          }
        else
          {
            err_num_argumentos(std::cerr,3,"GetProp",cod);
          }
      }
    else if(cod == "format") //Devuelve la cadena de caracteres que representa
                             //el objeto con el formato que se pasa como parametro.
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const std::string fmt= convert_to_string(InterpreteRPN::Pila().Pop());
            tmp_gp_str= boost_any_format(InterpreteRPN::Pila().Pop(),fmt);
            retval= any_const_ptr(tmp_gp_str);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"GetProp",cod);
          }
      }
    else if(cod == "expr2str") //Devuelve la cadena de caracteres que representa la expresión.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            const ExprAlgebra expr= convert_to_ExprAlgebra(InterpreteRPN::Pila().Pop());
            tmp_gp_str= expr.GetString();
            retval= any_const_ptr(tmp_gp_str);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetProp",cod);
          }
      }
    else if(cod == "regExpMatch")
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const std::string str= convert_to_string(InterpreteRPN::Pila().Pop()); //Cadena de caracteres.
            const std::string regExp=  convert_to_string(InterpreteRPN::Pila().Pop()); //Expresión regular.
            const boost::regex e(regExp);
            tmp_gp_int= boost::regex_match(str,e);
            retval= any_const_ptr(tmp_gp_int);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"GetProp",cod);
          }
      }
    else if(cod == "regExpReplace")
      {
        if(InterpreteRPN::Pila().size()>2)
          {
            const std::string nueva= convert_to_string(InterpreteRPN::Pila().Pop()); //Cadena a colocar.
            const boost::regex e(convert_to_string(InterpreteRPN::Pila().Pop())); //Expresión regular.
            const std::string str= convert_to_string(InterpreteRPN::Pila().Pop()); //Cadena de caracteres.
            tmp_gp_str= boost::regex_replace(str,e,nueva,boost::match_default);
            retval= any_const_ptr(tmp_gp_str);
          }
        else
          {
            err_num_argumentos(std::cerr,3,"GetProp",cod);
          }
      }
    else if(cod == "qBlancos")
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            const std::string str= convert_to_string(InterpreteRPN::Pila().Pop()); //Cadena de caracteres.
            tmp_gp_str= q_blancos(str);
            retval= any_const_ptr(tmp_gp_str);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetProp",cod);
          }
      }
    else if(cod == "copiaHasta")
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const std::string str= convert_to_string(InterpreteRPN::Pila().Pop()); //Cadena de caracteres.
            const char delim=  convert_to_string(InterpreteRPN::Pila().Pop())[0]; //Carácter delimitador.
            tmp_gp_str= copia_hasta(str,delim);
            retval= any_const_ptr(tmp_gp_str);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"GetProp",cod);
          }
      }
    else if(cod == "copiaDesde")
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const std::string str= convert_to_string(InterpreteRPN::Pila().Pop()); //Cadena de caracteres.
            const char delim=  convert_to_string(InterpreteRPN::Pila().Pop())[0]; //Carácter delimitador.
            tmp_gp_str= copia_desde(str,delim);
            retval= any_const_ptr(tmp_gp_str);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"GetProp",cod);
          }
      }
    else if(cod == "replaceAll")
      {
        if(InterpreteRPN::Pila().size()>2)
          {
            const std::string n= convert_to_string(InterpreteRPN::Pila().Pop()); //Cadena de caracteres nueva.
            const std::string v= convert_to_string(InterpreteRPN::Pila().Pop()); //Cadena de caracteres vieja.
            tmp_gp_str= convert_to_string(InterpreteRPN::Pila().Pop()); //Cadena de caracteres.
            boost::replace_all(tmp_gp_str, v, n);
            retval= any_const_ptr(tmp_gp_str);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"GetProp",cod);
          }
      }
    else if(cod == "str_dbl") //Devuelve una cadena de caracteres con un número fijo de decimales.
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const size_t &prec= convert_to_size_t(InterpreteRPN::Pila().Pop());
            const double &num=  convert_to_double(InterpreteRPN::Pila().Pop());
            tmp_gp_str= en_humano(num,prec); //Verdadero.
            retval= any_const_ptr(tmp_gp_str);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"GetProp",cod);
          }
      }
    else if(cod == "replace")
      {
        if(InterpreteRPN::Pila().size()>2)
          {
            const char n=  convert_to_string(InterpreteRPN::Pila().Pop())[0]; //Carácter nuevo.
            const char v=  convert_to_string(InterpreteRPN::Pila().Pop())[0]; //Carácter viejo.
            tmp_gp_str= convert_to_string(InterpreteRPN::Pila().Pop()); //Cadena de caracteres.
            replace_in_situ(tmp_gp_str,v,n);
            retval= any_const_ptr(tmp_gp_str);
          }
        else
          {
            err_num_argumentos(std::cerr,3,"GetProp",cod);
          }
      }
    else if(cod == "eliminaCar")
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const char c=  convert_to_string(InterpreteRPN::Pila().Pop())[0]; //Carácter a eliminar.
            const std::string str= convert_to_string(InterpreteRPN::Pila().Pop()); //Cadena de caracteres.
            tmp_gp_str= elimina_car(str,c);
            retval= any_const_ptr(tmp_gp_str);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"GetProp",cod);
          }
      }
    else if(cod == "getpass")
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            const std::string msg= convert_to_string(InterpreteRPN::Pila().Pop()); //Mensaje a mostrar.
            tmp_gp_str= getPass(msg);
            retval= any_const_ptr(tmp_gp_str);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetProp",cod);
          }
      }
    return retval;
  }

//! @brief Funciones booleanas básicas.
any_const_ptr EntProp::BasicBoolFunc(const std::string &cod) const
  {
    if(verborrea>4)
      std::clog << "EntProp::BasicBoolFunc (" << nombre_clase() << "::GetPropLocal) Buscando propiedad: " << cod << std::endl;
    any_const_ptr retval;
    if(cod == "true") //Devuelve verdadero si lo es la cadena que se pasa como parámetro.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            const std::string &cond= convert_to_string(InterpreteRPN::Pila().Pop());
            if(verdadero(cond))
              tmp_gp_dbl= 1.0; //Verdadero.
            else
              tmp_gp_dbl= 0.0; //Falso.
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetProp",cod);
          }
      }
    else if(cod == "false") //Devuelve falso si lo es la cadena que se pasa como parámetro.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            const std::string &cond= convert_to_string(InterpreteRPN::Pila().Pop());
            if(falso(cond))
              tmp_gp_dbl= 1.0; //Verdadero.
            else
              tmp_gp_dbl= 0.0; //Falso.
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetProp",cod);
          }
      }
    else if(cod == "not") //Devuelve verdadero si el argumento es falso.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            const bool &cond=  convert_to_bool(InterpreteRPN::Pila().Pop());
            if(!cond)
              tmp_gp_dbl= 1.0; //Verdadero.
            else
              tmp_gp_dbl= 0.0; //Falso.
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetProp",cod);
          }
      }
    else if(cod == "or")
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const bool a= convert_to_bool(InterpreteRPN::Pila().Pop());
            const bool b= convert_to_bool(InterpreteRPN::Pila().Pop());
            if(a||b)
              tmp_gp_dbl= 1.0; //Verdadero.
            else
              tmp_gp_dbl= 0.0; //Falso.
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"GetProp",cod);
          }
      }
    else if(cod == "and")
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const bool a= convert_to_bool(InterpreteRPN::Pila().Pop());
            const bool b= convert_to_bool(InterpreteRPN::Pila().Pop());
            if(a&&b)
              tmp_gp_dbl= 1.0; //Verdadero.
            else
              tmp_gp_dbl= 0.0; //Falso.
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"GetProp",cod);
          }
      }
    return retval;
  }


//! @brief Funciones básicas para imagenes.
any_const_ptr EntProp::BasicImageFunc(const std::string &cod) const
  {
    if(verborrea>4)
      std::clog << "EntProp::BasicImageFunc (" << nombre_clase() << "::GetPropLocal) Buscando propiedad: " << cod << std::endl;
    any_const_ptr retval;
    if(cod == "mseImagenes") //Devuelve el error medio cuadrático de las diferencias.
      {
	std::cerr << "Deprecated; use Python." << std::endl;
      }
    if(cod == "psnrImagenes") //Devuelve el psnr de las diferencias.
      {
	std::cerr << "Deprecated; use Python." << std::endl;
      }
    else if(cod == "compara_imagenes") //Devuelve 0.0 si las imagenes son exactamente iguales.
      {
	std::cerr << "Deprecated; use Python." << std::endl;
      }
    return retval;
  }

//! @brief Funciones geométricas básicas.
any_const_ptr EntProp::BasicGeomFunc(const std::string &cod) const
  {
    if(verborrea>4)
      std::clog << "EntProp::BasicGeomFunc (" << nombre_clase() << "::BasicGeomFunc) Buscando propiedad: " << cod << std::endl;
    any_const_ptr retval;
    if(cod == "distancia") //Devuelve la distancia entre dos objetos.
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const boost::any a= InterpreteRPN::Pila().Pop();
            const boost::any b= InterpreteRPN::Pila().Pop();
            const boost::any dist= distancia_boost_any(a,b);
            retval= set_temp_var(dist,cod);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"EntProp::BasicGeomFunc",cod);
          }
      }
    else if(cod == "angulo") //Devuelve el ángulo entre dos objetos.
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const boost::any b= InterpreteRPN::Pila().Pop();
            const boost::any a= InterpreteRPN::Pila().Pop();
            const boost::any ang= angulo_boost_any(a,b);
            retval= set_temp_var(ang,cod);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"EntProp::BasicGeomFunc",cod);
          }
      }
    else if(cod == "interseccion") //Devuelve la interseccion de dos objetos.
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const boost::any a= InterpreteRPN::Pila().Pop();
            const boost::any b= InterpreteRPN::Pila().Pop();
            const boost::any intersec= interseccion_boost_any(a,b);
            retval= set_temp_var(intersec,cod);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"EntProp::BasicGeomFunc",cod);
          }
      }
    else if(cod == "punto_interseccion") //Devuelve el punto de interseccion de dos objetos.
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const boost::any a= InterpreteRPN::Pila().Pop();
            const boost::any b= InterpreteRPN::Pila().Pop();
            const boost::any intersec= punto_interseccion_boost_any(a,b);
            retval= set_temp_var(intersec,cod);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"EntProp::BasicGeomFunc",cod);
          }
      }
    return retval;
  }

//! \brief Devuelve la propiedad LOCAL del objeto cuyo código (de la propiedad) se pasa
//! como parámetro. Se entiende por propiedad LOCAL la que está definida en el propio objeto
//! y, por tanto, no requiere consultar a ningún otro (su propietario,pila de llamadas,...).
any_const_ptr EntProp::GetPropLocal(const std::string &cod) const
  {
    if(verborrea>4)
      std::clog << "EntProp::GetPropLocal (" << nombre_clase() << "::GetPropLocal) Buscando propiedad: " << cod << std::endl;
    any_const_ptr retval;
    any_const_ptr tmp= BasicMathFunc(cod);
    if(!tmp.empty())
      retval= tmp;
    else if(!(tmp= BasicStrFunc(cod)).empty())
      retval= tmp;
    else if(!(tmp= BasicImageFunc(cod)).empty())
      retval= tmp;
    else if(!(tmp= BasicBoolFunc(cod)).empty())
      retval= tmp;
    else if(!(tmp= BasicGeomFunc(cod)).empty())
      retval= tmp;
    else if(cod=="tipo")
      {
        tmp_gp_str= nombre_clase();
        retval= any_const_ptr(tmp_gp_str);
      }
    else if(cod == "tipoDe") //Devuelve el tipo de la propiedad.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            const std::string arg= convert_to_string(InterpreteRPN::Pila().Pop());
            tmp_gp_str= const_ptr_tipo_operando(Recall(arg));
            retval= any_const_ptr(tmp_gp_str); 
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetPropLocal",cod);
          }
      }
    else if(cod=="nverborrea")
      retval= any_const_ptr(verborrea);
    else if(cod=="address")
      {
        tmp_gp_szt= size_t(this);
        retval= any_const_ptr(tmp_gp_szt);
      }
    else if(cod=="num_props")
      {
        tmp_gp_szt= params.Props().size();
        retval= any_const_ptr(tmp_gp_szt);
      }
    else if(cod=="num_vars")
      {
        tmp_gp_szt= params.Vars().size();
        retval= any_const_ptr(tmp_gp_szt);
      }
    else if(cod=="has_prop")
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            const std::string arg= convert_to_string(InterpreteRPN::Pila().Pop());
            tmp_gp_bool= params.Props().ExisteUserParam(arg);
            retval= any_const_ptr(tmp_gp_bool);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetPropLocal",cod);
          }
      }
    else if(cod=="existe_var")
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            const std::string arg= convert_to_string(InterpreteRPN::Pila().Pop());
            tmp_gp_bool= params.Vars().ExisteUserParam(arg);
            retval= any_const_ptr(tmp_gp_bool);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetPropLocal",cod);
          }
      }
    else if(cod=="lista_nmb_props")
      {
	tmp_gp_str= params.Props().ListaNmbParams();
        retval= any_const_ptr(tmp_gp_str);
      }
    else if(cod=="lista_nmb_vars")
      {
	tmp_gp_str= params.Vars().ListaNmbParams();
        retval= any_const_ptr(tmp_gp_str);
      }
    else if(cod == "deref") //Des-referenciar una propiedad.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            static boost::any tmp;
            tmp= InterpreteRPN::Pila().Pop();
            if(boost_any_is_string(tmp))
              {
                const std::string arg= boost_any_to_string(tmp);
                retval= Recall(arg);
              }
            else
              retval= any_const_ptr(&tmp);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetPropLocal",cod);
          }
      }
    else if(cod == "eval") //Evalua una expresión.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            const std::string arg= convert_to_string(InterpreteRPN::Pila().Pop());
            static boost::any sretval;
            if(interpretaUno(arg))
              sretval= InterpreteRPN::Pila().Pop();
            else
	      std::cerr << "No se pudo evaluar la expresión: '"
                        << arg << "'." << std::endl;
            retval= any_const_ptr(sretval);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetPropLocal",cod);
          }
      }
    else if(cod == "empty") //Devuelve verdadero si la propiedad está vacía.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            const std::string arg= convert_to_string(InterpreteRPN::Pila().Pop());
            any_const_ptr tmp= Recall(arg);
            tmp_gp_bool= tmp.empty();
            retval= any_const_ptr(tmp_gp_bool); 
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetPropLocal",cod);
          }

      }
    else if(cod == "not_empty") //Devuelve verdadero si la propiedad NO está vacía.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            const std::string arg= convert_to_string(InterpreteRPN::Pila().Pop());
            any_const_ptr tmp= Recall(arg);
            tmp_gp_bool= !tmp.empty();
            retval= any_const_ptr(tmp_gp_bool); 
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetPropLocal",cod);
          }
      }
    else if(cod=="getMemoryUsed")
      {
	tmp_gp_szt= getMemoryUsed();
        retval= any_const_ptr(tmp_gp_szt);
      }
    else if(cod == "existeArchivo") //Devuelve verdadero si el archivo existe.
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            const std::string fname= convert_to_string(InterpreteRPN::Pila().Pop());
            if(verborrea>4)
              std::clog << "Comprobando la existencia del archivo: '" << fname << "'" << std::endl;
            if(existe_archivo(fname))
              tmp_gp_dbl= 1.0; //Verdadero.
            else
              tmp_gp_dbl= 0.0; //Falso.
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetPropLocal",cod);
          }
      }
    else if(cod == "fcmp") //Compara dos archivos.
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const std::string fname1= convert_to_string(InterpreteRPN::Pila().Pop());
            const std::string fname2= convert_to_string(InterpreteRPN::Pila().Pop());
            if(verborrea>4)
              std::clog << "Comparando archivos: '" << fname1
                        << "' y '" << fname2 << "'" << std::endl;
            if(archivos_iguales(fname1,fname2))
              tmp_gp_dbl= 1.0; //Verdadero.
            else
              tmp_gp_dbl= 0.0; //Falso.
            retval= any_const_ptr(tmp_gp_dbl);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"GetPropLocal",cod);
          }
      }
    else if(cod == "size_literales")
      {
        tmp_gp_szt= ExprAlgebra::Lex().getTablaLiterales().size();
        retval= any_const_ptr(tmp_gp_szt);
      }
    else if(cod == "size")
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_szt= size_boost_any(InterpreteRPN::Pila().Pop());
            retval= any_const_ptr(tmp_gp_szt);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetPropLocal",cod);
          }
      }
    else if(cod == "nFilas")
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_szt= nfilas_boost_any(InterpreteRPN::Pila().Pop());
            retval= any_const_ptr(tmp_gp_szt);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetPropLocal",cod);
          }
      }
    else if(cod == "nCols")
      {
        if(InterpreteRPN::Pila().size()>0)
          {
            tmp_gp_szt= ncols_boost_any(InterpreteRPN::Pila().Pop());
            retval= any_const_ptr(tmp_gp_szt);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetPropLocal",cod);
          }
      }
    else if(cod == "ifte")
      {
        if(InterpreteRPN::Pila().size()>2)
          {
            const boost::any c= InterpreteRPN::Pila().Pop();
            const boost::any b= InterpreteRPN::Pila().Pop();
            const boost::any a= InterpreteRPN::Pila().Pop();
            const boost::any tmp= ifte_boost_any(a,b,c);
            retval= set_temp_var(tmp,cod);
          }
        else
          {
            err_num_argumentos(std::cerr,3,"GetPropLocal",cod);
          }
      }
    return retval;
  }

//! \brief Intenta devolver el valor del párametro cuyo código es cod.
any_const_ptr EntProp::Recall(const std::string &cod) const
  {
    if(verborrea>4)
      std::clog << "EntProp::Recall (" << nombre_clase() << "::Recall) Buscando propiedad: " << cod << std::endl;
    static std::string last_cod= "";
    any_const_ptr tmp;
    if(!cod.empty())
      {
        if(sub)
          tmp= sub->GetValorArg(cod); //Parámetros con los que se ha llamado a la subrutina o función.
        if(tmp.empty())
          tmp= GetProp(cod);
        if(tmp.empty())
          {
            if(cod != last_cod) //Propiedad nueva.
              {
                clear_visitados();
                last_cod= cod;
              }
            visita(this); //Si fracasó la búsqueda en ESTE no lo intentes más.
            if(verborrea>5) std::clog << "  EntProp::Recall; buscando propiedad: " << cod << " en pila de llamadas." << std::endl;
            tmp= GetPropPilaLlamadas(cod);
            if(verborrea>5)
              {
                if(tmp.empty())
                  std::clog << "  no se encontró la propiedad: " << cod << " en la pila de llamadas." << std::endl;
                else
                  std::clog << "  se encontró la propiedad: " << cod << " en la pila de llamadas." << std::endl;
              }
            if(tmp.empty() && owner && !visitado(owner))
              {
                if(verborrea>5) std::clog << "  EntProp::Recall; buscando propiedad: " << cod << " en objeto propietario." << std::endl;
                tmp= owner->GetProp(cod);
                if(tmp.empty()) visita(owner); //Si fracasó la búsqueda en el propietario no lo intentes más.
                if(verborrea>5)
                  {
                    if(tmp.empty())
                      std::clog << "  no se encontró la propiedad: " << cod << " en el objeto propietario." << std::endl;
                    else
                      std::clog << "  se encontró la propiedad: " << cod << " en el objeto propietario." << std::endl;
                  }
              }
            else if(tmp.empty() && sub && !visitado(sub))
              {
                if(verborrea>5) std::clog << "  EntProp::Recall; buscando propiedad: " << cod << " en objeto sub." << std::endl;
                tmp= sub->GetProp(cod);
                if(tmp.empty()) visita(sub); //Si fracasó la búsqueda en sub no lo intentes más.
                if(verborrea>5)
                  {
                    if(tmp.empty())
                      std::clog << "  no se encontró la propiedad: " << cod << " en el objeto sub." << std::endl;
                    else
                      std::clog << "  se encontró la propiedad: " << cod << " en el objeto sub." << std::endl;
                  }
              }
            if(tmp.empty() && verborrea>4)
              std::clog << "EntProp::Recall (" << nombre_clase() << "::Recall) NO SE ENCONTRÓ la propiedad: " << cod << std::endl;
            clear_visitados();
            last_cod= "";
          }
      }
    return tmp;
  }

//! \brief Devuelve la propiedad del objeto cuyo código (de la propiedad) se pasa
//! como parámetro.
//!
//! Soporta los códigos:
//! tipo: Devuelve el nombre de la clase).
any_const_ptr EntProp::GetProp(const std::string &cod) const
  {
    if(verborrea>4)
      std::clog << "EntProp::GetProp (" << nombre_clase() << "::GetProp) Buscando propiedad: " << cod << std::endl;
    return GetPropLocal(cod);
  }

//! @brief Borra las propiedades de usuario del objeto.
void EntProp::clearProps(void)
  { params.clearProps(); }

//! @brief Desreferencia el comando que se le pasa como parámetro.
std::string EntProp::deref_cmd(const std::string &cmd) const
  {
    if(verborrea>3)
      std::clog << "EntProp::deref_cmd (" << nombre_clase() 
                << "::deref_cmd) intepretando comando: " << cmd << std::endl;
    std::string retval(cmd);
    if(has_char(cmd,'@'))
      retval= interpretaString(cmd);
    return retval;
  }

//! @brief Define una nueva expresión.
//!
//! @param nmb: Nombre de la variable.
//! @param expr: Expresión que se asigna a la variable.
void EntProp::nueva_expr(const std::string &nmb,const ExprAlgebra &expr)
  {
    const VarExpr *ve= ExprAlgebra::LexA().CalcDirExpr(nmb);
    if( (verborrea>5) && (ve!=NULL) )
       std::clog << "¡Ojo!, se redefine la expresión: " << nmb << std::endl;
    if(ve!=NULL) //Expresión existente.
      {
        if(expr.TieneVariable(*ve)) //Variable existente, expresión implícita.
          {
            const double d= expr.ToNum();
            ExprAlgebra::LexA().Asigna(nmb,d);
          }
        else //Varriable existente, expresión explícita.
          ExprAlgebra::LexA().AsignaExpr(nmb,expr);
      }
    else //Expresión nueva o variable existente.
      {
        Variable *var= ExprAlgebra::LexA().CalcDirVar(nmb);
        if(var) //Variable existente.
          {
            if(verborrea>5)
	      std::clog << "¡Ojo!; Se asigna a la variable: '" << nmb
                        << "', el valor numérico de: '" << expr
                        << "'\n";
            var->Asigna(expr.ToNum());
          }
        else //Expresión nueva.
          {
            ExprAlgebra::LexA().NuevaExpr(nmb);
            ExprAlgebra::LexA().AsignaExpr(nmb,expr);
          }
      }
  }

//! @brief Define una nueva expresión.
//!
//! @param nmb: Nombre de la expresión.
//! @param e: Valor de la expresión.
void EntProp::nueva_expr(const std::string &nmb,const std::string &e)
  {
    const ExprAlgebra expr= interpretaExpr(e);
    if(expr.ErrorTraduccion())
      std::cerr << "EntProp::nueva_expr; se produjo un error al interpretar la expresión: '"
                << e << "', se ignora la definición.";
    else
      nueva_expr(nmb,expr);
  }

void EntProp::nueva_var(const std::string &nmb,const double &d)
  {
    ExprAlgebra::LexA().NuevaVar(nmb);
    ExprAlgebra::LexA().Asigna(nmb,d);
  }

//! @brief Evalúa una expresión (devuelve verdadero si no hay errores).
bool EntProp::eval(const std::string &nmb_var)
  {
    bool retval= false;
    //Suponemos que es el nombre de una expresión.
    const VarExpr *ve= ExprAlgebra::LexA().CalcDirExpr(nmb_var);
    if(ve)
      {
        ExprAlgebra tmp= ve->GetExpr().Eval();
        nueva_expr(nmb_var,tmp);
        retval= true;
      }
    else //No es el nombre de una expresión, suponemos que es nombre de una variable.
      {
        const Variable *v= ExprAlgebra::LexA().CalcDirVar(nmb_var);
        if(v)
          retval= true;
        else //No es el nombre de una variable.
          std::cerr << "EntProp::eval: '" << nmb_var 
                    << "' no es el nombre de una expresión." << std::endl;
      }
    return retval;
  }


//! @brief Interpreta una cadena de caracteres y coloca los resultados en la pila.
bool EntProp::interpreta(const std::string &str,const int &numValEsperados) const
  {
    InterpreteRPN tmp(str);
    tmp.Interpreta(this,numValEsperados);
    return tmp.good();
  }

//! @brief Interpreta una cadena de caracteres y devuelve
//! verdadero si el resultado no es un objeto vacío.
bool EntProp::interpretaUno(const std::string &str) const
  {
    bool retval= false;
    if(!str.empty())
      {
        retval= interpreta(str,1);
        if(retval)
          {
            if(boost_any_is_empty(InterpreteRPN::Pila().top()))
              {
                std::cerr << "EntProp::interpretaUno (" << nombre_clase() 
                          << "::interpretaUno), la cadena: '" << str
                          << "' devuelve una propiedad vacía." << std::endl;
              }
            else
              retval= true;
          }
      }
    else
      std::cerr << "EntProp::interpretaUno, se recibió una cadena vacía." << std::endl;
    return retval;
  }


//! @brief Devuelve la cola de objetos boost::any que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
std::deque<boost::any> EntProp::crea_deque_boost_any(const std::string &str) const
  {
    const size_t sz1= InterpreteRPN::Pila().size();
    interpreta(str);
    const size_t sz2= InterpreteRPN::Pila().size();
    return Reverse(InterpreteRPN::Pila(),sz2-sz1);
  }

//! @brief Devuelve el vector de strings que resulta de interpretar la cadena de caracteres
//! que se pasa como parámetro.
std::vector<std::string> EntProp::crea_vector_string(const std::string &str) const
  {
    std::vector<std::string> retval;
    if(check_comillas(str))
      {
        const std::deque<boost::any> tmp= crea_deque_boost_any(str);
        const size_t sz= tmp.size();
        retval.resize(sz);
        for(size_t i= 0;i<sz;i++)
          retval[i]= convert_to_string(tmp[i]);
      }
    else
      std::cerr << "EntProp::crea_vector_string; error al interpretar la cadena: '"
                << str << "'\n"; 
    return retval;
  }

//! @brief Devuelve el vector de caracteres que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
std::vector<char> EntProp::crea_vector_char(const std::string &str) const
  {
    const std::deque<boost::any> tmp= crea_deque_boost_any(str);
    const size_t sz= tmp.size();
    std::vector<char> retval;
    if(sz>0)
      {
        retval.resize(sz);
        if(sz==1)
	  retval= convert_to_vector_char(tmp[0]);
        else
         {
           for(size_t i= 0;i<sz;i++)
             retval[i]= convert_to_char(tmp[i]);
         }
      }
    else
      {
        std::cerr << "EntProp::crea_vector_char; se creó un vector de dimensión cero." << std::endl;
      }
    return retval;
  }

//! @brief Devuelve el vector de doubles que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
std::vector<double> EntProp::crea_vector_double(const std::string &str) const
  {
    const std::deque<boost::any> tmp= crea_deque_boost_any(str);
    const size_t sz= tmp.size();
    std::vector<double> retval;
    if(sz>0)
      {
        retval.resize(sz);
        if(sz==1)
	  retval= convert_to_vector_double(tmp[0]);
        else
         {
           for(size_t i= 0;i<sz;i++)
             retval[i]= convert_to_double(tmp[i]);
         }
      }
    else
      {
        std::cerr << "EntProp::crea_vector_double; se creó un vector de dimensión cero." << std::endl;
      }
    return retval;
  }

//! @brief Devuelve el vector de enteros que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
std::vector<int> EntProp::crea_vector_int(const std::string &str) const
  {
    const std::deque<boost::any> tmp= crea_deque_boost_any(str);
    const size_t sz= tmp.size();
    std::vector<int> retval;
    if(sz>0)
      {
        retval.resize(sz);
        if(sz==1)
	  retval= convert_to_vector_int(tmp[0]);
        else
         {
           for(size_t i= 0;i<sz;i++)
             retval[i]= convert_to_int(tmp[i]);
         }
      }
    else
      {
        std::cerr << "EntProp::crea_vector_int; se creó un vector de dimensión cero." << std::endl;
      }
    return retval;
  }

//! @brief Devuelve el vector de enteros que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
std::vector<size_t> EntProp::crea_vector_size_t(const std::string &str) const
  {
    const std::deque<boost::any> tmp= crea_deque_boost_any(str);
    const size_t sz= tmp.size();
    std::vector<size_t> retval;
    if(sz>0)
      {
        retval.resize(sz);
        if(sz==1)
	  retval= convert_to_vector_size_t(tmp[0]);
        else
         {
           for(size_t i= 0;i<sz;i++)
             retval[i]= convert_to_size_t(tmp[i]);
         }
      }
    else
      {
        std::cerr << "EntProp::crea_vector_size_t; se creó un vector de dimensión cero." << std::endl;
      }
    return retval;
  }

//! @brief Devuelve el vector de expresiones que resulta de interpretar la cadena de caracteres que se pasa como parámetro.
std::vector<ExprAlgebra> EntProp::crea_vector_expr(const std::string &str) const
  {
    const std::deque<boost::any> tmp= crea_deque_boost_any(str);
    const size_t sz= tmp.size();
    std::vector<ExprAlgebra> retval;
    if(sz>0)
      {
        retval.resize(sz);
        if(sz==1)
	  retval= convert_to_vector_expr(tmp[0]);
        else
         {
           for(size_t i= 0;i<sz;i++)
             retval[i]= convert_to_ExprAlgebra(tmp[i]);
         }
      }
    else
      {
        std::cerr << "EntProp::crea_vector_expr; se creó un vector de dimensión cero." << std::endl;
      }
    return retval; 
  }

//! @brief Extrae (si puede) un objeto string de la pila.
std::string EntProp::popString(const std::string &cod) const
  {
    std::string retval;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_string(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) un objeto double de la pila.
double EntProp::popDouble(const std::string &cod) const
  {
    double retval= 0.0;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_double(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) un objeto int de la pila.
int EntProp::popInt(const std::string &cod) const
  {
    int retval= 0;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_int(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) un objeto bool de la pila.
bool EntProp::popBool(const std::string &cod) const
  {
    bool retval= false;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_bool(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) un objeto size_t de la pila.
size_t EntProp::popSize_t(const std::string &cod) const
  {
    size_t retval= 0;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_size_t(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) un objeto std::vector<double> de la pila.
std::vector<double> EntProp::popVectorDouble(const std::string &cod) const
  {
    std::vector<double> retval;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_vector_double(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) un objeto std::vector<int> de la pila.
std::vector<int> EntProp::popVectorInt(const std::string &cod) const
  {
    std::vector<int> retval;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_vector_int(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) un objeto std::vector<std::string> de la pila.
std::vector<std::string> EntProp::popVectorString(const std::string &cod) const
  {
    std::vector<std::string> retval;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_vector_string(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) un objeto m_double de la pila.
m_double EntProp::popMDouble(const std::string &cod) const
  {
    m_double retval;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_m_double(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) un objeto m_int de la pila.
m_int EntProp::popMInt(const std::string &cod) const
  {
    m_int retval;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_m_int(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) un objeto m_string de la pila.
m_string EntProp::popMString(const std::string &cod) const
  {
    m_string retval;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_m_string(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) un objeto Pos2d de la pila.
Pos2d EntProp::popPos2d(const std::string &cod) const
  {
    Pos2d retval;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_pos2d(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) un objeto Vector2d de la pila.
Vector2d EntProp::popVector2d(const std::string &cod) const
  {
    Vector2d retval;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_vector2d(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) un objeto Segmento2d de la pila.
Segmento2d EntProp::popSegmento2d(const std::string &cod) const
  {
    Segmento2d retval;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_segmento2d(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) un objeto Circulo2d de la pila.
Circulo2d EntProp::popCirculo2d(const std::string &cod) const
  {
    Circulo2d retval;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_circulo2d(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) un objeto Poligono2d de la pila.
Poligono2d EntProp::popPoligono2d(const std::string &cod) const
  {
    Poligono2d retval;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_poligono2d(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) una lista de Pos2d de la pila.
ListaPos2d EntProp::popListaPos2d(const std::string &cod) const
  {
    ListaPos2d retval;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_lista_pos2d(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) una Polilinea2d de la pila.
Polilinea2d EntProp::popPolilinea2d(const std::string &cod) const
  {
    Polilinea2d retval;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_polilinea2d(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) una lista de Polilineas3d de la pila.
ListaPos3d EntProp::popListaPos3d(const std::string &cod) const
  {
    ListaPos3d retval;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_lista_pos3d(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) un objeto Pos3d de la pila.
Pos3d EntProp::popPos3d(const std::string &cod) const
  {
    Pos3d retval;
    if(InterpreteRPN::Pila().size()>0)
      {
        const std::vector<double> coo= convert_to_vector_double(InterpreteRPN::Pila().Pop());
        if(coo.size()>2)
          { retval= Pos3d(coo[0],coo[1],coo[2]); }
        else
          std::cerr << "Error; " << cod 
                    << " se esperaba un vector de dimensión 3." << std::endl;
       }
     else
       err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) un objeto Vector3d de la pila.
Vector3d EntProp::popVector3d(const std::string &cod) const
  {
    Vector3d retval;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_vector3d(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) un objeto Segmento3d de la pila.
Segmento3d EntProp::popSegmento3d(const std::string &cod) const
  {
    Segmento3d retval;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_segmento3d(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) un objeto VDesliz2d de la pila.
VDesliz2d EntProp::popVDesliz2d(const std::string &cod) const
  {
    VDesliz2d retval;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_vdesliz2d(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) un objeto VDesliz3d de la pila.
VDesliz3d EntProp::popVDesliz3d(const std::string &cod) const
  {
    VDesliz3d retval;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_vdesliz3d(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) un objeto VFijo2d de la pila.
VFijo2d EntProp::popVFijo2d(const std::string &cod) const
  {
    VFijo2d retval;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_vfijo2d(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) un objeto VFijo3d de la pila.
VFijo3d EntProp::popVFijo3d(const std::string &cod) const
  {
    VFijo3d retval;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_vfijo3d(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) un objeto SVD3d de la pila.
SVD3d EntProp::popSVD3d(const std::string &cod) const
  {
    SVD3d retval;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_svd3d(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) un objeto Recta2d de la pila.
Recta2d EntProp::popRecta2d(const std::string &cod) const
  {
    Recta2d retval;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_recta2d(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) un objeto Recta3d de la pila.
Recta3d EntProp::popRecta3d(const std::string &cod) const
  {
    Recta3d retval;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_recta3d(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) un objeto Plano3d de la pila.
Plano3d EntProp::popPlano3d(const std::string &cod) const
  {
    Plano3d retval;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_plano3d(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) un objeto SemiEspacio3d de la pila.
SemiEspacio3d EntProp::popSemiEspacio3d(const std::string &cod) const
  {
    SemiEspacio3d retval;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_se3d(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Extrae (si puede) un objeto Ref2d3d de la pila.
Ref2d3d EntProp::popRef2d3d(const std::string &cod) const
  {
    Ref2d3d retval;
    if(InterpreteRPN::Pila().size()>0)
      retval= convert_to_ref2d3d(InterpreteRPN::Pila().Pop());
    else
      err_num_argumentos(std::cerr,1,"GetProp",cod);
    return retval;
  }

//! @brief Imprime la cadena que se pasa como parámetro.
void EntProp::print(std::ostream *out_file,const std::string &campos) const
  {
    const std::deque<boost::any> tmp= crea_deque_boost_any(campos);
    for(std::deque<boost::any>::const_iterator i= tmp.begin();i!=tmp.end();i++)
      boost_any_print(*out_file,*i);
  }


