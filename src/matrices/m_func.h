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
//m_func.h
//Matrices of real functions of n variables, that is a function
//from Rn to Rn.

#ifndef M_FUNC_H
#define M_FUNC_H

#include "ZMatrix.h"
#include "m_double.h"

template<class F>
//! @brief Matrix of objects that have a () operator (::operator())
//! that receives a double matrix and return a double.
class FMatrix: public ZMatrix<F>
  {
  public:
    typedef ZMatrix<F> f_matrix;
    typedef typename f_matrix::size_type size_type;

    FMatrix(void) : f_matrix(1,1) {}
    FMatrix(size_type n_rows,size_type cols) : f_matrix(n_rows,cols) {}
    FMatrix(const FMatrix<F> &otra) : f_matrix(otra) {}
    m_double Eval(const m_double &d) const;
  };

template <class F>
m_double FMatrix<F>::Eval(const m_double &d) const
  {
    size_t sz= this->size();
    m_double retval(sz,1);
    for(size_t i= 1; i<=sz; i++)
      retval(i)= ((*this)(i))(d);
    return retval;
  }

typedef double (*tipo_m_func)(const m_double &);
typedef FMatrix<tipo_m_func> m_func;

#endif
