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
//CacheExpresiones.h

#ifndef CACHEEXPRESIONES_H
#define CACHEEXPRESIONES_H

#include "ExprAlgebra.h"
#include <ext/hash_map>

struct eqstr
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) == 0;
  }
};

class CacheExpresiones
  {
  private:

    typedef __gnu_cxx::hash_map<const char *,ExprAlgebra,__gnu_cxx::hash<const char*>,eqstr> tabla_expresiones;
    typedef tabla_expresiones::iterator iterator;
    typedef tabla_expresiones::const_iterator const_iterator;
    typedef tabla_expresiones::value_type value_type;
    tabla_expresiones expresiones;
  public:
    CacheExpresiones(void)
      : expresiones() {}
    void Nueva(const std::string &,const ExprAlgebra &d);
    const ExprAlgebra *Busca(const std::string &) const;
    inline size_t size(void) const
      { return expresiones.size(); }
 };

#endif
