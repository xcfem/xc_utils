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
//solver.cc

#include "solver.h"

void Solver::inic_p(void)
  { 
    PP= m_sizet(n,1);
    for(register size_t i= 1;i<= n;i++) P(i)= i;
  }
int Solver::check_pp(const size_t n_rows) const
  {
    if(PP.getNumberOfRows()!= n_rows || PP.getNumberOfColumns()!=1)
      {
        if(verbosity) std::cerr << "Matrix " << PP
				<< "has invalid dimensions."
			        << std::endl;
        return 0;
      }
    return 1;
  }
