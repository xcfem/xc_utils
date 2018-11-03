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
//vcolM.cc

#include "vcolM.h"

//! @brief Constructor.
//!
//! @param dim: Dimensiones de rows and columns (square matrix).
vcolM::vcolM(const std::vector<size_t> &dim)
  : MMatrix(dim.size(),1)
  {
    const size_t num_gdl= dim.size();
    vcolM retval(num_gdl,m_double(1,1,0.0));
    for(size_t i=0;i<num_gdl;i++) //Iteramos sobre los grados de libertad.
      (*this)(i+1)= m_double(dim[i],1,0.0); //Inicializamos el vector.
  }
//! @brief Constructor.
vcolM::vcolM(const MMatrix &m,const size_type &c)
  : MMatrix(m.getNumberOfRows(),1)
  {
    const size_type nf= m.getNumberOfRows();
    for(register size_type i=1;i<=nf;i++)
      (*this)(i)= m(i,1);
  }
vcolM &vcolM::operator*=(const m_double &m)
  {
    Prod(m);
    return *this;
  }
vcolM &vcolM::operator*=(const double &d)
  {
    MMatrix::operator*=(d);
    return *this;
  }
vcolM operator*(const MMatrix &a,const vcolM &b)
  {
    MMatrix tmp(a);
    tmp*=b;
    return vcolM(tmp,1);
  }

vcolM operator+(const vcolM &m1,const vcolM &m2)
  {
    vcolM retval(m1);
    retval+=m2;
    return retval;
  }

vcolM operator-(const vcolM &m1,const vcolM &m2)
  {
    vcolM retval(m1);
    retval-=m2;
    return retval;
  }

vcolM operator*(const vcolM &m,const double &d)
  {
    vcolM retval(m);
    retval*=d;
    return retval;
  }
vcolM operator*(const m_double &m,const vcolM &mM)
  {
    vcolM retval(mM); retval*=m;
    return retval;
  }
