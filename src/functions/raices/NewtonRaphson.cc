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
//NewtonRaphson.cc

#include "NewtonRaphson.h"

bool norma_inf_nula(const m_double &x,const double &tolerance)
  {
    size_t sz= x.getNumberOfRows();
    for(register size_t i= 1;i<= sz;i++)
      if(fabs(x(i)) > tolerance) return false;
    return true;
  }

double dot_trn(const m_double &v1,const m_double &v2)
    //Producto escalar de dos vectores COLUMNA
     //Sirve para evitar calcular la traspuesta de v1.
      {
        const size_t n_rows= v1.getNumberOfRows();
        register double retval(v1(1,1)*v2(1,1));
        for(register m_double::size_type i=2;i<=n_rows;i++)
          { retval+= v1(i,1) * v2(i,1); }
        return retval;
      }
