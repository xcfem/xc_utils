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
//CacheExpresiones.cc

#include "CacheExpresiones.h"

void CacheExpresiones::Nueva(const std::string &str_expr,const ExprAlgebra &expr)
  {
    const ExprAlgebra *i= Busca(str_expr);
    if(!i)
      expresiones[str_expr.c_str()]= expr;
    if(expresiones.size()>50000)
      std::clog << "Tamaño del caché de expresiones muy grande:" << expresiones.size() << std::endl;
  }
const ExprAlgebra *CacheExpresiones::Busca(const std::string &str_expr) const
  {
    const_iterator i= expresiones.find(str_expr.c_str());
    if(i!=expresiones.end())
      return &((*i).second);
    else
      return NULL;
  }
