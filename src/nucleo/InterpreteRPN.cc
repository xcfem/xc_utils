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
//InterpreteRPN.cc

#include "InterpreteRPN.h"
#include "boost/any.hpp"
#include "boost/lexical_cast.hpp"
#include "xc_utils/src/base/utils_any.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/nucleo/aux_any.h"
#include "xc_utils/src/base/utils_any_const_ptr.h"
#include "EntProp.h"
#include <stack>
#include <boost/algorithm/string/trim.hpp>
#include "xc_basic/src/funciones/algebra/ExprAlgebra.h"
#include "xc_basic/src/funciones/algebra/LexAlgebra.h"
#include "MatrizAny.h"

InterpreteRPN::PilaParciales InterpreteRPN::pila_parciales; //Resultados parciales.

//! @brief Constructor.
InterpreteRPN::InterpreteRPN(const std::string &in)
  : error(false) 
  { AS.setNewInput(in); }


void InterpreteRPN::setNewInput(const std::string &in)
  { AS.setNewInput(in); }

void InterpreteRPN::OperaIdent(const Token &t,const EntProp *ptr_ent)
  {
    if(t.EsMiembro()) //Es una propiedad de otro objeto (ver OP_RCL en TokenList::DetectaOpRcl)
      pila_parciales.push(boost::trim_left_copy_if(t.Lexema(),boost::is_any_of("_")));
    else if(t.Lexema()[0] == '@') //Suponemos que es el nombre de una propiedad.
      {
//         if(EntProp::GetNivelVerborrea()>6)
//           std::clog << "  InterpreteRPN::OperaIdent; buscando propiedad: " << t.Lexema() << std::endl;
        const std::string nmb_prop= boost::trim_copy_if(t.Lexema(),boost::is_any_of("@"));
        const any_const_ptr ptr= ptr_ent->Recall(nmb_prop);
        if(!const_ptr_is_empty(ptr)) //Tiene chicha.
          pila_parciales.push(convert_to_boost_any(ptr));
        else
          pila_parciales.push(boost::any()); //Colocamos un objeto vacío. XXXXX
      }
    else 
      {
//         if(EntProp::GetNivelVerborrea()>6)
//           std::clog << "  InterpreteRPN::OperaIdent; buscando expresión: " << t.Lexema() << std::endl;
        const VarExpr *ve= ExprAlgebra::LexA().CalcDirExpr(t.Lexema());
        if(ve) //Es el nombre de una expresión.
          pila_parciales.push(ve->GetExpr());
        else
          {
            const Variable *v= ExprAlgebra::LexA().CalcDirVar(t.Lexema());
            if(v) //Es el nombre de una variable.
              pila_parciales.push(v->GetValor());
            else //Suponemos que es una cadena de caracteres literal.
              {
                //if(!t.Lexema().empty()) pila_parciales.push(t.Lexema());
                std::cerr << "InterpreteRPN::OperaIdent; No se sabe interpretar el identificador: '" << t.Lexema() << "'" << std::endl;
                error= true;
              }
          }
      }      
  }

//! @brief Comprueba que hay argumentos suficientes para el operador.
//! @param narg: Número de argumentos necesarios para el operador.
//! @param nmb_op: Nombre del operador.
bool InterpreteRPN::HayArgumentos(const size_t narg,const std::string &nmb_op)
  {
    if(pila_parciales.size()<narg)
      {
        std::cerr << "InterpreteRPN; error en operador: '" << nmb_op
                  << "'; se esperaba(n) " << narg << " argumento(s)." << std::endl;
        return false;
      }
    else
      return true;
  }


//! @brief Ejecuta la operación suma.
void InterpreteRPN::OperaSuma(const Token &t)
  {
    if(HayArgumentos(2,t.Lexema()))
      {
        const boost::any b= pila_parciales.Pop();
        const boost::any a= pila_parciales.Pop();
        const boost::any sum= suma_boost_any(a,b);
        pila_parciales.push(sum);
        if(boost_any_is_empty(sum))
          error= true;
      }
    else
      error= true;
  }

//! @brief Ejecuta la operación resta.
void InterpreteRPN::OperaResta(const Token &t)
  {
    if(HayArgumentos(2,t.Lexema()))
      {
        const boost::any b= pila_parciales.Pop();
        const boost::any a= pila_parciales.Pop();
        const boost::any resta= resta_boost_any(a,b);
        pila_parciales.push(resta);
        if(boost_any_is_empty(resta))
          error= true;
      }
    else
      error= true;
  }

//! @brief Ejecuta la operación multiplicación.
void InterpreteRPN::OperaMult(const Token &t)
  {
    if(HayArgumentos(2,t.Lexema()))
      {
        const boost::any b= pila_parciales.Pop();
        const boost::any a= pila_parciales.Pop();
        const boost::any prod= mult_boost_any(a,b);
        pila_parciales.push(prod);
        if(boost_any_is_empty(prod))
          error= true;
      }
    else
      error= true;
  }

//! @brief Ejecuta la operación división.
void InterpreteRPN::OperaDiv(const Token &t)
  {
    if(HayArgumentos(2,t.Lexema()))
      {
        const boost::any b= pila_parciales.Pop();
        const boost::any a= pila_parciales.Pop();
        const boost::any coc= div_boost_any(a,b);
        pila_parciales.push(coc);
        if(boost_any_is_empty(coc))
          error= true;
      }
    else
      error= true;
  }

//! @brief Ejecuta la operación división.
void InterpreteRPN::OperaPow(const Token &t)
  {
    if(HayArgumentos(2,t.Lexema()))
      {
        const boost::any b= pila_parciales.Pop();
        const boost::any a= pila_parciales.Pop();
        const boost::any pow= pow_boost_any(a,b);
        pila_parciales.push(pow);
        if(boost_any_is_empty(pow))
          error= true;
      }
    else
      error= true;
  }

//! @brief Ejecuta el cambio de signo.
void InterpreteRPN::OperaNeg(const Token &t)
  {
    if(HayArgumentos(1,t.Lexema()))
      {
        const boost::any a= pila_parciales.Pop();
        const boost::any neg= neg_boost_any(a);
        pila_parciales.push(neg);
        if(boost_any_is_empty(neg))
          error= true;
      }
    else
      error= true;
  }

//! @brief Ejecuta el operador menor.
void InterpreteRPN::OperaMenor(const Token &t)
  {
    if(HayArgumentos(2,t.Lexema()))
      {
        const boost::any b= pila_parciales.Pop();
        const boost::any a= pila_parciales.Pop();
        const boost::any menor= menor_boost_any(a,b);
        pila_parciales.push(menor);
        if(boost_any_is_empty(menor))
          error= true;      }
    else
      error= true;
  }

//! @brief Ejecuta el operador mayor.
void InterpreteRPN::OperaMayor(const Token &t)
  {
    if(HayArgumentos(2,t.Lexema()))
      {
        const boost::any b= pila_parciales.Pop();
        const boost::any a= pila_parciales.Pop();
        const boost::any mayor= mayor_boost_any(a,b);
        pila_parciales.push(mayor);
        if(boost_any_is_empty(mayor))
          error= true;      }
    else
      error= true;
  }

//! @brief Ejecuta el operador igual.
void InterpreteRPN::OperaIgual(const Token &t)
  {
    if(HayArgumentos(2,t.Lexema()))
      {
        const boost::any b= pila_parciales.Pop();
        const boost::any a= pila_parciales.Pop();
        const boost::any igual= igual_boost_any(a,b);
        pila_parciales.push(igual);
        if(boost_any_is_empty(igual))
          error= true;
      }
    else
      error= true;
  }

//! @brief Ejecuta el operador menor o igual.
void InterpreteRPN::OperaMenorOIgual(const Token &t)
  {
    if(HayArgumentos(2,t.Lexema()))
      {
        const boost::any b= pila_parciales.Pop();
        const boost::any a= pila_parciales.Pop();
        const boost::any menoroigual= menor_o_igual_boost_any(a,b);
        pila_parciales.push(menoroigual);
        if(boost_any_is_empty(menoroigual))
          error= true;
      }
    else
      error= true;
  }

//! @brief Ejecuta el operador mayor o igual.
void InterpreteRPN::OperaMayorOIgual(const Token &t)
  {
    if(HayArgumentos(2,t.Lexema()))
      {
        const boost::any b= pila_parciales.Pop();
        const boost::any a= pila_parciales.Pop();
        const boost::any mayoroigual= mayor_o_igual_boost_any(a,b);
        pila_parciales.push(mayoroigual);
        if(boost_any_is_empty(mayoroigual))
          error= true;
      }
    else
      error= true;
  }

//! @brief Ejecuta el operador distinto.
void InterpreteRPN::OperaDistinto(const Token &t)
  {
    if(HayArgumentos(2,t.Lexema()))
      {
        const boost::any b= pila_parciales.Pop();
        const boost::any a= pila_parciales.Pop();
        const boost::any distinto= distinto_boost_any(a,b);
        pila_parciales.push(distinto);
        if(boost_any_is_empty(distinto))
          error= true;
      }
  }

//! @brief Ejecuta el operador and.
void InterpreteRPN::OperaAnd(const Token &t)
  {
    if(HayArgumentos(2,t.Lexema()))
      {
        const boost::any b= pila_parciales.Pop();
        const boost::any a= pila_parciales.Pop();
        const boost::any y= and_boost_any(a,b);
        pila_parciales.push(y);
        if(boost_any_is_empty(y))
          error= true; 
      }
    else
      error= true;
  }

//! @brief Ejecuta el operador or.
void InterpreteRPN::OperaOr(const Token &t)
  {
    if(HayArgumentos(2,t.Lexema()))
      {
        const boost::any b= pila_parciales.Pop();
        const boost::any a= pila_parciales.Pop();
        const boost::any o= or_boost_any(a,b);
        pila_parciales.push(o);
        if(boost_any_is_empty(o))
          error= true;
      }
    else
      error= true;
  }

//! @brief Ejecuta el operador not.
void InterpreteRPN::OperaNot(const Token &t)
  {
    if(HayArgumentos(1,t.Lexema()))
      {
        const boost::any a= pila_parciales.Pop();
        const boost::any no= not_boost_any(a);
        pila_parciales.push(no);
        if(boost_any_is_empty(no))
          error= true;
      }
    else
      error= true;
  }


//! @brief Ejecuta el operador asigna.
void InterpreteRPN::OperaAsigna(const Token &t)
  {
    if(HayArgumentos(2,t.Lexema()))
      {
        const boost::any b= pila_parciales.Pop();
        const boost::any a= pila_parciales.Pop();
        std::cerr << "No se sabe interpretar el operador asignación";
        boost_any_print(std::cerr,a);
        std::cerr << "= ";
        boost_any_print(std::cerr,b);
        std::cerr << std::endl;
        error= true;
      }
    else
      error= true;
  }

//! @brief Ejecuta la operación recall.
void InterpreteRPN::OperaRcl(const Token &t)
  {
    if(HayArgumentos(2,t.Lexema()))
      {
        const boost::any a= pila_parciales.Pop();
        const boost::any b= pila_parciales.Pop();
        if(boost_any_is_string(a))
	  error= opera_rcl(b,a);
        else
          error= opera_rcl(a,b);
      }
    else
      error= true;
  }

//! @brief Ejecuta la operación at.
void InterpreteRPN::OperaAt(const Token &t)
  {
    if(HayArgumentos(2,t.Lexema()))
      {
        const boost::any b= pila_parciales.Pop();
        const boost::any a= pila_parciales.Pop();
        const boost::any at= at_boost_any(a,b);
        pila_parciales.push(at);
        if(boost_any_is_empty(at))
          error= true;
      }
    else
      error= true;
  }



//! @brief Crea un vector.
void InterpreteRPN::CreaVector(const Token &t)
  {
    if(HayArgumentos(1,t.Lexema()))
      {
        const boost::any sz= pila_parciales.Pop();
        if(boost_any_is_int(sz))
          {
            const size_t n= boost_any_to_int(sz);
            if(n>0)
              {
                if(HayArgumentos(n,t.Lexema()))
                  {
                    std::vector<boost::any> v(n);
                    for(std::vector<boost::any>::reverse_iterator i=v.rbegin();i!=v.rend();i++)
                      (*i)= pila_parciales.Pop();
                    if(boost_any_is_vector_any(v[0]))
                      pila_parciales.push(convert_from_vector(v));
                    else
                      pila_parciales.push(v);
                  }
              }
            else
              {
                std::cerr << "Error en operador: " << t.Lexema()
                          << "; se intentó crear un vector de dimensión 0" << std::endl;
                error= true;
              }
          }
        else
          {
            std::cerr << "Error en operador: " << t.Lexema()
                      << "; se esperaba un argumento de tipo int y se obtuvo uno de tipo"
                      << boost_any_tipo_operando(sz) << std::endl;
            error= true;
          }
      }
    else
      error= true;
  }

//! @brief Ejecuta la expresión.
void InterpreteRPN::Interpreta(const EntProp *ptr_ent,const int &numValEsperados)
  {
    input= AS.Analiza();
    const size_t tam_pila_antes= pila_parciales.size();
    if(!input.empty())
      {
        error= false;
        if(pila_parciales.size()>100)
          std::clog << "El tamaño de la pila (" << pila_parciales.size() << ") es muy grande." << std::endl;
        for(TokenList::const_iterator i= input.begin();i!=input.end();i++)
          {
            const Token &t= *i;
            switch(t.Tipo())
              {
              case Token::IDENT:
              case Token::BASERCL:
              case Token::OP_PREFIJO:
                OperaIdent(t,ptr_ent);
                break;
              case Token::INT_LIT:
                try
                  {
                    pila_parciales.push(boost::any(boost::lexical_cast<int>(t.Lexema())));
                  }
                catch(boost::bad_lexical_cast &)
                  {
		    std::cerr << "InterpreteRPN::Interpreta; error a interpretar el entero: "
                              << t.Lexema() << std::endl;
                  }
                break;
              case Token::DBL_LIT:
                try
                  {
                    pila_parciales.push(boost::any(boost::lexical_cast<double>(t.Lexema())));
                  }
                catch(boost::bad_lexical_cast &)
                  {
		    std::cerr << "InterpreteRPN::Interpreta; error a interpretar el double: "
                              << t.Lexema() << std::endl;
                  }
                break;
              case Token::EXPR_LIT:
                pila_parciales.push(boost::any(ExprAlgebra(t.Lexema())));
                break;
              case Token::STR_LIT:
                pila_parciales.push(boost::any(t.Lexema()));
                break;
              case Token::OP_SUMA:
                OperaSuma(t);
                break;
              case Token::OP_RESTA:
                OperaResta(t);
                break;
              case Token::OP_MULT:
                OperaMult(t);
                break;
              case Token::OP_DIV:
                OperaDiv(t);
                break;
              case Token::OP_POW:
                OperaPow(t);
                break;
              case Token::OP_NEG:
                OperaNeg(t);
                break;
              case Token::OP_MENOR:
                OperaMenor(t);
                break;
              case Token::OP_MAYOR:
                OperaMayor(t);
                break;
              case Token::OP_IGUAL:
                OperaIgual(t);
                break;
              case Token::OP_MENORIGUAL:
                OperaMenorOIgual(t);
                break;
              case Token::OP_MAYORIGUAL:
                OperaMayorOIgual(t);
                break;
              case Token::OP_DISTINTO:
                OperaDistinto(t);
                break;
              case Token::OP_AND:
                OperaAnd(t);
                break;
              case Token::OP_OR:
                OperaOr(t);
                break;
              case Token::OP_NOT:
                OperaNot(t);
                break;
              case Token::OP_RCL:
                OperaRcl(t);
                break;
              case Token::VECTOR:
                CreaVector(t);
                break;
              case Token::OP_AT:
                OperaAt(t);
                break;
              default:
                std::cerr << "InterpreteRPN::Interpreta; No se supo tratar el lexema: '" << t.Lexema() << "'\n";
                error= true;
                break;
              }
            if(error) break;
          }
      }
    input.clear();
    const size_t tam_pila_despues= pila_parciales.size();
    if(numValEsperados>0)
      {
        const size_t inc_tam_pila= tam_pila_despues-tam_pila_antes;
        if(inc_tam_pila!=size_t(numValEsperados))
          {
	    std::cerr << "La expresión: '" << AS.Input() << "' devolvió "
                      << inc_tam_pila << " valores, y se esperaba que devolviera "
                      << numValEsperados << ".\n";
            error= true;
          }
      }
    if(error)
      {
        std::cerr << "InterpreteRPN::Interpreta; se produjo un error al interpretar la expresión: '"
                  << AS.Input() << "'\n" << std::endl;
      }
  }

void InterpreteRPN::Interpreta(const EntProp *ptr,const std::string &str)
  {
    if(input.empty()) //No hay ninguna interpretación en curso.
      {
        setNewInput(str);
        Interpreta(ptr);
      }
    else //Interpretación anidada.
      {
        InterpreteRPN tmp(str);
        tmp.Interpreta(ptr);
      }
  }




