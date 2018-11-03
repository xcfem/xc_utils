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
//StrTok.cc

#include "StrTok.h"
#include <cstdlib>

std::string StrTok::get_token(char c)
  //Si no encuentra el caracter c devuelve la cadena
  //desde pos hasta el final.
  {
    std::string retval("");
    if(empty()) return retval;
    if(final()) return retval;
    size_t nueva_pos= find(c,pos);
    if(nueva_pos<length()) //Encontró c.
      retval= substr(pos,nueva_pos-pos);
    else //Devuelve hasta el final
      {
        retval= substr(pos,length());
        nueva_pos= length();
      }
    pos= std::min(nueva_pos+1,length());
    return retval;
  }
std::string StrTok::resto(void)
  {
    std::string retval("");
    if(final())
      return retval;
    else
      return substr(pos,length()-pos);
  }
StrTok::dq_campos StrTok::campos(char sep)
  {
    dq_campos retval;
    std::string campo;
    do
      {
        campo= get_token(sep);
        retval.push_back(campo);
      }
    while(pos<size());
    return retval;
  }

double StrTok::get_float(char c)
  { return atof(get_token(c).c_str()); }
long int StrTok::get_int(char c)
  { return atol(get_token(c).c_str()); }
