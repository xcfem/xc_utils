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
//AnalisisSintactico.cpp

#include "AnalisisSintactico.h"
#include "Signos.h"
#include <iostream>
#include <string>
#include "boost/lexical_cast.hpp"
#include "xc_basic/src/texto/cadena_carac.h"

//! @brief Constructor.
AnalisisSintactico::AnalisisSintactico(const std::string &in)
  {
    check_parentesis(in);
    check_corchetes(in);
    LA.setNewInput(in);
  }

//! @brief Asigna una nueva entrada.
void AnalisisSintactico::setNewInput(const std::string &in)
  {
    check_parentesis(in);
    check_corchetes(in);
    LA.setNewInput(in);
  }

//! @brief Proceso al encontrar un paréntesis derecho.
void AnalisisSintactico::TrataParentDcho(TokenStack &pila,TokenList &lista,const size_t &numEntradas)
  {
    Token tmp;
    do
      {
        if(pila.empty()) break;
        tmp= pila.Pop();
        if(tmp.Tipo() == Token::PARENT_IZDO) break;
        lista.push_back(tmp);
      }
    while(tmp.Tipo() != Token::PARENT_IZDO);
    if(!pila.empty())
      {
        //Si hay un operador prefijo pendiente, lo volcamos.
        if(pila.top().Tipo() == Token::OP_PREFIJO)
          lista.push_back(pila.Pop());
      }
  }

//! @brief Proceso al encontrar un corchete derecho.
void AnalisisSintactico::TrataCorcheteDcho(TokenStack &pila,TokenList &lista,const size_t &numEntradas)
  {
    Token tmp;
    do
      {
        if(pila.empty()) break;
        tmp= pila.Pop();
        if(tmp.Tipo() == Token::CORCHETE_IZDO) break;
        if(tmp.Tipo() == Token::OP_AT) break;
        lista.push_back(tmp);
      }
    while(tmp.Tipo() != Token::CORCHETE_IZDO);
    lista.push_back(Token(boost::lexical_cast<std::string>(numEntradas),Token::INT_LIT)); //No. elementos.
    lista.push_back(Token("vector",Token::VECTOR)); //Forma vector.
    if(!pila.empty())
      {
        //Si hay un operador AT pendiente, lo volcamos.
        if(pila.top().Tipo() == Token::OP_AT)
          lista.push_back(pila.Pop());
      }
  }

//! @brief Proceso al encontrar una coma.
void AnalisisSintactico::TrataComa(TokenStack &pila,TokenList &lista)
  {
    Token tmp;
    do
      {
        if(pila.empty()) break;
        tmp= pila.Pop();
        if(tmp.Tipo() == Token::PARENT_IZDO)
          {
            pila.push(tmp); //No lo quitamos hasta que se encuentra el paréntesis derecho.
            break;
          }
        if(tmp.Tipo() == Token::CORCHETE_IZDO)
          {
            pila.push(tmp); //No lo quitamos hasta que se encuentra el paréntesis derecho.
            break;
          }
        lista.push_back(tmp);
      }
    while(tmp.Tipo() != Token::COMA);
  }

//! @brief Inserta los operandos antes del operador.
void AnalisisSintactico::TrataOperador(TokenStack &pila,const Token &t,TokenList &lista)
  {
    bool fin_derecha= false;
    do
      {
        if(pila.empty()) 
          fin_derecha= true;
        else if(pila.top().Tipo() == Token::PARENT_IZDO)
          fin_derecha= true;
        else if(pila.top().Tipo() == Token::CORCHETE_IZDO)
          fin_derecha= true;
        else if(pila.top().Tipo() == Token::COMA)
          fin_derecha= true;
        else if(pila.top().Tipo() == Token::OP_PREFIJO) //Esperar hasta encontrar el paréntesis derecho.
          fin_derecha= true;
        else if(pila.top().Tipo() == Token::OP_AT) //Esperar hasta encontrar el corchete derecho.
          fin_derecha= true;
        else if(pila.top().Prioridad() < t.Prioridad())
          fin_derecha= true;
        else
          {
            fin_derecha= false;
            lista.push_back(pila.Pop());
          }
      }
    while(!fin_derecha);
    pila.push(t);
  }

//! @brief Proceso al finalizar una expresión.
void AnalisisSintactico::TrataFinExpr(TokenStack &pila,TokenList &lista)
  {
    while(!pila.empty())
      { lista.push_back(pila.Pop()); }
  }

//! @brief Análisis de la expresion.
TokenList AnalisisSintactico::Analiza(void)
  {
    TokenList retval;
    input= LA.Analiza();
    if(input.empty()) return retval;
    input.ProcesaSintaxis();
    bool tiene_errores= (input.TieneErroresLexicos() || input.TieneErroresParentesis() || input.TieneErroresCorchetes());
    if(!tiene_errores)
      {
        TokenStack pila;
        TokenList::const_iterator i= input.begin();
        while(i!= input.end())
          {
            switch((*i).Clase())
              {
              case Token::CL_OPERANDO:
                pila.push(*i);
                break;
              case Token::CL_PARENT_IZDO:
                num_entradas.push(0);
                pila.push(*i);
                break;
              case Token::CL_PARENT_DCHO:
                num_entradas.top()++;
                TrataParentDcho(pila,retval,num_entradas.top());
                num_entradas.pop();
                break;
              case Token::CL_CORCHETE_IZDO:
                num_entradas.push(0);
                pila.push(*i);
                break;
              case Token::CL_CORCHETE_DCHO:
                num_entradas.top()++;
                TrataCorcheteDcho(pila,retval,num_entradas.top());
                num_entradas.pop();
                break;
              case Token::CL_OPERADOR:
                TrataOperador(pila,*i,retval);
                break;
              case Token::CL_COMA:
                if(!num_entradas.empty()) num_entradas.top()++;
                TrataComa(pila,retval);
                break;
              case Token::CL_FIN:
                break;
              case Token::CL_ERROR:
		std::cerr << "AnalisisSintactico::Analiza; error sintáctico en expresión: '"
                          << LA.Input() << "' no se supo interpretar el lexema: '"
                          << (*i).Lexema() << "', de tipo: " << (*i).strTipo() << "\n";
              }
            i++;
          }
        TrataFinExpr(pila,retval);
        retval.InvierteOpRcl();
      }
    return retval;
  }
