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
//TokenList.cc

#include "TokenList.h"
#include "xc_basic/src/text/text_string.h"



//! Return verdadero si se han encontrado errores léxicos
bool TokenList::TieneErroresLexicos(void) const
  {
    for(TokenList::const_iterator i= begin();i!=end();i++)
      if((*i).Tipo() == Token::ERROR)
        return true;
    return false;
  }

//! Return verdadero si se han encontrado errores con los paréntesis.
bool TokenList::TieneErroresParentesis(void) const
  {
    int cuenta= 0;
    for(TokenList::const_iterator i= begin();i!=end();i++)
      if((*i).Tipo() == Token::PARENT_IZDO)
        cuenta++;
      else if((*i).Tipo() == Token::PARENT_DCHO)
        cuenta--;
    return (cuenta != 0);
  }

//! Return verdadero si se han encontrado errores con los corchetes.
bool TokenList::TieneErroresCorchetes(void) const
  {
    int cuenta= 0;
    for(TokenList::const_iterator i= begin();i!=end();i++)
      if((*i).Tipo() == Token::CORCHETE_IZDO)
        cuenta++;
      else if((*i).Tipo() == Token::CORCHETE_DCHO)
        cuenta--;
    return (cuenta != 0);
  }

//! @brief Detecta los casos en los que "-" no significa resta
//! sino cambio de signo.
//! Estos casos son:
//! -El signo menos es es primero de la lista.
//! -El valor anterior al signo menos en la la lista es una de estas dos cosas
//!       - un paréntesis izquierdo.
//!       - un corchete izquierdo.
//!       - un operador.
void TokenList::DetectaNeg(void)
  {
    int ultima_clase= Token::CL_ERROR; 
    for(TokenList::iterator i= begin();i!=end();i++)
      {
        Token &tmp= *i;
        if(tmp.Tipo() == Token::OP_RESTA)
          {
            if( (i==begin()) || 
                (ultima_clase == Token::CL_PARENT_IZDO) || 
                (ultima_clase == Token::CL_CORCHETE_IZDO) || 
                (ultima_clase == Token::CL_OPERADOR) || 
                (ultima_clase == Token::CL_COMA) )
              tmp.Tipo()= Token::OP_NEG;
          }
        ultima_clase= tmp.Clase();
      }
  }

//! @brief Detect the cases in which the identifier corresponds to a prefix
//! operator, that is to say, when the identifier precedes a left parenthesis.
void TokenList::DetectaOpPrefix(void)
  {
    for(TokenList::iterator i= begin();i!=end();i++)
      {
        Token &tmp= *i;
        if((tmp.Tipo() == Token::IDENT))
          {
            TokenList::iterator j= i; j++;
            if(j!=end())
              {
                if((*j).Clase() == Token::CL_PARENT_IZDO)
                  tmp.Tipo()= Token::OP_PREFIX;
              }
          }
      }
  }

//! @brief Detecta los casos en los que el "." corresponde al operador OP_RCL,
//! es decir cuando el "." va entre identificadores como en "@lista.size".
void TokenList::DetectaOpRcl(void)
  {
    const std::deque<Token> buffer(*this);
    clear(); //Borra toda la lista.
    for(std::deque<Token>::const_iterator i= buffer.begin();i!=buffer.end();i++)
      {
        const Token &tmp= *i;
        if((tmp.Tipo() == Token::IDENT))
          {
            const std::string &lexema= tmp.Lexema();
            if(has_char(lexema,'.'))
              {
		std::deque<std::string> campos= split_at_first(lexema,'.');
                push_back(Token(campos[0],Token::BASERCL));
                push_back(Token(".",Token::OP_RCL));
		push_back(Token("_@"+campos[1],tmp.Tipo())); //Underscore indicates that 
                                                             //it is a property from another object (see InterpreteRPN::OperaIdent).
              }
            else
              push_back(tmp);
          }
        else if(tmp.Tipo() == Token::OP_PREFIX)
          {
            const std::string &lexema= tmp.Lexema();
            if(has_char(lexema,'.'))
              {
		std::deque<std::string> campos= split_at_first(lexema,'.');
                push_back(Token(campos[0],Token::BASERCL));
                push_back(Token(".",Token::OP_RCL));
		push_back(Token("_@"+campos[1],tmp.Tipo())); //Underscore indicates that it is a property from another object (see InterpreteRPN::OperaIdent).
              }                                              
            else
              push_back(tmp);
          }
        else
          push_back(tmp);
      }
  }

//! @brief Detecta los casos en los que el "." corresponde al operador OP_RCL,
//! es decir cuando el "." va tras paréntesis o corchetes como en "@lista(4).size".
void TokenList::DetectaOpRcl2(void)
  {
    for(std::deque<Token>::iterator i= begin();i!=end();i++)
      {
        Token &tmp= *i;
        if( (tmp.Tipo() == Token::DBL_LIT))
          {
            const std::string &lexema= tmp.Lexema();
            if(lexema == ".")
              {
                tmp.Tipo()= Token::OP_RCL;
                TokenList::iterator j= i; j++;
                if(j!=end())
                  {
                    if(((*j).Tipo() == Token::IDENT)) //Va seguido de un identificador
                      (*j).Lexema()= "_@"+(*j).Lexema();//Underscore indicates that it is a property from another object (see InterpreteRPN::OperaIdent).
                    else
		      std::cerr << "TokenList::DetectaOpRcl2; se esperaba un identificador." << std::endl;
                  }
              }
          }
      }
  }

//! @brief Detect the cases when the values between brackets "[...]" correspond to indexes,
//! of an object that can manage them (list, matrix,...).
void TokenList::DetectaOpAt(void)
  {
    for(TokenList::iterator i= begin();i!=end();i++)
      {
        Token &tmp= *i;
        if((tmp.Tipo() == Token::IDENT))
          {
            TokenList::iterator j= i; j++;
            if(j!=end())
              {
                if((*j).Clase() == Token::CL_CORCHETE_IZDO) //Va seguido de una expresión entre corchetes
                  insert(j,Token("at",Token::OP_AT));
              }
          }
      }
  }

//! @brief Detecta los casos en los un símbolo corresponde al operador igualdad "==".
void TokenList::DetectaOpIgual(void)
  {
    for(TokenList::iterator i= begin();i!=end();i++)
      {
        Token &tmp= *i;
        if(tmp.Tipo() == Token::OP_STO)
          {
            TokenList::iterator j= i; j++;
            if(j!=end())
              {
                if((*j).Tipo() == Token::OP_STO)
                  {
                    tmp.Tipo()= Token::OP_IGUAL;
                    tmp.Lexema()= "==";
                    erase(j);
                  }
              }
          }
      }
  }

//! @brief Detecta los casos en los un símbolo corresponde al operador menor o igual "<=".
void TokenList::DetectaOpMenorOIgual(void)
  {
    for(TokenList::iterator i= begin();i!=end();i++)
      {
        Token &tmp= *i;
        if(tmp.Tipo() == Token::OP_MENOR)
          {
            TokenList::iterator j= i; j++;
            if(j!=end())
              {
                if((*j).Tipo() == Token::OP_STO)
                  {
                    tmp.Tipo()= Token::OP_MENORIGUAL;
                    tmp.Lexema()= "<=";
                    erase(j);
                  }
              }
          }
      }
  }

//! @brief Detecta los casos en los un símbolo corresponde al operador mayor o igual ">=".
void TokenList::DetectaOpMayorOIgual(void)
  {
    for(TokenList::iterator i= begin();i!=end();i++)
      {
        Token &tmp= *i;
        if(tmp.Tipo() == Token::OP_MAYOR)
          {
            TokenList::iterator j= i; j++;
            if(j!=end())
              {
                if((*j).Tipo() == Token::OP_STO)
                  {
                    tmp.Tipo()= Token::OP_MAYORIGUAL;
                    tmp.Lexema()= ">=";
                    erase(j);
                  }
              }
          }
      }
  }

//! @brief Detecta los casos en los un símbolo corresponde al operador distinto "!=".
void TokenList::DetectaOpDistinto(void)
  {
    for(TokenList::iterator i= begin();i!=end();i++)
      {
        Token &tmp= *i;
        if(tmp.Tipo() == Token::OP_NOT)
          {
            TokenList::iterator j= i; j++;
            if(j!=end())
              {
                if((*j).Tipo() == Token::OP_STO)
                  {
                    tmp.Tipo()= Token::OP_DISTINTO;
                    tmp.Lexema()= "!=";
                    erase(j);
                  }
              }
          }
      }
  }

//! @brief Invierte el orden del operador OP_RCL y su argumento.
void TokenList::InvierteOpRcl(void)
  { 
    for(TokenList::iterator i= begin();i!=end();i++)
      {
        Token &tmp= *i;
        if(tmp.Tipo() == Token::OP_RCL)
          {
            TokenList::iterator j= i; j++;
            if(j!=end())
              {
                if((*j).Tipo() == Token::BASERCL)
                  {
                    std::swap(*i,*j);
                    i++; //Avanza.
                  }
//                 else
// 		  std::cerr << "Error en TokenList::InvierteOpRcl t:" << (*j) << std::endl;
              }
          }
      }
  }

//! @brief Detecta símbolos ambiguos (operador neg, igualdad, prefix operators,...)
void TokenList::ProcesaSintaxis(void)
  {
    DetectaNeg();
    DetectaOpPrefix();
    DetectaOpIgual();
    DetectaOpMenorOIgual();
    DetectaOpMayorOIgual();
    DetectaOpDistinto();
    DetectaOpRcl();
    DetectaOpRcl2();
    DetectaOpAt();
  }

//! Return una lista con los signos que son erróneos.
TokenList TokenList::Errores(void) const
  {
    TokenList retval;
    for(TokenList::const_iterator i= begin();i!=end();i++)
      if((*i).Tipo() == Token::ERROR)
        retval.push_back(*i);
    return retval;
  }

std::ostream &operator<<(std::ostream &os,const TokenList &tl)
  {
    for(TokenList::const_iterator i= tl.begin();i!=tl.end();i++)
      os << *i << std::endl;
    return os;
  }

Token TokenStack::Pop(void)
  {
    Token retval= top();
    pop();
    return retval;
  }

