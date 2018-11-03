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
//op_tensor.cc

#include "op_tensor.h"

//Producto tensorial de dos tensores de primer orden.
m_double prod_tensor(const m_double &u,const m_double &v)
//u: row vector.
//v: column vector.
  {
    const size_t sz_u= u.size();
    const size_t sz_v= v.size();
    m_double retval(sz_u,sz_v);
    for(size_t i=1;i<=sz_u;i++)
      for(size_t j=1;j<=sz_v;j++)
        retval(i,j)= u[i-1]*v[j-1];
    return retval;
  }
