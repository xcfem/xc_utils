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
//MapValores.cc

#include "MapValores.h"
#include "xc_utils/src/utils/text/text_string.h"

//! @brief Constructor.
MapValores::MapValores(void)
  :map_valores() {}

//! @brief Constructor (recibe una cadena de la forma 'x=4.2,y=x+z,...'.
MapValores::MapValores(const std::string &str)
  :map_valores()
  {
    std::deque<std::string> valores= separa_csv(str);
    std::deque<std::string> par;
    for(std::deque<std::string>::iterator i= valores.begin();i!=valores.end();i++)
      {
        par= split_at_first(*i,'=');
        if(par.size()>1)
          (*this)[par[0]]= ExprAlgebra(par[1]);
        else
	  std::cerr << "MapValores::MapValores("
                    << str << "); se esperaba una expresión de asignación, se obtuvo: '"
                    << *i << "'\n";
      }
  }
