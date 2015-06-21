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
//BoostAnyStack.cc

#include "BoostAnyStack.h"
#include "boost/any.hpp"

boost::any BoostAnyStack::tmp;

//! @brief Devuelve una referencia al valor que está más alto en la pila.
boost::any BoostAnyStack::Pop(void)
  {
    tmp= top();
    pop();
    return tmp;
  }

//! @brief Devuelve n valores de la pila en orden inverso.
std::deque<boost::any> Reverse(BoostAnyStack &pila,const size_t &n)
  {
    const size_t sz= pila.size();
    std::deque<boost::any> retval(n);
    if((sz>=n) && (n>0))
      {
        std::deque<boost::any>::reverse_iterator i= retval.rbegin();
        size_t conta= 0;
        do
          {
            (*i)= pila.Pop();
            i++; conta++;
          }
        while(!pila.empty() && conta<n);
      }
    return retval;
  }
