//----------------------------------------------------------------------------
//  xc_utils library; general purpose classes and functions.
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
//tab_cod.cc

#include "tab_cod.h"

//! Devuelve el codigo de las vocales con acento y la egne
//! en PC850 Multilingual a partir de su codigo en
//! iso8859/1 Latin 1.
char latin1TOpc850ML(int c)
  {
    switch(c)
      {
      case -31: //'a
        return char(160);
      case -23: //'e
        return char(130);
      case -19: //'i
        return char(161);
      case -13: //'o
        return char(162);
      case -6: //'u
        return char(163);
      case -63: //'A
        return char(181);
      case -55: //'E
        return char(144);
      case -51: //'I
        return char(214);
      case -45: //'O
        return char(224);
      case -38: //'U
        return char(233);
      case -15: //~n
        return char(164);
      case -47: //'a
        return char(165);
      default:
        return char(c);
      }
  }

std::string latin1TOpc850ML(const std::string &s)
  {
    std::string retval(s);
    for(size_t i= 0;i<s.length();i++)
      retval[i]= latin1TOpc850ML(s[i]);
    return retval;
  }

//! @brief Devuelve el código de las vocales con acento y la egne
//! en PC850 Multilingual a partir de su codigo en
//! iso8859/1 Latin 1.
unsigned char pc8TOlatin1(int c)
  {
    unsigned char retval= char(c);
    switch(c)
      {
      case -96: //'a
        retval= 225; //'á';
      case -126: //'e
        retval= 233; //'é';
      case -95: //'i
        retval= 237; //'í';
      case -94: //'o
        retval= 243; //'ó';
      case -93: //'u
        retval= 250; //'ú';
      case -75: //'A
        retval= 193; //'Á';
      case -112: //'E
        retval= 201; //'É';
      case -42: //'I
        retval= 205; //'Í';
      case -32: //'O
        retval= 211; //'Ó';
      case -23: //'U
        retval= 218; //'Ú';
      case -102: //Ü
        retval= 220; //'Ü';
      case -92: //~n ñ
        retval= 241; //'ñ';
      case -91: //~n ñ
        retval= 209; //'Ñ';
      default:
        retval= char(c);
      }
    return retval;
  }

std::string pc8TOlatin1(const std::string &s)
  {
    std::string retval(s);
    for(size_t i= 0;i<s.length();i++)
      retval[i]= pc8TOlatin1(s[i]);
    return retval;
  }

//! @brief Devuelve el codigo de las vocales con acento y la egne
//! en LaTex a partir de su c'odigo en ASCII iso8859/1 Latin 1.
std::string iso8859_1TOlatex(int c)
  {
    switch(c)
      {
      case -31: //'a
        return "\\'a";
      case -23: //'e
        return "\\'e";
      case -19: //'i
        return "\\'{\\i}";
      case -13: //'o
        return "\\'o";
      case -6: //'u
        return "\\'u";
      case -4: //"u
        {
          std::string str("\\");
          str+= char(34);
          str+= 'u';
          return str;
        }
      case -63: //'A
        return "\\'A";
      case -55: //'E
        return "\\'E";
      case -51: //'I
        return "\\'{\\I}";
      case -45: //'O
        return "\\'O";
      case -38: //'U
        return "\\'U";
      case -36: //"U;
        {
          std::string str("\\");
          str+= char(34);
          str+= 'U';
          return str;
        }
      case -15: //~n
        return "\\~n";
      case -47: //~N
        return "\\~N";
      case -65: //¿
        return "\\symbol{62}";
      case -70:
        {
          std::string str;
          str+= char(34);
          str+= 'o';
          return str;
        }
      case -86:
        {
          std::string str;
          str+= char(34);
          str+= 'a';
          return str;
        }
      default:
        return "";
      }
  }

std::string iso8859_1TO_utf8(const std::string &str)
  {
    std::string retval;
    for(std::string::const_iterator i= str.begin();i!=str.end();i++)
      {
        const unsigned char in= *i;
        if(in<128)
          retval.push_back(in);
        else
          {
            retval.push_back(0xc2+(in>0xbf));
            retval.push_back((in&0x3f)+0x80);
          }
      }
    return retval;
  }
