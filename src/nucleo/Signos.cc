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
//Signos.cc

#include "Signos.h"

Token::Token(const std::string &l,const int &t)
  : lexema(l), tipo(t) {}

int Token::Prioridad(void) const
  {
    switch(tipo)
      {
      case OP_MENOR:
      case OP_MAYOR:
      case OP_IGUAL:
      case OP_MENORIGUAL:
      case OP_MAYORIGUAL:
      case OP_DISTINTO:
        return 4;
      case OP_SUMA:
      case OP_RESTA:
        return 5;
      case OP_MULT:
      case OP_DIV:
        return 6;
      case BASERCL:
        return 7;
      case OP_RCL:
        return 8;
      case OP_NEG:
      case OP_NOT:
        return 9;
      default:
        return 10;
      }
  }

int Token::Clase(void) const
  {
    switch(tipo)
      {
      case IDENT:
      case INT_LIT:
      case DBL_LIT:
      case EXPR_LIT:
      case STR_LIT:
        return CL_OPERANDO;
      case OP_PREFIX:
      case OP_SUMA:
      case OP_RESTA:
      case OP_MULT:
      case OP_DIV:
      case OP_POW:
      case OP_MENOR:
      case OP_MAYOR:
      case OP_IGUAL:
      case OP_MENORIGUAL:
      case OP_MAYORIGUAL:
      case OP_DISTINTO:
      case OP_STO:
      case OP_NEG:
      case OP_AND:
      case OP_OR:
      case OP_NOT:
      case OP_RCL:
      case OP_AT:
      case BASERCL:
        return CL_OPERADOR;
      case PARENT_DCHO:
        return CL_PARENT_DCHO;
      case PARENT_IZDO:
        return CL_PARENT_IZDO;
      case CORCHETE_DCHO:
        return CL_CORCHETE_DCHO;
      case CORCHETE_IZDO:
        return CL_CORCHETE_IZDO;
      case COMA:
        return CL_COMA;
      case FIN:
        return CL_FIN;
      default:
        return CL_ERROR;
      }
  }

bool Token::EsMiembro(void) const
  { return (lexema[0] == '_'); }

int Token::tipoChar(const char &c)
  {
    int retval = Token::ERROR;

    if(isalpha(c) || (c== '@') || (c== '$') || (c== '_'))
      retval = Token::LETRA;

    if(isdigit(c))
      retval = Token::DIGIT;
    if(isblank(c)) retval= SPACE;
    if(c == '(') retval= PARENT_IZDO;
    if(c == ')') retval= PARENT_DCHO;
    if(c == '[') retval= CORCHETE_IZDO;
    if(c == ']') retval= CORCHETE_DCHO;
    if(c == '.') retval= POINT;
    if(c == ',') retval= COMA;
    if(c == ';') retval= FIN;
    if(c == '"') retval= COMILLAS;
    if(c == '\'') retval= COMILLA;
    if(c == '+') retval= OP_SUMA;
    if(c == '-') retval= OP_RESTA;
    if(c == '*') retval= OP_MULT;
    if(c == '/') retval= OP_DIV;
    if(c == '^') retval= OP_POW;
    if(c == '<') retval= OP_MENOR;
    if(c == '>') retval= OP_MAYOR;
    if(c == '=') retval= OP_STO;
    if(c == '&') retval= OP_AND;
    if(c == '|') retval= OP_OR;
    if(c == '!') retval= OP_NOT;
    return retval;
  }

const std::string &Token::convertToken(int t)
  {
    static const std::string str_UNKNOWN= "UNKNOWN";
    static const std::string str_POINT= "POINT";
    static const std::string str_COMA= "COMA";
    static const std::string str_PARENT_DCHO= "PARENT_DCHO";
    static const std::string str_PARENT_IZDO= "PARENT_IZDO";
    static const std::string str_CORCHETE_DCHO= "CORCHETE_DCHO";
    static const std::string str_CORCHETE_IZDO= "CORCHETE_IZDO";
    static const std::string str_SPACE= "SPACE";
    static const std::string str_LETRA= "LETRA";
    static const std::string str_DIGIT= "DIGIT";
    static const std::string str_IDENT= "IDENT";
    static const std::string str_IDENT_WITH_MEMBER= "IDENT_WITH_MEMBER";
    static const std::string str_BASERCL= "BASERCL";
    static const std::string str_INT_LIT= "INT_LIT";
    static const std::string str_DBL_LIT= "DBL_LIT";
    static const std::string str_EXPR_LIT= "EXPR_LIT";
    static const std::string str_STR_LIT= "STR_LIT";
    static const std::string str_ERROR= "ERROR";
    static const std::string str_FIN= "FIN";
    static const std::string str_OP_PREFIX= "OP_PREFIX";
    static const std::string str_OP_SUMA= "OP_SUMA";
    static const std::string str_OP_RESTA= "OP_RESTA";
    static const std::string str_OP_MULT= "OP_MULT";
    static const std::string str_OP_DIV= "OP_DIV";
    static const std::string str_OP_POW= "OP_POW";
    static const std::string str_OP_MENOR= "OP_MENOR";
    static const std::string str_OP_MAYOR= "OP_MAYOR";
    static const std::string str_OP_IGUAL= "OP_IGUAL";
    static const std::string str_OP_MENORIGUAL= "OP_MENORIGUAL";
    static const std::string str_OP_MAYORIGUAL= "OP_MAYORIGUAL";
    static const std::string str_OP_DISTINTO= "OP_DISTINTO";
    static const std::string str_OP_STO= "OP_STO";
    static const std::string str_OP_NEG= "OP_NEG";
    static const std::string str_OP_AND= "OP_AND";
    static const std::string str_OP_OR= "OP_OR";
    static const std::string str_OP_NOT= "OP_NOT";
    static const std::string str_OP_RCL= "OP_RCL";
    static const std::string str_OP_AT= "OP_AT";
    static const std::string str_VECTOR= "VECTOR";
    const std::string *retval= &str_UNKNOWN;
    switch(t)
      {
      case POINT:
        retval= &str_POINT;
        break;
      case COMA:
        retval= &str_COMA;
        break;
      case PARENT_DCHO:
        retval= &str_PARENT_DCHO;
        break;
      case PARENT_IZDO:
        retval= &str_PARENT_IZDO;
        break;
      case CORCHETE_DCHO:
        retval= &str_CORCHETE_DCHO;
        break;
      case CORCHETE_IZDO:
        retval= &str_CORCHETE_IZDO;
        break;
      case SPACE:
        retval= &str_SPACE;
        break;
      case LETRA:
        retval= &str_LETRA;
        break;
      case DIGIT:
        retval= &str_DIGIT;
        break;      
      case IDENT:
        retval= &str_IDENT;
        break;
      case IDENT_WITH_MEMBER:
        retval= &str_IDENT_WITH_MEMBER;
        break;
      case BASERCL:
        retval= &str_BASERCL;
        break;
      case INT_LIT:
        retval= &str_INT_LIT;
        break;
      case DBL_LIT:
        retval= &str_DBL_LIT;
        break;
      case EXPR_LIT:
        retval= &str_EXPR_LIT;
        break;
      case STR_LIT:
        retval= &str_STR_LIT;
        break;
      case ERROR:
        retval= &str_ERROR;
        break;
      case FIN:
        retval= &str_FIN;
        break;
      case OP_PREFIX:
        retval= &str_OP_PREFIX;
        break;
      case OP_SUMA:
        retval= &str_OP_SUMA;
        break;
      case OP_RESTA:
        retval= &str_OP_RESTA;
        break;
      case OP_MULT:
        retval= &str_OP_MULT;
        break;
      case OP_DIV:
        retval= &str_OP_DIV;
        break;
      case OP_POW:
        retval= &str_OP_POW;
        break;
      case OP_MENOR:
        retval= &str_OP_MENOR;
        break;
      case OP_MAYOR:
        retval= &str_OP_MAYOR;
        break;
      case OP_IGUAL:
        retval= &str_OP_IGUAL;
        break;
      case OP_MENORIGUAL:
        retval= &str_OP_MENORIGUAL;
        break;
      case OP_MAYORIGUAL:
        retval= &str_OP_MAYORIGUAL;
        break;
      case OP_DISTINTO:
        retval= &str_OP_DISTINTO;
        break;
      case OP_STO:
        retval= &str_OP_STO;
        break;
      case OP_NEG:
        retval= &str_OP_NEG;
        break;
      case OP_AND:
        retval= &str_OP_AND;
        break;
      case OP_OR:
        retval= &str_OP_OR;
        break;
      case OP_NOT:
        retval= &str_OP_NOT;
        break;
      case OP_RCL:
        retval= &str_OP_RCL;
        break;
      case OP_AT:
        retval= &str_OP_AT;
        break;
      case VECTOR:
        retval= &str_VECTOR;
        break;
      default:
        retval= &str_UNKNOWN;
        break;
      }
    return *retval;
  }

std::ostream &operator<<(std::ostream &os,const Token &t)
  {
    os << "lexema: '" << t.Lexema() << "' tipo: '" << t.strTipo() << "'";
    return os;
  }

