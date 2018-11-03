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
//latex.cc

#include "latex.h"
#include <boost/algorithm/string.hpp>

//! @brief Devuelve el código equivalente el LaTeX
//! para los caracteres con significado especial
std::string ascii2latex(const std::string &s)
  {
    std::string tmp(s);
    if(tmp.find('\\')) //Tiene escape.
      boost::replace_all(tmp,"\\(","(");
    if(tmp.find('\\'))
      boost::replace_all(tmp,"\\)",")");
    if(tmp.find('\\'))
      boost::replace_all(tmp,"\\[","[");
    if(tmp.find('\\'))
      boost::replace_all(tmp,"\\]","]");
    std::string retval;
    for(size_t i=0;i<tmp.length();i++)
      {
        if(tmp[i]=='_') retval+= "\\";
        if(tmp[i]=='%') retval+= "\\";
        if(tmp[i]=='$') retval+= "\\";
        if(tmp[i]=='&') retval+= "\\";
        if(tmp[i]=='>')
	  {
            retval+= "$>$";
            continue;
          }
        retval+= tmp[i];
      }
    return retval;
  }
