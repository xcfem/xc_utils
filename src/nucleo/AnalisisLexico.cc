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
// AnalisisLexico.cc

#include "AnalisisLexico.h"
#include "TokenList.h"
#include "xc_basic/src/texto/cadena_carac.h"
#include <cctype>


//! @brief Constructor.
AnalisisLexico::AnalisisLexico(const std::string &in)
  : input(in), buffer(in), nextChar(' '), charClass(Token::ERROR), lexeme("")
  { getChar(); }

//! @brief Asigna una nueva entrada.
void AnalisisLexico::setNewInput(const std::string &in) 
  {
    input=in;
    buffer= in;
    getChar();
  }

void AnalisisLexico::getChar(void)
  {
    if(buffer.size()>0)
      {
        nextChar= buffer[0];
        buffer.erase(0,1);
      }
    else nextChar = ';';
    charClass= Token::tipoChar(nextChar);
  }

//! @brief Añade el siguiente carácter a lexema.
void AnalisisLexico::addChar()
  { lexeme+=nextChar; }

//! @brief Lee un número entero o de coma flotante.
int AnalisisLexico::leeNumero(void)
  {
    int retval= Token::ERROR;
    bool leidoSignoExponente= false;
    bool leidoExponente= false;
    bool leidoPuntoDecimal= false;
    while(charClass == Token::DIGIT || nextChar == 'E' || nextChar == 'e' || nextChar == '.' || nextChar == '+' || nextChar == '-') //Forma número.
      {
        if((nextChar == '+' || nextChar == '-') && !leidoExponente) break; //Signo + sin haber leído E ó e;
        if( ((nextChar == '.') && leidoPuntoDecimal) || ((nextChar == '+' || nextChar == '-') && leidoSignoExponente) || ((nextChar == 'E' || nextChar == 'e') && leidoExponente) ) break;
        addChar();
        leidoSignoExponente= (nextChar == '+' || nextChar == '-');
        leidoExponente= (nextChar == 'E' || nextChar == 'e');
        leidoPuntoDecimal= (nextChar == '.');
        getChar();
      }
    if(isInteger(lexeme))
      retval= Token::INT_LIT;
    else if(isNumber(lexeme))
      retval= Token::DBL_LIT;
    return retval;
  }

//! @brief Lee un identificador.
int AnalisisLexico::leeIdentificador(void)
  {
    while(charClass == Token::LETRA || charClass == Token::DIGIT || charClass == Token::POINT) //Forma identificador.
      {
        addChar();
        getChar();
      }
    return Token::IDENT;
  }

//! @brief Lee una expresión literal por ejemplo: '4*x^2'.
int AnalisisLexico::leeExprLiteral(void)
  {
    while(charClass != Token::COMILLA) //Forma literal expresión.
      {
        addChar();
        getChar();
      }
    getChar(); //Ignora la comilla de cierre.
    return Token::EXPR_LIT;
  }

//! @brief Lee una cadena de caracteres literal por ejemplo "pepito".
int AnalisisLexico::leeStringLiteral(void)
  {
    bool leido_backslash= false;
    while(charClass != Token::COMILLAS) //Forma string literal.
      {
        if(nextChar == '\\') //Puede ser una secuencia de escape.
          {
            leido_backslash= true;
            getChar();
          }
        if(leido_backslash)
          {
            switch(nextChar)
              {
              case 'a':
                nextChar= '\a'; //Bell (beep)
                break;
              case 'b':
                nextChar= '\b'; //Backspace
                break;
              case 'f':
                nextChar= '\f'; //Formfeed
                break;
              case 'n':
                nextChar= '\n'; //Newline
                break;
              case 'r':
                nextChar= '\r'; //Return
                break;
              case 't':
                nextChar= '\t'; //Tab
                break;
              case '\\':
                nextChar= '\\'; //Backslash
                break;
              case '\'':
                nextChar= '\''; //Single quote
                break;
              case '\"':
                nextChar= '\"'; //Double quote
                break;
              default:
                const char tmp= nextChar; //No es secuencia de escape, añadimos el backslash.
                nextChar= '\\';
                addChar();
                nextChar= tmp;
                break;
              }
            leido_backslash= false;
          }
        addChar();
        getChar();
      }
    getChar(); //Ignora las comillas de cierre.
    return Token::STR_LIT;
  }


//! @brief Devuelve la clase de la siguiente señal (Identificador,número entero,...) en la cadena de entrada
//! y guarda su valor en lexema.
int AnalisisLexico::lex(void)
  {
    lexeme="";
    while(charClass == Token::SPACE) getChar();
    if(charClass == Token::ERROR) {addChar(); getChar(); return Token::ERROR;}
    if(charClass == Token::FIN) { return Token::FIN;}
    int retval= Token::ERROR;
    switch(charClass)
      {
      case Token::LETRA:
        addChar();
        getChar();
        retval= leeIdentificador();
        break;
      case Token::COMILLAS:
        getChar();
        retval= leeStringLiteral();
        break;
      case Token::COMILLA:
        getChar();
        retval= leeExprLiteral();
        break;
      case Token::DIGIT:
      case Token::POINT:
        addChar();
        getChar();
        retval= leeNumero();
        break;
      case Token::OP_SUMA: //Símbolo +
      case Token::OP_RESTA://Símbolo -
      case Token::OP_DIV:  //Símbolo /
      case Token::OP_POW: //Símbolo ^
      case Token::OP_MULT: //Símbolo *
      case Token::OP_MENOR: //Símbolo <
      case Token::OP_MAYOR: //Símbolo >
      case Token::OP_STO: //Símbolo =
      case Token::OP_AND: //Símbolo &
      case Token::OP_OR: //Símbolo |
      case Token::OP_NOT: //Símbolo !
        addChar();
        retval= charClass;
        getChar();
        break;
      case Token::PARENT_IZDO: //Paréntesis
      case Token::PARENT_DCHO:
      case Token::CORCHETE_IZDO: //Corchetes
      case Token::CORCHETE_DCHO:
        addChar();
        retval= charClass;
        getChar();
        break;
      case Token::COMA:
        addChar();
        retval= charClass;
        getChar();
        break;
      default:
	std::cerr << "AnalisisLexico::lex; no se supo interpretar el carácter: " << nextChar << " de tipo: " << Token::convertToken(charClass) << std::endl;
        getChar();
        break; 
      }
    return retval;
  }

TokenList AnalisisLexico::Analiza(void)
  {
    int token=Token::SPACE;
    TokenList retval;
    while(token!=Token::FIN)
      {
        token = lex();
        const std::string &lexema= Lexema();
        Token tmp(lexema,token);
        if((tmp.Tipo()== Token::IDENT) & has_char(lexema,'.')) //Protegemos las llamadas a miembro.
          retval.push_back(Token(Lexema(),Token::IDENT_WITH_MEMBER));
        else
          retval.push_back(tmp);
      }
    TokenList retval2= retval;
    retval.erase(retval.begin(),retval.end());
    for(TokenList::iterator i= retval2.begin();i!=retval2.end();i++)
      {
        if((*i).Tipo()== Token::IDENT_WITH_MEMBER)
	  {
            retval.push_back(Token("(",Token::PARENT_IZDO)); //Abre paréntesis.
            retval.push_back(Token((*i).Lexema(),Token::IDENT));
            TokenList::iterator j= i;
            j++;
            if(j!=retval2.end())
              {
                if((*j).Tipo()==Token::PARENT_IZDO)
                  {
                    size_t cuenta_parent(1);
                    retval.push_back(*j); //Paréntesis argumentos.
                    while(cuenta_parent && (j!=retval2.end()))
                      {
                        j++;
                        const int c= (*j).Tipo();
                        if(c == Token::PARENT_IZDO) cuenta_parent++;
                        if(c == Token::PARENT_DCHO) cuenta_parent--;
                        retval.push_back(*j);
                      }
                    i= j;
                  }
                if((*j).Tipo()==Token::CORCHETE_IZDO)
                  {
                    size_t cuenta_parent(1);
                    retval.push_back(*j); //Paréntesis argumentos.
                    while(cuenta_parent && (j!=retval2.end()))
                      {
                        j++;
                        const int c= (*j).Tipo();
                        if(c == Token::CORCHETE_IZDO) cuenta_parent++;
                        if(c == Token::CORCHETE_DCHO) cuenta_parent--;
                        retval.push_back(*j);
                      }
                    i= j;
                  }
              }
            retval.push_back(Token(")",Token::PARENT_DCHO)); //Cierra paréntesis.
          }
        else
          retval.push_back(*i);
      }
    if(retval.TieneErroresLexicos())
      std::cerr << "AnalisisLexico::Analiza; errores léxicos en expresion: '"
                << input << "':\n"
                << retval.Errores();
    return retval;
  }
