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
//StrTok.h

#ifndef STR_TOK_HXX
#define STR_TOK_HXX

#include <string>
#include <deque>

class StrTok: public std::string
  {
    size_t pos;
  public:

    typedef std::deque<std::string> dq_campos;

    StrTok(const std::string &str)
      : std::string(str), pos(0) {}
    inline bool final(void) const
      { return (pos>=length()); } 
    std::string get_token(char c);
      //Si no encuentra el caracter c devuelve la cadena
      //desde pos hasta el final.
    double get_float(char c);
    long int get_int(char c);
    std::string resto(void);
    dq_campos campos(char sep);
  };

#endif
