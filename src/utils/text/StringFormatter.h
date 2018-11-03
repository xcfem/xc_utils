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
//StringFormatter.h

#ifndef STRINGFORMATTER_H
#define STRINGFORMATTER_H

#include <string>

//! @brief Formatea cadenas de caracteres.
class StringFormatter
  {
    static const size_t sz= 1024;
    static char buf[sz];
    std::string fmt;
    size_t num_format_strings(void) const;
    char char_espec_format_string(void) const;
    bool check_format_string(const std::string &,const std::string &) const;
  public:
    StringFormatter(const std::string &format);
    const std::string &format_string(void) const
      { return fmt; }
    std::string &format_string(void)
      { return fmt; }
    std::string format(const std::string &str);
    std::string format(const bool &i);
    std::string format(const int &i);
    std::string format(const long int &i);
    std::string format(const size_t &i);
    std::string format(const double &d);
    std::string format(const float &f);
  };

std::string format(const std::string &format,const std::string &str);
std::string format(const std::string &format,const bool &i);
std::string format(const std::string &format,const int &i);
std::string format(const std::string &format,const long int &i);
std::string format(const std::string &format,const size_t &i);
std::string format(const std::string &format,const double &d);
std::string format(const std::string &format,const float &f);

#endif
